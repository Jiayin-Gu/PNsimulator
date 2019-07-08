#include <iostream>
#include <tuple>
#include <cmath>
#include <vector>
#include "Class_vector.h"
#include "Class_matrix.h"
#include "Class_diode.h"
std::vector<double> random_number_generating(int);
using std::cin;
using std::cout;
using std::endl;
std::tuple<Cdiode, Cvector, Cvector, double> diode_evolving(Cdiode &state)
{
	int N=Cdiode::m_N[0]+Cdiode::m_N[1];
	double alpha=Cdiode::m_alpha;
	double beta=Cdiode::m_beta;
	double e=Cdiode::m_e;
	double epsilon=Cdiode::m_epsilon;
	double dL=Cdiode::m_dL;
	double dt=Cdiode::m_dt;
	double D_electron=Cdiode::m_D_electron;
	double D_hole=Cdiode::m_D_hole;
	double kg=Cdiode::m_k_creation;
	double kr=Cdiode::m_k_annihilation;
	double volume=Cdiode::m_volume;
	double potential_L=Cdiode::m_potential_L;
	double potential_R=Cdiode::m_potential_R;
	double electron_L=Cdiode::m_electron_L;
	double electron_R=Cdiode::m_electron_R;
	double hole_L=Cdiode::m_hole_L;
	double hole_R=Cdiode::m_hole_R;
	Cvector J_n(0.0, N+1), J_p(0.0, N+1);
	double current{0.0};
	double k_electron, k_hole;
	double CDU, DUp, DUm, fp, fm;
	double Wg, Wr;
	double F_electron[N+1], F_hole[N+1], R[N];
	double Wp_electron[N+1], Wm_electron[N+1], Wp_hole[N+1], Wm_hole[N+1];

	k_electron=D_electron/(dL*dL);
	k_hole=D_hole/(dL*dL);

	CDU=0.5*e*e*N/(alpha*(N+1));

	DUp=e*(state.m_potential(0)-potential_L)+CDU;
	fp=beta*DUp/(exp(beta*DUp)-1.0);
	DUm=e*(0-state.m_potential(0)+potential_L)+CDU;
	fm=beta*DUm/(exp(beta*DUm)-1.0);
	Wp_electron[0]=fm*k_electron*electron_L;
	Wm_electron[0]=fp*k_electron*state.m_electron(0);
	Wp_hole[0]=fp*k_hole*hole_L;
	Wm_hole[0]=fm*k_hole*state.m_hole(0);

	for(int i{1}; i<N; i++)
	{
		DUp=e*(state.m_potential(i)-state.m_potential(i-1))+CDU;
		fp=beta*DUp/(exp(beta*DUp)-1.0);
		DUm=e*(0-state.m_potential(i)+state.m_potential(i-1))+CDU;
		fm=beta*DUm/(exp(beta*DUm)-1.0);
		Wp_electron[i]=fm*k_electron*state.m_electron(i-1);
		Wm_electron[i]=fp*k_electron*state.m_electron(i);
		Wp_hole[i]=fp*k_hole*state.m_hole(i-1);
		Wm_hole[i]=fm*k_hole*state.m_hole(i);
	}

	DUp=e*(potential_R-state.m_potential(N-1))+CDU;
	fp=beta*DUp/(exp(beta*DUp)-1.0);
	DUm=e*(0-potential_R+state.m_potential(N-1))+CDU;
	fm=beta*DUm/(exp(beta*DUm)-1.0);
	Wp_electron[N]=fm*k_electron*state.m_electron(N-1);
	Wm_electron[N]=fp*k_electron*electron_R;
	Wp_hole[N]=fp*k_hole*state.m_hole(N-1);
	Wm_hole[N]=fm*k_hole*hole_R;

	std::vector<double> gaussian{random_number_generating(3*N+2)};
	int j{0};
	double S;
	S=(Wp_electron[0]+Wm_electron[0])/dt;
	S=sqrt(S)*gaussian[j++];
	F_electron[0]=Wp_electron[0]-Wm_electron[0]+S;
	J_n(0)=F_electron[0];
	S=(Wp_hole[0]+Wm_hole[0])/dt;
	S=sqrt(S)*gaussian[j++];
	F_hole[0]=Wp_hole[0]-Wm_hole[0]+S;
	J_p(0)=F_hole[0];
	for(int i{1}; i<N; i++)
	{
		S=(Wp_electron[i]+Wm_electron[i])/dt;
		S=sqrt(S)*gaussian[j++];
		F_electron[i]=Wp_electron[i]-Wm_electron[i]+S;
		J_n(i)=F_electron[i];
		S=(Wp_hole[i]+Wm_hole[i])/dt;
		S=sqrt(S)*gaussian[j++];
		F_hole[i]=Wp_hole[i]-Wm_hole[i]+S;
		J_p(i)=F_hole[i];
	}
	S=(Wp_electron[N]+Wm_electron[N])/dt;
	S=sqrt(S)*gaussian[j++];
	F_electron[N]=Wp_electron[N]-Wm_electron[N]+S;
	J_n(N)=F_electron[N];
	S=(Wp_hole[N]+Wm_hole[N])/dt;
	S=sqrt(S)*gaussian[j++];
	F_hole[N]=Wp_hole[N]-Wm_hole[N]+S;
	J_p(N)=F_hole[N];

	for(int i{0}; i<N; i++)
	{
		Wg=kg*volume;
		Wr=kr*state.m_electron(i)*state.m_hole(i)/volume;
		S=(Wg+Wr)/dt;
		S=sqrt(S)*gaussian[j++];
		R[i]=Wg-Wr+S;
	}

	Cdiode next_state;

	for(int i{0}; i<N; i++)
	{
		next_state.m_electron(i)=state.m_electron(i)+dt*(F_electron[i]-F_electron[i+1]+R[i]);
		if(next_state.m_electron(i)<0) cout<<"alarm"<<endl;
		next_state.m_hole(i)=state.m_hole(i)+dt*(F_hole[i]-F_hole[i+1]+R[i]);
		if(next_state.m_hole(i)<0) cout<<"alarm"<<endl;
	}
	next_state.coordinating();
	for(int i{0}; i<N+1; i++)
	{
		current+=e*(J_p(i)-J_n(i))/(N+1); // total current including the contribution of displacement current
	}
	return std::make_tuple(next_state, J_n, J_p, current);
}
