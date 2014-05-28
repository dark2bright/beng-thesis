// GraphLoader.h: interface for the CGraphLoader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHLOADER_H__C8963ED0_5425_40A8_B07E_14DEF11542D8__INCLUDED_)
#define AFX_GRAPHLOADER_H__C8963ED0_5425_40A8_B07E_14DEF11542D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GMLParser.h"
#include "GraphController.h"

class CGraphLoader
{
	class CGMLParserEx : public CGMLParser
	{
		friend class CGraphLoader;
	};
	class CGraphControllerEx : public CGraphController{
		friend class CGraphLoader;
	};
public:
	CGraphLoader();
	virtual ~CGraphLoader();
public:
	CGraphController* load(const char*);
};

#endif // !defined(AFX_GRAPHLOADER_H__C8963ED0_5425_40A8_B07E_14DEF11542D8__INCLUDED_)
