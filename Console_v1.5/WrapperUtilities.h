// WrapperUtilities.h: interface for the CWrapperUtilities class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WRAPPERUTILITIES_H__2A071761_24FF_4DE8_9F72_FCD2B7143D90__INCLUDED_)
#define AFX_WRAPPERUTILITIES_H__2A071761_24FF_4DE8_9F72_FCD2B7143D90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Algorithms.h"
#include "BObject.h"

class CWrapperUtilities  
{
public:
	static CAlgorithms* buildAlgorithmImpl(INT);
	static CObjectEx& buildWrapper(INT,CString);
	static CString getType(INT);
};

#endif // !defined(AFX_WRAPPERUTILITIES_H__2A071761_24FF_4DE8_9F72_FCD2B7143D90__INCLUDED_)
