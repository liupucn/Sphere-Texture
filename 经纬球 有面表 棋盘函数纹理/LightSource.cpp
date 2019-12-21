#include "StdAfx.h"
#include "LightSource.h"


CLightSource::CLightSource(void)
{
	L_Diffuse = CRGBA(0.0, 0.0, 0.0);//��Դ���������	
	L_Specular = CRGBA(1.0, 1.0, 1.0);//��Դ���淴���
	L_Position.x = 0.0, L_Position.y = 0.0, L_Position.z = 1000.0;//��Դλ��ֱ������
	L_C0 = 1.0;//����˥������
	L_C1 = 0.0;//����˥������
	L_C2 = 0.0;//����˥������
	L_OnOff = TRUE;//��Դ����
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