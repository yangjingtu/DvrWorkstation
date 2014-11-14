#include "stdafx.h"
#include "zcjm.h"
#include "chmzc.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <windef.h>

#include <iostream>
#include <sstream>
using namespace std;

#include <winsock2.h>
#include <iphlpapi.h>

#pragma comment(lib,"Iphlpapi.lib")

string GetAppPath()
{
	CString path;   
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH),MAX_PATH);   
	int pos = path.ReverseFind('\\');
	path = path.Mid(0, pos);
	return ws2s(path.GetBuffer(0));
}

#pragma comment(lib, "netapi32.lib")

#define  ENCRYPTER_DECRYPTER_NUM  18

int getMAC(char * mac);

/**
* 描		述：	 加密，返回加密结果
* 参		数：	szSource [IN]	--	源
* 			szPassWord [IN]	--	密码
*
* 时间作者： 	created by yjt 2012-08-29
*/
string zcjm::jiami(const string& szSource, const string& szPassWord)
{
	if(szSource.empty() || szPassWord.empty())
		return NULL;

	unsigned char* ret = new unsigned char[szSource.length()];
	int ret_len = 0;
	if(RC4((const unsigned char*)szSource.c_str(), szSource.length(), (const unsigned char*)szPassWord.c_str(), 
		szPassWord.length(), ret, ret_len) == NULL)
		return NULL;
	string strRlt = ByteToHex(ret, ret_len);
	delete[] ret;
	return strRlt;
}


/**
* 描		述：	 解密，返回解密结果
* 参		数：	szSource [IN]	--	源
* 			szPassWord [IN]	--	密码
*
* 时间作者： 	created by yjt 2012-08-29
*/
string zcjm::jiemi(const string& szSource, const string& szPassWord)
{
	if(szSource.empty() || (szSource.size()%2 != 0) || szPassWord.empty())
		return NULL;

	unsigned char* pSrc = new unsigned char[szSource.length()];
	int len = HexToByte(szSource, &pSrc);

	int ret_len = 0;
	unsigned char* ret = new unsigned char[szSource.length() /2 + 1];
	if(RC4((const unsigned char*)pSrc, len / 2,  (const unsigned char*)szPassWord.c_str(), szPassWord.length(), ret, ret_len) == NULL)
		return NULL;
	ret[ret_len] = '\0';
	string strRlt((const char*)ret);
	delete[] ret;
	delete[] pSrc;
	return strRlt;
}

int zcjm::RC4(const unsigned char* data, int data_len, const unsigned char* key,
	int key_len,unsigned char* out, int& out_len)
{
	if (data == NULL || key == NULL || out == NULL)
		return NULL;

	unsigned char* mBox = new unsigned char[BOX_LEN];

	if(GetKey(key, key_len, mBox) == NULL)
		return NULL;

	int i=0;
	int x=0;
	int y=0;

	for(int k = 0; k < data_len; ++k)
	{
		x = (x + 1) % BOX_LEN;
		y = (mBox[x] + y) % BOX_LEN;
		swap_byte((unsigned char*)&mBox[x], (unsigned char*)&mBox[y]);
		out[k] = data[k] ^ mBox[(mBox[x] + mBox[y]) % BOX_LEN];
	}
	out_len = data_len;
	delete[] mBox;
	return -1;
}


int zcjm::GetKey(const unsigned char* pass, int pass_len, unsigned char* out)
{
	if(pass == NULL || out == NULL)
		return NULL;

	int i;
	for(i = 0; i < BOX_LEN; i++)
		out[i] = i;

	int j = 0;
	for(i = 0; i < BOX_LEN; i++)
	{
		j = (pass[i % pass_len] + out[i] + j) % BOX_LEN;
		swap_byte(&out[i], &out[j]);
	}
	return -1;
}

/**
* 描述： 交换字节
*/
void zcjm::swap_byte(unsigned char* a, unsigned char* b)
{
	unsigned char swapByte;
	swapByte = *a;
	*a = *b;
	*b = swapByte;
}

/**
* 描	述：	把字节码转为十六进制码，一个字节两个十六进制，内部为字符串分配空间
* 参	数:	vByte [IN]	--	要转换的字节序列
* 返回值：	16进制序列串
* 时间作者： created by yjt 2012-08-28
*/
string zcjm::ByteToHex(unsigned char* vByte, int vLen)
{
	if(vByte == NULL)
		return NULL;

	char* tmp = new char[vLen * 2 + 1];
	string strRlt;
	int tmp2;
	for (int i = 0; i < vLen; ++i)
	{
		tmp2 = (int)(vByte[i])/16;
		tmp[i*2] = (char)(tmp2+((tmp2>9)?'A'-10:'0'));
		tmp2 = (int)(vByte[i])%16;
		tmp[i*2 + 1] = (char)(tmp2+((tmp2>9)?'A'-10:'0'));
	}
	tmp[vLen*2] = '\0';
	strRlt = tmp;
	delete[] tmp;
	return strRlt;
}

/**
* 描	述：	把十六进制字符串，转为字节码，每两个十六进制字符作为一个字节
* 		1. 取两位16进制数
* 		2. 合成字节
* 参	数：	szHex [IN]		--	16进制串
* 返回值：字节串 
* 时间作者：	created by yjt 2012-08-29
*/
int zcjm::HexToByte(const string& szHex, unsigned char** vByte)
//string zcjm::HexToByte(const string& szHex)
{
	if(szHex.empty())
		return NULL;

	int iLen = szHex.size();
	if ( iLen <= 0 || 0 !=  iLen % 2 )
		return NULL;

	unsigned char* pbBuf = *vByte;
//	unsigned char* pbBuf = new unsigned char[iLen/2];
	int tmp1, tmp2;
	for (int i=0; i<iLen/2; i++)
	{
		tmp1 = (int)szHex[i*2] - (((int)szHex[i*2]>='A')?'A'-10:'0');

		if(tmp1 >= 16)
			return NULL;

		tmp2 = (int)szHex[i*2+1] - (((int)szHex[i*2+1]>='A')?'A'-10:'0');

		if(tmp2 >= 16)
			return NULL;

//		pbBuf[i] = (tmp1*16+tmp2);
// 	}
// 	string strRlt((const char*)pbBuf);
// 	delete[] pbBuf;
// 	return strRlt;

		*(pbBuf + i) = (tmp1*16 + tmp2);
	}

	return iLen;
}

string zcjm::GetCpuID()
{
	BYTE szSystemInfo[256]; // 在程序执行完毕后，此处存储取得的系统特征码
	UINT uSystemInfoLen = 0;

	// CPU ID
	BOOL bException = FALSE;
	BYTE szCpu[16]  = { 0 };
	UINT uCpuID     = 0U; 

	try
	{
		_asm 
		{
			mov eax, 0
			cpuid
			mov dword ptr szCpu[0], ebx
			mov dword ptr szCpu[4], edx
			mov dword ptr szCpu[8], ecx
			mov eax, 1
			cpuid
			mov uCpuID, edx
		}
	}
	catch(...)
	{
		bException = TRUE;
	}

	if( !bException )
	{
		CopyMemory( szSystemInfo + uSystemInfoLen, &uCpuID, sizeof( UINT ) );
		uSystemInfoLen += sizeof( UINT );
		uCpuID = strlen( ( char* )szCpu );
		CopyMemory( szSystemInfo + uSystemInfoLen, szCpu, uCpuID );
		uSystemInfoLen += uCpuID;

	}

	return (char*)szSystemInfo;
}

/**
* 描	述：	获取网卡信息
*/
string zcjm::GetMACInfo(void)
{
#if _LINUX
	//获取网卡16进制形式的MAC编号
	unsigned char macaddr[6];
	int i;
	int sock;
	struct sockaddr_in sin;
	struct ifreq ifr[16];			//最大网卡数量
	struct ifconf ifc;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
		return ""; 	//printf("get the socket file descriptor faild!\n");


	ifc.ifc_len = sizeof(ifr);
	ifc.ifc_buf = (caddr_t)ifr;
	if(!ioctl(sock, SIOCGIFCONF, (char*)&ifc) == -1)
	{
		cout << "get network card interface info is failed!" << endl;
		return "";
	}
	//得到接口数量
	int intrface = ifc.ifc_len / sizeof(struct ifreq);
	int retn = 0;
	//循环获取设备的IP或MAC
	while(intrface-- > 0)
	{
		//设备名称
		//	cout << "network card name:" << ifr[intrface].ifr_name << endl;

		//判断网卡类型
		if(!(ioctl(sock, SIOCGIFFLAGS, (char*)&ifr[intrface])))
		{
			if(ifr[intrface].ifr_flags & IFF_PROMISC)
			{
				puts("the interface is PROMISC");
				retn ++;
			}
		}
		else
		{
			char str[256];
			sprintf(str, "cpm: ioctl device %s", ifr[intrface].ifr_name);
			perror(str);
		}
		/*	
		//判断网卡状态
		if(ifr[intrface].ifr_flags & IFF_UP)
		puts("the interface is UP");
		else
		puts("the interface status is DOWN");

		//获取当前网卡的IP地址
		if(!(ioctl(sock, SIOCGIFADDR, (char*)&ifr[intrface])))
		{
		puts("IP address is:");
		puts(inet_ntoa(((struct sockaddr_in*)(&ifr[intrface].ifr_addr))->sin_addr));
		puts("");
		}
		else
		{
		char str[256];
		sprintf(str, "cpm: ioctl device %s", ifr[intrface].ifr_name);
		puts(str);
		}
		*/	
		if((ioctl(sock, SIOCGIFHWADDR, &ifr[intrface])) < 0)
		{
			cout << "get the network card addr faild!"<< endl;
			return "";
		}
		memcpy(macaddr, ifr[intrface].ifr_hwaddr.sa_data, 6);
		char macHex[15] = {0};
		sprintf(macHex, "%.2x%.2x%.2x%.2x%.2x%.2x", macaddr[0], macaddr[1],
			macaddr[2],macaddr[3],macaddr[4],macaddr[5]);
		close(sock);
		return macHex;
	}
#else

	char chMac[64] = {0};
	//PIP_ADAPTER_INFO结构体指针存储本机网卡信息
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
	//得到结构体大小,用于GetAdaptersInfo参数
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);
	//调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量;其中stSize参数既是一个输入量也是一个输出量
	int nRel = GetAdaptersInfo(pIpAdapterInfo,&stSize);
	//记录网卡数量
	int netCardNum = 0;
	//记录每张网卡上的IP地址数量
	int IPnumPerNetCard = 0;
	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		//如果函数返回的是ERROR_BUFFER_OVERFLOW
		//则说明GetAdaptersInfo参数传递的内存空间不够,同时其传出stSize,表示需要的空间大小
		//这也是说明为什么stSize既是一个输入量也是一个输出量
		//释放原来的内存空间
		delete pIpAdapterInfo;
		//重新申请内存空间用来存储所有网卡信息
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		//再次调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量
		nRel=GetAdaptersInfo(pIpAdapterInfo,&stSize);    
	}
	if (ERROR_SUCCESS == nRel)
	{
		//输出网卡信息
		//可能有多网卡,因此通过循环去判断
		while (pIpAdapterInfo)
		{
// 			cout<<"网卡数量："<<++netCardNum<<endl;
// 			cout<<"网卡名称："<<pIpAdapterInfo->AdapterName<<endl;
// 			cout<<"网卡描述："<<pIpAdapterInfo->Description<<endl;
// 			switch(pIpAdapterInfo->Type)
// 			{
// 			case MIB_IF_TYPE_OTHER:
// 				cout<<"网卡类型："<<"OTHER"<<endl;
// 				break;
// 			case MIB_IF_TYPE_ETHERNET:
// 				cout<<"网卡类型："<<"ETHERNET"<<endl;
// 				break;
// 			case MIB_IF_TYPE_TOKENRING:
// 				cout<<"网卡类型："<<"TOKENRING"<<endl;
// 				break;
// 			case MIB_IF_TYPE_FDDI:
// 				cout<<"网卡类型："<<"FDDI"<<endl;
// 				break;
// 			case MIB_IF_TYPE_PPP:
// 				printf("PP\n");
// 				cout<<"网卡类型："<<"PPP"<<endl;
// 				break;
// 			case MIB_IF_TYPE_LOOPBACK:
// 				cout<<"网卡类型："<<"LOOPBACK"<<endl;
// 				break;
// 			case MIB_IF_TYPE_SLIP:
// 				cout<<"网卡类型："<<"SLIP"<<endl;
// 				break;
// 			default:
// 
// 				break;
// 			}
// 			cout<<"网卡MAC地址：";
			for (DWORD i = 0; i < pIpAdapterInfo->AddressLength; i++)
			{
				sprintf(chMac + i * 2, "%02X", pIpAdapterInfo->Address[i]);
			
// 				if (i < pIpAdapterInfo->AddressLength-1)
// 				{
// 					printf("%02X-", pIpAdapterInfo->Address[i]);
// 				}
// 				else
// 				{
// 					printf("%02X\n", pIpAdapterInfo->Address[i]);
// 				}
// 				cout<<"网卡IP地址如下："<<endl;
// 				//可能网卡有多IP,因此通过循环去判断
// 				IP_ADDR_STRING *pIpAddrString =&(pIpAdapterInfo->IpAddressList);
// 				do 
// 				{
// 					cout<<"该网卡上的IP数量："<<++IPnumPerNetCard<<endl;
// 					cout<<"IP 地址："<<pIpAddrString->IpAddress.String<<endl;
// 					cout<<"子网地址："<<pIpAddrString->IpMask.String<<endl;
// 					cout<<"网关地址："<<pIpAdapterInfo->GatewayList.IpAddress.String<<endl;
// 					pIpAddrString=pIpAddrString->Next;
// 				} while (pIpAddrString);
// 				pIpAdapterInfo = pIpAdapterInfo->Next;
// 				cout<<"--------------------------------------------------------------------"<<endl;
			}

			break;
		}

	}
	//释放内存空间
	if (pIpAdapterInfo)
	{
		delete pIpAdapterInfo;
	}

	return chMac;
#endif
}

/**
* 描	述：	获取系统信息
* 	linux的系统名称 + linux的硬件信息 + linux发布信息 + 加上网卡MAC信息
* 	  linux                   x86_64              2.6.40.4-5.fc15.x86_64
*/
string zcjm::GetSysInfo(void)
{
#if _LINUX
	struct utsname un;
	if(uname(&un)!=0)
		return NULL;

	string strRlt;
	strRlt += un.sysname;
	strRlt += un.machine;
	strRlt += un.release;
	strRlt += GetMACInfo();
	return strRlt;
#endif
	SYSTEM_INFO sInfo;
	GetSystemInfo(&sInfo);

	ostringstream os;
	os << sInfo.dwActiveProcessorMask;
	os << sInfo.dwAllocationGranularity;
	os << sInfo.dwNumberOfProcessors;
	os << sInfo.dwOemId;
	os << sInfo.dwProcessorType;
	os << sInfo.dwNumberOfProcessors;
	os << GetMACInfo();
	return os.str();
}

/**
* 描	述:	解密
*/
void zcjm::decrypter(char *a)
{
	int i;
	int len = strlen(a);
	for (i=0; i<len-1; i=i+2)
	{
		char c;
		c = a[i];
		a[i] = a[i+1];
		a[i+1] = c;
	}
	for (i = 0; a[i]; i++)
	{
		if(a[i]>='0' && a[i]<='9')
		{
			a[i]+=ENCRYPTER_DECRYPTER_NUM;
		}
		else if(a[i]>='B' && a[i]<='K')
		{
			a[i]-=ENCRYPTER_DECRYPTER_NUM;
		}
	}
}

void zcjm::encrypter(char* a)
{
	int i;
	for( i = 0; a[i]; ++i)
	{
		if(a[i] > '0' && a[i] <= '9')
			a[i] += ENCRYPTER_DECRYPTER_NUM;
		else if(a[i] >= 'B' && a[i] <= 'K')
			a[i] -= ENCRYPTER_DECRYPTER_NUM;
	}
	int len = strlen(a);
	for( i = 0; i < len -1; i=i+2){
		char c;
		c = a[i];
		a[i] = a[i+1];
		a[i+1] = c;
	}
}

/**
* 描	述：	获取机器码
* 		1. 获取MAC
* 		2. 获取取系统信息
* 		3. 两部分合成机器码
* 返 回 值： 获取成功返回机器码，失败返回""
* 时间作者： created by yjt 2012-08-29
*/
string zcjm::GetMachineCode()
{
	string strInfo = GetSysInfo();
	encrypter((char*)strInfo.c_str());
	return strInfo;
}

/**
* 描	述：	获取注册码
* 参	数：	strMichineCode [IN]	--	机器码（GetMichineCode返回的)
* 			strPass [IN]			--	加密码,如果为空用系统默认的加密码
* 返 回 值：  返回注册码, 如果生成失败返回""
* 时间作者： created by yjt 2012-08-29
*/
string zcjm::GetRegisterCode(const string& strMichineCode, const string& strPass)
{
	string pass("@abc231@");
	if(strPass != "" && !strPass.empty())
		pass = strPass;
	return jiami(strMichineCode, pass);
}

/**
* 描	述：	注册
* 		1. 把注册码写入文件
* 		2. 把注册码与当前根据硬件信息生成的注册信息进行比较
* 			2.1 把比较结果输出
* 参	数：	strRegisterCode [IN]		--		注册码
* 返 回 值：	注册成功返回true, 失败返回false
* 时间作者： created by yjt 2012-08-29
*/
//modified by yjt 2014-10-16 添加有效期
bool zcjm::Register(const string& strRegisterCode)
{
	//获取机器码
	string strCode = GetMachineCode();
	if(strCode == "" || strCode.empty())
		return false;
	//获取注册码
	strCode = GetRegisterCode(strCode);
	if(strRegisterCode.length() > strCode.length())
	{
		string strTmp = strRegisterCode.substr(0, strCode.length());
		if(strTmp != strCode)
			return false;
	}
	else if(strCode != strRegisterCode)
		return false;

	//写入配置文件
	string strAppPath;
	strAppPath = GetAppPath();
	//CDirHelper::GetAppPath(strAppPath);
	strAppPath += "/info.dll";

	//写入
	FILE *pFile = fopen(strAppPath.c_str(), "w+");
	if(pFile == NULL)
		return false;
	//写入注册码
	fwrite(strRegisterCode.c_str(), strRegisterCode.length(), 1, pFile);
	fclose(pFile);

	return true;
}

/**
* 描	述：	返回是否已注册成功--可能注册但码不对
* 		1. 从文件中读取注册码
* 		2. 把注册码与当前根据硬件信息生成的注册信息进行比较
* 			2.1 把比较结果输出
* 返 回 值：	已经注册返回true, 没有返回false
* 时间作者： created by yjt 2012-08-29
*/
bool zcjm::IsRegister()
{
	//读入配置文件
	string strAppPath;
	strAppPath = GetAppPath();
//	CDirHelper::GetAppPath(strAppPath);
	strAppPath += "/info.dll";

	//读
	FILE *pFile = fopen(strAppPath.c_str(), "r");
	if(pFile == NULL)
		return false;

	//获取文件的长度
	struct stat fs;
	stat(strAppPath.c_str(), &fs);
	int len = fs.st_size;
	if(len < 2)
		return false;

	//开始读取注册码
	char* pBuff = new char[len + 1];
	fread(pBuff, len, 1, pFile);
	pBuff[len] = '\0';
	fclose(pFile);

	string strCodeR= pBuff;
	delete[] pBuff;
	pBuff = NULL;

	//获取机器码
	string strCode = GetMachineCode();
	if(strCode == "" || strCode.empty())
		return false;
	//获取注册码
	strCode = GetRegisterCode(strCode);
	if(strCodeR.length() > strCode.length())
	{
		string strTmp = strCodeR.substr(0, strCode.length());
		if(strTmp != strCode)
			return false;

		//计算时间
		string pass("@abc231@");
		string strDt = jiemi(strCodeR, pass);
		string strS = strDt.substr(strDt.find('@') + 1, 8);
		string strE = strDt.substr(strDt.find('-') + 1, 8);
		CTime tm = CTime::GetCurrentTime();
		CTime tmS = String2Time(strS);
		CTime tmE = String2Time(strE);
		
		CTimeSpan tS = tm - tmS;
		CTimeSpan tE = tmE - tm;

		if(tS.GetDays() >= 0 && tE.GetDays() >= 0)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	else if(strCode != strCodeR)
	{
		return false;
	}

	return true;
}

CTime zcjm::String2Time(string&  strS)
{
	int a, b, c;   
	a = atoi(strS.substr(0, 4).c_str());
	b = atoi(strS.substr(4, 2).c_str());
	c = atoi(strS.substr(6, 2).c_str());  
	return CTime(a,b,c,0,0,0); 
}

/*
* 调用--及测试示例
*
int main()
{
string strCode = zcjm::GetMichineCode();
cout << "MichineCode : " << strCode << endl;
strCode = zcjm::GetRegisterCode(strCode);
cout << "register code: " << strCode << endl;

if(zcjm::Register(strCode))
cout << "register successful" << endl;
else
cout << "register code is not invalide! " << endl;

if(zcjm::IsRegister())
cout << "is has register" << endl;
else
cout << "no register " << endl;

return 0;
}
*/