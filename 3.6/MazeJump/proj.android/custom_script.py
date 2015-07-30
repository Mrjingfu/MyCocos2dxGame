# -*- coding: utf-8 -*-
#http://www.cocos2d-x.org/wiki/Cocos2d-console
import os
def pre_build():
    print 'pre_build'
def post_build():
    print 'post_build'
def pre_ndk_build():
    print 'pre_ndk_build'
def post_ndk_build():
    print 'post_ndk_build'
def pre_copy_assets():
    print 'pre_copy_assets'
def post_copy_assets(project_path,platform_project_path):
    sourcePath = os.path.dirname(os.path.dirname(project_path))
    
    sqlAssetPath = os.path.join(sourcePath,'SQLCipher_android/assets')
    sqllibPath = os.path.join(sourcePath,'SQLCipher_android/libs/armeabi')
    
    projectAssetPath = os.path.join(platform_project_path,'assets')
    projectLibPath = os.path.join(platform_project_path,'libs/armeabi')
    
    copyDirFile(sqlAssetPath,projectAssetPath)
    copyDirFile(sqllibPath,projectLibPath)
    print 'post_copy_assets'
def pre_ant_build():
    print 'pre_ant_build'
def post_ant_build():
    print 'post_ant_build'
def copyDirFile(soruce,target):
    if (not os.path.isdir(soruce)) or (not os.path.exists(soruce)):
        return;
    if (not os.path.isdir(target)) or (not os.path.exists(target)):
        return;
    for fName in os.listdir(soruce):
        sourceFile = os.path.join(soruce,fName)
        targetFile = os.path.join(target,fName)
        if fName == ".DS_Store":
            continue
        if os.path.isfile(sourceFile):
            copyFile(sourceFile,targetFile)
def copyFile(sourceFile, targetFile):
    print 'sourceFile:'+sourceFile
    print 'targetFile:'+targetFile
    if not os.path.exists(sourceFile):
        return
    if not os.path.exists(targetFile) or os.path.exists(targetFile) and os.path.getsize(targetFile) != os.path.getsize(sourceFile):
        targetDir = os.path.dirname(targetFile)
        if not os.path.exists(targetDir):
            os.makedirs(targetDir)
        targetFileHandle = open(targetFile, 'wb')
        sourceFileHandle = open(sourceFile, 'rb')
        targetFileHandle.write(sourceFileHandle.read())
        targetFileHandle.close()
        sourceFileHandle.close()
def handle_event(event, target_platform, args):    
    project_path=args['project-path'] 
    platform_project_path=args['platform-project-path']
    build_mode=args['build-mode']
    output_dir=args['output-dir']
    ndk_build_mode=args['ndk-build-mode']
    #print 'event:'+event+ '\nproject_path:'+ project_path +'\nplatform_project_path:'+platform_project_path \
    #   +'\nbuild_mode:'+ build_mode+'\noutput_dir:'+ output_dir+'\nndk_build_mode:'+ndk_build_mode;

    if event == 'pre-build':
        pre_build()
    elif event == 'post-build':
        post_build()
    elif event == 'pre-ndk-build':
        pre_ndk_build()
    elif event == 'post-ndk-build':
        post_ndk_build()
    elif event == 'pre-copy-assets':
        pre_copy_assets()
    elif event == 'post-copy-assets':
        post_copy_assets(project_path,platform_project_path)
    elif event == 'pre-ant-build':
        pre_ant_build()
    elif event == 'post-ant-build':
        post_ant_build()