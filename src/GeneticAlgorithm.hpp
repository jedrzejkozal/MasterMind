#pragma once

#include <functional>

#include "crossover/DefaultCrossover.hpp"
#include "mutation/IMutationStrategy.hpp"
#include "mutation/DefaultMutation.hpp"
#include "selection/DefaultSelection.hpp"
#include "Individual.hpp"
#include "FitnessCalculator.hpp"

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(unsigned popSize,
                     unsigned allelesSize,
                     float crossoverProb,
                     float mutationProb,
                     const std::function<float(const Individual &)> fitnessFunc,
                     const std::function<bool(const float &)> stoppingFunc = [](const float &fitness) { return false; })
        : selection(std::make_unique<DefaultSelection>()),
          crossing(std::make_unique<DefaultCrossover>(std::move(DefaultCrossover(crossoverProb)))),
          mutation(std::make_unique<DefaultMutation>(std::move(DefaultMutation(mutationProb)))),
          fitnessCalculator(std::move(fitnessFunc)),
          stoppingFunction(std::move(stoppingFunc))
    {
        initialisePopulation(popSize, allelesSize);
    }

    GeneticAlgorithm(unsigned popSize,
                     unsigned allelesSize,
                     const std::function<float(const Individual &)> fitnessFunction,
                     std::unique_ptr<ICrossoverStrategy> &&crossingStrategy,
                     std::unique_ptr<IMutationStrategy> &&mutationStrategy)
        : GeneticAlgorithm(popSize, allelesSize, 0.0, 0.0, fitnessFunction)
    {
        crossing.release();
        crossing = std::move(crossingStrategy);
        crossing.release();
        mutation = std::move(mutationStrategy);
    }

    void findSolution(const unsigned &rounds);
    Individual bestIndividual();

private:
    void initialisePopulation(unsigned populationSize, unsigned allelesSize);
    bool checkStoppingCondintion() const;
    void mutate();
    void select();
    void cross();
    void updateFitness();

    std::vector<Individual> population;
    std::unique_ptr<ISelectionStrategy> selection;
    std::unique_ptr<ICrossoverStrategy> crossing;
    std::unique_ptr<IMutationStrategy> mutation;
    FitnessCalculator fitnessCalculator;

    std::function<bool(const float &)> stoppingFunction;
};