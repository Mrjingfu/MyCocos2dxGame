# -*- coding: utf-8 -*-
import os,shutil
'''
Created on 2015年7月10日
@author: chuangli
'''
c3t ='c3t'
c3b = 'c3b'
pngT = 'texture'
def convC3b(path):
    for fName in os.listdir(path):
        fNPath = os.path.join(pwdPath,fName)
        if fName == ".DS_Store":
            continue        
        if os.path.isfile(fNPath):
            fming = os.path.splitext(fName)[1]
            if fming=='.fbx':
                syscomm = 'fbx-conv  -a %s' % (fNPath)
                ret = os.system(syscomm)
                ret >>= 8 
                if ret!=0:
                    print "system error"
                    continue 
                
def creatDir(path):
    if not os.path.exists(path):
        os.mkdir(path) 
    else:
        shutil.rmtree(path)
        os.mkdir(path)
def sortC3b(path):
    c3tPath = os.path.join(path,c3t);
    c3bPath = os.path.join(path,c3b);
    pntPath = os.path.join(path,pngT);
    creatDir(c3tPath)
    creatDir(c3bPath)
    creatDir(pntPath)    
                       
    for fName in os.listdir(path):
        fNPath = os.path.join(pwdPath,fName)
        if fName == ".DS_Store":
            continue 
        if os.path.isfile(fNPath):
            fming = os.path.splitext(fName)[1]
            if fming == '.c3b':
                shutil.copy(fNPath, c3bPath)
                os.remove(fNPath)
            elif fming == '.c3t':
                shutil.copy(fNPath, c3tPath)
                os.remove(fNPath)
        else:
            texvMing =os.path.splitext(fName)[0]
            texv = texvMing+'.fbm'
            if fName == texv:
                if os.path.exists(fNPath) and os.path.isdir(fNPath):
                    for pngName in os.listdir(fNPath):
                        pngNamePath = os.path.join(fNPath,pngName)
                    if os.path.isfile(pngNamePath):
                        shutil.copy(pngNamePath, pntPath)
                shutil.rmtree(fNPath)

if __name__ == '__main__':
    pwdPath = os.getcwd()
    convC3b(pwdPath)
    sortC3b(pwdPath)
    