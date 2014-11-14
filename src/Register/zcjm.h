/**
 * 描	述：　加密类
 * 	1. 没有用到解密
 * 	2. 加密过程
 * 		2.1　根据mac和系统信息得到 机器码
 * 		2.2	根据机器码生成注册码
 *		2.3 	把注册码写入文件
 *	3. 判断是否加密
 *		3.1 动态生成注册码 
 * 		3.2 读取注册码
 * 		3.3 对比两个注册码，一致说明有加密
 * 时间作者：　created by yjt 2012-08-29
 */

#ifndef _ENCRYPT_RC4_
#define _ENCRYPT_RC4_

#include <string>
#include <sys/stat.h>
using namespace std;

#define BOX_LEN 256

/**
 * 描	述：	解密操作类
 * 	1. 移植window的解密代码
 * 时间作者： created by yjt 2012-08-29
 */
class zcjm {
private:
    zcjm();

public:
    /**
     * 描	述：	获取机器码
     * 		1. 获取MAC
     * 		2. 获取取系统信息
     * 		3. 两部分合成机器码
     * 返 回 值： 获取成功返回机器码，失败返回""
     * 时间作者： created by yjt 2012-08-29
     */
    static string GetMachineCode();
    
    /**
     * 描	述：	获取注册码
     * 参	数：	strMichineCode [IN]	--	机器码（GetMichineCode返回的)
     * 			strPass [IN]			--	加密码,如果为空用系统默认的加密码
     * 返 回 值：  返回注册码, 如果生成失败返回""
     * 时间作者： created by yjt 2012-08-29
     */
    static string GetRegisterCode(const string& strMichineCode, const string& strPass="");
    
    /**
     * 描	述：	注册
     * 		1. 把注册码写入文件
     * 		2. 把注册码与当前根据硬件信息生成的注册信息进行比较
     * 			2.1 把比较结果输出
     * 参	数：	strRegisterCode [IN]		--		注册码
     * 返 回 值：	注册成功返回true, 失败返回false
     * 时间作者： created by yjt 2012-08-29
     */
    static bool Register(const string& strRegisterCode);
    
    /**
     * 描	述：	返回是否已注册
     * 		1. 从文件中读取注册码
     * 		2. 把注册码与当前根据硬件信息生成的注册信息进行比较
     * 			2.1 把比较结果输出
     * 返 回 值：	已经注册返回true, 没有返回false
     * 时间作者： created by yjt 2012-08-29
     */
    static bool IsRegister();

protected:
    /**
     * 加密
     */
    static string jiami(const string& szSource, const string& szPassWord);    
    
     /**
     * 解密，返回解密结果
     */
    static string jiemi(const string& szSource, const string& szPassWord);

    /**
     * 解密 -- 针对硬件信息
     */
    static void decrypter(char *a);

    /**
     * 加密 -- 针对硬件信息
     */
    static void encrypter(char* a);
    
private:
    /**
     * 得到键值--生成随机器
     */
    static int GetKey(const unsigned char* pass, int pass_len, unsigned char* out);

    /**
     * 
     */
    static int RC4(const unsigned char* data, int data_len, const unsigned char* key, int key_len,
		   unsigned char* out, int& out_len);

    /**
     * 交换字节
     */
    static void swap_byte(unsigned char* a, unsigned char* b);

    /**
     * 把字节码pbBuffer转为十六进制字符串，方便传输
     */
    static string ByteToHex(unsigned char* vByte, int vLen);

    /**
     * 把十六进制字符串转为字节码pbBuffer，解码
     */
    static int HexToByte(const string& szHex, unsigned char** vByte);

    /**
     *	获取系统信息
     */
    static string GetSysInfo(void);
    
    /**
     *	攻取网卡MAC信息
     */
    static string GetMACInfo(void);

	static string GetCpuID(void);

	static CTime zcjm::String2Time(string&  strS);
};

#endif // #ifndef _ENCRYPT_RC4_
