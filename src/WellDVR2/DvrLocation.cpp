#include "stdafx.h"
#include "DvrLocation.h"
#include "ShareData.h"
#include "config/Config.h"
#include "USBCtrl/UsbHelper.h"
#include "config/LocationConfig.h"

CDvrLocation::CDvrLocation(void)
	: m_xx(-1)
	, m_yy(-1)
{
}


CDvrLocation::~CDvrLocation(void)
{
}

void CDvrLocation::FindPos(int& x, int& y)
{
	//单机模式
#ifdef ONE_DVR
	{
		x = 0;
		y = 0;
		m_xx = 0;
		m_yy = 0;
		return;
	}
#endif

	//定位模式下，用鼠标选择位置
	SHAREDATA.g_pMainFrame->GetSelectPos(x, y);
	if(x != -1 || y != -1)
	{
		m_xx = x;
		m_yy = y;
		return;
	}

	if( m_xx == -1 || m_yy == -1 )
	{
		m_xx = 0;
		m_yy = 0;
	}
	else
	{
		int tmp = m_yy + 1;
		if( tmp >= SHAREDATA.g_dvrProp.numCol )
		{
			m_yy = 0;

			tmp = m_xx + 1;
			if( tmp >= SHAREDATA.g_dvrProp.numRow )
				//m_xx = SHAREDATA.g_dvrProp.numRow - 1;
				m_xx = 0;
			else
				m_xx += 1;
		}
		else
		{
			m_yy += 1;

			tmp = m_xx + 1;
			if( tmp >= SHAREDATA.g_dvrProp.numRow )
				m_xx = SHAREDATA.g_dvrProp.numRow - 1;
		}
	}
	

	x = m_xx;
	y = m_yy;
}

//保存窗口
bool CDvrLocation::PutDvr()
{
	wstring strPort(USBHUB.GetNewInsertUsbPort());
	if(strPort.empty())
		return false;

	int pos = 0;
	int x = -1;
	int y = -1;
	FindPos(x, y);
	if(x == -1 || y == -1)
	{
		return false;
	}


	int index = GetWndIndexByRowCol(x, y);

	//校验--pos已定位,或新定位
	if( CheckIsDericted(strPort, x, y))
		return false;

	//改变颜色
	CDvrWnd* dvr = m_vecDvrWnd[index];
	if(dvr == NULL)
	{
		dvr = new CDvrWnd;
	}
	dvr->SetStatus(DVR_DERICT);

	CDuiString str;
	str.Format(_T("请选择当前DVR设置插入的位置, 当前位置: %d, %d"), x+1, y+1);
	SHAREDATA.g_pMainFrame->ShowMsgInfo(str);

	dvr->SetStatusStr(_T("成功定位, 可以安全拔出!"));

	//定位成功马上保存
	SaveDvrPos(strPort, index);

	return true;
}


//检查是否已定位
//如果已定位，返回值指示是否用新的定位替换旧的定位
bool CDvrLocation::CheckIsDericted(const wstring& strPort, int x, int y)
{
	int row = -1;
	int col = -1;
	if(!GetRowCol(strPort, row, col))
		return false;

	if(x == row && y == col)
		return true;

	CString strMsg;
	strMsg.Format(_T("此接口已定位为位置(%d,%d)! \r\n新的定位为(%d,%d)！\r\n确认使用新定位吗？"), row + 1, col + 1, x + 1, y + 1);
	bool isOk = SHAREDATA.g_pMainFrame->Alert(strMsg);
	if(!isOk)
	{
		m_xx = row;
		m_yy = col;
		return true;
	}

 	//替换成旧的dvr
 	int indexOld = GetWndIndexByRowCol(row, col);
 	CDvrWnd* dvrOld = m_vecDvrWnd[indexOld];
	dvrOld->ClearInfo();

	return false;
}

void CDvrLocation::SaveDvrPos( const wstring& strPort, int nWndIndex)
{
	if( nWndIndex == -1)
		return;

	int row = nWndIndex / SHAREDATA.g_dvrProp.numCol;
	int col = nWndIndex % SHAREDATA.g_dvrProp.numCol;

	int nIndex = ((row + 1) * 10)  + (col + 1);

	//存配置文件
	LOCATIONCONF.SaveDvrPos(strPort, nIndex);

	CString strDef;
	strDef.Format(_T("保存威尔DVR位置 %02d 成功"), nIndex);
	SHAREDATA.g_pMainFrame->ShowMsgInfo(strDef.GetBuffer(strDef.GetLength()));
	strDef.ReleaseBuffer();
}

void CDvrLocation::RemoveDvr()
{
	wstring strPort = USBHUB.GetRemoveUsbPort();
	if(strPort.empty())
		return;

	int index = GetWndIndex(strPort);
	if(index == -1)
		return;

	CDvrWnd *dvr = m_vecDvrWnd[index];
	if(dvr)
	{
		dvr->SetStatusStr(_T("成功定位, 保存成功!"));
		dvr->SetStatus(DVR_DISABLE);
	}
}
