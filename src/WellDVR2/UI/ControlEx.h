#ifndef __CONTROLEX_H__
#define __CONTROLEX_H__

#include <vector>
#include <math.h>

#include "DvrListUI.h"

class CDialogBuilderCallbackEx : public IDialogBuilderCallback
{
public:
    CControlUI* CreateControl(LPCTSTR pstrClass) 
    {
        if( _tcscmp(pstrClass, _T("DvrList")) == 0 ) 
		{
			return new DvrListUI;
		}
        return NULL;
    }
};


#endif __CONTROLEX_H__
