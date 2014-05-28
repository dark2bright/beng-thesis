#ifndef _BARRAY_H_
#define _BARRAY_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdexcept>

template<class T>
class CArray2D;

template<class T>
class CArrayEx
{
	T* data;
    UINT base;
    UINT length;
	friend class CArray2D<T>;
public:
    CArrayEx ():data (new T [0]), base (0), length (0){}
	
    CArrayEx (UINT uLength, UINT uBase = 0):
	data(new T[uLength]), base(uBase), length(uLength) {}
	
	CArrayEx (CArrayEx const& array)
		: data(new T [array.length]), base(array.base), length(array.length)			
	{
		for (UINT i = 0; i < length; ++i)
			data[i] = array.data[i];		
	}
	
	~CArrayEx (){ delete [] data;}
public:
    CArrayEx& operator = (CArrayEx const& target)
	{
		delete [] data;
		length = target.length;
		data = new T[length];
		for(UINT i = 0; i < length; i++)
			data[i] = target.data[i];
		return *this;
	}
	
    T const& operator [] (UINT uPosition) const
	{
		UINT const uOffset = uPosition - base;
		if (uOffset >= length)
			throw std::out_of_range ("Invalid Position");
		return data[uOffset];
	}
	
    T& operator [] (UINT uPosition)
	{
		UINT const uOffset = uPosition - base;
		if (uOffset >= length)
			throw std::out_of_range ("Invalid Position");
		return data[uOffset];	
	}
	
    T const* getData () const
	{
		return data;
	}
	
    UINT getBase () const
	{ 
		return base; 
	}
	
    UINT getLength () const
	{ 
		return length; 
	}
	
    VOID setBase (UINT uNewBase)
	{ 
		base = uNewBase; 
	}
	
    VOID setLength (UINT uNewLength) 
	{
		T* const newData = new T [uNewLength];
		UINT const min =
			length < uNewLength ? length : uNewLength;
		for (UINT i = 0; i < min; ++i)
			newData [i] = data [i];
		delete [] data;
		data = newData;
		length = uNewLength;
	}	
};

#endif // #define _BARRAY_H_