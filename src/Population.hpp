#pragma once

#include <functional>

#include "Individual.hpp"
#include "DefaultSelection.hpp"
#include "DefaultCrossover.hpp"
#include "IMutationStrategy.hpp"
#include "DefaultMutation.hpp"

class Population
{
public:
    Population(unsigned popSize,
               unsigned allelesSize,
               float crossoverProb,
               float mutationProb,
               const std::function<float(const Individual &)> fitnessFunction)
        : selection(std::make_unique<DefaultSelection>(std::move(DefaultSelection(fitnessFunction)))),
          crossing(std::make_unique<DefaultCrossover>(std::move(DefaultCrossover(crossoverProb)))),
          mutation(std::make_unique<DefaultMutation>(std::move(DefaultMutation(mutationProb))))
    {
        initialisePopulation(popSize, allelesSize);
    }

    Population(unsigned popSize,
               unsigned allelesSize,
               const std::function<float(const Individual &)> fitnessFunction,
               std::unique_ptr<ICrossoverStrategy> &&crossingStrategy,
               std::unique_ptr<IMutationStrategy> &&mutationStrategy)
        : Population(popSize, allelesSize, 0.0, 0.0, fitnessFunction)
    {
        crossing.release();
        crossing = std::move(crossingStrategy);
        crossing.release();
        mutation = std::move(mutationStrategy);
    }

private:
    void initialisePopulation(unsigned populationSize, unsigned allelesSize);
    void mutate();
    void select();
    void cross();

    std::vector<Individual> population;
    std::unique_ptr<ISelectionStrategy> selection;
    std::unique_ptr<ICrossoverStrategy> crossing;
    std::unique_ptr<IMutationStrategy> mutation;
};