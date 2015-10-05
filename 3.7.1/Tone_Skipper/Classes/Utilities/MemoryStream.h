/********************************************************************
	
	purpose:	内存Stream，读写均可
*********************************************************************/

#ifndef __Tone_Skipper_MemoryStream_h__
#define __Tone_Skipper_MemoryStream_h__

#include "Stream.h"

class MemoryStream: public Stream
{
public:
    MemoryStream();
    MemoryStream(const char *buffer, size_t len, bool freeOnClose=false);
    virtual ~MemoryStream();
public:
    virtual size_t read(void* buf, size_t count);
    virtual size_t write(const void* buf, size_t count);
    virtual void skip(size_t count);
    virtual void seek( size_t pos );
    virtual size_t tell(void);
    virtual bool eof(void) const ;
    virtual void close(void);
    void setFreeOnClose(bool b) { m_freeOnClose = b;}

    const char* getBuffer() { return m_buffer;}
    
    /*
     * 设置新的size，默认m_size = m_length
     */
    void setSize(size_t size);

protected:
    char*		m_buffer;
    char*		m_bufferStart;
    char*		m_bufferEnd;
    bool		m_freeOnClose;
    size_t		m_length;			// buffer的长度
};


#endif