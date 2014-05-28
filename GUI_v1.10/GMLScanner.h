// CGMLScanner.h: interface for the CGMLScanner class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMLSCANNER_H__39BDF138_9F9C_43E8_8265_D43F3A5BFFE8__INCLUDED_)
#define AFX_GMLSCANNER_H__39BDF138_9F9C_43E8_8265_D43F3A5BFFE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Definitions.h"

class CGMLScanner  
{
protected:
	struct GML_error {
		GML_error_value err_num;
		int line;
		int column;
	};
	
	union GML_tok_val {
		long integer;
		double floating;
		char* string;
		GML_error err;
	};
	
	struct GML_token { 
		GML_value kind;
		union GML_tok_val value;
	};	
public:
	CGMLScanner();
	virtual ~CGMLScanner();
protected:
	GML_token scan(FILE*);
	int searchISO (char* str, int len);
protected:
	unsigned int GML_line;
	unsigned int GML_column;
};

#endif // !defined(AFX_GMLSCANNER_H__39BDF138_9F9C_43E8_8265_D43F3A5BFFE8__INCLUDED_)
