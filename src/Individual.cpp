#include <iostream>
#include <cstdlib>
#include <math.h>

#include "Individual.hpp"
#include "globals.hpp"


using namespace std;

extern list<Color *> poprzednie;
extern list<unsigned> poprzednie_dobre, poprzednie_miejsca;

Individual::Individual(unsigned seriesSize)
	: size(seriesSize)
{
	allele = new Color[size];
	if (allele != NULL)
	{
		for (unsigned i = 0; i < size; i++) //losowe przydzielenie bitow
			allele[i] = static_cast<color>(std::rand() % ILOSC_DOSTEPNYCH);
		calcFitness();
	}
	else
		std::cerr << "Individual: konstrutor: nie mozna przydzielic pamieci!" << std::endl;
}

Color Individual::operator[] (unsigned index) const
{
	if (index < 0 || index > size - 1)
	{
		std::cerr << "Individual: operator[]: Podano zly indeks!" << std::endl;
		return allele[0];
	}
	else
		return allele[index];
}

Color &Individual::operator[] (unsigned index)
{
	if(index < 0 || index > size-1)
	{
		std::cerr << "Individual: operator[]: Podano zly indeks!" << std::endl;
		return allele[0];
	}
	else
		return allele[index];
}

Individual &Individual::operator = (Individual &osob)
{
	for (unsigned i = 0; i < size; i++)
		allele[i] = osob[i];

	fitness = osob.getFitness();
	return osob;
}

double Individual::decode()
{
	int odleglosc = 0;
	unsigned dobre_miejsce, dobry_kolor;

	list<unsigned>::iterator it1 = poprzednie_dobre.begin();
	list<unsigned>::iterator it2 = poprzednie_miejsca.begin();
	for (list<Color *>::iterator it = poprzednie.begin(); it != poprzednie.end(); it++, it1++, it2++)
	{
		check(*it, allele, size, dobre_miejsce, dobry_kolor);
		odleglosc -= abs((int)(*it1 - dobre_miejsce)) + abs((int)(*it2 - dobry_kolor));
	}
	return odleglosc;
}

double Individual::calcFitness()
{
	return fitness = decode();
}

double Individual::getFitness() const
{
	return fitness;
}

void Individual::setFitness(double arg)
{
	fitness = arg;
}

void Individual::print() const
{
	for(unsigned i = 0; i < size; i++)
		std::cout << allele[i];
}

void Individual::freeMemory()
{
	if (allele != NULL)
		delete[] allele;
	allele = NULL;
}
