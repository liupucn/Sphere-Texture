#include "StdAfx.h"
#include "Material.h"

CMaterial::CMaterial(void)
{
	M_Ambient = CRGBA(0.2, 0.2, 0.2);//环境反射率
	M_Diffuse = CRGBA(0.8, 0.8, 0.8);//漫反射率
	M_Specular = CRGBA(0.0, 0.0, 0.0);//镜面反射率
	M_n = 1.0;//高光指数
}

CMaterial::~CMaterial(void)
{
}

void CMaterial::SetAmbient(CRGBA c)
{
	M_Ambient = c;
}

void CMaterial::SetDiffuse(CRGBA c)
{
	M_Diffuse = c;
}

void CMaterial::SetSpecular(CRGBA c)
{
	M_Specular = c;
}

void CMaterial::SetExponent(double n)
{
	M_n = n;
}
