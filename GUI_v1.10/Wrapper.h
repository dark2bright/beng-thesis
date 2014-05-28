#ifndef _WRAPPER_H
#define _WRAPPER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
#include "BObject.h"
#include <typeinfo.h>

template <class T>
class CWrapper : public CObjectEx
{
protected:
    T datum;
	INT compareTo (CObjectEx const& obj) const{
		CWrapper const& arg = (CWrapper const&) (obj);
		if (datum > arg.datum) return 1;
		if (datum < arg.datum) return -1;
		return 0;
	}
public:
    CWrapper () : datum() {}
    CWrapper (T const& d) : datum(d) {}
	
    const CWrapper& operator = (T const& d){
		datum = d;
		return *this;
    }
	
    operator T const& () const { return datum; }
	
	CObjectEx&clone()const
	{
		return *new CWrapper(datum);
	}

	INT typeId() const { return WRAPPERID; }
	// Override this function to wrapper un built-in type
	CString toString()const{
		const char* type = typeid(datum).name();
		CString str;
		if (strcmp(type,"int") == 0)
			str.Format("%d",datum);
		if (strcmp(type,"float") == 0)
			str.Format("%f",datum);
		return str;
	}
};

#define		Integer			CWrapper<int>	

#endif // #define _WRAPPER_H