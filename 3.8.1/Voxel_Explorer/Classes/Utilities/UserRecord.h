//
//  UserRecord.h
//  Tone_Skipper
//
//  Created by 创李 on 15/10/5.
//
//

#ifndef __Tone_Skipper__UserRecord__
#define __Tone_Skipper__UserRecord__
#include "ChaosNumber.h"

#define MAX_RECORD_LEN (256*1024)
#define MD5_LEN 16
#define MAX_CHAOSE_NUM 8

class UserRecord:public cocos2d::Data
{
public:
    UserRecord();
    ~UserRecord();
    void load(int archiveCount);
    void save();
    void init();
    void release();
public:
    int  mArchiveCount;
    std::string mDeciveUid;
    CChaosNumber mChaosValues[MAX_CHAOSE_NUM];
    unsigned char mVesion;
    int mTotalGameTime;
private:
    char*		m_buf;
    unsigned char			m_md5[MD5_LEN];
};

#endif /* defined(__Tone_Skipper__UserRecord__) */
