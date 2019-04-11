---
title: cocos-creator Android obb
date: 2019-04-08 12:14:15
tags: Technology
---

obb文件作为apk的拓展文件，android下从apk读取资源的方式为从zip中读取。所以需要在读取路径时考虑读取obb中资源。

### 0x01 查看apk的包名和version
aapt dump badging xxx.apk
ep: package: name='org.cocos2d.helloworld' versionCode='1' versionName='6.0'
    
### 0x02 OBB文件命名规则
main.[versionCode].[packageName].obb
ep: main.1.org.cocos2d.helloworld.obb
    
### 0x03 OBB文件存储路径
/sdcard/Android/obb/packageName/
ep: sdcard/Android/obb/org.cocos2d.helloworld/
    
### 0x04 本地测试
    
将OBB文件放到下载目录
adb push main.1.org.cocos2d.helloworld.obb sdcard/Android/obb/org.cocos2d.helloworld/

sdcard/Android/obb/org.cocos2d.helloworld/ 如果这个目录不存在  
adb shell。 进入obb目录下，mkdir创建对应文件夹
    
### 0x05 Question

1. cocos creator 1.9.0版本，本身支持OBB文件的读取
2. OBB文件后，音效文件无法播放。  
    1. 全包正常播放
    2. 分包情况：只安装apk，不传obb文件。正常播放
    3. 分包情况：即使apk和obb文件中都有音乐文件，还是不播放
    
根据log查到读取音乐文件的地方。AudioEngine-inl.cpp文件中fdGetter方法，如果存在obb方法，则直接从obb中查找，而不会检查音乐文件是否读取成功。
解决方案：
   1. 不要将音乐文件放入OBB文件中。  
   2. 如果OBB中读取失败，则从apk中读取。

    ```
    if (cocos2d::FileUtilsAndroid::getObbFile() != nullptr)
    {
        fd = getObbAssetFileDescriptorJNI(url.c_str(), start, length);
    } 
    - else {
    + if (fd <= 0) {
        auto asset = AAssetManager_open(cocos2d::FileUtilsAndroid::getAssetManager(), url.c_str(), AASSET_MODE_UNKNOWN);
        // open asset as file descriptor
        fd = AAsset_openFileDescriptor(asset, start, length);
        AAsset_close(asset);
    }
    ```

    解决方案2：  
        为何从OBB读取音乐文件失败？

2. OBB文件后，进游戏有概率崩溃。
    ```
        #00 pc 0117c85c  /data/app/org.cocos2d.helloworld-GGEnXejYbqGdx_F0Z7jSGw==/lib/arm/libcocos2djs.so (inflate+847)
        #01 pc 01015b3c  /data/app/org.cocos2d.helloworld-GGEnXejYbqGdx_F0Z7jSGw==/lib/arm/libcocos2djs.so (cocos2d::unzReadCurrentFile(void*, void*, unsigned int)+720)
        #02 pc 00fe9aa8  /data/app/org.cocos2d.helloworld-GGEnXejYbqGdx_F0Z7jSGw==/lib/arm/libcocos2djs.so (cocos2d::ZipFile::getFileData(std::string const&, cocos2d::ResizableBuffer*)+280)
        #03 pc 003b7107  /data/app/org.cocos2d.helloworld-GGEnXejYbqGdx_F0Z7jSGw==/lib/arm/libcocos2djs.so (cocos2d::FileUtilsAndroid::getContents(std::string const&, cocos2d::ResizableBuffer*)+282)
        #04 pc 00f9f720  /data/app/org.cocos2d.helloworld-GGEnXejYbqGdx_F0Z7jSGw==/lib/arm/libcocos2djs.so (cocos2d::FileUtils::getDataFromFile(std::string const&)+92)
        #05 pc 00fab3a0  /data/app/org.cocos2d.helloworld-GGEnXejYbqGdx_F0Z7jSGw==/lib/arm/libcocos2djs.so (cocos2d::Image::initWithImageFile(std::string const&)+136)
        #06 pc 01007ad4  /data/app/org.cocos2d.helloworld-GGEnXejYbqGdx_F0Z7jSGw==/lib/arm/libcocos2djs.so (cocos2d::TextureCache::loadImage()+260)
        #07 pc 011b8f9f  /data/app/org.cocos2d.helloworld-GGEnXejYbqGdx_F0Z7jSGw==/lib/arm/libcocos2djs.so
        #08 pc 000485af  /system/lib/libc.so (__pthread_start(void*)+22)
        #09 pc 0001b0d1  /system/lib/libc.so (__start_thread+32)
    ```  
    从zip中读取文件的时候崩溃，因为读取为非线程安全的，需要增加线程锁。
    解决方案：
    ZipUtils.h
        30  + #include <mutex>
        293 + std::mutex _ReadMutex;
    ZipUtils.cpp: getFileData方法开始和结束分别添加：
        _ReadMutex.lock();
        _ReadMutex.unlock();


### 0x06 OBB文件下载失败的情况
1. 经测试，如果同一个文件在APK和OBB中都存在，则会使用OBB中的文件。
2. 如果OBB文件下载失败，则走通过热更新的方式，将没有的资源更新到本地。
3. 所以apk中保存一份只包含apk资源md5信息的project.mainfest。obb中保存一份完整资源的md5信息。

### 0x07 索引
1. https://7dot9.com/2017/10/12/google-play-obb-fundamental-pitfall/
2. https://juejin.im/post/5ae3431bf265da0b8d41aa75
3. https://www.jianshu.com/p/af3f8e8f2a96