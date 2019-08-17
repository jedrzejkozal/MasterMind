#include "DefaultAlleles.hpp"

DefaultAlleles::DefaultAlleles(const unsigned &allelesSize,
                               const unsigned &min,
                               const unsigned &max)
    : alleles(allelesSize, 0),
      minAllelesValue(min),
      maxAllelesValue(max)
{
    Probabilistic probabilistic;
    for (auto it = alleles.begin(); it != alleles.end(); it++)
        *it = probabilistic.uniform_int(minAllelesValue, maxAllelesValue);
}

std::shared_ptr<IAlleles> DefaultAlleles::copy()
{
    return std::make_shared<DefaultAlleles>(*this);
}

void DefaultAlleles::switch_allele_at(std::vector<unsigned>::iterator &iterator)
{
    (*iterator)++;
    if (*iterator > maxAllelesValue)
        *iterator = minAllelesValue;
}

unsigned DefaultAlleles::size() const
{
    return alleles.size();
}

DefaultAlleles::AllelesIterators DefaultAlleles::iterators()
{
    return std::make_tuple(std::begin(alleles), std::end(alleles));
}

DefaultAlleles::AllelesConstIterators DefaultAlleles::constIterators() const
{
    return std::make_tuple(std::cbegin(alleles), std::cend(alleles));
}

DefaultAlleles::AllelesReverseIterators DefaultAlleles::reverseIterators()
{
    return std::make_tuple(std::rbegin(alleles), std::rend(alleles));
}
