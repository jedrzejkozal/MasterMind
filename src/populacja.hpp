#include "osobnik.hpp"

#ifndef POPULACJA
#define POPULACJA

class populacja
{
	osobnik** osobniki;

	//zmienne do kontroli populacji
	unsigned rozm_populacji;
	unsigned rozmiar_ciagu;
	double prawd_mutacji;		//w procentach:  1 to 1% = 0.01
	double prawd_krzyzowania;	//normalny ulamek
	double* prawd_wybrania; //tablica do realizacji losowania

	//statystyki
	double suma;					//suma wszystkich przystosowan
	double srednie_przystosowanie;
	double max_przystosowanie;
	double min_przystosowanie;

	//tworzenie nowej populacji
	osobnik** nowa;
	void selekcja_elitarna();
	void krzyzuj();
	void mutuj();
	void nowa_tablica_inicjalizuj();
	void losuj_nowych_osobnikow();
public:
	void nowa_populacja();
	void wyswietl() const;
	void wyswietl_statystyki() const;		//raport o statystykach populacji
	void oblicz_statystyki();
	void oblicz_przystosowania();
	void nieujemne_przystosowania();
	void reinicjalizuj();


	//wybrani osobnicy
	osobnik *najlepszy;
	osobnik *najgorszy;

	populacja(unsigned lpop, unsigned rozm_alleli, double p_mutacji, double p_krzyozwania);
	~populacja();
};


#endif //!POPULACJA
