#pragma once
class CDevBase;

#define CREATE_DVR  CDvrFactory::Instance().GetDvr()

class CDvrFactory
{
private:
	CDvrFactory(void);
	~CDvrFactory(void);

public:
	static CDvrFactory& Instance();

	CDevBase* GetDvr();

protected:
	CDevBase* DetectDvr();
};

