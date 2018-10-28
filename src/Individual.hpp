#pragma once

#include "Color.hpp"

class Individual
{
public:
	Individual(unsigned seriesSize);
	Color operator [] (unsigned index) const;
	Color &operator [](unsigned index);
	Individual &operator = (Individual &osob);

	double decode();
	double calcFitness();
	double getFitness() const;
	void setFitness(double arg);
	void print() const;
	void freeMemory();

private:
	Color *allele;
	const unsigned size;
	double fitness;
};
