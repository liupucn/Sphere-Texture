#pragma once
class CPatch
{
public:
	CPatch(void);
	virtual ~CPatch(void);
	void SetPtNumber(int ptN);//������Ķ�����
public:
	int ptN; //��Ķ�����
	int* ptI;//��Ķ�������
};

