#include "StdAfx.h"
#include "AviHelper.h"
#include "StringHelper.h"
#include "CharSetHelper.h"


CAviHelper::CAviHelper(void)
{
}


CAviHelper::~CAviHelper(void)
{
}

AVIFILEINFO CAviHelper::AVI_GetFileInfo(const wstring& strFileName)
{
	AVIFileInit();
	PAVIFILE avi;
	AVIFILEINFO avi_info;
	memset(&avi_info, 0, sizeof(AVIFILEINFO));

	int res = AVIFileOpen(&avi, strFileName.c_str(), OF_READ, NULL);
	int n = GetLastError();
	if (res!=AVIERR_OK)
	{
		//an error occures
		if (avi!=NULL)
			AVIFileRelease(avi);
		return avi_info;
	}

	res = AVIFileInfo(avi, &avi_info, sizeof(AVIFILEINFO));
	if( res != AVIERR_OK)
	{
		AVIFileExit();
		return avi_info;
	}

	AVIFileExit();
	return avi_info;
}

AVIFILEINFO CAviHelper::AVI_GetFileInfo(const string& strFileName)
{
	return AVI_GetFileInfo(S2WS(strFileName));
}

bool CAviHelper::AVI_GetStreamInfo(const wstring& strFileName, PAVISTREAM pVideoStream, PAVISTREAM pAudioStream)
{
	HRESULT hr;   
	PAVIFILE pAVIFile=NULL;   
	
	hr=AVIFileOpen(&pAVIFile, strFileName.c_str(), OF_READ,NULL);   
	if(FAILED(hr))
	{   
		//AfxMessageBox(_T("AVIFileOpen failed!"));   
		return false;   
	}   
	
	AVIFILEINFO fileinfo;   
	ZeroMemory(&fileinfo,sizeof(AVIFILEINFO));   
	hr=AVIFileInfo(pAVIFile,&fileinfo,sizeof(AVIFILEINFO));   
	if(FAILED(hr))
	{   
		//AfxMessageBox(_T("AVIFileInfo failed!"));   
		return false;   
	}   
	
	// Extract stream   
	hr=AVIFileGetStream(pAVIFile,&pVideoStream,streamtypeVIDEO,0);   
	if(SUCCEEDED(hr))
	{   
		AVISTREAMINFO v_stream;   
		ZeroMemory(&v_stream,sizeof(AVISTREAMINFO));   
		
		hr=AVIStreamInfo(pVideoStream,&v_stream,sizeof(AVISTREAMINFO));   
		if(FAILED(hr))
		{   
			//AfxMessageBox(_T("AVIStreamInfo failed!"));   
			return false;   
		}      
		
		int totalframes = fileinfo.dwLength;   
		double rate = (double)v_stream.dwRate/(double)v_stream.dwScale;   
		int streams = fileinfo.dwStreams;   
		char* fccHandler = (char*)&v_stream.fccHandler;   
		int width = v_stream.rcFrame.right - v_stream.rcFrame.left;   
		int height = v_stream.rcFrame.bottom - v_stream.rcFrame.top;   
		
// 		CString str;   
// 		str.Format("%1.2f",rate);   
// 		str.TrimRight('0');   
// 		str.TrimRight('.');   
// 		SetDlgItemText(IDC_EDIT2,str);   
// 		SetDlgItemInt(IDC_EDIT1,totalframes);   
// 		SetDlgItemInt(IDC_EDIT4,streams);   
// 		SetDlgItemText(IDC_EDIT3,fccHandler);   
// 		SetDlgItemInt(IDC_EDIT5,width);   
// 		SetDlgItemInt(IDC_EDIT6,height);   
		 
	}      
	
	hr=AVIFileGetStream(pAVIFile,&pAudioStream,streamtypeAUDIO,0);   
	if(SUCCEEDED(hr))
	{   
		WAVEFORMATEX wfex;   
		/*  Note:  
		*   对于PCM音频，WAVEFORMATEX 各成员之间的关系如下：  
		*   nAvgBytesPerSec = nSamplesPerSec * nBlockAlign  
		*                   = nSamplesPerSec * wBitsPerSample/8 * nChannels  
		*   其中：nSamplesPerSec就是音频的采样频率，主要有8000Hz,11025Hz,22050Hz,44100Hz  
		*   wBitsPerSample只有8位和16位两种  
		*   对于单声道nChannels＝1，对于立体声nChannels＝2  
		*/   
		
		ZeroMemory(&wfex,sizeof(WAVEFORMATEX));   
		long size=sizeof(WAVEFORMATEX);   
		AVIStreamReadFormat(pAudioStream,0,&wfex,&size);   
		
		int tag=wfex.wFormatTag;   
		CString strFormat;   
		switch(tag)
		{   
		case WAVE_FORMAT_PCM:   
			strFormat = _T("PCM");   
			break;   
		case WAVE_FORMAT_ADPCM:   
			strFormat= _T("ADPCM");   
			break;   
		case WAVE_FORMAT_MPEGLAYER3:   
			strFormat= _T("MPEGLAYER3");   
			break;   
		case WAVE_FORMAT_MPEG:   
			strFormat= _T("MPEG");   
			break;   
		case WAVE_FORMAT_DSPGROUP_TRUESPEECH:   
			strFormat= _T("TRUESPEECH");   
			break;   
		default:   
			strFormat.Format(_T("%d"),tag);   
			break;   
		}   
		
// 		int channel=wfex.nChannels;   
// 		if(channel==1)   
// 			SetDlgItemText(IDC_EDIT8,"1 (Monaural)");   
// 		if(channel==2)   
// 			SetDlgItemText(IDC_EDIT8,"2 (Stereo)");   
// 		   
// 		int bits=wfex.wBitsPerSample;    
// 		
// 		CString strFreq;   
// 		int samples=wfex.nSamplesPerSec;   
// 		strFreq.Format(_T("%d Hz"),samples);   
// 		SetDlgItemText(IDC_EDIT11,strFreq);   
// 		
// 		int bytes=wfex.nAvgBytesPerSec;   
// 		SetDlgItemInt(IDC_EDIT12,bytes);   
// 		
// 		CString strAlign;   
// 		int align=wfex.nBlockAlign;   
// 		strAlign.Format(_T("%d bytes"),align);   
// 		SetDlgItemText(IDC_EDIT10,strAlign);      
	}      

// 	if (pVideoStream != NULL)
// 		AVIStreamRelease(pVideoStream);	
// 	if (pAudioStream != NULL)
// 		AVIStreamRelease(pVideoStream);

	AVIFileRelease(pAVIFile);   
	pAVIFile=NULL;   

	return true;
}


bool CAviHelper::AVI_resolution(const string& strAviFileName, int& width, int& height)
{
	return AVI_resolution(S2WS(strAviFileName), width, height);
}

bool CAviHelper::AVI_resolution(const wstring& strAviFileName, int& width, int& height)
{
	AVIFILEINFO avi_info = AVI_GetFileInfo(strAviFileName);

	width = avi_info.dwWidth;
	height = avi_info.dwHeight;

	if(width > 0 && height > 0)
		return true;
	return false;
}

void CAviHelper::AVItoBmp(const string& strAVIFileName, const string& strBmpDir)
{
	AVItoBmp(S2WS(strAVIFileName), S2WS(strBmpDir));
}

void CAviHelper::AVItoBmp(const wstring& strAVIFileName, const wstring& strBmpDir)
{
	AVIFileInit();
	PAVIFILE avi;
	int res = AVIFileOpen(&avi, strAVIFileName.c_str(), OF_READ, NULL);
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
			
				AVIFileOpen(&pfile, szAVIName.c_str(), OF_WRITE | OF_CREATE,NULL);
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