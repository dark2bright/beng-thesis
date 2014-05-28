#ifndef _ARRAY_2D_H_
#define _ARRAY_2D_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BArray.h"

template<class T>
class CArray2D
{
	UINT m_uNumberOfRows;
	UINT m_uNumberOfCols;
	CArrayEx<T> array;
public:
    class CRow
    {
		CArray2D& array2D;
		UINT const row; // index of this row
    public:
		CRow (CArray2D& _array2D, UINT _row) : array2D (_array2D), row (_row) {}
		
		T& operator [] (UINT column) const 
		{ 
			return array2D.select (row, column); 
		}
    };
	
    CArray2D (UINT uNumberOfRows, UINT uNumberOfCols)
		: m_uNumberOfRows(uNumberOfRows),m_uNumberOfCols(uNumberOfCols),array(uNumberOfRows*uNumberOfCols)
	{
	}
	
    T& select (UINT row , UINT col)
	{
		if (row >= m_uNumberOfRows)
			throw std::out_of_range ("Invalid Row");
		if (col >= m_uNumberOfCols)
			throw std::out_of_range ("Invalid Column");
		return array [row * m_uNumberOfCols + col];		
    }
	
    CRow operator [] (UINT row)
	{
		return CRow (*this, row); 
    }
	
	void setSize(UINT newNumberOfRows, UINT newNumberOfCols)
	{
		if (newNumberOfRows == m_uNumberOfRows && newNumberOfCols == m_uNumberOfCols) return;
		UINT minRows = m_uNumberOfRows <= newNumberOfRows ? m_uNumberOfRows : newNumberOfRows;
		UINT minCols = m_uNumberOfCols <= newNumberOfCols ? m_uNumberOfCols : newNumberOfCols;
		T* newData = new T[newNumberOfRows*newNumberOfCols];
		for(UINT i = 0; i < minRows; i++)
			for(UINT j = 0; j < minCols; j++)
				newData[i*newNumberOfRows+j] = select(i,j);
		delete []array.data;
		array.data = newData;
		array.length = newNumberOfRows*newNumberOfCols;
		m_uNumberOfRows = newNumberOfRows;
		m_uNumberOfCols = newNumberOfCols;
	}

	void getSize(UINT&numberOfRows, UINT&numberOfCols)
	{
		numberOfRows = m_uNumberOfRows;
		numberOfCols = m_uNumberOfCols;
	}
};

#endif // #define _ARRAY_2D_H_