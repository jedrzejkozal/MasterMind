#pragma once

#include <functional>
#include <iostream>
#include <algorithm>

#include "crossover/DefaultCrossover.hpp"
#include "mutation/IMutationStrategy.hpp"
#include "mutation/DefaultMutation.hpp"
#include "selection/DefaultSelection.hpp"
#include "individual/Individual.hpp"
#include "FitnessCalculator.hpp"

#include "exceptions/PopulationSizeNotEvenException.hpp"
#include "exceptions/PopulationSizeToSmallException.hpp"

template <typename IndividualType = Individual>
class GeneticAlgorithm
{
public:
    template <typename... IndividualConstructorArgs>
    GeneticAlgorithm(const unsigned &popSize,
                     const unsigned &allelesSize,
                     float crossoverProb,
                     float mutationProb,
                     const std::function<float(const IndividualType &)> fitnessFunc,
                     const std::function<bool(const float &)> stoppingFunc = [](const float &fitness) { return false; },
                     IndividualConstructorArgs... args)
        : selection(std::make_unique<DefaultSelection<IndividualType>>()),
          crossing(std::make_unique<DefaultCrossover<IndividualType>>(std::move(DefaultCrossover<IndividualType>(crossoverProb)))),
          mutation(std::make_unique<DefaultMutation>(std::move(DefaultMutation(mutationProb)))),
          fitnessCalculator(std::move(fitnessFunc)),
          stoppingFunction(std::move(stoppingFunc))
    {
        initialisePopulation(popSize, allelesSize, args...);
    }

    GeneticAlgorithm(const unsigned &popSize,
                     const unsigned &allelesSize,
                     const std::function<float(const IndividualType &)> fitnessFunction,
                     std::unique_ptr<ICrossoverStrategy<IndividualType>> &&crossingStrategy,
                     std::unique_ptr<IMutationStrategy> &&mutationStrategy)
        : GeneticAlgorithm(popSize, allelesSize, 0.0, 0.0, fitnessFunction)
    {
        crossing.release();
        crossing = std::move(crossingStrategy);
        crossing.release();
        mutation = std::move(mutationStrategy);
    }

    void findSolution(const unsigned &rounds);
    IndividualType bestIndividual();

private:
    template <typename... IndividualConstructorArgs>
    void initialisePopulation(unsigned populationSize,
                              const unsigned &allelesSize,
                              IndividualConstructorArgs... args);
    bool checkStoppingCondintion() const;
    void mutate();
    void select();
    void cross();
    void updateFitness();
    void evenPopulationSizeCheck() const;
    void populationSizeCheck() const;

    std::vector<IndividualType> population;
    std::unique_ptr<ISelectionStrategy<IndividualType>> selection;
    std::unique_ptr<ICrossoverStrategy<IndividualType>> crossing;
    std::unique_ptr<IMutationStrategy> mutation;
    FitnessCalculator<IndividualType> fitnessCalculator;

    std::function<bool(const float &)> stoppingFunction;
};

template <typename IndividualType>
template <typename... IndividualConstructorArgs>
void GeneticAlgorithm<IndividualType>::initialisePopulation(unsigned populationSize,
                                                            const unsigned &allelesSize,
                                                            IndividualConstructorArgs... args)
{
    while (populationSize > 0)
    {
        population.push_back(IndividualType(allelesSize, args...));
        populationSize--;
    }
    fitnessCalculator.updateFitness(population);
}

template <typename IndividualType>
void GeneticAlgorithm<IndividualType>::findSolution(const unsigned &rounds)
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

template <typename IndividualType>
bool GeneticAlgorithm<IndividualType>::checkStoppingCondintion() const
{
    for (const auto &individual : population)
        if (stoppingFunction(individual.fitness))
            return true;
    return false;
}

template <typename IndividualType>
IndividualType GeneticAlgorithm<IndividualType>::bestIndividual()
{
    IndividualType best(2);
    float maxFitness = 0;
    for (auto &individual : population)
        if (individual.fitness > maxFitness)
        {
            maxFitness = individual.fitness;
            best = individual;
        }
    return best;
}

template <typename IndividualType>
void GeneticAlgorithm<IndividualType>::select()
{
    populationSizeCheck();
    selection->select(population);
}

template <typename IndividualType>
void GeneticAlgorithm<IndividualType>::cross()
{
    evenPopulationSizeCheck();
    crossing->cross(population);
}

template <typename IndividualType>
void GeneticAlgorithm<IndividualType>::mutate()
{
    for (auto &i : population)
        i.mutate(*mutation.get());
}

template <typename IndividualType>
void GeneticAlgorithm<IndividualType>::updateFitness()
{
    fitnessCalculator.updateFitness(population);
}

template <typename IndividualType>
void GeneticAlgorithm<IndividualType>::populationSizeCheck() const
{
    if (population.size() < 2)
        throw PopulationSizeToSmallException();
}

template <typename IndividualType>
void GeneticAlgorithm<IndividualType>::evenPopulationSizeCheck() const
{
    if (population.size() % 2 != 0)
        throw PopulationSizeNotEvenException();
}