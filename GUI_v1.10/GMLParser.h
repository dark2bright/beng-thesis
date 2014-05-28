// CGMLParser.h: interface for the CGMLParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMLPARSER_H__114460A0_80E0_46CE_AEC1_0048AB3D87A2__INCLUDED_)
#define AFX_GMLPARSER_H__114460A0_80E0_46CE_AEC1_0048AB3D87A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GMLScanner.h"
#include "Message.h"
#include "GMLPair.h"

class CGMLParser  : public CGMLScanner
{
	struct GML_list_elem {
		char* key;
		GML_list_elem* next;
	};
	
	struct GML_stat {
		GML_error err;
		GML_list_elem* key_list;
	};	
public:
	CGMLParser(const char*);
	virtual ~CGMLParser();
public:
	void showAllKeys(CMessage*);
	bool parse();
	void showLastError(CMessage*)const;
protected:
	void purge ();
	void freeList(LPGMLPAIR);
	LPGMLPAIR parse (int open);
protected:
	GML_stat* stat;
	LPGMLPAIR list;
	FILE* source;
	BOOL isDone;
};

#endif // !defined(AFX_GMLPARSER_H__114460A0_80E0_46CE_AEC1_0048AB3D87A2__INCLUDED_)