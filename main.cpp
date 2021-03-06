#include <iostream>

#include "src/GeneticAlgorithm.hpp"

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

auto evaluateSequence(std::vector<unsigned> sequence,
                      std::vector<unsigned> sequenceToGuess)
{
    std::vector<bool> usedPlace(8, false);
    unsigned i = 0, correctPlace = 0, correctColor = 0;

    for (auto it = sequence.cbegin(); it != sequence.cend(); it++)
    {
        if (sequenceToGuess[i] == *it)
        {
            correctPlace++;
            usedPlace[i] = true;
        }
        i++;
    }

    for (auto it = sequence.cbegin(); it != sequence.cend(); it++)
        for (unsigned i = 0; i < sequenceToGuess.size(); i++)
            if (*it == sequenceToGuess[i] and not usedPlace[i])
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

std::vector<unsigned> individualToSequence(const Individual individual)
{
    std::vector<unsigned> sequence;
    auto iterators = individual.alleles->constIterators();
    auto cbegin = std::get<0>(iterators);
    auto cend = std::get<1>(iterators);
    for (auto it = cbegin; it != cend; it++)
        sequence.push_back(*it);
    return sequence;
}

void drawRandomSequence(std::vector<std::vector<unsigned>> &proposedSequences,
                        std::vector<unsigned> &proposedCorrectPlaces,
                        std::vector<unsigned> &proposedCorrectColors,
                        const unsigned &sequenceLength,
                        const std::vector<unsigned> sequenceToGuess)
{
    Individual individual(sequenceLength, 0, 8);
    auto sequence = individualToSequence(individual);

    proposedSequences.push_back(sequence);
    auto correctBalls = evaluateSequence(sequence, sequenceToGuess);
    proposedCorrectPlaces.push_back(correctBalls.first);
    proposedCorrectColors.push_back(correctBalls.second);
}

unsigned experiment()
{
    const unsigned short sequenceLength = 6;
    auto sequenceToGuess = drawSequence(sequenceLength);

    std::vector<std::vector<unsigned>> proposedSequences;
    std::vector<unsigned> proposedCorrectPlaces;
    std::vector<unsigned> proposedCorrectColors;

    drawRandomSequence(proposedSequences, proposedCorrectPlaces, proposedCorrectColors,
                       sequenceLength, sequenceToGuess);

    auto mastermindFitness = [&proposedSequences, &proposedCorrectPlaces, &proposedCorrectColors](const Individual &individual) {
        auto sequence = individualToSequence(individual);
        float fitness = 0;
        for (auto i = 0; i < proposedSequences.size(); i++)
        {
            auto correctBalls = evaluateSequence(sequence, proposedSequences[i]);
            fitness -= 2 * abs(proposedCorrectPlaces[i] - correctBalls.first);
            fitness -= abs(proposedCorrectColors[i] - correctBalls.second);
        }

        return fitness;
    };
    auto stopping = [](const float &fitness) { return fitness > 12 - 1 ? true : false; };

    auto genetic = GeneticAlgorithm<Individual>(1000, sequenceLength, 0.95, 0.05,
                                                mastermindFitness,
                                                stopping,
                                                0, 8);
    std::cout << "sequence to guess = ";
    printSequence(sequenceToGuess);
    std::cout << std::endl;
    unsigned round = 1;

    while (proposedCorrectPlaces.back() != sequenceLength)
    {
        genetic.findSolution(1);
        auto best = genetic.bestIndividual();
        auto sequence = individualToSequence(best);

        std::cout << "round " << round << std::endl;
        round++;
        std::cout << "genetic algorithm sequence = ";
        printSequence(best.alleles.get()->iterators());
        std::cout << std::endl;

        float bestFitnessValue = mastermindFitness(best);
        std::cout << "fitnessValue = " << bestFitnessValue << std::endl
                  << std::endl;

        auto correctBalls = evaluateSequence(sequence, sequenceToGuess);

        proposedSequences.push_back(sequence);
        proposedCorrectPlaces.push_back(correctBalls.first);
        proposedCorrectColors.push_back(correctBalls.second);
    }
    return round + 1;
}

int main()
{
    float numberOfTrials = 1000;
    float sum = 0;
    std::vector<unsigned> rounds;

    for (int i = 0; i < numberOfTrials; i++)
    {
        auto r = experiment();
        sum += r;
        rounds.push_back(r);
    }
    std::cout << "[ ";
    for (auto it = rounds.cbegin(); it != rounds.cend(); it++)
        std::cout << *it << ", ";
    std::cout << "]" << std::endl
              << "mean rounds = " << sum / numberOfTrials << std::endl;
    return 0;
}