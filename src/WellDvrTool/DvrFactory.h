#pragma once

class CDevBase;

class CDvrFactory
{
public:
	CDvrFactory(void);
	~CDvrFactory(void);

	static CDevBase* GetDvr();
};

