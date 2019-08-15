#include "Population.hpp"

void Population::initialisePopulation(unsigned populationSize, unsigned allelesSize)
{
    while (populationSize > 0)
    {
        population.push_back(Individual(allelesSize));
        populationSize--;
    }
}

void Population::select()
{
    selection->select(population);
}

void Population::cross()
{
    crossing->cross(population);
}

void Population::mutate()
{
    for (auto &i : population)
        i.mutate(*mutation.get());
}