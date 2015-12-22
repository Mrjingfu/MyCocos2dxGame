
#include "Stream.h"


#define MAX_STRING_LEN 2048

static char s_tempStringBuf[MAX_STRING_LEN];

Stream::Stream()
{
	
}

Stream::~Stream()
{
	
}

void Stream::swapEndian(void* pData, size_t size)
{
    unsigned char swapByte;
    for(unsigned int byteIndex = 0; byteIndex < size/2; byteIndex++)
    {
        swapByte = *(char *)((size_t)pData + byteIndex);
        *(unsigned char *)((size_t)pData + byteIndex) = *(unsigned char *)((size_t)pData + size - byteIndex - 1);
        *(unsigned char *)((size_t)pData + size - byteIndex - 1) = swapByte;
    }
}
//////////////////////////////////////////////////////////////////////////
// read
bool Stream::readBool()
{
    char c;
    read(&c, 1);
    return (c==1);
}
char Stream::read8()
{
    char c;
    read(&c, 1);
    return c;
}

std::string Stream::readString()
{
    int len = read32le();
    CCAssert( (len < MAX_STRING_LEN-1), "string too long");
    // 此处声明一个静态变量去替代以前的临时分配的动态内存 added by reedhong 2013.12.25
    read(s_tempStringBuf, len);
    s_tempStringBuf[len] = '\0';
    std::string sRet(s_tempStringBuf, len);
    return sRet;
}


short Stream::read16()
{
    short s;
    read(&s, 2);
    swapEndian(&s, 2);
    return s;
}

int Stream::read32()
{
    int i;
    read(&i, 4);
    swapEndian(&i, 4);
    return i;
}

int64 Stream::read64()
{
    int64 l;
    read(&l, sizeof(int64));
    swapEndian(&l, sizeof(int64));
    return l;
}

float Stream::readf()
{
    float f;
    read(&f, sizeof(float));
    return f;
}


short Stream::read16le()
{
    short s;
    read(&s, 2);
    return s;
}

int Stream::read32le()
{
    int i;
    read(&i, 4);
    return i;
}

int64 Stream::read64le()
{
    int64 l;
    read(&l, sizeof(int64));
    return l;
}

//////////////////////////////////////////////////////////////////////////
// write
void Stream::writeBool(bool b)
{
    if(b){
        write8(1);
    }else{
        write8(0);
    }
}
void Stream::write8(char c)
{
    write(&c, 1);
}

void Stream::writeString(const std::string& str)
{
    size_t len = str.size();
    write32le(len);
    write(str.c_str(), len);
}

void Stream::write16(short s)
{
    swapEndian(&s, 2);
    write(&s, 2);
}

void Stream::write32(int i)
{
    swapEndian(&i, 4);
    write(&i, 4);
}

void Stream::write64(int64 l)
{
    swapEndian(&l, sizeof(int64));
    write(&l, sizeof(int64));
}

void Stream::writef(float f)
{
    write(&f, sizeof(float));
}
void Stream::write16le(short s)
{
    write(&s, 2);
}

void Stream::write32le(int i)
{
    write(&i, 4);
}

void Stream::write64le(int64 l)
{
    write(&l, sizeof(int64));
}
