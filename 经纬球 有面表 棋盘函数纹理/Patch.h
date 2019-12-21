#pragma once
class CPatch
{
public:
	CPatch(void);
	virtual ~CPatch(void);
	void SetPtNumber(int ptN);//设置面的顶点数
public:
	int ptN; //面的顶点数
	int* ptI;//面的顶点索引
};

