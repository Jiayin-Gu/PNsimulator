#include <iostream>
#include "Class_matrix.h"
using std::cin;
using std::cout;
using std::endl;
class Cvector
{
	public:
		int m_dimensions;
		double *m_vector;

		Cvector(void);
		Cvector(double num, int dim);
		Cvector(const Cvector &vector);
		~Cvector(void);
		Cvector &operator=(const Cvector &vector);
		Cvector operator+(const Cvector &vector) const;
		Cvector operator-(const Cvector &vector) const;
		Cvector operator*(double multiplier) const;
		double &operator()(int);

	private:
		friend Cvector operator*(double multiplier, Cvector vector);
};

Cvector::Cvector()
{
	m_dimensions=0;
	m_vector=nullptr;
}

Cvector::Cvector(double num, int dim)
{
	m_dimensions=dim;
	m_vector=new double[m_dimensions];
	for(int i{0}; i<m_dimensions; i++) *(m_vector+i)=num;
}

Cvector::Cvector(const Cvector &vector)
{
	m_dimensions=vector.m_dimensions;
	m_vector=new double[m_dimensions];
	for(int i{0}; i<m_dimensions; i++) *(m_vector+i)=*(vector.m_vector+i);
}

Cvector::~Cvector()
{
	delete [] m_vector;
	m_vector=nullptr;
	m_dimensions=0;
}

Cvector &Cvector::operator=(const Cvector &vector)
{
	if(this==&vector) return *this;
	delete [] m_vector;
	m_vector=nullptr;
	m_dimensions=vector.m_dimensions;
	m_vector=new double[m_dimensions];
	for(int i{0}; i<m_dimensions; i++) *(m_vector+i)=*(vector.m_vector+i);
	return *this;
}

Cvector Cvector::operator+(const Cvector &vector) const
{
	Cvector vec(0.0, m_dimensions);
	for(int i{0}; i<m_dimensions; i++) *(vec.m_vector+i)=*(m_vector+i)+*(vector.m_vector+i);
	return vec;
}

Cvector Cvector::operator-(const Cvector &vector) const
{
	Cvector vec(0.0, m_dimensions);
	for(int i{0}; i<m_dimensions; i++) *(vec.m_vector+i)=*(m_vector+i)-*(vector.m_vector+i);
	return vec;
}

Cvector Cvector::operator*(double multiplier) const
{
	Cvector vec(0.0, m_dimensions);
	for(int i{0}; i<m_dimensions; i++) *(vec.m_vector+i)=*(m_vector+i)*multiplier;
	return vec;
}

double &Cvector::operator()(int index)
{
	return *(m_vector+index);
}

Cvector operator*(double multiplier, Cvector vector)
{
	return vector*multiplier;
}
