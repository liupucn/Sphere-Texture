#pragma once
#include "Facet.h"
#include "Lighting.h"
#include "Material.h"
#include "Triangle.h"
#include "Projection.h"

class CSphere
{
public:
	CSphere(void);
	virtual ~CSphere(void);
	void SetParameter(int nRadius);//��������뾶
	void SetScene(CLighting* pLight, CMaterial* pMaterial);//���ó���
	void ReadVertex(void);//������
	void ReadFacet(void);//�������
	void Draw(CDC* pDC);//����ͼ��	
public:	
	int r;//����뾶
	int Alpha, Beta;
	CP3* V;//�������
	int nVertex;//������
	int N1, N2;//N1Ϊγ������,N2Ϊ��������
	CFacet** F;//�������
	CT2* T;//��������
	CLighting* pLight;//����
	CMaterial* pMaterial;//����	
	CProjection projection;//ͶӰ
};

