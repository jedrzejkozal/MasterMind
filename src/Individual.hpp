#pragma once

#include "Color.hpp"

class Individual
{
public:
	double decode();
	double calcFitness();
	double getFitness() const;
	void set_przystosowanie(double arg);
	void wyswietl() const;

	Color operator [] (unsigned index) const;
	Color &operator [](unsigned index);
	Individual &operator = (Individual &osob);

	Individual(unsigned rozmiar_ciagu);
	void zwolnij_pamiec();

private:
	Color *allele;
	const unsigned rozmiar;
	double przystosowanie;
};
