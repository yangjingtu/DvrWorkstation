#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#define ACK              	0xe8

#define DATA_LEN			(100)


#define SLEEP_TIME 10
#define TIME_OUT (5000/SLEEP_TIME);

typedef struct tagSUsbSetting
{
	char uwCommand;
	char uwCommandLenth;
	char pParam[DATA_LEN];    
} SUsbSetting, *PSUsbSetting;

#define COMMAND_LEN (sizeof(SUsbSetting) - DATA_LEN)

typedef struct tagSTime
{
	unsigned short uYear;
	unsigned short uMonth;
	unsigned short uDay;    
	unsigned short uHour;    
	unsigned short uMinute;    
	unsigned short uSecond;    
} STime, *PSTime;


class AFX_EXT_CLASS CDevBase
{
public:
	CDevBase();
	~CDevBase();
public:
	virtual BOOL GetTimeEx(SYSTEMTIME *pst){ return TRUE; }
	virtual BOOL SetTimeEx(){ return TRUE; }

	virtual BOOL GetIDEx(CString &strID){ return TRUE; }
	virtual BOOL SetIDEx(const CString& strID){ return TRUE; }

	virtual BOOL SetMassEx(){ return TRUE; }
	virtual BOOL IsMassed() { return m_bMass; }

	virtual BOOL GetPwd(CString &strPwd){ return TRUE; }
	virtual BOOL SetPwd(const CString& strPwd){ return TRUE; }

	virtual BOOL GetMachinID(CString &str){ return TRUE; }
	virtual BOOL SetMachinID(const CString& MachiID){ return TRUE; }

public:
	BOOL IsDeviceReady();

protected:

	virtual BOOL GetValue(char uCommandID,char *pData,char *cLen){ return TRUE; }
	virtual BOOL SetValue(char uCommandID,char *pData,char cLen){ return TRUE; }
protected:
	BOOL InitInterface();
	void DeinitInterface();

protected:
	SUsbSetting *pSetting;

	//是否已枚举成U盘
	bool m_bMass;
};

#endif // __INTERFACE_H__