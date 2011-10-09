/* 
 * File:   Series.h
 * Author: cjsmart <alexey.pozin@gmail.com>
 *
 * Created on 15 Август 2011 г., 15:12
 */

#ifndef SERIES_H
#define	SERIES_H

#include "Includes.h"
#include <exception>
#include <iostream>

namespace vicos
{

typedef double numeric;
typedef double time;

///////////////////////////////////////////////////////////////
// class CVectorT - базовый класс для векторов
template<typename V>
class CVectorT
{
public:	// Construction
	CVectorT() : m_pRef(NULL), m_iCount(0) {}
	CVectorT(long iCount) : m_iCount(iCount)
	{
		m_pRef = new V[iCount];
	}
	CVectorT(const CVectorT<V>& Right) : 
		m_pRef(NULL), m_iCount(0) // лучше наверное explicit
	{
		CopyFrom(Right);
	}
	
	virtual ~CVectorT()
	{
		Destroy();
	}
	

public:
	inline bool IsEmpty() const 
	{
		return m_pRef == NULL;
	}
	
	inline long GetCount() const
	{
		return m_iCount;
	}
	
	inline void Create(long iCount)
	{
		Destroy();
		
		m_iCount = iCount;
		m_pRef = new V[iCount];
	}
	
	inline void Destroy()
	{
		if (m_pRef != NULL)
		{
			delete [] m_pRef;
			m_pRef = NULL;
		}
		m_iCount = 0;
	}
	
	inline void Attach(V* pRef, long iCount)
	{
		Destroy();
		
		m_pRef = pRef;
		m_iCount = iCount;
	}
	
	inline V* Detach()
	{
		V* pResult = m_pRef;
		m_pRef = NULL;
		m_iCount = 0;
		
		return pResult;
	}
	
	void CopyFrom(const CVectorT<V>& Right)
	{
		Destroy();
		
		if (Right.m_pRef != NULL)
		{
			Create(Right.m_iCount);
			
			for (long i = 0; i < m_iCount; i++)
			{
				m_pRef[i] = Right.m_pRef[i];
			}
		}
	}
	
	inline const CVectorT<V>& operator =(const CVectorT<V>& Right)
	{
		CopyFrom(Right);
		
		return *this;
	}
	
	inline const V& operator[](long iIndex) const
	{
		if (iIndex >= m_iCount)
			throw new std::exception();
		
		return m_pRef[iIndex];
	}
	
	inline V& operator[](long iIndex)
	{
		if (iIndex >= m_iCount)
			throw new std::exception();
		
		return m_pRef[iIndex];
	}
	
	inline V* GetData()
	{
		return m_pRef;
	}
	
	inline void Fill(const V& Value)
	{
		for (long i = 0; i < m_iCount; i++)
			m_pRef[i] = Value;
	}
	
	void Dump(std::ostream& os) const
	{
		os << "[" << m_iCount << "]" << "(";
		
		if (IsEmpty())
		{
			os << "null";
		}
		else
		{
			for (long i = 0; i < m_iCount; i++)
			{
				if (i > 0)
					os << "; ";
				os << m_pRef[i];
			}
		}
		
		os << ")";
	}
	
private:
	V* m_pRef;
	long m_iCount;
};

template<typename V>
std::ostream &operator<<(std::ostream& os, const CVectorT<V>& value) 
{
	value.Dump(os);
}


///////////////////////////////////////////////////////////////
// class CMatrixT - базовый класс для матриц
template<typename V>
class CMatrixT
{
public:	// Construction
	CMatrixT() : m_ppRef(NULL), m_iRows(0), m_iColumns(0) {}
	CMatrixT(long iRows, long iColumns) : 
		m_iRows(0), m_iColumns(0), m_ppRef(NULL)
	{
		Create(iRows, iColumns);
	}
	CMatrixT(const CVectorT<V>& Right) : 
		m_ppRef(NULL), m_iRows(0), m_iColumns(0) // лучше наверное explicit
	{
		CopyFrom(Right);
	}
	
	virtual ~CMatrixT()
	{
		Destroy();
	}
	

public:
	inline bool IsEmpty() const 
	{
		return m_ppRef == NULL;
	}
	
	inline long GetRows() const
	{
		return m_iRows;
	}
	
	inline long GetColumns() const
	{
		return m_iColumns;
	}
	
	inline void Create(long iRows, long iColumns)
	{
		Destroy();
		
		m_iRows = iRows;
		m_iColumns = iColumns;
		
		m_ppRef = new V*[m_iRows];
		
		for(long i = 0; i < m_iRows; i++)
			m_ppRef[i] = new V[m_iColumns];
	}
	
	inline void Destroy()
	{
		if (m_ppRef != NULL)
		{
			// Deallocation
			for(long i= m_iRows - 1 ; i >= 0; i--)
				delete [] m_ppRef[i];
			
			delete [] m_ppRef;
			
			m_ppRef = NULL;
		}
		m_iRows = 0;
		m_iColumns = 0;
	}
	
	inline void Attach(V** ppRef, long iRows, long iColumns)
	{
		Destroy();
		
		m_ppRef = ppRef;
		m_iRows = iRows;
		m_iColumns = iColumns;
	}
	
	inline V** Detach()
	{
		V** pResult = m_ppRef;
		m_ppRef = NULL;
		m_iRows = 0;
		m_iColumns = 0;
		
		return pResult;
	}
	
	void CopyFrom(const CVectorT<V>& Right)
	{
		Destroy();
		
		if (Right.m_pRef != NULL)
		{
			Create(Right.m_iRows, Right.m_iColumns);
			
			for (long i = 0; i < m_iRows; i++)
			{
				for (long j = 0; j < m_iColumns; j++)
					m_ppRef[i][j] = Right.m_ppRef[i][j];
			}
		}
	}
	
	inline const CVectorT<V>& operator =(const CVectorT<V>& Right)
	{
		CopyFrom(Right);
		
		return *this;
	}
	
	inline const V& operator()(long iRow, long iColumn) const
	{
		if (iRow >= m_iRows || iColumn >= m_iColumns)
			throw new std::exception();
		
		return m_ppRef[iRow][iColumn];
	}
	
	inline V& operator()(long iRow, long iColumn)
	{
		if (iRow >= m_iRows || iColumn >= m_iColumns)
			throw new std::exception();
		
		return m_ppRef[iRow][iColumn];
	}
	
	inline V** GetData()
	{
		return m_ppRef;
	}
	
	inline void Fill(const V& Value)
	{
		for (long i = 0; i < m_iRows; i++)
			for (long j = 0; j < m_iColumns; j++)
				m_ppRef[i][j] = Value;
	}
	
	void Dump(std::ostream& os) const
	{
		os << "[" << m_iRows << ", " << m_iColumns << "]" << "(";
		
		if (IsEmpty())
		{
			os << "null";
		}
		else
		{
			for (long i = 0; i < m_iRows; i++)
			{
				if (i > 0)
					os << "; ";
				
				os << "(";
				
				for (long j = 0; j < m_iColumns; j++)
				{
					if (j > 0)
						os << "; ";
					
					os << m_ppRef[i][j];
				}
				
				os << ")";
			}
		}
		
		os << ")";
	}
	
private:
	V** m_ppRef;
	long m_iRows, m_iColumns;
};

template<typename V>
std::ostream &operator<<(std::ostream& os, const CMatrixT<V>& value) 
{
	value.Dump(os);
}

typedef CVectorT<numeric> timepoint;
typedef CVectorT<timepoint> series;

typedef CMatrixT<numeric> matrixpoint;



typedef CVectorT<matrixpoint> matrixseries;

};

#endif	/* SERIES_H */

