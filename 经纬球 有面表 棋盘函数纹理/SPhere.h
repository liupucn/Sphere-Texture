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
	void SetParameter(int nRadius);//设置球体半径
	void SetScene(CLighting* pLight, CMaterial* pMaterial);//设置场景
	void ReadVertex(void);//读入点表
	void ReadFacet(void);//读入面表
	void Draw(CDC* pDC);//绘制图形	
public:	
	int r;//球体半径
	int Alpha, Beta;
	CP3* V;//点表数组
	int nVertex;//顶点数
	int N1, N2;//N1为纬度区域,N2为经度区域
	CFacet** F;//面表数组
	CT2* T;//纹理坐标
	CLighting* pLight;//光照
	CMaterial* pMaterial;//材质	
	CProjection projection;//投影
};

