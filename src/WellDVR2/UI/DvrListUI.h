#pragma once
#include "../DvrWnd.h"
#include <map>
using namespace std;

using namespace DuiLib;

//每一个DVR项的控件指针
typedef struct tagDvrItemCtrl{
	//三个顶子元不素
	CVerticalLayoutUI* pImg;
	CVerticalLayoutUI* pLabel;
	CVerticalLayoutUI* pValue;

	//图片中的标签（无设备）
	CLabelUI* pDev;

	//ID
	CLabelUI* pId;
	//Name
	CLabelUI* pName;
	//盘符
	CLabelUI* pDisk;
	//进度条
	CProgressUI* pProgress;
	CLabelUI* pSpeed;
	//状态
	CLabelUI* pStatus;
	CLabelUI* pFile;
	//停止传输的按钮
	CButtonUI* pStop;
}DvrItemCtrl, *PDvrItemCtrl;

//<窗口索引， 每个项的指针>
typedef map<int, DvrItemCtrl> MapDvrCtrl;
typedef MapDvrCtrl::iterator MapDvrCtrlItor;

class DvrListUI : public CTileLayoutUI
{
public:
	enum { SCROLL_TIMERID = 10 };

	DvrListUI();

	void DoEvent(TEventUI& event);

	void SetPos(RECT rc);

	void BKColor(int row, int column, DWORD boderColor, DWORD bkcolor);

	//设置Dvr信息，显示出来
	void SetInfo(int row, int col, CDvrWnd* dvr);
	void ClearInfo(int row, int col);	
	void ClearAllInfo();

	//获取选中的位置
	void GetSelectPos(int& row, int& col);
	void ClearSelectPos();

	void OnBtnClick(TNotifyUI& msg);
private:
	//调整DVR的位置（充满客户区)
	void SetDvrPos(RECT rc);

	void OnClick(const POINT& pt);

	CControlUI* HitPtInItem(const POINT& pt);

	void HitItem(CControlUI* pItem);

	//根据行列获取对应项
	CContainerUI* GetItem(int row, int col);

	//获取指定行列的控件指针对象
	DvrItemCtrl GetDvrItemCtrl(int row, int col);

	DvrItemCtrl InitDvrItemCtrl(int row, int col);

	void SetInfo_Active(const DvrItemCtrl& dic, CDvrWnd* pDvr);
	void SetInfo_Nomal(const DvrItemCtrl& dic, CDvrWnd* pDvr);
	void SetInfo_Disable(const DvrItemCtrl& dic, CDvrWnd* pDvr);
	void SetInfo_Direct(const DvrItemCtrl& dic, CDvrWnd* pDvr);
	void SetInfo_Copy(const DvrItemCtrl& dic, CDvrWnd* pDvr);
	void SetInfo_Copy_OK(const DvrItemCtrl& dic, CDvrWnd* pDvr);
	void SetInfo_Stop(const DvrItemCtrl& dic, CDvrWnd* pDvr);
private:
	//选择的行列,从0开始
	int m_selectRow;
	int m_selectCol;

	MapDvrCtrl m_mapItem;
};