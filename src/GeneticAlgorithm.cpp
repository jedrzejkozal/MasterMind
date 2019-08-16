#include <iostream>
#include <algorithm>

#include "GeneticAlgorithm.hpp"
#include "exceptions/PopulationSizeNotEvenException.hpp"
#include "exceptions/PopulationSizeToSmallException.hpp"

void GeneticAlgorithm::initialisePopulation(unsigned populationSize, const unsigned &allelesSize)
{
    while (populationSize > 0)
    {
        population.push_back(Individual(allelesSize));
        populationSize--;
    }
    fitnessCalculator.updateFitness(population);
}

void GeneticAlgorithm::findSolution(const unsigned &rounds)
{
    for (unsigned iterations = 0; iterations < rounds; iterations++)
    {
        select();
        cross();
        mutate();
        updateFitness();
        if (checkStoppingCondintion())
        {
            std::cout << "Early stop at iteration " << iterations << std::endl;
            break;
        }
    }
}

bool GeneticAlgorithm::checkStoppingCondintion() const
{
    for (const auto &individual : population)
        if (stoppingFunction(individual.fitness))
            return true;
    return false;
}

Individual GeneticAlgorithm::bestIndividual()
{
    Individual best(2);
    float maxFitness = 0;
    for (auto &individual : population)
        if (individual.fitness > maxFitness)
        {
            maxFitness = individual.fitness;
            best = individual;
        }
    return best;
}

void GeneticAlgorithm::select()
{
    populationSizeCheck();
    selection->select(population);
}

void GeneticAlgorithm::cross()
{
    evenPopulationSizeCheck();
    crossing->cross(population);
}

void GeneticAlgorithm::mutate()
{
    for (auto &i : population)
        i.mutate(*mutation.get());
}

void GeneticAlgorithm::updateFitness()
{
    fitnessCalculator.updateFitness(population);
}

void GeneticAlgorithm::populationSizeCheck() const
{
    if (population.size() < 2)
        throw PopulationSizeToSmallException();
}

void GeneticAlgorithm::evenPopulationSizeCheck() const
{
    if (population.size() % 2 != 0)
        throw PopulationSizeNotEvenException();
}