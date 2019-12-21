#include "StdAfx.h"
#include "Triangle.h"
#include "math.h"
#define Round(d) int(floor(d + 0.5))

CTriangle::CTriangle(void)
{

}

CTriangle::~CTriangle(void)
{

}

void CTriangle::SetPoint(CP3 P0, CP3 P1, CP3 P2, CVector3 N0, CVector3 N1, CVector3 N2)//三角形初始化
{
	this->P0 = P0, this->P1 = P1, this->P2 = P2;
	point0.x = Round(P0.x);
	point0.y = Round(P0.y);
	point0.z = P0.z;
	point0.c = P0.c;
	point0.n = N0;
	point1.x = Round(P1.x);
	point1.y = Round(P1.y);
	point1.z = P1.z;
	point1.c = P1.c;
	point1.n = N1;
	point2.x = Round(P2.x);
	point2.y = Round(P2.y);
	point2.z = P2.z;
	point2.c = P2.c;
	point2.n = N2;
}

void CTriangle::SetPoint(CP3 P0, CP3 P1, CP3 P2, CVector3 N0, CVector3 N1, CVector3 N2, CT2 T0, CT2 T1, CT2 T2)
{
	this->P0 = P0, this->P1 = P1, this->P2 = P2;
	point0.x = Round(P0.x);
	point0.y = Round(P0.y);
	point0.z = P0.z;
	point0.c = P0.c;
	point0.n = N0;
	point0.t = T0;
	point1.x = Round(P1.x);
	point1.y = Round(P1.y);
	point1.z = P1.z;
	point1.c = P1.c;
	point1.n = N1;
	point1.t = T1;
	point2.x = Round(P2.x);
	point2.y = Round(P2.y);
	point2.z = P2.z;
	point2.c = P2.c;
	point2.n = N2;
	point2.t = T2;
}

void CTriangle::PhongShading(CDC* pDC, CP3 ViewPoint, CLighting* pLight, CMaterial* pMaterial)
{
	double	CurrentDepth = 0.0;//当前扫描线的深度
	CVector3 Vector01(P0, P1), Vector02(P0, P2);
	CVector3 fNormal = CrossProduct(Vector01, Vector02);
	double A = fNormal.x, B = fNormal.y, C = fNormal.z;//平面方程Ax+By+Cz＋D=0的系数
	double D = -A * P0.x - B * P0.y - C * P0.z;//当前扫描线随着x增长的深度步长
	if (fabs(C) < 1e-4)
		C = 1.0;
	double DepthStep = -A / C;//计算扫描线深度步长增量
	//三点能构成三角形
	if (point0 != point1 && point0 != point2 && point1 != point2)	//重载了 ！= 运算符
	{
		//point0点为y坐标最小的点,point1点为y坐标最大的点,point2点的y坐标位于二者之间。如果y值相同，取x最小的点
		SortVertex();
		//定义三角形覆盖的扫描线条数
		int nTotalLine = point1.y - point0.y + 1;
		//定义span的起点与终点数组
		pLeft = new CPoint3[nTotalLine];
		pRight = new CPoint3[nTotalLine];
		//判断三角形与P0P1边的位置关系，0-1-2为右手系
		int nDeltz = (point1.x - point0.x) * (point2.y - point1.y) - (point1.y - point0.y) * (point2.x - point1.x);//点矢量叉积的z坐标
		if (nDeltz > 0)//三角形位于P0P1边的左侧
		{
			nIndex = 0;
			EdgeFlag(point0, point2, TRUE);
			EdgeFlag(point2, point1, TRUE);
			nIndex = 0;
			EdgeFlag(point0, point1, FALSE);
		}
		else//三角形位于P0P1边的右侧
		{
			nIndex = 0;
			EdgeFlag(point0, point1, TRUE);
			nIndex = 0;
			EdgeFlag(point0, point2, FALSE);
			EdgeFlag(point2, point1, FALSE);
		}
		for (int y = point0.y; y < point1.y; y++)//下闭上开
		{
			int n = y - point0.y;
			BOOL bInFlag = FALSE;//跨度内外测试标志，初始值为假表示三角形外部
			for (int x = pLeft[n].x; x < pRight[n].x; x++)//左闭右开
			{
				if (bInFlag == FALSE)
				{
					CurrentDepth = -(A*x + B * y + D) / C;//z=-(Ax+By+D)/C
					bInFlag = TRUE;
					x -= 1;
				}
				else
				{
					CVector3 ptNormal = LinearInterp(x, pLeft[n].x, pRight[n].x, pLeft[n].n, pRight[n].n);
					CT2 Texture = LinearInterp(x, pLeft[n].x, pRight[n].x, pLeft[n].t, pRight[n].t);
					//颜色纹理
					CRGBA TextureColor = GetTextureColor(Texture.u, Texture.v);
					pMaterial->SetDiffuse(TextureColor);//用纹理颜色作为材质的漫反射光反射率
					pMaterial->SetAmbient(TextureColor);//用纹理颜色作为材质的环境光反射率

					CRGBA clr = pLight->Illuminate(ViewPoint, CP3(Round(x), y, CurrentDepth), ptNormal, pMaterial);
					pDC->SetPixelV(x, y, RGB(clr.red * 255, clr.green * 255, clr.blue * 255));
				}
			}
		}
		if (pLeft)
		{
			delete[]pLeft;
			pLeft = NULL;
		}
		if (pRight)
		{
			delete[]pRight;
			pRight = NULL;
		}
	}
}

CRGBA CTriangle::GetTextureColor(double u, double v)//获得纹理颜色
{
	if (0 == (int(floor(u * 32.0)) + int(floor(v * 16.0))) % 2)
		return CRGBA(0.1, 0.1, 0.1);
	else
		return CRGBA(0.9, 0.9, 0.9);
}

void CTriangle::EdgeFlag(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature)
{
	CVector3 ptNormal = PStart.n;
	CT2 ptTexture = PStart.t;
	int dx = abs(PEnd.x - PStart.x);
	int dy = abs(PEnd.y - PStart.y);
	BOOL bInterChange = FALSE;//bInterChange为假，主位移方向为x方向
	int e, s1, s2, temp;
	s1 = (PEnd.x > PStart.x) ? 1 : ((PEnd.x < PStart.x) ? -1 : 0);
	s2 = (PEnd.y > PStart.y) ? 1 : ((PEnd.y < PStart.y) ? -1 : 0);
	if (dy > dx)//bInterChange为真，主位移方向为y方向
	{
		temp = dx;
		dx = dy;
		dy = temp;
		bInterChange = TRUE;
	}
	e = -dx;
	int x = PStart.x, y = PStart.y;
	for (int i = 0; i < dx; i++)
	{
		if (bFeature)
			pLeft[nIndex] = CPoint2(x, y, ptNormal, ptTexture);
		else
			pRight[nIndex] = CPoint2(x, y, ptNormal, ptTexture);
		if (bInterChange)
		{
			y += s2;
			ptNormal = LinearInterp(y, PStart.y, PEnd.y, PStart.n, PEnd.n);
			ptTexture = LinearInterp(y, PStart.y, PEnd.y, PStart.t, PEnd.t);//插值边任意一点纹理坐标
			if (bFeature)
				pLeft[++nIndex] = CPoint2(x, y, ptNormal, ptTexture);
			else
				pRight[++nIndex] = CPoint2(x, y, ptNormal, ptTexture);
		}
		else
		{
			x += s1;
			ptNormal = LinearInterp(x, PStart.x, PEnd.x, PStart.n, PEnd.n);
			ptTexture = LinearInterp(x, PStart.x, PEnd.x, PStart.t, PEnd.t);
		}
		e += 2 * dy;
		if (e >= 0)
		{
			if (bInterChange)
			{
				x += s1;
				ptNormal = LinearInterp(y, PStart.y, PEnd.y, PStart.n, PEnd.n);
				ptTexture = LinearInterp(y, PStart.y, PEnd.y, PStart.t, PEnd.t);
			}
			else
			{
				y += s2;
				ptNormal = LinearInterp(x, PStart.x, PEnd.x, PStart.n, PEnd.n);
				ptTexture = LinearInterp(x, PStart.x, PEnd.x, PStart.t, PEnd.t);
				if (bFeature)
					pLeft[++nIndex] = CPoint2(x, y, ptNormal, ptTexture);
				else
					pRight[++nIndex] = CPoint2(x, y, ptNormal, ptTexture);
			}
			e -= 2 * dx;
		}
	}
}

CVector3 CTriangle::LinearInterp(double t, double tStart, double tEnd, CVector3 vStart, CVector3 vEnd)//法矢量线性插值
{
	CVector3 vector;
	vector = (tEnd - t) / (tEnd - tStart) * vStart + (t - tStart) / (tEnd - tStart) * vEnd;
	return vector;
}

CT2 CTriangle::LinearInterp(double t, double coorStart, double coorEnd, CT2 textureStart, CT2 textureEnd)//纹理线性插值
{
	CT2 texture;
	texture = (t - coorEnd) / (coorStart - coorEnd) * textureStart + (t - coorStart) / (coorEnd - coorStart) * textureEnd;
	return texture;
}

void CTriangle::SortVertex(void)
{
	CPoint3 p[3];
	p[0] = point0;
	p[1] = point1;
	p[2] = point2;
	for (int i = 0; i < 2; ++i)
	{
		int k = i;
		for (int j = i + 1; j < 3; ++j)
		{
			if (p[k].y > p[j].y)
				k = j;
			if (p[k].y == p[j].y)
				if (p[k].x > p[j].x)
					k = j;
		}
		if (k != i)
		{
			CPoint3 pTemp = p[i];
			p[i] = p[k];
			p[k] = pTemp;
		}
	}
	point0 = p[0];
	point1 = p[2];
	point2 = p[1];
}