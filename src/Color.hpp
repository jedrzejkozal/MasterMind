#pragma once

#define ILOSC_DOSTEPNYCH 9

#include <iostream>
#include <cstdlib>


enum color
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

class Color
{
public:
	color col;

	bool operator == (Color arg)
	{
		if ((int)col == (int)arg.col)
			return true;
		else
			return false;
	}

	Color()	{		col = static_cast<color>(std::rand() % ILOSC_DOSTEPNYCH);	}
	Color(int arg)	{		col = static_cast<color>(arg);	}
	Color(Color *arg)	{		col = arg->col;	}
	Color operator = (Color arg)
	{
		col = arg.col;
		return arg;
	}
	Color operator = (color arg)
	{
		col = arg;
		return arg;
	}
};

std::ostream& operator << (std::ostream& wyj, Color const &arg);
std::istream& operator >> (std::istream &wej, Color &arg);
