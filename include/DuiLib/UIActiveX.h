#ifndef __UIACTIVEX_H__
#define __UIACTIVEX_H__

#define REQUEST_UIACTIVATE				  WM_USER + 10000

#pragma once
#include <mshtmhst.h>
#include "downloadmgr.h"
struct IOleObject;


namespace DuiLib {
/////////////////////////////////////////////////////////////////////////////////////
//

class CActiveXCtrl;

template< class T >
class CSafeRelease
{
public:
    CSafeRelease(T* p) : m_p(p) { };
    ~CSafeRelease() { if( m_p != NULL ) m_p->Release(); };
    T* Detach() { T* t = m_p; m_p = NULL; return t; };
    T* m_p;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CActiveXUI : public CControlUI, public IMessageFilterUI
{
    friend class CActiveXCtrl;
public:
    CActiveXUI();
    virtual ~CActiveXUI();

    LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

    HWND GetHostWindow() const;

    bool IsDelayCreate() const;
    void SetDelayCreate(bool bDelayCreate = true);

    bool CreateControl(const CLSID clsid);
    bool CreateControl(LPCTSTR pstrCLSID);
    HRESULT GetControl(const IID iid, LPVOID* ppRet);
	CLSID GetClisd() const;
    CStdString GetModuleName() const;
    void SetModuleName(LPCTSTR pstrText);

    void SetVisible(bool bVisible = true);
    void SetInternVisible(bool bVisible = true);
    void SetPos(RECT rc);
    void DoPaint(HDC hDC, const RECT& rcPaint);

    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void SetExternalUIHandler(IDocHostUIHandler* handler);
	void SetDownloadManager(IDownloadManager* handler);
	void SetDispatchHandler(IDispatch* handler);

	void SetHwnd(HWND hwnd){m_hwnd = hwnd;}
	HWND GetHwnd(){return m_hwnd;}

    LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

protected:
    virtual void ReleaseControl();
    virtual bool DoCreateControl();

protected:
    CLSID m_clsid;
    CStdString m_sModuleName;
    bool m_bCreated;
    bool m_bDelayCreate;
    IOleObject* m_pUnk;
    CActiveXCtrl* m_pControl;
    HWND m_hwndHost;	
	IDocHostUIHandler* m_HostUIHandler;
	IDownloadManager* m_pDownMan;
	IDispatch*	m_pHostDispatch;
	
private:
	HWND m_hwnd;
};

} // namespace DuiLib

#endif // __UIACTIVEX_H__
