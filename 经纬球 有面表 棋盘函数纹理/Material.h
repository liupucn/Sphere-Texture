#pragma once
#include "RGBA.h"

class CMaterial
{
public:
	CMaterial(void);
	virtual~CMaterial(void);
	void SetAmbient(CRGBA c);//设置环境反射率	
	void SetDiffuse(CRGBA c);//设置漫反射率
	void SetSpecular(CRGBA c);//设置镜面反射率
	void SetExponent(double n);//设置高光指数
public:
	CRGBA M_Ambient;//环境反射率
	CRGBA M_Diffuse;//漫反射反射率
	CRGBA M_Specular;//镜面反射率
	double M_n;//高光指数
};