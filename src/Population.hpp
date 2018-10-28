#pragma once

#include "Individual.hpp"

class Population
{
public:
	Population(unsigned lpop, unsigned rozm_alleli, double p_mutacji, double p_krzyozwania);
	~Population();

	void newPopulation();
	void print() const;
	void printStats() const;		//raport o statystykach populacji
	void calcStats();
	void calcFitness();
	void nonnegativeFitness();
	void reinitialize();

	//wybrani osobnicy
	Individual *najlepszy;
	Individual *najgorszy;

private:
	Individual** individuals;

	//zmienne do kontroli populacji
	unsigned populationSize;
	unsigned seriesSize;
	double mutationProbablity;		//w procentach:  1 to 1% = 0.01
	double crossOverProbability;	//normalny ulamek
	double* chossingProbability; //tablica do realizacji losowania

	//statystyki
	double fitnessSum;					//suma wszystkich przystosowan
	double avrageFitness;
	double maxFitness;
	double minFitness;

	//tworzenie nowej populacji
	Individual** newPop;
	void selekcja_elitarna();
	void crossover();
	void mutate();
	void initializeNewTable();
	void drawNewIndividual();
};
