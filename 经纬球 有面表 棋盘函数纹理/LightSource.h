#pragma once
#include "P3.h"

class CLightSource
{
public:
	CLightSource(void);
	virtual ~CLightSource(void);
	void SetDiffuse(CRGBA diffuse);//�����������
	void SetSpecular(CRGBA specular);//���þ��淴���
	void SetPosition(double x, double y, double z);//����ֱ������λ��
	void SetPosition(CP3 position);//����ֱ������λ��
	void SetAttenuationFactor(double c0, double c1, double c2);//���ù�ǿ��˥������
	void SetOnOff(BOOL onoff);//���ù�Դ����״̬
public:
	CRGBA L_Diffuse;//�������	
	CRGBA L_Specular;//���淴���
	CP3 L_Position;//��Դλ��
	double L_C0;//����˥������
	double L_C1;//����˥������
	double L_C2;//����˥������
	BOOL L_OnOff;//��Դ����
};