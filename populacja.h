#include "osobnik.h"

#ifndef POPULACJA
#define POPULACJA

class populacja
{
	osobnik** osob;				//tablica wszystkich osobnikow

	//zmienne do kontroli populacji
	unsigned lpopulacji;		//liczebnosc populacji
	unsigned rozmiar_ciagu;		//dlugosc ciagu kodowego danego osobnika
	double prawd_mutacji;		//w procentach:  1 to wartosc 1%, czyli tak na prawde 0.01
	double prawd_krzyzowania;	//normalny ulamek

	//statystyki
	double suma;					//suma wszystkich przystosowan
	double srednie_przystosowanie;	//srednie przystosowanie wystepujace w populacji
	double max_przystosowanie;		//maksymalne przysosowanie wystepujace w populacji
	double min_przystosowanie;		//minimalne przystosowanie wystpujace w populacji
public:
	void nowa_populacja();		//tworzy nowa populacje na podstawie obecnej
	void krzyzuj(); 			//krzyzuje ze soba osbniki po kolei
	void mutuj();				//mutuje wszystkie osobniki
	void wyswietl() const;		//wyswietla populacje
	void raport() const;		//raport o statystykach populacji
	void skaluj();				//skalowanie przystosowan, zapewnia lepsza zbieznosc
	void statystyki();			//oblicza wszystkie statystyki
	void oblicz_przystosowania(); //oblicza aktualne przystosowania populacji
	void reinicjalizuj();		//reinicjalizuje wszystkich osbnikow
	void skaluj_przystosowania();

	//wybrani osobnicy
	osobnik *najlepszy;
	osobnik *najgorszy;

	populacja(unsigned lpop, unsigned rozm_alleli, double p_mutacji, double p_krzyozwania);
	~populacja();
};


#endif //!POPULACJA
