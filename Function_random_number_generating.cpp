#include <iostream>
#include <tuple>
#include <vector>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
using std::cin;
using std::cout;
using std::endl;
static gsl_rng* generator=nullptr;

bool random_initializing()
{
	generator=gsl_rng_alloc(gsl_rng_default);
	gsl_rng_set(generator, 0); // seeded with 0
	return true;
}

std::vector<double> random_number_generating(int num)
{
	gsl_rng_env_setup(); // setup the environment for random number generation
	double sigma{1.0};
	gsl_rng* r=generator;
	std::vector<double> gaussian(num, 0.0);
	for(auto &gau:gaussian) gau=gsl_ran_gaussian(r, sigma); //generating gaussian distribution numbers with mu=0 and sigma
	return std::move(gaussian);
}

bool random_finalizing()
{
	gsl_rng_free(generator);
	delete [] generator;
	generator=nullptr;
	return true;
}
