#if !defined(AFX_CONTROL_STRUCT_H_INCLUDED_)
#define AFX_CONTROL_STRUCT_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Definitions.h"

typedef struct tagCONTROLSTRUCT{
	INT maxSize;
	INT edgeStorage; // 0 : as matrix, 1 : as lists
	INT vertexType;
	INT edgeType;
	BOOL fastInsertVertex;
	BOOL fastInsertEdge;
	BOOL isNetWork;
	CString defaultWeightOfVertex;
	CString defaultWeightOfEdge;
	CString defaultCapacity;
	COLORREF vertexColor;
	COLORREF edgeColor;
	// initialize default configuration
	tagCONTROLSTRUCT();
}CONTROLSTRUCT, *LPCONTROLSTRUCT;

#endif // !defined(AFX_CONTROL_STRUCT_H_INCLUDED_)