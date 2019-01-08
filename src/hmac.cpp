#include "hmac.h"  
#include <openssl/hmac.h>  
#include <string.h>  
/*#include <iostream>  */
using namespace std;  
extern "C"
{
    #include <lua.h>
    #include <lauxlib.h>
}
int HmacEncode(const char * algo,  
                const char * key, unsigned int key_length,  
                const char * input, unsigned int input_length,  
                unsigned char ** output, unsigned int* output_length) {  
        const EVP_MD * engine = NULL;  
        if(strcasecmp("sha512", algo) == 0) {  
                engine = EVP_sha512();  
        }  
        else if(strcasecmp("sha256", algo) == 0) {  
                engine = EVP_sha256();  
        }  
        else if(strcasecmp("sha1", algo) == 0) {  
                engine = EVP_sha1();  
        }  
        else if(strcasecmp("md5", algo) == 0) {  
                engine = EVP_md5();  
        }  
        else if(strcasecmp("sha224", algo) == 0) {  
                engine = EVP_sha224();  
        }  
        else if(strcasecmp("sha384", algo) == 0) {  
                engine = EVP_sha384();  
        }  
        else if(strcasecmp("sha", algo) == 0) {  
                engine = EVP_sha();  
        }  
        else if(strcasecmp("md2", algo) == 0) {  
                engine = EVP_md2();  
        }  
        else {  
                /*cout << "Algorithm " << algo << " is not supported by this program!" << endl;  */
                return -1;  
        }  
  
        *output = (unsigned char*)malloc(EVP_MAX_MD_SIZE);  
  
        HMAC_CTX ctx;  
        HMAC_CTX_init(&ctx);  
        HMAC_Init_ex(&ctx, key, strlen(key), engine, NULL);  
        HMAC_Update(&ctx, (unsigned char*)input, strlen(input));        // input is OK; &input is WRONG !!!  
  
        HMAC_Final(&ctx, *output, output_length);  
        HMAC_CTX_cleanup(&ctx);  
  
        return 0;  
}  

static int lSha256 (lua_State *L)
{
        size_t msgLen = 0;
        const char* msg = lua_tolstring(L, 1, &msgLen);
        size_t keyLen = 0;
        const char* key = lua_tolstring(L, 2, &keyLen);
        unsigned char* output = NULL;
        unsigned int outputLen = 0;
        int ret = HmacEncode("sha256", key, keyLen, msg, msgLen, &output, &outputLen);
        char* buf = (char*) malloc(outputLen * 2);
        char buf2[2] = {0};
        for(int i = 0; i < outputLen; i++) {
                sprintf(buf2, "%02x", output[i]);
                strncpy(buf + i*2, buf2, 2);
        }
/*  size_t purchaseLen = 0;
    const char *purchaseData = lua_tolstring (L, 1, &purchaseLen);
    size_t signatureLen = 0;
    const char *signatureData = lua_tolstring (L, 2, &signatureLen);
    size_t googlePubKeyLen = 0;
    const char *googlePubKeyData = lua_tolstring (L, 3, &googlePubKeyLen);

    string purchaseStr;
    purchaseStr.assign((char*)purchaseData, purchaseLen);
    string signatureStr;
    signatureStr.assign((char*)signatureData, signatureLen);
    string googlePubKeyStr;
    googlePubKeyStr.assign((char*)googlePubKeyData, googlePubKeyLen);

    EVP_PKEY* pubKey = GoogleVerify::getKeyByPKCS1(googlePubKeyStr, 0);
    int ret = GoogleVerify::verifySignWithRsa(purchaseStr, signatureStr, EVP_sha1(), pubKey);
*/
        lua_pushinteger(L, ret);
        lua_pushlstring(L, buf, outputLen * 2);
        return 1;
}


extern "C"
{
    int luaopen_hmac(lua_State *L) {
        luaL_checkversion(L);
        luaL_Reg l[] = {
            {"sha256", lSha256},
            {NULL,     NULL},
        };
        luaL_newlib(L, l);
    return 1;
    }
}
