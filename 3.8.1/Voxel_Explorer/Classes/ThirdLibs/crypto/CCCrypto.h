
#ifndef __CC_EXTENSION_CCCRYPTO_H_
#define __CC_EXTENSION_CCCRYPTO_H_



#if CC_LUA_ENGINE_ENABLED > 0
#include "CCLuaEngine.h"
#endif



class CCCrypto
{
public:
    static const int MD5_BUFFER_LENGTH = 16;
    static const int SHA1_BUFFER_LENGTH = 20;
    

    
    /** @brief Encoding data with Base64 algorithm, return encoded string length */
    static int encodeBase64(const void* input, int inputLength,
                            char* output, int outputBufferLength);
    
    
    /** @brief Decoding Base64 string to data, return decoded data length */
    static int decodeBase64(const char* input,
                            void* output, int outputBufferLength);
    
    /** @brief Calculate MD5, get MD5 code (not string) */
    static void md5(void* input, int inputLength,
                    unsigned char* output);
    
    /** @brief Calculate SHA1 with a secret key. */
    static void sha1(unsigned char* input, int inputLength,
                     unsigned char* key, int keyLength,
                     unsigned char* buffer, int bufferLength);


	static void encryptXOR(char* memptr, int memlen);
	static void decryptXOR(char* memptr, int memlen);

    static void encryptXOR(char* memptr, int memlen,const char* deKey);
    static void decryptXOR(char* memptr, int memlen,const char* deKey);

    
#if CC_LUA_ENGINE_ENABLED > 0
    

    
    /** @brief Encoding data with Base64 algorithm, return encoded string */
    static cocos2d::LUA_STRING encodeBase64Lua(const char* input, int inputLength)
    {
        return encodingBase64Lua(false, input, inputLength);
    }
    
    /** @brief Decoding Base64 string to data, return decoded data length */
    static cocos2d::LUA_STRING decodeBase64Lua(const char* input)
    {
        return encodingBase64Lua(true, input, strlen(input));
    }
    
    /** @brief Calculate MD5, return MD5 string */
    static cocos2d::LUA_STRING MD5Lua(char* input, bool isRawOutput);
    
    /** @brief Calculate SHA1 with a secret key, return digest string */
    static cocos2d::LUA_STRING sha1Lua(char* input, char* key, bool isRawOutput);
    
#endif /* CC_LUA_ENGINE_ENABLED */
    
    
private:
    CCCrypto(void) {}
    
    static int cryptAES256(bool isDecrypt,
                           const void* input,
                           int inputLength,
                           void* output,
                           int outputBufferLength,
                           const void* key,
                           int keyLength);
    
#if CC_LUA_ENGINE_ENABLED > 0
    static cocos2d::LUA_STRING cryptAES256Lua(bool isDecrypt,
                                              const void* input,
                                              int inputLength,
                                              const void* key,
                                              int keyLength);
    
    static cocos2d::LUA_STRING encodingBase64Lua(bool isDecoding,
                                                 const char* input,
                                                 int inputLength);
    
    static char* bin2hex(unsigned char* bin, int binLength);
#endif /* CC_LUA_ENGINE_ENABLED */
    
};



#endif // __CC_EXTENSION_CCCRYPTO_H_
