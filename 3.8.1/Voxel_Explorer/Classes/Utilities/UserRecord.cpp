//
//  UserRecord.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/5.
//
//

#include "UserRecord.h"
#include "cocos2d.h"
#include "MemoryStream.h"
#include "CCCrypto.h"
#include "UtilityHelper.h"
#include "GameConfig.h"
#include "NativeBridge.h"
#include "FileStream.h"
UserRecord::UserRecord()
{
    init();
}
UserRecord::~UserRecord()
{
    delete [] m_buf;
    release();
    
}
void UserRecord::init()
{
    m_buf = new char[MAX_RECORD_LEN];
//    mDeciveUid = NativeBridge::getInstance()->generateUUID();
    mDeciveUid = "ssssss";
    mTotalGameTime = 0;
    mArchiveCount = 0;
    for (int i =0; i < MAX_CHAOSE_NUM; i++) {
        mChaosValues[i].SetLongValue(0);
    }
    release();
    
}
void UserRecord::release()
{
    
}
void UserRecord::load(int archiveCount)
{
    mArchiveCount = archiveCount ;
    std::string path = cocos2d::FileUtils::getInstance()->getWritablePath()+cocos2d::StringUtils::format("%s%d",sArchiveName,mArchiveCount);
    
    if (!cocos2d::FileUtils::getInstance()->isFileExist(path)) {
        init();
        save();
        return ;
    }
    
    //1.读取存档
    ssize_t size;
    const unsigned char* content = cocos2d::FileUtils::getInstance()->getFileData(path.c_str(), "rb", &size);
    //存档不存在,重置存档
    if (size <= 0 ) {
        CCLOG("init record, can't record file %s", path.c_str());
        CC_SAFE_DELETE_ARRAY(content);
        init();
        return ;
    }
    //2.获取存档内容到buf
    memcpy(m_buf, content, size);
    CC_SAFE_DELETE_ARRAY(content);
    //3.校验MD5
    CCCrypto::md5((void *)m_buf, size, m_md5);
    std::string hex;
    UtilityHelper::getHexDigest(m_md5, MD5_LEN, hex);
    
    std::string fileMD5 = cocos2d::UserDefault::getInstance()->getStringForKey(sRecordMD5);
    if (fileMD5.compare(hex)!=0) {
        CCLOG("init record,md5 error %s",path.c_str());
        init();
        return;
    }
    
    MemoryStream stream(m_buf, MAX_RECORD_LEN, false);
    
    mVesion = stream.read8();
    //此处应该做版本比较
    //Wait
    mDeciveUid = stream.readString();
    mTotalGameTime = stream.read32le();
    char buf[16];
    for (int i=0; i<MAX_CHAOSE_NUM; i++)
    {
        mChaosValues[i].SetLongValue(0);
        stream.read(buf,16);
        mChaosValues[i].PutValueToMatrix(buf);
    }
    
    stream.close();
    
    
}
void UserRecord::save()
{
    
    MemoryStream stream(m_buf, MAX_RECORD_LEN, false);
    
    //每次存储最新版本号
    stream.write8(eUserRecordVersionCount-1);
    stream.writeString(mDeciveUid);
    stream.write32le(mTotalGameTime);
    char buf[16];
    for (int i =0 ; i<MAX_CHAOSE_NUM; i++) {
        
        mChaosValues[i].GetValueFromMatric(buf);
        stream.write(buf, 16);
    }
    
    //每次写文件前,把整个文件的md5 存到userDefualt做校验
    size_t writeCount = stream.tell();
    stream.close();
    
    CCCrypto::md5((void*)m_buf, writeCount, m_md5);
    std::string hex;
    UtilityHelper::getHexDigest(m_md5, MD5_LEN, hex);
    CCLOG("save md5 to userdefault: md5=%s, begin", hex.c_str());
    cocos2d::UserDefault::getInstance()->setStringForKey(sRecordMD5, hex);
    cocos2d::UserDefault::getInstance()->flush();
    CCLOG("save md5 to userdefault: md5=%s, end", hex.c_str());
    //存文件
    std::string path = cocos2d::FileUtils::getInstance()->getWritablePath()+cocos2d::StringUtils::format("%s%d",sArchiveName,mArchiveCount);
    FileStream fs(path.c_str(),"wb");
    CCLOG("record save file begin");
     size_t iRet = fs.write(m_buf, writeCount);
    CCLOG("record save file end,writeCount=%d,iRet=%d",(int)writeCount,(int)iRet);
    fs.close();
}
