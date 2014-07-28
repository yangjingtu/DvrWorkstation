#pragma once
class CFtpObj
{
public:
	CFtpObj(void);
	~CFtpObj(void);

public:
	//是否启用
	bool m_bEnable;
	//IP
	CString m_strIp;
	//端口
	CString m_strPort;
	//用户
	CString m_strUser;
	//密码
	CString m_strPwd;
	//传输重要视频
	bool m_bTransImp;
	//传输高清视频
	bool m_bTransHd;
	//传输标清视频
	bool m_bTransSd;

	//传输后是否删除
	bool m_bDelAfterTrans;
};

