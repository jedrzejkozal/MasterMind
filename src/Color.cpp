#include <string>

#include "Color.hpp"

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
