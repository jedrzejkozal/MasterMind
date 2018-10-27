#include <string>

#include "Color.hpp"

std::ostream& operator << (std::ostream& wyj, Kolor const &arg)
{
	wyj << (int) arg.kol;
	return wyj;
}


std::istream& operator >> (std::istream &wej, Kolor &arg)
{
	int tmp;
	wej >> tmp;
	arg.kol = (kolor)tmp;
	return wej;
}
