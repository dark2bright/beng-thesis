// GMLPair.h: interface for the GMLPair class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMLPAIR_H__19C41A06_7C92_4F10_A72A_8136BF82C691__INCLUDED_)
#define AFX_GMLPAIR_H__19C41A06_7C92_4F10_A72A_8136BF82C691__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Definitions.h"

typedef union tagGMLPAIRVAL{
	long integer;
	double floating;
	char* string;
	struct tagGMLPAIR* list;
}GMLPAIRVAL;

typedef struct tagGMLPAIR {
	char* key;
	GML_value kind;
	union tagGMLPAIRVAL value;
	tagGMLPAIR* next;
}GMLPAIR ,*LPGMLPAIR;

#endif // !defined(AFX_GMLPAIR_H__19C41A06_7C92_4F10_A72A_8136BF82C691__INCLUDED_)
