#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <tuple>
#include "Class_vector.h"
#include "Class_matrix.h"
#include "Class_diode.h"
std::tuple<Cdiode, Cvector, Cvector, double> diode_evolving(Cdiode &);
std::tuple<Cdiode, Cvector, Cvector, double> steady_state_evaluating(Cdiode);
bool random_initializing(void);
bool random_finalizing(void);
using std::cin;
using std::cout;
using std::endl;
int main(int argc, char *argv[])
{
	random_initializing();

	double e=Cdiode::m_e;
	double beta=Cdiode::m_beta;
	double dt=Cdiode::m_dt;
	int N=Cdiode::m_N[0]+Cdiode::m_N[1];

	int e_L{400}, h_L{1600000000};
	int e_R{1600000000}, h_R{400};
	double V_eq=0.0-log(h_L/h_R)/(beta*e);
	double p_R{0.0};

	Cvector J_n(0.0, N+1), J_p(0.0, N+1);
	double current;

	std::ofstream fout("I_V.out");
	fout.setf(std::ios_base::showpoint);
	fout.setf(std::ios::right);

	for(double V=-5; V<4.1; V+=0.5)
	{
		double p_L=V+V_eq;
		Cdiode::initializing(e_L, h_L, p_L, e_R, h_R, p_R);
		Cdiode state, steady_state;
		state.coordinating();
		steady_state.coordinating();
		std::tie(steady_state, J_n, J_p, current)=steady_state_evaluating(state);
		fout<<std::setw(15)<<std::setprecision(8)<<V<<"  ";
		fout<<std::setw(15)<<std::setprecision(8)<<current<<'\n';
		cout<<"progress: voltage "<<V<<"  in range [-5.0, 4.0]"<<endl;
	}
	fout.close();

	random_finalizing();
	return 0;
}
