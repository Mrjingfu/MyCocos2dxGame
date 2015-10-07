//
//  FileStream.h
//  Tone_Skipper
//
//  Created by 创李 on 15/10/5.
//
//

#ifndef __Tone_Skipper__FileStream__
#define __Tone_Skipper__FileStream__

#include "Stream.h"
class FileStream:public Stream
{
    std::string fileName;
public:
    FileStream(const char* path,const char* mode);
    virtual ~FileStream();
    virtual size_t read(void* buf,size_t count);
    virtual size_t write(const void* buf,size_t const);
    virtual void skip(size_t count);
    virtual void seek(size_t pos);
    virtual size_t tell(void);
    virtual bool eof(void) const;
    virtual void close(void);
    void flush();
private:
    FILE* m_file;
};

#endif /* defined(__Tone_Skipper__FileStream__) */
