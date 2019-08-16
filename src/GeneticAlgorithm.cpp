#include <iostream>

#include "GeneticAlgorithm.hpp"

void GeneticAlgorithm::initialisePopulation(unsigned populationSize, unsigned allelesSize)
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
        fitnessCalculator.updateFitness(population);
        if (checkStoppingCondintion())
        {
            std::cout << "Early stop at iteration " << iterations << std::endl;
            break;
        }
    }
}

bool GeneticAlgorithm::checkStoppingCondintion() const
{
    for (const auto &ind : population)
        if (stoppingFunction(ind.fitness))
            return true;
    return false;
}

Individual GeneticAlgorithm::bestIndividual()
{
    Individual best = Individual(2);
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
    selection->select(population);
}

void GeneticAlgorithm::cross()
{
    crossing->cross(population);
}

void GeneticAlgorithm::mutate()
{
    for (auto &i : population)
        i.mutate(*mutation.get());
}