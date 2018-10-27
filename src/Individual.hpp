#ifndef OSOBNIK
#define OSOBNIK


#include <iostream>

#include "Color.hpp"


//osobnik
class Individual
{
	Color *allele;
	const unsigned rozmiar;
	double przystosowanie;
public:
	double odkoduj();
	double oblicz_przystosowanie();
	double get_przystosowanie() const {return przystosowanie; }
	void set_przystosowanie(double arg) { przystosowanie = arg; }


	Color operator [] (unsigned index) const;
	Color &operator [](unsigned index);
	Individual &operator = (Individual &osob);

	void wyswietl() const
	{
		for(unsigned i = 0; i < rozmiar; i++)
			std::cout << allele[i];
	}

	Individual(unsigned rozmiar_ciagu);
	void zwolnij_pamiec() { if (allele != NULL) delete[] allele; allele = NULL; }
};



#endif // !OSOBNIK
