#include "StdAfx.h"
#include "Patch.h"


CPatch::CPatch(void)
{
}


CPatch::~CPatch(void)
{
	if(NULL != ptI)
	{
		delete []ptI;
		ptI = NULL;
	}
}

void CPatch::SetPtNumber(int ptN)
{
	this->ptN = ptN;
	ptI = new int[ptN];
}
