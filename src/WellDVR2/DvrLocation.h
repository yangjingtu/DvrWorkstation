//////////////////////////////////////////////////////////////////////////
//Describe: ¶¨Î»
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "dvrmgr.h"

class CDvrLocation :
	public CDvrMgrBase
{
public:
	CDvrLocation(void);
	~CDvrLocation(void);

	static CDvrLocation& Instance()
	{
		static CDvrLocation dvrl;
		return dvrl;
	}

	virtual bool PutDvr();
	virtual void RemoveDvr();

protected:
	void FindPos(int& x, int& y);	

	void SaveDvrPos(const wstring& strPort, int nWndIndex);
	bool CheckIsDericted( const wstring& strPort, int x, int y);

private:
	int m_xx;
	int m_yy;
};

