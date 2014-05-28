// Vector2D.h: interface for the CVector2D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTOR2D_H__8B453F0B_7245_11D7_A984_F4212B4C3035__INCLUDED_)
#define AFX_VECTOR2D_H__8B453F0B_7245_11D7_A984_F4212B4C3035__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVector2D
{
public:
	CVector2D();
	CVector2D(CPoint);	
	CVector2D(CPoint,CPoint);
	CVector2D(double,double);
	CVector2D(const CVector2D &);
public:
	void normalize();
	CVector2D & operator = (const CVector2D &vect);
	CVector2D operator + (const CVector2D &vect);
	CVector2D operator - (const CVector2D &vect);
	CVector2D & operator *= (const double nScale);
	double operator * (const CVector2D &vect);
	double magnitude();
public:
	double x,y;
};

#endif // !defined(AFX_VECTOR2D_H__8B453F0B_7245_11D7_A984_F4212B4C3035__INCLUDED_)
