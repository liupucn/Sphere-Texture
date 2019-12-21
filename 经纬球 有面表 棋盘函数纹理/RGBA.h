#pragma once

class CRGBA
{
public:
	CRGBA(void);
	CRGBA(double red, double green, double blue, double alpha = 0.0);
	virtual ~CRGBA (void);
	friend CRGBA operator + (const CRGBA &c0, const CRGBA &c1);//���������
	friend CRGBA operator - (const CRGBA &c0, const CRGBA &c1);
	friend CRGBA operator * (const CRGBA &c0, const CRGBA &c1);
	friend CRGBA operator * (const CRGBA &c, double scalar);
	friend CRGBA operator * (double scalar,const CRGBA &c);
	friend CRGBA operator / (const CRGBA &c, double scalar);
	friend CRGBA operator += (CRGBA &c1, CRGBA &c2);
	friend CRGBA operator -= (CRGBA &c1, CRGBA &c2);
	friend CRGBA operator *= (CRGBA &c1, CRGBA &c2);
	friend CRGBA operator /= (CRGBA &c1, double scalar);
	void Normalize(void);//�淶����[0,1]����
public:
	double red;//��ɫ����
	double green;//��ɫ����
	double blue;//��ɫ����
	double alpha;//alpha����
};

