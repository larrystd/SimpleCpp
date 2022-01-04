#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@Description:       :
@Date     :2021/11/26 21:09:39
@Author      :xia
@version      :1.0
'''
class PlainFile:
    def __init__(self, name: str, owner="default"):
        self.name_ = name
        self.type_ = "PlainFile"
        self.owner = owner
    
    def __str__(self):
        return "PlainFile(" + self.name_ + ")"
    
    def chown(self, newowner):
        self.owner = newowner
    def ls(self, d=False):
        if d == True:
            print(self.permission, self.owner, self.name_)
        print (self.name_)
        
        

class Directory:
    def __init__(self, name, childlist, owner="default"):
        self.name_ = name
        self.type_ = "Directory"
        self.owner = owner
        self.shift_ = 0

        self.contents = []
        for child in childlist:
            self.contents.append(child)
            
    def __str__(self):
        fmtstr = "Directory(" + self.name_ + ","
        fmtstr += "["
        for i in range(len(self.contents)):
            fmtstr += str(self.contents[i])
            if i != len(self.contents)-1:
                fmtstr += ","
        fmtstr += "])"
        return fmtstr 
    
    def chown(self, newowner):
        self.owner = newowner
    
    def ls(self, d=False):
        if d == True:
            print(self.permission, self.owner, self.name_)
        print (self.name_)

        print (" "*self.shift_*4, end='')
        for content in self.contents:
            print (" "*4, end='')
            if (content.type_ == "Directory"):
                content.shift_ += 1
            content.ls(d)
    
            
class FileSystem:
    def __init__(self,directory:Directory):
        self.curdir_= directory
        self.shift_ = 0
        self.parentdir_ = self.curdir_ # init
        
        
    def pwd(self):
        return self.curdir_.name_
    
    def ls(self, d=False):
        """
        print (self.name_)
        print (" "*self.shift_*4, end='')
        for content in self.contents:
            print (" "*4, end='')
            if (content.type == "Directory"):
                content.shift_ += 1
            content.ls()
        """
        self.curdir_.ls(d)
        
    def cd(self, dirname):
        if dirname == "..":
            self.curdir_ = self.parentdir_
            return
        for content in self.curdir_.contents:
            if (content.type_=="Directory" and content.name_ == dirname):
                self.curdir_ = content
                return
        print ("The directory does not exist!")

    
    def create_file(self, newfilename, owner="default"):
        self.curdir_.contents.append(PlainFile(newfilename, owner))
    
    def mkdir(self, newdirname, owner="default"):
        self.curdir_.contents.append(Directory(newdirname, [], owner))
    
    def rm(self, rmname):
        idx = 0
        for node in self.curdir_.contents:
            if (node.name_ == rmname and (node.type_ == "PlainFile" or len(node.contents)==0)):
                del self.curdir_.contents[idx]  # 删除list元素, 根据索引
                return
            if (node.name_ == rmname and node.type_ == "directory"):
                print ("Sorry, the directory is not empty")
                return
            idx += 1
        print ("The directory does not exist!")
    
    def find(self, name):
        if (self.curdir_.name_ == name):
            return self.curdir_.name_
        filepath = [self.curdir_.name_]
        retstr = ""
        if findfilebyname(self.curdir_, name, filepath):    # 根据名字寻找
            for i in range(len(filepath)-1):
                retstr += filepath[i]
                retstr += "/"
            retstr += filepath[len(filepath)-1]
            return retstr

        return "False"
    
    def chown(self, newowner):
        chownimpl(self.curdir_, newowner)
        
    def chmod(self, newpermission):
        chmodimpl(self.curdir_, newpermission)
        
    def mv(self, src:str, dst:str):
        srcpathlst = src.split("/")
        dstpathlst = dst.split("/")
        srcnode,srcparnode = findfilebypath(self.curdir_, self.curdir_, srcpathlst, 0)
        dstnode,dstparnode =  findfilebypath(self.curdir_, self.curdir_,dstpathlst,0)
        if (srcnode == None or dstnode == None):
            print ("The directory does not exist!")
            return
        srcparnode.contents.remove(srcnode)
        srcparnode.contents.remove(dstnode)
        srcparnode.append(dstnode)
        dstparnode.append(srcnode)
    
    
def findfilebyname(curnode, name, retpath):

    if (curnode.name_ == name):
        return True
    if (curnode.type_ == "PlainFile"):
        return False

    for childnode in curnode.contents:
        retpath.append(childnode.name_)
        if findfilebyname(childnode, name, retpath) == True:
            return True
        retpath.pop()
    return False

def findfilebypath(curnode, parentnode, namelst,idx):

    if (idx == len(namelst)-1 and curnode.name_ == namelst[idx]):
        return curnode, parentnode
    if (curnode.type_ == "PlainFile"):
        return None

    for childnode in curnode.contents:
        if (childnode.anme_ == namelst[idx]):
            return findfilebypath(childnode, curnode, namelst,idx+1)
    return None
            
        

def chownimpl(curnode, newowner):
    curnode.owner = newowner
    for childnode in curnode.contents:
        chownimpl(childnode, newowner)

def chmodimpl(curnode, newpermission):
    curnode.permission = newpermission
    for childnode in curnode.contents:
        chownimpl(childnode, newpermission)

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