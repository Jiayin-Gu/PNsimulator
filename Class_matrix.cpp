#include <iostream>
#include "Class_vector.h"
using std::cin;
using std::cout;
using std::endl;
class Cmatrix
{
	public:
		int m_dimensions;
		double **m_matrix;

		Cmatrix(void);
		Cmatrix(double num, int dim);
		Cmatrix(const Cmatrix &matrix);
		~Cmatrix(void);
		Cmatrix &operator=(const Cmatrix &matrix);
		Cvector operator*(const Cvector &vector) const;
		double &operator()(int row, int column);
};

Cmatrix::Cmatrix()
{
	m_dimensions=0;
	m_matrix=nullptr;
}

Cmatrix::Cmatrix(double num, int dim)
{
	m_dimensions=dim;
	m_matrix=new double*[m_dimensions];
	for(int i{0}; i<m_dimensions; i++) *(m_matrix+i)=new double[m_dimensions];
	for(int i{0}; i<m_dimensions; i++)
	{
		for(int j{0}; j<m_dimensions; j++)
		{
			if(i==j) *(*(m_matrix+i)+j)=num;
			else *(*(m_matrix+i)+j)=0.0;
		}
	}
}

Cmatrix::Cmatrix(const Cmatrix &matrix)
{
	m_dimensions=matrix.m_dimensions;
	m_matrix=new double*[m_dimensions];
	for(int i{0}; i<m_dimensions; i++) *(m_matrix+i)=new double[m_dimensions];
	for(int i{0}; i<m_dimensions; i++)
	{
		for(int j{0}; j<m_dimensions; j++) *(*(m_matrix+i)+j)=*(*(matrix.m_matrix+i)+j);
	}
}

Cmatrix::~Cmatrix()
{
	for(int i{0}; i<m_dimensions; i++)
	{
		delete [] *(m_matrix+i);
		*(m_matrix+i)=nullptr;
	}
	m_dimensions=0;
	delete [] m_matrix;
	m_matrix=nullptr;
}

Cmatrix &Cmatrix::operator=(const Cmatrix &matrix)
{
	if(this==&matrix) return *this;
	for(int i{0}; i<m_dimensions; i++)
	{
		delete [] *(m_matrix+i);
		*(m_matrix+i)=nullptr;
	}
	delete [] m_matrix;
	m_matrix=nullptr;
	m_dimensions=matrix.m_dimensions;
	m_matrix=new double*[m_dimensions];
	for(int i{0}; i<m_dimensions; i++)
	{
		*(m_matrix+i)=new double[m_dimensions];
		for(int j{0}; j<m_dimensions; j++) *(*(m_matrix+i)+j)=*(*(matrix.m_matrix+i)+j);
	}
	return *this;
}

Cvector Cmatrix::operator*(const Cvector &vector) const
{
	Cvector vec(0.0, m_dimensions);
	for(int i{0}; i<m_dimensions; i++)
	{
		for(int j{0}; j<vector.m_dimensions; j++) *(vec.m_vector+i)=*(vec.m_vector+i)+*(*(m_matrix+i)+j)**(vector.m_vector+j);
	}
	return vec;
}

double &Cmatrix::operator()(int row, int column)
{
	return *(*(m_matrix+row)+column);
}
