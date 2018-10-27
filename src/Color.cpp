#include <string>
#include <iostream>

#include "Color.hpp"

Color::Color()
{
	col = static_cast<color>(std::rand() % ILOSC_DOSTEPNYCH);
}

Color::Color(int arg)
{
	col = static_cast<color>(arg);
}

Color::Color(Color *arg)
{
	col = arg->col;
}

Color Color::operator = (Color arg)
{
	col = arg.col;
	return arg;
}

Color Color::operator = (color arg)
{
	col = arg;
	return arg;
}

std::ostream& operator << (std::ostream& wyj, Color const &arg)
{
	wyj << (int) arg.col;
	return wyj;
}


std::istream& operator >> (std::istream &wej, Color &arg)
{
	int tmp;
	wej >> tmp;
	arg.col = (color)tmp;
	return wej;
}
