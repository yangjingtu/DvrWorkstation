#ifndef _CHMZC_H_
#define _CHMZC_H_

#include <string>
using namespace std;

extern "C" {
    /**
     * 描	述：	获取机器码
     * 		1. 获取MAC
     * 		2. 获取取系统信息
     * 		3. 两部分合成机器码
     * 返 回 值： 获取成功返回机器码，失败返回""
     * 时间作者： created by yjt 2012-08-29
     */
    __declspec(dllexport) string GetMachineCode();
	__declspec(dllexport) int _GetMachineCode(char* mc);
    
    /**
     * 描	述：	获取注册码
     * 参	数：	strMichineCode [IN]	--	机器码（GetMichineCode返回的)
     * 			strPass [IN]			--	加密码,如果为空用系统默认的加密码
     * 返 回 值：  返回注册码, 如果生成失败返回""
     * 时间作者： created by yjt 2012-08-29
     */
	__declspec(dllexport) string GetRegisterCode(const string& strMichineCode);
	__declspec(dllexport) int _GetRegisterCode(const char* chMichineCode, char* rlt);
    
    /**
     * 描	述：	注册
     * 		1. 把注册码写入文件
     * 		2. 把注册码与当前根据硬件信息生成的注册信息进行比较
     * 			2.1 把比较结果输出
     * 参	数：	strRegisterCode [IN]		--		注册码
     * 返 回 值：	注册成功返回true, 失败返回false
     * 时间作者： created by yjt 2012-08-29
     */
	__declspec(dllexport) bool Register(const string& strRegisterCode);
	__declspec(dllexport) bool _Register(const char* chRegisterCode);
    
    /**
     * 描	述：	返回是否已注册
     * 		1. 从文件中读取注册码
     * 		2. 把注册码与当前根据硬件信息生成的注册信息进行比较
     * 			2.1 把比较结果输出
     * 返 回 值：	已经注册返回true, 没有返回false
     * 时间作者： created by yjt 2012-08-29
     */
    __declspec(dllexport) bool IsRegister();

	__declspec(dllexport) std::string ws2s(const std::wstring& ws);
	__declspec(dllexport) int _ws2s(const wchar_t* ws, char* _rlt);

	__declspec(dllexport) std::wstring s2ws(const std::string& s);
	__declspec(dllexport) int _s2ws(const char* s, wchar_t* _rlt);
}

/*
 * 调用--及测试示例
 *
#include <iostream>
int main()
{
    string strCode = GetMachineCode();
    cout << "MachineCode : " << strCode << endl;
    
    strCode = GetRegisterCode(strCode);
    cout << "register code: " << strCode << endl;
    
    if(Register(strCode))
	cout << "register successful" << endl;
    else
	cout << "register code is not invalide! " << endl;
    
    if(IsRegister())
	cout << "is has register" << endl;
    else
	cout << "no register " << endl;
   
    return 0;
}
*/

#endif