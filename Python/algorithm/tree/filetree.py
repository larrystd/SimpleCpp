#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@Description:       :
@Date     :2021/11/26 21:09:39
@Author      :xia
@version      :1.0
'''
class PlainFile:
    def __init__(self, name: str):
        self.name_ = name
        self.type_ = "PlainFile"
        self.owner = "default"
    
    def __str__(self):
        return "PlainFile(" + self.name_ + ")"
    
    def chown(self, newowner):
        self.owner = newowner
    def ls(self):
        print (self.name_)

class Directory:
    def __init__(self, name, childlist):
        self.name_ = name
        self.type_ = "Directory"
        self.owner = "default"
        self.shift = 0

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
    
    def ls(self):
        print (self.name_)

        print (" "*self.shift*4, end='')
        for content in self.contents:
            print (" "*4, end='')
            if (isinstance(content, Directory)):
                content.shift += 1
            content.ls()
            



        
print("Testing question 1")

# question 1 should allow to create simple files and folders:
#file = PlainFile("boot.exe")
#folder = Directory("Downloads",[])
    
root = Directory("root",[PlainFile("boot.exe"),
               Directory("home",[
                   Directory("thor",
                      [PlainFile("hunde.jpg"),
                       PlainFile("quatsch.txt")]),
                   Directory("isaac",
                      [PlainFile("gatos.jpg")])])])

print (root)   

file = PlainFile("boot.exe")
folder = Directory("Downloads",[])
print(f'file.owner: {file.owner}; folder: {folder.owner}')
file.chown("root")
folder.chown("isaac")
print(f'file.owner: {file.owner}; folder: {folder.owner}')

root.ls() 