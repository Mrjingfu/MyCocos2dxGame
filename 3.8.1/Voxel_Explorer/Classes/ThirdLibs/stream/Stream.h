/********************************************************************
	
	purpose:	一般的读取和写入均为big endian，另外也提供little endian的接口，以 le结尾
					Big endian：将高序字节存储在起始地址
					Little endian：将低序字节存储在起始地址
					windows和linux的本地字节序均为 le， 网络字节序为be
					此处，我们默认本地字节序均为le，这样可以减少计算和分支判断
					默认的read/write 为be模式，因为读写网络的情况更多
*********************************************************************/

#ifndef __TinyFlare_Stream_h__
#define __TinyFlare_Stream_h__



typedef long long int64;


class Stream 
{
protected:
    /// Size of the data in the stream (may be 0 if size cannot be determined)
    size_t mSize;
public:
    Stream();
    virtual ~Stream();
    static void swapEndian(void* pData, size_t size);

    virtual size_t read(void* buf, size_t count) = 0;
    virtual size_t write(const void* buf, size_t count)=0;
    virtual void skip(size_t count) = 0;
    virtual void seek( size_t pos ) = 0;
    virtual size_t tell(void)  = 0;
    virtual bool eof(void) const = 0;
    virtual void close(void) = 0;

    size_t size(void) const { return mSize; }
    
    virtual bool readBool();
    virtual char read8();
    virtual std::string readString();

    // BE 网络字节序
    virtual short read16();
    virtual int read32();
    virtual int64 read64();
    virtual float readf();


    /* 以le字节序读入*/
    // win32/linux local
    virtual short read16le();
    virtual int read32le();
    virtual int64 read64le();


    virtual void writeBool(bool b);
    virtual void write8(char c);
    virtual void writeString(const std::string& str);
    
    virtual void write16(short s);
    virtual void write32(int i);
    virtual void write64(int64 l);
    virtual void writef(float f);
    
    /* 以le字节序写入，可以直接写入，无需转换*/
    // win32/linux local 
    virtual void write16le(short s);
    virtual void write32le(int i);
    virtual void write64le(int64 l);

protected:
};



#endif