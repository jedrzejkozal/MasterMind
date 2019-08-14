#include "IAlleles.hpp"

DefaultAlleles::DefaultAlleles(unsigned allelesSize,
                               unsigned min,
                               unsigned max)
    : alleles(allelesSize, 0),
      minAllelesValue(min),
      maxAllelesValue(max)
{
    Probabilistic p;
    for (auto it = alleles.begin(); it != alleles.end(); it++)
        *it = p.uniform(minAllelesValue, maxAllelesValue);
}

void DefaultAlleles::switch_allele_at(std::vector<unsigned>::iterator &iterator)
{
    (*iterator)++;
    if (*iterator > maxAllelesValue)
        *iterator = minAllelesValue;
}

DefaultAlleles::AllelesIterators DefaultAlleles::iterators()
{
    return std::make_tuple(std::begin(alleles), std::end(alleles));
}