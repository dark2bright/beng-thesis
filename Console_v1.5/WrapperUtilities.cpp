// WrapperUtilities.cpp: implementation of the CWrapperUtilities class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "thesis.h"
#include "AlgorithmImpls.h"
#include "WrapperUtilities.h"
#include "NullObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CObjectEx& CWrapperUtilities::buildWrapper(INT type, CString strValue)
{	
	if (type == Int) {
		INT nVal =  atoi(strValue);
		return *new CWrapper<int>(nVal);
	}
	if (type == Float) {
		FLOAT fVal =  atof(strValue);
		return *new CWrapper<float>(fVal);
	}
	// Reach here ==> type == None
	return CNullObject::instance();
}

CString CWrapperUtilities::getType(INT type)
{
	switch(type) {
	case None:	return "None";
	case Int:	return "Int";
	case Float: return "Float";
	}
	return "None";
}

CAlgorithms* CWrapperUtilities::buildAlgorithmImpl(INT type)
{
	switch(type) {
	case Int:	return new CAlgorithmImpls<int>;
	case Float: return new CAlgorithmImpls<float>;
	}
	return NULL;
}
