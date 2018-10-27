#ifndef OSOBNIK
#define OSOBNIK


#include <iostream>

#include "kolor.hpp"


//osobnik
class osobnik
{
	Kolor *allele;
	const unsigned rozmiar;
	double przystosowanie;
public:
	double odkoduj();
	double oblicz_przystosowanie();
	double get_przystosowanie() const {return przystosowanie; }
	void set_przystosowanie(double arg) { przystosowanie = arg; }


	Kolor operator [] (unsigned index) const;
	Kolor &operator [](unsigned index);
	osobnik &operator = (osobnik &osob);

	void wyswietl() const
	{
		for(unsigned i = 0; i < rozmiar; i++)
			std::cout << allele[i];
	}

	osobnik(unsigned rozmiar_ciagu);
	void zwolnij_pamiec() { if (allele != NULL) delete[] allele; allele = NULL; }
};



#endif // !OSOBNIK
