#ifndef class_matrix_h
#define class_matrix_h
class Cvector;
class Cmatrix
{
	public:
		int m_dimensions;
		double **m_matrix;

		Cmatrix(void);
		Cmatrix(double, int);
		Cmatrix(const Cmatrix &);
		~Cmatrix(void);
		Cmatrix &operator=(const Cmatrix &);
		Cvector operator*(const Cvector &) const;
		double &operator()(int, int);
};
#endif
