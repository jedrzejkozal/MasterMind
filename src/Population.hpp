#pragma once

#include <functional>

#include "Individual.hpp"
#include "ICrossingStrategy.hpp"
#include "DefaultCrossing.hpp"
#include "IMutationStrategy.hpp"
#include "DefaultMutation.hpp"

class Population
{
public:
    Population(unsigned popSize,
               unsigned allelesSize,
               float mutationProb,
               float crossingProb,
               const std::function<float(const Individual &)> fitnessFunction)
        : crossing(std::make_unique<DefaultCrossing>(std::move(DefaultCrossing(crossingProb, fitnessFunction)))),
          mutation(std::make_unique<DefaultMutation>(std::move(DefaultMutation(mutationProb))))
    {
    }

    Population(unsigned popSize,
               unsigned allelesSize,
               const std::function<float(const Individual &)> fitnessFunction,
               std::unique_ptr<ICrossingStrategy> &&crossingStrategy,
               std::unique_ptr<IMutationStrategy> &&mutationStrategy)
        : Population(popSize, allelesSize, 0.0, 0.0, fitnessFunction)
    {
        crossing.release();
        crossing = std::move(crossingStrategy);
        crossing.release();
        mutation = std::move(mutationStrategy);
    }

private:
    void mutate();
    void cross();

    std::vector<Individual> population;
    std::unique_ptr<ICrossingStrategy> crossing;
    std::unique_ptr<IMutationStrategy> mutation;
};

void Population::cross()
{
    crossing->cross(population);
}

void Population::mutate()
{
    for (auto &i : population)
        i.mutate(*mutation.get());
}