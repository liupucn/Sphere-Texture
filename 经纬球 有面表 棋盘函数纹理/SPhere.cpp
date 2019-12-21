#include "StdAfx.h"
#include "Sphere.h"
#include "math.h"//包含数学头文件
#define  PI 3.1415926//PI的宏定义
#define Round(d) int(floor(d + 0.5))//四舍五入宏定义

CSphere::CSphere(void)
{
	V = NULL;
	F = NULL;
}

CSphere::~CSphere(void)
{
	if(NULL != V)
	{
		delete []V;
		V = NULL;
	}
	if (NULL != T)
	{
		delete[]T;
		T = NULL;
	}
	if(NULL != F)
	{
		for(int n = 0; n < N1; n++)
		{
			delete []F[n];
			F[n] = NULL;
		}
		delete []F;
		F = NULL;
	}
}

void CSphere::SetParameter(int nRadius)
{
	r = nRadius;
}

void CSphere::SetScene(CLighting* pLight, CMaterial* pMaterial)
{
	this->pLight = pLight;
	this->pMaterial = pMaterial;
}

void CSphere::ReadVertex(void)//点表
{
	Alpha = 5, Beta = 5;//面片夹角
	N1 = 180 / Alpha, N2 = 360 / Beta;
	V = new CP3[(N1 - 1) * N2 + 2];//球的顶点
	T = new CT2[(N1 - 1) * N2 + 2];//球的纹理
	nVertex = (N1 - 1) * N2 + 2;
	double Alpha1, Beta1;//夹角增量
	//计算北极点坐标
	V[0].x = 0, V[0].y = r, V[0].z = 0;
	T[0].u = 0; T[0].v = 0;
	//按行循坏计算球体上的点的坐标
	for(int i = 0; i < N1 - 1; i++)
	{
		Alpha1 = (i + 1) * Alpha * PI / 180;
		for (int j = 0; j < N2; j++)
		{
			Beta1 = j * Beta * PI / 180;
			V[i * N2 + j + 1].x = r * sin(Alpha1) * sin(Beta1);
			V[i * N2 + j + 1].y = r * cos(Alpha1);
			V[i * N2 + j + 1].z = r * sin(Alpha1) * cos(Beta1);
			T[i * N2 + j + 1].u = Beta1 / (2 * PI);
			T[i * N2 + j + 1].v = (PI - Alpha1) / PI;
		}
	}
	//计算南极点坐标
	V[(N1 - 1) * N2 + 1].x = 0, V[(N1 - 1) * N2 + 1].y = -r, V[(N1 - 1) * N2 + 1].z = 0;
	T[(N1 - 1) * N2 + 1].u = 0; T[(N1 - 1) * N2 + 1].v = 0;
}

void CSphere::ReadFacet(void)//面表
{
	//设置二维动态数组
	F = new CFacet *[N1];//设置行
	for(int n = 0; n < N1; n++)
		F[n] = new CFacet[N2];//设置列
	for(int j = 0; j < N2; j++)//构造北极三角形面片
	{
		int tempj = j + 1;
		if(N2 == tempj) 
			tempj = 0;//面片的首尾连接
		int NorthIndex[3];//北极三角形面片索引号数组
		NorthIndex[0] = 0;
		NorthIndex[1] = j+1;
		NorthIndex[2] = tempj + 1;
		F[0][j].SetVertexNumber(3);
		for(int k = 0; k < F[0][j].vNumber; k++)
			F[0][j].vIndex[k] = NorthIndex[k];
	}
	for(int i = 1; i < N1 - 1; i++)//构造球面四边形面片
	{
		for(int j = 0; j < N2; j++)
	    {
			int tempi = i + 1;
			int tempj = j + 1;
			if(N2 == tempj) 
				tempj = 0;//面片的首尾连接
			int BodyIndex[4];//球面四边形面片索引号数组
			BodyIndex[0] = (i - 1) * N2 + j + 1;
			BodyIndex[1] = (tempi - 1) * N2 + j + 1;
			BodyIndex[2] = (tempi - 1) * N2 + tempj + 1;
			BodyIndex[3] = (i - 1) * N2 + tempj + 1;
			F[i][j].SetVertexNumber(4);
			for(int k = 0; k < F[i][j].vNumber; k++)
				F[i][j].vIndex[k] = BodyIndex[k];
		}
	}
	for(int j = 0; j < N2; j++)//构造南极三角形面片
	{
		int tempj = j + 1;
		if(N2 == tempj) 
			tempj = 0;//面片的首尾连接
		int SouthIndex[3];//南极三角形面片索引号数组
		SouthIndex[0] = (N1 - 2) * N2 + j + 1;
		SouthIndex[1] = (N1 - 1) * N2 + 1;
		SouthIndex[2] = (N1 - 2) * N2 + tempj + 1;
		F[N1-1][j].SetVertexNumber(3);	
		for(int k = 0; k < F[N1-1][j].vNumber; k++)
			F[N1-1][j].vIndex[k] = SouthIndex[k];
	}
}

void CSphere::Draw(CDC* pDC)
{
	CTriangle* pFill = new CTriangle;//申请内存
	CP3 Point[4];
	CVector3 Normal[4];
	CT2 Texture[4];
	CP3 ViewPoint = projection.GetEye();
	for (int i = 0; i < N1; i++)
	{
		for (int j = 0; j < N2; j++)
		{
			CVector3 ViewVector(V[F[i][j].vIndex[0]], ViewPoint);//面的视矢量
			ViewVector=ViewVector.Normalize();//单位化视矢量
			F[i][j].SetFacetNormal(V[F[i][j].vIndex[0]], V[F[i][j].vIndex[1]], V[F[i][j].vIndex[2]]);
			CVector3 FacetNormal = F[i][j].fNormal.Normalize();//单位化法矢量
			double dotproduct = DotProduct(ViewVector, FacetNormal);
			if (dotproduct >= 0)//背面剔除算法
			{
				if(3==F[i][j].vNumber)//处理三角形面片
				{
					for(int m=0;m<F[i][j].vNumber;m++)
					{
						Point[m] = projection.PerspectiveProjection(V[F[i][j].vIndex[m]]);
						Normal[m]=CVector3(V[F[i][j].vIndex[m]]);
						Texture[m] = T[F[i][j].vIndex[m]];
					}
					double tempi=i+1,tempj=j+1;//对三角形面片进行特殊处理
					Texture[0].u=Beta*(j)/360.0;Texture[0].v=(1.0-Alpha*i/180.0);
					Texture[1].u=Beta*(j)/360.0;Texture[1].v=(1.0-Alpha*tempi/180.0);
					Texture[2].u=Beta*tempj/360.0;Texture[2].v=(1.0-Alpha*i/180.0);
					pFill->SetPoint(Point[0], Point[1], Point[2], Normal[0], Normal[1], Normal[2], Texture[0], Texture[1], Texture[2]);
					pFill->PhongShading(pDC, ViewPoint, pLight, pMaterial);
				}
				else//处理四边形面片
				{
					for(int m=0;m<F[i][j].vNumber;m++)
					{
						Point[m] = projection.PerspectiveProjection(V[F[i][j].vIndex[m]]);
						Normal[m] = CVector3(V[F[i][j].vIndex[m]]);
						Texture[m] = T[F[i][j].vIndex[m]];
					}
					if(N2-1==j)//消除图像纹理的接缝
					{
						Texture[2].u = 1;
						Texture[3].u = 1;
					}
					pFill->SetPoint(Point[0], Point[1], Point[2], Normal[0], Normal[1], Normal[2],Texture[0], Texture[1], Texture[2]);
					pFill->PhongShading(pDC, ViewPoint, pLight, pMaterial);
					pFill->SetPoint(Point[0], Point[2], Point[3], Normal[0], Normal[2], Normal[3], Texture[0], Texture[2], Texture[3]);
					pFill->PhongShading(pDC, ViewPoint, pLight, pMaterial);
				}		
			}
		}
	}
	delete pFill;
}
