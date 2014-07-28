#include "StdAfx.h"
#include "AviHelper.h"
#include "StringHelper.h"

#include <Vfw.h>
#pragma comment(lib, "Vfw32.lib")


CAviHelper::CAviHelper(void)
{
}


CAviHelper::~CAviHelper(void)
{
}

bool CAviHelper::AVI_resolution(const string& strAviFileName, int& width, int& height)
{
	return AVI_resolution(S2WS(strAviFileName), width, height);
}

bool CAviHelper::AVI_resolution(const wstring& strAviFileName, int& width, int& height)
{
	AVIFileInit();
	PAVIFILE avi;
	int res = AVIFileOpen(&avi, WS2S(strAviFileName).c_str(), OF_READ, NULL);
	int n = GetLastError();
	if (res!=AVIERR_OK)
	{
		//an error occures
		if (avi!=NULL)
			AVIFileRelease(avi);
		return false;
	}

	AVIFILEINFO avi_info;
	memset(&avi_info, 0, sizeof(AVIFILEINFO));

	res = AVIFileInfo(avi, &avi_info, sizeof(AVIFILEINFO));
	if( res != AVIERR_OK)
	{
		AVIFileExit();
		return false;
	}
	width = avi_info.dwWidth;
	height = avi_info.dwHeight;

	AVIFileExit();
	return true;
}

void CAviHelper::AVItoBmp(const string& strAVIFileName, const string& strBmpDir)
{
	AVItoBmp(S2WS(strAVIFileName), S2WS(strBmpDir));
}

void CAviHelper::AVItoBmp(const wstring& strAVIFileName, const wstring& strBmpDir)
{
	AVIFileInit();
	PAVIFILE avi;
	int res = AVIFileOpen(&avi, WS2S(strAVIFileName).c_str(), OF_READ, NULL);
	int n = GetLastError();
	if (res!=AVIERR_OK)
	{
		//an error occures
		if (avi!=NULL)
			AVIFileRelease(avi);
		return ;
	}
	
	AVIFILEINFO avi_info;
	AVIFileInfo(avi, &avi_info, sizeof(AVIFILEINFO));
	PAVISTREAM pStream;
	res=AVIFileGetStream(avi, &pStream, streamtypeVIDEO /*video stream*/, 0 /*first stream*/);
	if (res!=AVIERR_OK)
	{
		if (pStream!=NULL)
			AVIStreamRelease(pStream);
		AVIFileExit();
		return ;
	}
	
	//do some task with the stream
	int iNumFrames;
	int iFirstFrame;
	iFirstFrame = AVIStreamStart(pStream);
	if (iFirstFrame==-1)
	{
		//Error getteing the frame inside the stream
		if (pStream!=NULL)
			AVIStreamRelease(pStream);
		AVIFileExit();
		return ;
	}
	
	iNumFrames = AVIStreamLength(pStream);
	if (iNumFrames==-1)
	{
		//Error getteing the number of frames inside the stream
		if (pStream!=NULL)
			AVIStreamRelease(pStream);
		AVIFileExit();
		return ;
	}
	
	//getting bitmap from frame
	BITMAPINFOHEADER bih;
	ZeroMemory(&bih, sizeof(BITMAPINFOHEADER));
	bih.biBitCount=24; //24 bit per pixel
	bih.biClrImportant=0;
	bih.biClrUsed = 0;
	bih.biCompression = BI_RGB;
	bih.biPlanes = 1;
	bih.biSize = 40;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;
	
	//calculate total size of RGBQUAD scanlines (DWORD aligned)
	bih.biSizeImage = (((bih.biWidth * 3) + 3) & 0xFFFC) * bih.biHeight ;
	PGETFRAME pFrame;
	pFrame=AVIStreamGetFrameOpen(pStream, NULL );
	AVISTREAMINFO streaminfo;
	AVIStreamInfo(pStream,&streaminfo,sizeof(AVISTREAMINFO));
	
	//Get the first frame
	BITMAPINFOHEADER bih2;
	long lsize = sizeof(bih2);
	int index= 0;
	for (int i = iFirstFrame; i < iNumFrames; i++)
	{
		index= i-iFirstFrame;
		BYTE* pDIB = (BYTE*) AVIStreamGetFrame(pFrame, index); //
		AVIStreamReadFormat(pStream,index,&bih2,&lsize);
		BITMAPFILEHEADER stFileHdr;
		BYTE* Bits=new BYTE[bih2.biSizeImage];
		AVIStreamRead(pStream,index,1,Bits,bih2.biSizeImage,NULL,NULL);
		//RtlMoveMemory(Bits, pDIB + sizeof(BITMAPINFOHEADER), bih2.biSizeImage);
		bih2.biClrUsed =0;
		stFileHdr.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
		stFileHdr.bfSize=sizeof(BITMAPFILEHEADER);
		stFileHdr.bfType=0x4d42; 
		CString FileName;
		FileName.Format(_T("Frame-%05d.bmp"), index);
		CString strtemp;
		strtemp.Format(_T("%s\\%s"), strBmpDir.c_str(), FileName);
		FILE* fp=_tfopen(strtemp ,_T("wb"));
		fwrite(&stFileHdr,1,sizeof(BITMAPFILEHEADER),fp);
		fwrite(&bih2,1,sizeof(BITMAPINFOHEADER),fp);
		int ff = fwrite(Bits,1,bih2.biSizeImage,fp);
		int e = GetLastError();
		fclose(fp);
		/////
		delete Bits;
		//CreateFromPackedDIBPointer(pDIB, index);
	}
	
	AVIStreamGetFrameClose(pFrame);
	//close the stream after finishing the task
	if (pStream!=NULL)
		AVIStreamRelease(pStream);
	AVIFileExit();
}

void CAviHelper::BMPtoAVI(const string& szAVIName, const string& strBDir)
{
	BMPtoAVI(S2WS(szAVIName), S2WS(strBDir));
}

void CAviHelper::BMPtoAVI(const wstring& szAVIName, const wstring& strBDir)
{
	CFileFind finder;
	CString strBmpDir;
	strBmpDir.Format(_T("%s\\*.*"), strBDir.c_str()); 
	AVIFileInit(); 
	AVISTREAMINFO strhdr;
	PAVIFILE pfile;
	PAVISTREAM ps; 
	int nFrames =0; 
	HRESULT hr; 
	BOOL bFind = finder.FindFile(strBmpDir);
	while(bFind)
	{
		bFind = finder.FindNextFile();
		if(!finder.IsDots() && !finder.IsDirectory())
		{
			CString str = finder.GetFilePath();
			FILE *fp = _tfopen(str, _T("rb"));
			
			BITMAPFILEHEADER bmpFileHdr;
			BITMAPINFOHEADER bmpInfoHdr;
			fseek( fp,0,SEEK_SET);
			fread(&bmpFileHdr,sizeof(BITMAPFILEHEADER),1, fp);
			fread(&bmpInfoHdr,sizeof(BITMAPINFOHEADER),1, fp);
			BYTE *tmp_buf = NULL;
			if(nFrames ==0 )
			{
			
				AVIFileOpen(&pfile, WS2S(szAVIName).c_str(), OF_WRITE | OF_CREATE,NULL);
				memset(&strhdr, 0, sizeof(strhdr));
				strhdr.fccType = streamtypeVIDEO;// stream type
				strhdr.fccHandler = 0;
				strhdr.dwScale = 1;
				strhdr.dwRate = 15; // 15 fps
				strhdr.dwSuggestedBufferSize = bmpInfoHdr.biSizeImage ;
				SetRect(&strhdr.rcFrame, 0, 0, bmpInfoHdr.biWidth, bmpInfoHdr.biHeight);
				
				// And create the stream;
				hr = AVIFileCreateStream(pfile,&ps,&strhdr); 
				// hr = AVIStreamSetFormat(ps,nFrames,&bmpInfoHdr,sizeof(bmpInfoHdr));
			}
			
			tmp_buf = new BYTE[bmpInfoHdr.biWidth * bmpInfoHdr.biHeight * 3];
			fread(tmp_buf, 1, bmpInfoHdr.biWidth * bmpInfoHdr.biHeight * 3, fp);
			hr = AVIStreamSetFormat(ps,nFrames,&bmpInfoHdr,sizeof(bmpInfoHdr));
			hr = AVIStreamWrite(ps, // stream pointer
				nFrames , // time of this frame
				1, // number to write
				(LPBYTE) tmp_buf,
				bmpInfoHdr.biSizeImage , // size of this frame
				AVIIF_KEYFRAME, // flags....
				NULL,
				NULL);
			nFrames ++; 
			fclose(fp);
		}
	}
	
	AVIStreamClose(ps);
	if(pfile != NULL)
		AVIFileRelease(pfile);
	AVIFileExit();
}