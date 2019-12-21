#include "StdAfx.h"
#include "LightSource.h"


CLightSource::CLightSource(void)
{
	L_Diffuse = CRGBA(0.0, 0.0, 0.0);//光源的漫反射光	
	L_Specular = CRGBA(1.0, 1.0, 1.0);//光源镜面反射光
	L_Position.x = 0.0, L_Position.y = 0.0, L_Position.z = 1000.0;//光源位置直角坐标
	L_C0 = 1.0;//常数衰减因子
	L_C1 = 0.0;//线性衰减因子
	L_C2 = 0.0;//二次衰减因子
	L_OnOff = TRUE;//光源开启
}

CLightSource::~CLightSource(void)
{
}

void CLightSource::SetDiffuse(CRGBA difuse)
{
	L_Diffuse = difuse;
}

void CLightSource::SetSpecular(CRGBA specular)
{
	L_Specular = specular;
}

void CLightSource::SetPosition(double x, double y, double z)
{
	L_Position.x = x;
	L_Position.y = y;
	L_Position.z = z;
}

void CLightSource::SetPosition(CP3 position)
{
	L_Position = position;
}

void CLightSource::SetOnOff(BOOL onoff)
{
	L_OnOff = onoff;
}

void CLightSource::SetAttenuationFactor(double c0, double c1, double c2)
{
	L_C0 = c0;
	L_C1 = c1;
	L_C2 = c2;
}