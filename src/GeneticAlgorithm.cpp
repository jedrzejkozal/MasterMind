// #include <iostream>
// #include <algorithm>

// #include "GeneticAlgorithm.hpp"
// #include "exceptions/PopulationSizeNotEvenException.hpp"
// #include "exceptions/PopulationSizeToSmallException.hpp"

// template <typename IndividualType>
// void GeneticAlgorithm<IndividualType>::findSolution(const unsigned &rounds)
// {
//     for (unsigned iterations = 0; iterations < rounds; iterations++)
//     {
//         select();
//         cross();
//         mutate();
//         updateFitness();
//         if (checkStoppingCondintion())
//         {
//             std::cout << "Early stop at iteration " << iterations << std::endl;
//             break;
//         }
//     }
// }

// template <typename IndividualType>
// bool GeneticAlgorithm<IndividualType>::checkStoppingCondintion() const
// {
//     for (const auto &individual : population)
//         if (stoppingFunction(individual.fitness))
//             return true;
//     return false;
// }

// template <typename IndividualType>
// Individual GeneticAlgorithm<IndividualType>::bestIndividual()
// {
//     Individual best(2);
//     float maxFitness = 0;
//     for (auto &individual : population)
//         if (individual.fitness > maxFitness)
//         {
//             maxFitness = individual.fitness;
//             best = individual;
//         }
//     return best;
// }

// template <typename IndividualType>
// void GeneticAlgorithm<IndividualType>::select()
// {
//     populationSizeCheck();
//     selection->select(population);
// }

// template <typename IndividualType>
// void GeneticAlgorithm<IndividualType>::cross()
// {
//     evenPopulationSizeCheck();
//     crossing->cross(population);
// }

// template <typename IndividualType>
// void GeneticAlgorithm<IndividualType>::mutate()
// {
//     for (auto &i : population)
//         i.mutate(*mutation.get());
// }

// template <typename IndividualType>
// void GeneticAlgorithm<IndividualType>::updateFitness()
// {
//     fitnessCalculator.updateFitness(population);
// }

// template <typename IndividualType>
// void GeneticAlgorithm<IndividualType>::populationSizeCheck() const
// {
//     if (population.size() < 2)
//         throw PopulationSizeToSmallException();
// }

// template <typename IndividualType>
// void GeneticAlgorithm<IndividualType>::evenPopulationSizeCheck() const
// {
//     if (population.size() % 2 != 0)
//         throw PopulationSizeNotEvenException();
// }