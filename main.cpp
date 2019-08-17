#include <iostream>

#include "src/GeneticAlgorithm.hpp"

// enum color
// {
//     white = 0,
//     red = 1,
//     green = 2,
//     purple = 3,
//     turquoise = 4,
//     gray = 5,
//     blue = 6,
//     yellow = 7,
//     black = 8
// };

std::vector<unsigned> drawSequence(const unsigned short &sequenceLength)
{
    std::vector<unsigned> sequence;
    Probabilistic probabilistic;
    while (sequence.size() != sequenceLength)
    {
        sequence.push_back(probabilistic.uniform_int(0, 8));
    }
    return sequence;
}

auto evaluateSequence(std::vector<unsigned>::iterator sequenceBegin,
                      std::vector<unsigned>::iterator sequenceEnd,
                      std::vector<unsigned> correctsequence)
{
    std::vector<bool> usedPlace(8, false);
    unsigned i = 0, correctPlace = 0, correctColor = 0;

    for (auto it = sequenceBegin; it != sequenceEnd; it++)
    {
        if (correctsequence[i] == *it)
        {
            correctPlace++;
            usedPlace[i] = true;
        }
        i++;
    }

    for (auto it = sequenceBegin; it != sequenceEnd; it++)
        for (unsigned i = 0; i < correctsequence.size(); i++)
            if (*it == correctsequence[i] and not usedPlace[i])
            {
                correctColor++;
                usedPlace[i] = true;
                break;
            }
    return std::make_pair<unsigned, unsigned>(std::move(correctPlace),
                                              std::move(correctColor));
}

void printSequence(std::vector<unsigned> sequence)
{
    for (auto &elem : sequence)
        std::cout << elem;
}

void printSequence(std::tuple<std::vector<unsigned>::iterator, std::vector<unsigned>::iterator> iterators)
{
    auto begin = std::get<0>(iterators);
    auto end = std::get<1>(iterators);
    for (auto it = begin; it != end; it++)
        std::cout << *it;
}

int main()
{
    const unsigned short sequenceLength = 6;
    auto sequence = drawSequence(sequenceLength);

    auto mastermindFitness = [&sequence](const Individual &individual) {
        auto iterators = individual.alleles.get()->iterators();
        auto begin = std::get<0>(iterators);
        auto end = std::get<1>(iterators);

        auto correct = evaluateSequence(begin, end, sequence);

        return 2 * correct.first + correct.second;
    };
    auto stopping = [](const float &fitness) { return fitness > 12 - 1 ? true : false; };

    auto genetic = GeneticAlgorithm<Individual>(100, sequenceLength, 0.9, 0.01,
                                                mastermindFitness,
                                                stopping,
                                                0, 8);
    genetic.findSolution(100);
    auto best = genetic.bestIndividual();

    std::cout << "sequence to guess = ";
    printSequence(sequence);
    std::cout << std::endl
              << "genetic algorithm sequence = ";
    printSequence(best.alleles.get()->iterators());
    std::cout << std::endl;

    float bestFitnessValue = mastermindFitness(best);
    std::cout << "bestFitnessValue = " << bestFitnessValue << std::endl;

    return 0;
}