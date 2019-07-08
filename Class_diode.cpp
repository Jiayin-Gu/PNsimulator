#include <iostream>
#include <cmath>
#include "Class_vector.h"
#include "Class_matrix.h"
using std::cin;
using std::cout;
using std::endl;
class Cdiode
{
	public:
		static int m_N[2];
		static double m_epsilon;
		static double m_alpha;
		static double m_beta;
		static double m_e;
		static double m_dL;
		static double m_dt;
		static double m_D_electron; 
		static double m_D_hole; 
		static double m_k_creation; 
		static double m_k_annihilation; 
		static double m_volume;
		static double m_section;
		static double m_electron_L; 
		static double m_electron_R; 
		static double m_hole_L; 
		static double m_hole_R; 
		static double m_potential_L; 
		static double m_potential_R; 
		static Cvector m_acceptor; 
		static Cvector m_donor; 
		static Cvector m_electron_initial_state;
		static Cvector m_hole_initial_state;
		static Cmatrix m_c_inverse;
		static bool initializing(double e_L, double h_L, double p_L, double e_R, double h_R, double p_R);

		Cvector m_electron;
		Cvector m_hole;
		Cvector m_charge;
		Cvector m_potential;

		Cdiode(void);
		bool coordinating(void);
		Cdiode &operator=(const Cdiode &state);
};

int Cdiode::m_N[2]={20, 20};
double Cdiode::m_epsilon=0.01;
double Cdiode::m_alpha=0.0;
double Cdiode::m_beta=1.0;
double Cdiode::m_e=1.0;
double Cdiode::m_dL=0.1;
double Cdiode::m_dt=0.0002;
double Cdiode::m_D_electron=0.01;
double Cdiode::m_D_hole=0.01;
double Cdiode::m_k_creation=0.01;
double Cdiode::m_k_annihilation=0.01;
double Cdiode::m_electron_L=0.0;
double Cdiode::m_electron_R=0.0;
double Cdiode::m_hole_L=0.0;
double Cdiode::m_hole_R=0.0;
double Cdiode::m_potential_L=0.0;
double Cdiode::m_potential_R=0.0;
double Cdiode::m_volume=0.0;
double Cdiode::m_section=0.0;
Cvector Cdiode::m_acceptor(0.0, 0);
Cvector Cdiode::m_donor(0.0, 0);
Cvector Cdiode::m_electron_initial_state(0.0, 0);
Cvector Cdiode::m_hole_initial_state(0.0, 0);
Cmatrix Cdiode::m_c_inverse(0.0, 0);

bool Cdiode::initializing(double e_L, double h_L, double p_L, double e_R, double h_R, double p_R)
{
	int N=m_N[0]+m_N[1];
	m_electron_L=e_L;
	m_electron_R=e_R;
	m_hole_L=h_L;
	m_hole_R=h_R;
	m_potential_L=p_L;
	m_potential_R=p_R;
	m_acceptor=Cvector(0.0, N);
	m_donor=Cvector(0.0, N);
	m_electron_initial_state=Cvector(0.0, N);
	m_hole_initial_state=Cvector(0.0, N);
	m_c_inverse=Cmatrix(0.0, N);
	for(int i=0; i<m_N[0]; i++)
	{
		m_electron_initial_state(i)=400;
		m_hole_initial_state(i)=1600000000;
		m_acceptor(i)=m_hole_initial_state(i)-m_electron_initial_state(i);
		m_donor(i)=0;
	}
	for(int i=m_N[0]; i<N; i++)
	{
		m_electron_initial_state(i)=1600000000;
		m_hole_initial_state(i)=400;
		m_acceptor(i)=0;
		m_donor(i)=m_electron_initial_state(i)-m_hole_initial_state(i);
	}
	m_volume=sqrt(m_k_annihilation*m_electron_initial_state(0)*m_hole_initial_state(0)/m_k_creation);
	m_section=m_volume/m_dL;
	m_alpha=m_epsilon*m_volume/(m_dL*m_dL);
	for(int i{0}; i<N; i++)
	{
		for(int j{0}; j<N; j++)
		{
			if(i<=j)
				m_c_inverse(i, j)=1.0*((i+1)*(N-j))/(m_alpha*(N+1));

			else
				m_c_inverse(i, j)=1.0*((j+1)*(N-i))/(m_alpha*(N+1));
		}		
	}
	return true;
}

Cdiode::Cdiode()
{
	int N=m_N[0]+m_N[1];
	m_electron=Cvector(0.0, N);
	m_hole=Cvector(0.0, N);
	m_charge=Cvector(0.0, N);
	m_potential=Cvector(0.0, N);
	m_electron=m_electron_initial_state;
	m_hole=m_hole_initial_state;
	coordinating();
}

Cdiode &Cdiode::operator=(const Cdiode &state)
{
	m_electron=state.m_electron;
	m_hole=state.m_hole;
	m_charge=state.m_charge;
	m_potential=state.m_potential;
	return *(this);
}

bool Cdiode::coordinating()
{
	int N=m_N[0]+m_N[1];
	m_charge=m_e*(m_donor-m_acceptor-m_electron+m_hole);
	Cvector charge=m_charge;
	charge(0)=charge(0)+m_alpha*m_potential_L;
	charge(N-1)=charge(N-1)+m_alpha*m_potential_R;
	m_potential=m_c_inverse*charge;
	return true;
}
