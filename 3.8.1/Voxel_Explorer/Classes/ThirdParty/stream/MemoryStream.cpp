 /********************************************************************

	filename: 	MemroyStream.cpp
*********************************************************************/

#include "MemoryStream.h"

using namespace cocos2d;

MemoryStream::MemoryStream():m_buffer(0),m_bufferStart(0),m_bufferEnd(0),m_freeOnClose(false)
{

}

MemoryStream::MemoryStream(const char *buffer, size_t len, bool freeOnClose):m_freeOnClose(freeOnClose)
{
    m_buffer =  (char *)buffer;
    m_bufferStart = (char *)buffer;
    m_bufferEnd = (char *)buffer + len;
    mSize = len;
    m_length = len;
}

MemoryStream::~MemoryStream()
{
    m_buffer = m_bufferStart = m_bufferEnd  = 0;
    close();
}
	
size_t MemoryStream::read(void* buf, size_t count)
{
    CCAssert(count <= (size_t)(m_bufferEnd-m_buffer), "MemoryStream::read error");
    memcpy(buf, m_buffer, count);
    m_buffer += count;

    return count;
}

void MemoryStream::setSize(size_t size)
{
    CCAssert(m_length >= size, "MemoryStream::setSize error");
    mSize = size; 
    seek(0);
    m_bufferEnd = (char *)m_buffer + mSize;
}

size_t MemoryStream::write(const void* buf, size_t count)
{
    CCAssert(count <= (size_t)(m_bufferEnd-m_buffer), "MemoryStream::write error");
    memcpy(m_buffer, buf, count);
    m_buffer += count;

    return count;
}
void MemoryStream::skip(size_t count)
{
    CCAssert(count <= (size_t)(m_bufferEnd-m_buffer), "MemoryStream::skip error");
    m_buffer += count;
}
void MemoryStream::seek( size_t pos )
{
    CCAssert(pos <= (size_t)(m_bufferEnd-m_bufferStart), "MemoryStream::seek error");
    m_buffer = m_bufferStart+pos;
}
size_t MemoryStream::tell(void)
{
    return (m_buffer-m_bufferStart);
}
bool MemoryStream::eof(void) const 
{
    return (m_buffer == m_bufferEnd);
}

void MemoryStream::close(void)
{
    if(m_freeOnClose && m_bufferStart){
       CC_SAFE_DELETE_ARRAY(m_bufferStart);// free(m_bufferStart);
    }
}