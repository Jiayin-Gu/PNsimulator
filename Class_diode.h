#ifndef class_diode_h
#define class_diode_h
class Cvector;
class Cvector;
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
		static bool initializing(double, double, double, double, double, double);

		Cvector m_electron;
		Cvector m_hole;
		Cvector m_charge;
		Cvector m_potential;

		Cdiode(void);
		bool coordinating(void);
		Cdiode &operator=(const Cdiode &);
};
#endif
