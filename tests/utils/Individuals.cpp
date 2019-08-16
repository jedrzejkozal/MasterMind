#include "Individuals.hpp"

Individual individualWithAlleleZero() noexcept
{
    auto allelesZeros = std::make_shared<DefaultAllelesTestable>(
        std::initializer_list<unsigned>({0, 0}));
    return Individual(allelesZeros);
}

Individual individualWithAlleleOne() noexcept
{
    auto allelesOnes = std::make_shared<DefaultAllelesTestable>(
        std::initializer_list<unsigned>({1, 1}));
    return Individual(allelesOnes);
}