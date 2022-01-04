#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@Description:       :
@Date     :2021/11/26 21:09:39
@Author      :xia
@version      :1.0
'''

class File:
    def __init__(self, name:str, owner="default", shift=0):
        self.name_ = name # file's name
        self.owner = owner # file's owner
        self.shift_ = shift  # to be used in ls format indent
    
    def __str__(self):
        pass
    
    def chown(self, newowner:str):
        """ update owner

        Args:
            newowner (str): newowner name
        """
        self.owner = newowner
        
    def ls(self, d):
        pass
        
class PlainFile(File):
    def __init__(self, name: str, owner="default"):
        """inint PlainFile

        Args:
            name (str): File's name
            owner (str, optional): File's owner. Defaults to "default".
        """
        File.__init__(self, name, owner,0)
        self.type_ = "PlainFile"    

        self.permission = 6 # execute: 1, write: 2, read: 4, exec and write: 3 ...
    
    def __str__(self):
        """implement PlainFile __str__, for stdout format
        """
        return "PlainFile(" + self.name_ + ")"
    
    def ls(self, d=False):
        """PlainFile: ls

        Args:
            d (bool, optional): d set true means ls -l implement Q5(h)
        """
        print (" "*self.shift_*3, end='')  # self.shift_ is used to indent
        if d == True:
            print(self.permission, self.owner, self.name_)
        else:
            print (self.name_)      

class Directory(File):
    def __init__(self, name, childlist, owner="default"):
        """inint Directory

        Args:
            name (str): File's name
            owner (str, optional): File's owner. Defaults to "default".
        """
        File.__init__(self, name, owner,0)
        self.type_ = "Directory"  # type, file or direction  
        self.permission = 6 # execute: 1, write: 2, read: 4, exec and write: 3 ...
        
        self.contents = []  # this directory contents
        for child in childlist:
            self.contents.append(child)
            
    def __str__(self):
        """implement Directory __str__, for stdout format
        """
        fmtstr = "Directory(" + self.name_ + ","
        fmtstr += "["
        for i in range(len(self.contents)):
            fmtstr += str(self.contents[i])
            if i != len(self.contents)-1:
                fmtstr += ","
        fmtstr += "])"
        return fmtstr 
    
    def ls(self, d=False):
        """Directory: ls

        Args:
            d (bool, optional): d set true means ls -l implement Q5(h)
        """
        
        print (" "*self.shift_*3, end='')  # self.shift_ is used to indent
        if d == True:
            print(self.permission, self.owner, self.name_)
        else:
            print (self.name_)
        for content in self.contents:
            content.shift_ =self.shift_+ 1
            content.ls(d)  # recurse
        
            
class FileSystem:
    def __init__(self,directory:Directory):
        """construction, with Directory class

        Args:
            directory (Directory)
        """
        self.curdir_= directory  # current work director
        self.shift_ = 0  # be used in ls format indent
        self.pathdir_ = [self.curdir_] # init its parentdir, used in command cd ..
        
        
    def pwd(self):
        """ current working directory. just print self.curdir_.name
        """
        return self.curdir_.name_
    
    def ls(self, d=False):
        """ls command, can be achieved by calling Directory::ls(). 

        Args:
            d (bool, optional): True means ls -l i.e. list detailly. Defaults to False.
        """
        self.curdir_.shift_ = 0  # set current directory indent = 0
        self.curdir_.ls(d)
        
    def cd(self, dirname):
        """cd enter a directory, not plainfile

        Args:
            dirname ([type]): directory's name
        """
        if dirname == "..":
            if len(self.pathdir_) > 0:
                self.curdir_ = self.pathdir_.pop()
            return
        for content in self.curdir_.contents:
            if (content.type_=="Directory" and content.name_ == dirname):
                self.pathdir_.append(self.curdir_)
                self.curdir_ = content
                
                return
        print ("The directory does not exist!")

    
    def create_file(self, newfilename, owner="default"):
        """create a plainfile within current work directory

        Args:
            newfilename ([type]): new file name
            owner (str, optional): file's owner. Defaults to "default".
        """
        self.curdir_.contents.append(PlainFile(newfilename, owner))
    
    def mkdir(self, newdirname, owner="default"):
        """create a directory within current work directory
        """
        self.curdir_.contents.append(Directory(newdirname, [], owner))
    
    def rm(self, rmname):
        """remove plainfile or empty directory within current work directory

        Args:
            rmname ([type]): the removed file's name
        """
        idx = 0
        for node in self.curdir_.contents:
            if (node.name_ == rmname and (node.type_ == "PlainFile" or len(node.contents)==0)):
                del self.curdir_.contents[idx]  # delete with index
                return
            if (node.name_ == rmname and node.type_ == "directory"):
                print ("Sorry, the directory is not empty")
                return
            idx += 1
        print ("The directory does not exist!")
    
    def find(self, name):
        """file a file by name within current work directory

        Args:
            name ([type]): finded file's name

        Returns:
            [type]: path of target file if success, or False if not find that file
        """
        if (self.curdir_.name_ == name):
            return self.curdir_.name_
        filepath = [self.curdir_.name_]
        retstr = ""
        if findfilebyname(self.curdir_, name, filepath):  # find file with filepath
            for i in range(len(filepath)-1):
                retstr += filepath[i]
                retstr += "/"
            retstr += filepath[len(filepath)-1]
            return retstr

        return "False"
        
    def chmod(self, newpermission):
        """update permission, where 1mean exec, 2mean write, 4mean read， i.e. r=4，w=2，x=1

        Args:
            newpermission ([type]): [description]
        """
        chmodimpl(self.curdir_, newpermission)
        
    def chown(self, newowner):
        """change all file owner of work directory

        Args:
            newowner ([type]): new owner's name
        """
        chownimpl(self.curdir_, newowner)
        
    def mv(self, src:str, dst:str):
        """move source path file to dst path file

        Args:
            src (str): source path
            dst (str): destination path
        """
        srcpathlst = src.split("/")
        dstpathlst = dst.split("/")
        srcnode,srcparnode = findfilebypath(self.curdir_, self.curdir_, srcpathlst, 0)
        dstnode,dstparnode =  findfilebypath(self.curdir_, self.curdir_,dstpathlst,0)
        if (srcnode == None or dstnode == None):
            print ("The File does not exist!")
            return
        srcparnode.contents.remove(srcnode)
        srcparnode.contents.remove(dstnode)
        srcparnode.append(dstnode)
        dstparnode.append(srcnode)
    
    
def findfilebyname(curfile, name, retpath):
    """implement of FileSystem's findfilebyname

    Args:
        curfile ([File]): current file when recurse
        name ([type]): target file name
        retpath ([type]): target file path

    Returns:
        [type]: True when success, False if failed
    """
    if (curfile.name_ == name): # find it
        return True
    if (curfile.type_ == "PlainFile"):
        return False

    for childnode in curfile.contents:
        retpath.append(childnode.name_)
        if findfilebyname(childnode, name, retpath) == True:
            return True
        retpath.pop()
    return False

def findfilebypath(curfile, parentfile, namelst,idx):
    """find file with its path

    Args:
        curfile ([type]): current file
        parentfile ([type]): parent file
        namelst ([type]): path name list
        idx ([type]): [description]
    """

    if (idx == len(namelst)-1 and curfile.name_ == namelst[idx]):  # find file
        return curfile, parentfile
    if (curfile.type_ == "PlainFile"):
        return None,None

    for childfile in curfile.contents:
        if (childfile.anme_ == namelst[idx]):
            return findfilebypath(childfile, curfile, namelst,idx+1)
    return None

def chownimpl(curfile, newowner):
    """implement of FileSystem's chown

    Args:
        curfile ([type: File]): current file
        newowner ([type]): new owner
    """
    curfile.chown(newowner)
    for childnode in curfile.contents:
        chownimpl(childnode, newowner)

def chmodimpl(curfile, newpermission):
    """implement of FileSystem's chomd

    Args:
        curfile ([type: File]): current file
        newowner ([type]): new owner
    """
    curfile.permission = newpermission
    for childnode in curfile.contents:
        chownimpl(childnode, newpermission)




#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Nov 15 13:46:38 2021

@author: pszit
"""


print("Testing question 1")

# question 1 should allow to create simple files and folders:
file = PlainFile("boot.exe")
folder = Directory("Downloads",[])
    
root = Directory("root",[PlainFile("boot.exe"),
               Directory("home",[
                   Directory("thor",
                      [PlainFile("hunde.jpg"),
                       PlainFile("quatsch.txt")]),
                   Directory("isaac",
                      [PlainFile("gatos.jpg")])])])
    
print("Testing question 2")

# question 2: implement the str

print(root)
"""
Directory(root,[PlainFile(boot.exe),Directory(home,[Directory(thor,[PlainFile(hunde.jpg),PlainFile(quatsch.txt)],Directory(isaac,[PlainFile(gatos.jpg)]]]
"""

print("Testing question 3")

# question 3: test chown()
file = PlainFile("boot.exe")
folder = Directory("Downloads",[])
print(f'file.owner: {file.owner}; folder: {folder.owner}')
file.chown("root")
folder.chown("isaac")
print(f'file.owner: {file.owner}; folder: {folder.owner}')


print("Testing question 4")

#question 4: ls() doesn't return anything but prints.
root.ls() 
"""
root
	boot.exe
	home
		thor
			hunde.jpg
			quatsch.txt
		isaac
			gatos.jpg
"""


# question 5: create FileSystem
print("Testing question 5a: basic filesystem and pwd")

fs = FileSystem(root)

# 5a:      
print(fs.pwd())

print("Testing question 5b: ls in working directory")

# 5b: 
fs.ls()

# 5c:
    
print("Testing question 5c: cd")

# if you try to move to a non existing directory or to a file, 
# the method should complain:
fs.cd("casa")
# But you can move to an existing directory in the working directory.
fs.cd("home")
# if we now do ls(), you should only see the content in home:
fs.ls()

# you can't go backwards yet...

print("Testing question 5d:  mkdir and create file")
fs = FileSystem(root) # re-initialise fs

fs.mkdir("test") # the owner of the directory should be 'default' as not indicated.  fs.mkdir("test","isaac") would set the owner to isaac
fs.cd("test")
fs.create_file("test.txt")
fs.ls()

print("Testing question 5e:  dot dot")

# to test this properly, let's create the entire file system using our previous functions!

root = Directory("root",[],owner="root")
fs = FileSystem(root)
fs.create_file("boot.exe")  # when creating a file we do not need to indicate owner, it will be the same as the working directory
fs.mkdir("home",owner="root")
fs.cd("home")
fs.mkdir("thor",owner="thor")
fs.mkdir("isaac",owner="isaac")
fs.cd("thor")
fs.create_file("hunde.jpg")
fs.create_file("quatsch.txt")
fs.cd("..")
fs.cd("isaac")
fs.create_file("gatos.jpg")
fs.cd("..")
fs.cd("..")
fs.ls()


print("Testing question 5f:  rm")

fs.rm("test") # shouldn't work!
fs.cd("test")
fs.rm("test.txt")
fs.cd("..")
fs.rm("test")
fs.ls()

print("Testing question 5e:  find")

print(fs.find("gatos.jpg"))
fs.cd("home")
print(fs.find("boot.exe")) # shouldn't find it!
