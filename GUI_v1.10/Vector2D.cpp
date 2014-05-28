// Vector2D.cpp: implementation of the CVector2D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Vector2D.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVector2D::CVector2D()
{
	x = 0;
	y = 0;
}

CVector2D::CVector2D(double dx,double dy)
{
	x = dx;
	y = dy;
}

CVector2D::CVector2D(const CVector2D& v)
{
	x = v.x;
	y = v.y;
}

CVector2D::CVector2D(CPoint pB,CPoint pE)
{
	x = pE.x-pB.x;
	y = pE.y-pB.y;
}

void CVector2D::normalize()
{
	double nMagnitude = magnitude();
	x = x/nMagnitude;
	y = y/nMagnitude;
}

CVector2D & CVector2D::operator = (const CVector2D &vect)
{
	x = vect.x;
	y = vect.y;
	return *this;
}

CVector2D CVector2D::operator + (const CVector2D &vect)
{
	CVector2D temp;
	temp.x = x + vect.x;
	temp.y = y + vect.y;
	return temp;
}

double CVector2D::operator * (const CVector2D &vect)
{
	return x*vect.x + y*vect.y;
}

CVector2D CVector2D::operator - (const CVector2D &vect)
{
	CVector2D temp;
	temp.x = x - vect.x;
	temp.y = y - vect.y;
	return temp;
}

double CVector2D::magnitude()
{
	return sqrt(x*x+y*y);
}

CVector2D & CVector2D::operator *= (const double nScale)
{
	x *= nScale;
	y *= nScale;
	return *this;
}

CVector2D::CVector2D(CPoint point)
{
	x = point.x;
	y = point.y;
}
