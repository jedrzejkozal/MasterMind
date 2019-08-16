#pragma once

#include <array>
#include <vector>
#include <tuple>
#include <memory>

#include "Probabilistic.hpp"

class IAlleles
{
public:
    virtual ~IAlleles() = default;

    virtual std::shared_ptr<IAlleles> copy() = 0;

    virtual void switch_allele_at(std::vector<unsigned>::iterator &iterator) = 0;
    virtual unsigned size() const = 0;

    using AllelesIterators = std::tuple<std::vector<unsigned>::iterator,
                                        std::vector<unsigned>::iterator>;
    virtual AllelesIterators iterators() = 0;
    using AllelesConstIterators = std::tuple<std::vector<unsigned>::const_iterator,
                                             std::vector<unsigned>::const_iterator>;
    virtual AllelesConstIterators constIterators() const = 0;
    using AllelesReverseIterators = std::tuple<std::vector<unsigned>::reverse_iterator,
                                               std::vector<unsigned>::reverse_iterator>;
    virtual AllelesReverseIterators reverseIterators() = 0;
};

class DefaultAlleles : public IAlleles
{
public:
    DefaultAlleles(unsigned allelesSize,
                   unsigned minAllelesValue,
                   unsigned maxAllelesValue);
    virtual ~DefaultAlleles() = default;

    virtual std::shared_ptr<IAlleles> copy() override;

    virtual void switch_allele_at(std::vector<unsigned>::iterator &iterator) override;
    virtual unsigned size() const override;

    virtual AllelesIterators iterators() override;
    virtual AllelesConstIterators constIterators() const override;
    virtual AllelesReverseIterators reverseIterators() override;

protected:
    std::vector<unsigned> alleles;
    unsigned minAllelesValue;
    unsigned maxAllelesValue;
};
