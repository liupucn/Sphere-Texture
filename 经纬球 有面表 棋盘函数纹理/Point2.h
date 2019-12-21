#pragma once
#include "RGBA.h"
#include "Vector3.h"
#include "T2.h"

class CPoint2
{
public:
	CPoint2(void);	
	CPoint2(int x, int y);
	CPoint2(int x, int y, CRGBA c);
	CPoint2(int x, int y, CVector3 n);
	CPoint2(int x, int y, CVector3 n, CT2 t);
	virtual ~CPoint2(void);
	friend CPoint2 operator + (const CPoint2 &pt0, const CPoint2 &pt1);//‘ÀÀ„∑˚÷ÿ‘ÿ
	friend CPoint2 operator - (const CPoint2 &pt0, const CPoint2 &pt1);
	friend CPoint2 operator * (int scalar, const CPoint2 &pt);
	friend BOOL operator != (const CPoint2 pt0, const CPoint2 pt1);	
public:
	int x; 
	int y;
	CRGBA c;
	CVector3 n;
	CT2 t;
};