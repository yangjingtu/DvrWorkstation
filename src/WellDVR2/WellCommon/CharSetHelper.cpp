#include "StdAfx.h"
#include "CharSetHelper.h"


CCharSetHelper::CCharSetHelper(void)
{
}


CCharSetHelper::~CCharSetHelper(void)
{
}

/***************************************************************************************
*描    述: 将wchar_t* 转成char*
*
*参数列表: *pcstr [OUT]		--		用于接收转换后的数据
*		   *pwstr [IN]		--		要转换的宽字节指针
*		   len [IN]			--		接收缓冲区的长度
*								如果len = 0，长度自动计算: 宽字节长度*2 + 1								
*
*返 回 值: 
*
*时间作者: created by yjt [2012/5/25 13:12]
*
*修改记录:
//modified by yjt [2012/10/29 11:31] 修改了buff[nbytes + 1] = 0; 下标nbytes即为nbytes+1位置
***************************************************************************************/
char* CCharSetHelper::w2c(char *pcstr,wchar_t *pwstr, size_t len)
{
	if(!pwstr)
	{
		pcstr = NULL;
		return 0;
	}

	int nlength=wcslen(pwstr);
	
	//自动计算长度
	if(len == 0)
		len = nlength*2 + 1;

	//获取（计算）转换后的长度
	int nbytes = WideCharToMultiByte( 0, // specify the code page used to perform the conversion
		0,         // no special flags to handle unmapped characters
		pwstr,     // wide character string to convert
		nlength,   // the number of wide characters in that string
		NULL,      // no output buffer given, we just want to know how long it needs to be
		0,
		NULL,      // no replacement character given
		NULL );    // we don't want to know if a character didn't make it through the translation
	
	// make sure the buffer is big enough for this, making it larger if necessary
	if((size_t)nbytes >= len)   
		nbytes = len - 1;
	
	char* buff = new char[nbytes + 1];

	//通过以上得到的结果，转换unicode 字符为ascii 字符
	WideCharToMultiByte( 0, // specify the code page used to perform the conversion
		0,			// no special flags to handle unmapped characters
		pwstr,		// wide character string to convert
		nlength,	// the number of wide characters in that string
		buff,		// put the output ascii characters at the end of the buffer
		nbytes,		// there is at least this much space there
		NULL,		// no replacement character given
		NULL );
	
	//结束符
	buff[nbytes] = 0;
	pcstr = buff;

	return pcstr ;
}

/***************************************************************************************
*描    述: 将wchar_t* 转成char*
*
*参数列表: *pcstr [OUT]		--		用于接收转换后的数据
*		   *pwstr [IN]		--		要转换的宽字节指针							
*
*返 回 值: 返回接收缓冲区(转换后数据)的长度
*
*时间作者: created by yjt [2012/5/25 13:12]
*
*修改记录:
//modified by yjt [2012/10/29 11:31] 修改了buff[nbytes + 1] = 0; 下标nbytes即为nbytes+1位置
***************************************************************************************/
size_t CCharSetHelper::w2c(char *pcstr, wchar_t *pwstr)
{
	if(!pwstr)
	{
		pcstr = NULL;
		return 0;
	}

	int nlength=wcslen(pwstr);

	//获取（计算）转换后的长度
	int nbytes = WideCharToMultiByte( 0, // specify the code page used to perform the conversion
		0,         // no special flags to handle unmapped characters
		pwstr,     // wide character string to convert
		nlength,   // the number of wide characters in that string
		NULL,      // no output buffer given, we just want to know how long it needs to be
		0,
		NULL,      // no replacement character given
		NULL );    // we don't want to know if a character didn't make it through the translation

	char* buff = new char[nbytes + 1];

	//通过以上得到的结果，转换unicode 字符为ascii 字符
	WideCharToMultiByte( 0, // specify the code page used to perform the conversion
		0,			// no special flags to handle unmapped characters
		pwstr,		// wide character string to convert
		nlength,	// the number of wide characters in that string
		buff,		// put the output ascii characters at the end of the buffer
		nbytes,		// there is at least this much space there
		NULL,		// no replacement character given
		NULL );

	//结束符
	buff[nbytes] = 0;
	pcstr = buff;

	return nbytes;
}

string CCharSetHelper::w2c(const wstring& wstr)
{
	if(wstr.size() == 0)
	{
		return "";
	}

	int nlength=wstr.size();

	//获取（计算）转换后的长度
	int nbytes = WideCharToMultiByte( 0, // specify the code page used to perform the conversion
		0,         // no special flags to handle unmapped characters
		wstr.c_str(),     // wide character string to convert
		nlength,   // the number of wide characters in that string
		NULL,      // no output buffer given, we just want to know how long it needs to be
		0,
		NULL,      // no replacement character given
		NULL );    // we don't want to know if a character didn't make it through the translation

	char* buff = new char[nbytes + 1];

	//通过以上得到的结果，转换unicode 字符为ascii 字符
	WideCharToMultiByte( 0, // specify the code page used to perform the conversion
		0,			// no special flags to handle unmapped characters
		wstr.c_str(),		// wide character string to convert
		nlength,	// the number of wide characters in that string
		buff,		// put the output ascii characters at the end of the buffer
		nbytes,		// there is at least this much space there
		NULL,		// no replacement character given
		NULL );
	buff[nbytes] = 0;
	//结束符
	string strRlt = buff;
	delete[] buff;
	return strRlt;
}

size_t CCharSetHelper::w2c(const wstring& wstrIn, string& strOut)
{
	if(wstrIn.empty())
	{
		strOut = "";
		return 0;
	}

	int nlength=wstrIn.size();

	//获取（计算）转换后的长度
	int nbytes = WideCharToMultiByte( 0, // specify the code page used to perform the conversion
		0,         // no special flags to handle unmapped characters
		wstrIn.c_str(),     // wide character string to convert
		nlength,   // the number of wide characters in that string
		NULL,      // no output buffer given, we just want to know how long it needs to be
		0,
		NULL,      // no replacement character given
		NULL );    // we don't want to know if a character didn't make it through the translation

	char* buff = new char[nbytes + 1];

	//通过以上得到的结果，转换unicode 字符为ascii 字符
	WideCharToMultiByte( 0, // specify the code page used to perform the conversion
		0,			// no special flags to handle unmapped characters
		wstrIn.c_str(),		// wide character string to convert
		nlength,	// the number of wide characters in that string
		buff,		// put the output ascii characters at the end of the buffer
		nbytes,		// there is at least this much space there
		NULL,		// no replacement character given
		NULL );
	buff[nbytes] = 0;
	//结束符
	strOut = buff;

	//delete[] buff;
	return nbytes;
}

/***************************************************************************************
*描    述: 将char* 转成wchar_t*
*
*参数列表: *pwstr [OUT]		--		接收转换后的宽字节数据
*		   *pstr [IN]		--		指向源数据
*		   len [IN]			--		接收缓冲区的长度
*
*返 回 值:
*
*时间作者: created by yjt [2012/5/25 13:16]
*
*修改记录:
//modified by yjt [2012/10/29 11:31] 修改了buff[nbytes + 1] = 0; 下标nbytes即为nbytes+1位置
***************************************************************************************/
void CCharSetHelper::c2w(wchar_t *pwstr, size_t len, char *pstr)
{
	if(pstr)
	{
		size_t nu = strlen(pstr);
		
		//计算出长度
		size_t n = (size_t)MultiByteToWideChar(CP_ACP,0,(const char *)pstr,(int)nu,NULL,0);
		
		//如果计算后的长度大于缓冲区，只取缓冲区的大小
		if(n >= len)
			n = len - 1;
		
		MultiByteToWideChar(CP_ACP,0,(const char *)pstr,(int)nu, pwstr,(int)n);
		
		//最后一个字符赋空
		pwstr[n]=0;
	}
}

/***************************************************************************************
*描    述: 把ascii 字符转换为unicode字符
*
*参数列表: *pwstr [OUT]		--		接收转换后的宽字节数据
*		   *pstr [IN]		--		指向源数据
*
*返 回 值: 返回转换后数据的长度
*
*时间作者: created by yjt [2012/5/25 13:19]
*
*修改记录:
//modified by yjt [2012/10/29 11:31] 修改了buff[nbytes + 1] = 0; 下标nbytes即为nbytes+1位置
***************************************************************************************/
size_t CCharSetHelper::c2w(wchar_t *pwstr, char *str)
{
	wchar_t* buffer = NULL;
	size_t n = 0;
	if(str)
	{
		size_t nu = strlen(str);
		n =(size_t)MultiByteToWideChar(CP_ACP,0,(const char *)str,int(nu),NULL,0);
		buffer=0;
		buffer = new wchar_t[n+1];
		//if(n>=len) n=len-1;
		::MultiByteToWideChar(CP_ACP,0,(const char *)str,int(nu),buffer,int(n));    
		//结束符
		buffer[n] = 0;
	}
	pwstr = buffer;

	//返回缓冲区的长度
	return n;
	//delete[] buffer;
}

wstring CCharSetHelper::c2w(const string& str)
{
	if(str.empty())
		return L"";

	wchar_t* buffer = NULL;
	size_t n = 0;
	if(str.size() > 0)
	{
		size_t nu = str.size();
		n = (size_t)MultiByteToWideChar(CP_ACP,0,(const char *)str.c_str(), int(nu),NULL,0);
		buffer = new wchar_t[n + 1];
		//if(n>=len) n=len-1;
		::MultiByteToWideChar(CP_ACP,0,(const char *)str.c_str(),int(nu),buffer,int(n));    
		//结束符
		buffer[n] = 0;
	}
	//返回缓冲区的长度
	wstring strRlt = buffer;
	delete[] buffer;

	return strRlt;
}

size_t CCharSetHelper::c2w(const string& strIn, wstring& wstrOut)
{
	if(strIn.empty())
	{
		wstrOut = L"";
		return 0;
	}

	wchar_t* buffer = NULL;
	size_t n = 0;
	if(strIn.size() > 0)
	{
		size_t nu = strIn.size();
		n =(size_t)MultiByteToWideChar(CP_ACP,0,(const char *)strIn.c_str(),int(nu),NULL,0);
		buffer=0;
		buffer = new wchar_t[n + 1];
		//if(n>=len) n=len-1;
		::MultiByteToWideChar(CP_ACP,0,(const char *)strIn.c_str(),int(nu),buffer,int(n));    
	
		//结束符
		buffer[n] = 0;
	}
	//返回缓冲区的长度
	wstrOut = buffer;
	//delete[] buffer;
	return n;
}

/************************************************************************/
/* 
	使用示例                                                                     
*/
/************************************************************************/
/*
int _tmain(int argc, _tchar* argv[])
{
	wchar_t pwstr[] =l"我是中国人";
	wchar_t pwstr2[20];
	char *pcstr = (char *)malloc(sizeof(char)*(2 * wcslen(pwstr)+1));
	memset(pcstr , 0 , 2 * wcslen(pwstr)+1 );
	w2c(pcstr,pwstr,2 * wcslen(pwstr)+1) ;
	printf("%s\n",pcstr);
	c2w(pwstr2,20,pcstr);
	wprintf(l"%s",pwstr2);
	free(pcstr) ;
	return 0;
}
*/

/************************************************************************/