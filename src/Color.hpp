#pragma once

#define ILOSC_DOSTEPNYCH 9

#include <cstdlib>


enum color
{
	white = 0,
	red = 1,
	green = 2,
	purple = 3,
	turquoise = 4,
	gray = 5,
	blue = 6,
	yellow = 7,
	black = 8
};

class Color
{
public:
	Color();
	Color(int arg);
	Color(Color *arg);
	Color operator = (Color arg);
	Color operator = (color arg);
	bool operator == (Color arg);

	color col;
};

std::ostream& operator << (std::ostream& wyj, Color const &arg);
std::istream& operator >> (std::istream &wej, Color &arg);
