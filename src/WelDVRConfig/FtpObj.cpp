#include "StdAfx.h"
#include "FtpObj.h"


CFtpObj::CFtpObj(void)
	: m_bTransImp(false)
	, m_bTransHd(false)
	, m_bTransSd(false)
	, m_bDelAfterTrans(false)
{

}


CFtpObj::~CFtpObj(void)
{
}
