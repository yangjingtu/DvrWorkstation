#include "StdAfx.h"
#include "FileBackUp.h"
#include "WellCommon/CharSetHelper.h"

#define FILEMAX 100   

typedef struct _SRCFILE   
{   
	WIN32_FIND_DATA  fd;   
	bool bIsNew;   
}SRCFILE;   
typedef struct _DSTFILE   
{   
	WIN32_FIND_DATA  fd;   
	bool bIsMatch;   
}DSTFILE;   

SRCFILE SrcFiles[FILEMAX];   
DSTFILE DstFiles[FILEMAX];   

WIN32_FIND_DATA fd;   

CFileBackUp::CFileBackUp(void)
{
}


CFileBackUp::~CFileBackUp(void)
{
}


//////////////////////////////////////////////////////////////////////////
//参数:
//		pSrcDir [IN]	--		源, 如: D:\\aaa\\*
//		pDstDir [IN]	--		备份到哪里去, 如: E:\\bbb\\*
//
//////////////////////////////////////////////////////////////////////////
bool CFileBackUp::BackUp(const wstring& src, const wstring& dst)
{
	return CopyFile(src.c_str(), dst.c_str(), FALSE);   

	bool bRet=TRUE;   
	int iSrcFile=0;   
	int iDstFile=0;   

	TCHAR* pSrcDir = const_cast<TCHAR*>(src.c_str());
	TCHAR* pDstDir = const_cast<TCHAR*>(dst.c_str());

    //在源目录下遍历所有的文件保存在SrcFiles结构体中   
    HANDLE hFile=FindFirstFile(pSrcDir,&fd);   
    while(hFile!=INVALID_HANDLE_VALUE && bRet)   
    {   
        if(fd.dwFileAttributes==FILE_ATTRIBUTE_ARCHIVE)   
        {   
            SrcFiles[iSrcFile].fd=fd;   
            SrcFiles[iSrcFile].bIsNew=FALSE;   
            //out<<SrcFiles[iSrcFile].fd.cFileName<<endl;   
            iSrcFile++;   
        }   
        bRet=FindNextFile(hFile,&fd);   
    }   
       
    //在目标目录下遍历所有的文件保存在DstFiles结构体中   
    bRet=TRUE;   
    hFile=FindFirstFile(pDstDir,&fd);   
    while(hFile!=INVALID_HANDLE_VALUE && bRet)   
    {   
        if(fd.dwFileAttributes==FILE_ATTRIBUTE_ARCHIVE)   
        {   
            DstFiles[iDstFile].fd=fd;   
            DstFiles[iDstFile].bIsMatch=FALSE;   
            iDstFile++;   
        }   
        bRet=FindNextFile(hFile,&fd);   
    }   
///////////////////////////////////////////////////////////////    
//  下面开始比较源目录和目标目录的所有文件名称与建表时间     //   
//  找出SrcFile中那些文件比DstFile文件时间上更早，           //   
//  就讲bIsNew设为TRUE，同时DstFile文件中存在，而在SrcFile中 //   
//  不存在，就把bMatch设为False                              //   
    for(int i=0;i<iSrcFile-1;i++)   
    {   
        bool bNull=TRUE;   
        for(int j=0;j<iDstFile-1;j++)   
        {   
            if(lstrcmpi(SrcFiles[i].fd.cFileName,DstFiles[j].fd.cFileName)==0)   
            {   
                DstFiles[j].bIsMatch=TRUE;   
                bNull=FALSE;   
                if(1==CompareFileTime(&SrcFiles[i].fd.ftCreationTime,&DstFiles[j].fd.ftCreationTime))   
            //  if(SrcFiles[i].fd.ftCreationTime.dwLowDateTime > DstFiles[j].fd.ftCreationTime.dwLowDateTime)   
                    SrcFiles[i].bIsNew=TRUE;   
                break;   
            }   
        }   
        if(bNull==TRUE)   
            SrcFiles[i].bIsNew=TRUE;   
    }   
   
   
    //拷贝SrcFile中bIsNew位TRUE的文件到DstFile中去   
    for(int a=0;a<iSrcFile-1;a++)   
    {   
        if(SrcFiles[a].bIsNew)   
        {   
            CopyFile(SrcFiles[a].fd.cFileName,pDstDir,FALSE);   
        }   
    }   
       
    //删除目标中bMatch为FALSE的文件   
    for (int b=0; b<iDstFile; b++)    
    {   
        if (!DstFiles[b].bIsMatch)   
        {   
            lstrcat(pDstDir, DstFiles[b].fd.cFileName);   
            DeleteFile(pDstDir);   
            // printf("delete %s \n", dest);   
        }   
    }   
   
    return 0;
}

bool CFileBackUp::BackUp(const string& src, const string& dst)
{
	return BackUp(S2WS(src), S2WS(dst));
}

bool CFileBackUp::FileCopyTo(CString source, CString destination, CString searchStr, BOOL cover)
{
	CString strSourcePath = source;
	CString strDesPath = destination;
	CString strFileName = searchStr;
	CFileFind filefinder;
	CString strSearchPath = strSourcePath + _T("\\") + strFileName;
	CString filename;
	BOOL bfind = filefinder.FindFile(strSearchPath);
	CString SourcePath, DisPath;

	bool bRlt = true;
	while (bfind)
	{
		bfind = filefinder.FindNextFile();
		filename = filefinder.GetFileName();
		SourcePath = strSourcePath + _T("\\") + filename;
		DisPath = strDesPath + _T("\\") + filename;
		bRlt |= CopyFile(SourcePath.GetString(), DisPath.GetString(), cover);
	}
	filefinder.Close();
	return bRlt;
}