
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1993 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/


#ifndef _UART_H_
#define _UART_H_

// Uart port time out in milliseconds.
#define UART_COMM_TIMEOUT   10000

#define USECOMM      // yes, we need the COMM API

//#undef NO_STRICT    // be bold!

//#define HINSTANCE HANDLE

//#include <afx.h>
#include <windows.h>
#include <stdio.h>

// constant definitions

#define GWL_NPTTYINFO        0
#define TTYEXTRABYTES        sizeof( LONG )

#define ABOUTDLG_USEBITMAP  1

#define ATOM_TTYINFO       0x100

// hard coded maximum number of ports for device under Win32

#define MAXPORTS        4

// terminal size

#define MAXROWS         25
#define MAXCOLS         80

#define MAXBLOCK        80

#define MAXLEN_TEMPSTR  81

#define RXQUEUE         4096
#define TXQUEUE         4096

// cursor states

#define CS_HIDE         0x00
#define CS_SHOW         0x01

// Flow control flags

#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04

// ascii definitions

#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13

// data structures

class CCommConnection
{
    public:
        CCommConnection();
        ~CCommConnection();
        BOOL Open(BYTE bPortNum, DWORD dwBoadRate);
        BOOL Close();
        BOOL Write(LPBYTE, DWORD);
        BOOL Read(LPBYTE, int);

    protected:

        BOOL Setup();
        int  ReadCommBlock(LPBYTE, int);

//        CString m_strCfgFile;
        HANDLE  m_idComDev ;
        BYTE    m_bPort;
        BOOL    m_fConnected;
        BYTE    m_bByteSize;
        BYTE    m_bFlowCtrl;
        BYTE    m_bParity;
        BYTE    m_bStopBits;
        DWORD   m_dwBaudRate ;
        WORD    m_wCursorState ;

        HANDLE      m_hPostEvent;
        HANDLE      m_hWatchThread;
        HANDLE      m_hWatchEvent;
        OVERLAPPED  m_osWrite;
        OVERLAPPED  m_osRead;

};



#endif // #ifndef _UART_H_


