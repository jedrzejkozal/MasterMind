//pojedynczy osobnik w populacji

#ifndef OSOBNIK
#define OSOBNIK


#include <iostream>

#include "kolor.h"


//osobnik
class osobnik
{
	Kolor *allele;
	const unsigned rozmiar;
	double przystosowanie;
public:
	double odkoduj();				 //odkodowywuje wartosc z ciagu kodowego
	double oblicz_przystosowanie();  //oblicza przystosowanie na podstawie odkowanej wartosci
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
	
	//osobnik();
	osobnik(unsigned rozmiar_ciagu);
	void zwolnij_pamiec() { if (allele != NULL) delete[] allele; allele = NULL; }
	//~osobnik() { if(allele != NULL) delete[] allele; }
};



#endif // !OSOBNIK