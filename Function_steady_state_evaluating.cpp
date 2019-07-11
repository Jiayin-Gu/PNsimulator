#include <iostream>
#include <tuple>
#include "Class_vector.h"
#include "Class_matrix.h"
#include "Class_diode.h"
std::tuple<Cdiode, Cvector, Cvector, double> diode_evolving(Cdiode &);
using std::cin;
using std::cout;
using std::endl;
std::tuple<Cdiode, Cvector, Cvector, double> steady_state_evaluating(Cdiode state)
{
	int N=Cdiode::m_N[0]+Cdiode::m_N[1];
	int num{100000}, runs{100000};
	Cvector electron(0.0, N), hole(0.0, N), charge(0.0, N), potential(0.0, N);
	Cvector J_n(0.0, N+1), J_n_sum(0.0, N+1);
	Cvector J_p(0.0, N+1), J_p_sum(0.0, N+1);
	double current, current_sum=0.0;
	
	for(int i{0}; i<num; i++) std::tie(state, J_n, J_p, current)=diode_evolving(state);

	for(int i{0}; i<runs; i++)
	{
		std::tie(state, J_n, J_p, current)=diode_evolving(state);
		electron=electron+state.m_electron;
		hole=hole+state.m_hole;
		charge=charge+state.m_charge;
		potential=potential+state.m_potential;
		J_n_sum=J_n_sum+J_n;
		J_p_sum=J_p_sum+J_p;
		current_sum+=current;
	}

	state.m_electron=electron*(1.0/runs);
	state.m_hole=hole*(1.0/runs);
	state.m_charge=charge*(1.0/runs);
	state.m_potential=potential*(1.0/runs);
	J_n=J_n_sum*(1.0/runs);
	J_p=J_p_sum*(1.0/runs);
	current=current_sum*(1.0/runs);

	return std::make_tuple(state, J_n, J_p, current);
}
