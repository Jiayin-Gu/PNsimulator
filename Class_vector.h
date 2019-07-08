#ifndef class_vector_h
#define class_vector_h
class Cmatrix;
class Cvector
{
	public:
		int m_dimensions;
		double *m_vector;

		Cvector(void);
		Cvector(double, int);
		Cvector(const Cvector &);
		~Cvector(void);
		Cvector &operator=(const Cvector &);
		Cvector operator+(const Cvector &) const;
		Cvector operator-(const Cvector &) const;
		Cvector operator*(double) const;
		double &operator()(int);

	private:
		friend Cvector operator*(double, Cvector);
};
#endif
