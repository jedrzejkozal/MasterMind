#pragma once

#include <array>
#include <vector>
#include <tuple>

#include "Probabilistic.hpp"

class IAlleles
{
public:
    virtual ~IAlleles() = default;

    virtual void switch_allele_at(std::vector<unsigned>::iterator &iterator) = 0;
    using AllelesIterators = std::tuple<std::vector<unsigned>::iterator, std::vector<unsigned>::iterator>;
    virtual AllelesIterators iterators() = 0;
};

class DefaultAlleles : public IAlleles
{
public:
    DefaultAlleles(unsigned allelesSize,
                   unsigned minAllelesValue,
                   unsigned maxAllelesValue);
    virtual ~DefaultAlleles() = default;

    virtual void switch_allele_at(std::vector<unsigned>::iterator &iterator) override;
    virtual AllelesIterators iterators() override;

protected:
    std::vector<unsigned> alleles;
    unsigned minAllelesValue;
    unsigned maxAllelesValue;
};
