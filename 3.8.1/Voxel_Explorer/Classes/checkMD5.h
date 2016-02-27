#ifndef __CHECK_MD5_H__
#define __CHECK_MD5_H__

// 这两个函数都是返回md5检查是否失败，而且算法也是完全一样的，之所以这样，是为了给黑客增加一点迷惑性 
bool getBooleanForKey();
bool getBooleanForKey(bool defaultValue);

#endif
