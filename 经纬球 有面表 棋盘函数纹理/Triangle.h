#pragma once
#include "P3.h"
#include "Point3.h"
#include "Lighting.h"

class CTriangle
{
public:
	CTriangle(void);
	virtual ~CTriangle(void);
	void SetPoint(CP3 P0, CP3 P1, CP3 P2, CVector3 N0, CVector3 N1, CVector3 N2);//三角形初始化
	void SetPoint(CP3 P0, CP3 P1, CP3 P2, CVector3 N0, CVector3 N1, CVector3 N2, CT2 T0, CT2 T1, CT2 T2);// 三角形初始化
	void PhongShading(CDC* pDC, CP3 ViewPoint, CLighting* pLight, CMaterial* pMaterial);//Phong明暗处理填充三角形
	CRGBA GetTextureColor(double u, double v);//获得纹理颜色
	void EdgeFlag(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature);//为边做标记
	CVector3 LinearInterp(double t, double tStart, double tEnd, CVector3 vStart, CVector3 vEnd);//法矢量线性插值
	CT2 LinearInterp(double t, double coorStart, double coorEnd, CT2 textureStart, CT2 textureEnd);//纹理线性插值
	void SortVertex(void);//顶点排序
private:
	CP3 P0, P1, P2;//三角形的浮点数顶点坐标
	CPoint3 point0, point1, point2;//三角形的整数顶点坐标	
	CPoint2* pLeft; //跨度的起点数组标志
	CPoint2* pRight;//跨度的终点数组标志
	int nIndex;//记录扫描线条数

};