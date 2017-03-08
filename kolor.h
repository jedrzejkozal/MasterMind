//klasa opisujaca stany w jakich mozne znalezc sie pojedynczy gen osobnika
//w tym zagadnieniu jest w zasadzie zbedna, ale zaimplementowana zeby latwiej bylo rozwijac kod

#ifndef  KOLOR
#define KOLOR

#define ILOSC_DOSTEPNYCH 9

#include <iostream>
#include <cstdlib>


enum kolor
{
	bialy = 0,
	czerwony = 1,
	zielony = 2,
	fioletowy = 3,
	turkusowy = 4,
	szary = 5,
	niebieski = 6,
	zolty = 7,
	czarny = 8
};

class Kolor
{
public:
	kolor kol;

	bool operator == (Kolor arg)
	{
		if ((int)kol == (int)arg.kol)
			return true;
		else
			return false;
	}

	Kolor()	{		kol = static_cast<kolor>(std::rand() % ILOSC_DOSTEPNYCH);	}
	Kolor(int arg)	{		kol = static_cast<kolor>(arg);	}
	Kolor(Kolor *arg)	{		kol = arg->kol;	}
	Kolor operator = (Kolor arg)
	{
		kol = arg.kol;
		return arg;
	}
	Kolor operator = (kolor arg)
	{
		kol = arg;
		return arg;
	}
};

std::ostream& operator << (std::ostream& wyj, Kolor const &arg);
std::istream& operator >> (std::istream &wej, Kolor &arg);

#endif // ! KOLOR
