#include "kolor.h"

std::ostream& operator << (std::ostream& wyj, Kolor const &arg)
{
	wyj << (int) arg.kol;
	return wyj;
}