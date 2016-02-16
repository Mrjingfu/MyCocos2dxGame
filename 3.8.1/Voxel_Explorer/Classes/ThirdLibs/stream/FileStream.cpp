//
//  FileStream.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/5.
//
//

#include "FileStream.h"
#include "ccMacros.h"

FileStream::FileStream(const char* path, const char* mode)
{
    m_file = fopen(path, mode);
    CCASSERT(m_file!=NULL,"m_file is null");
}

FileStream::~FileStream()
{
    close();
}

size_t FileStream::read(void* buf, size_t count)
{
    size_t size = fread(buf, 1, count,	m_file);
    CCAssert( size == count, "invalid data!" );
    return size;
}

size_t FileStream::write(const void* buf, size_t count)
{
    size_t size = fwrite(buf, 1, count, m_file);
    CCAssert( size == count, "invalid data!" );
    return size;
}

void FileStream::skip(size_t count)
{
    fseek(m_file, count, SEEK_CUR);
}

void FileStream::seek( size_t pos )
{
    fseek(m_file, static_cast<long>(pos), SEEK_SET);
}
void FileStream::seekEnd()
{
    fseek(m_file, static_cast<long>(0), SEEK_END);
}
size_t FileStream::tell(void)
{
    return ftell(m_file);
}

bool FileStream::eof(void) const
{
    return feof(m_file) != 0;
}

void FileStream::close(void)
{
    if(m_file){
        fclose(m_file);
        m_file = NULL;
    }
}

void FileStream::flush(void)
{
    fflush(m_file);
}
