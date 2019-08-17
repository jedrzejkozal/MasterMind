#pragma once

#include <memory>

#include "IndividualBase.hpp"
#include "../alleles/IAlleles.hpp"

class IndividualTwoAlleles : public IndividualBase
{
public:
    IndividualTwoAlleles(const unsigned &allelesSize);
    IndividualTwoAlleles(const IndividualTwoAlleles &lhs);
    IndividualTwoAlleles(IndividualTwoAlleles &&rhs);
    ~IndividualTwoAlleles() = default;
    IndividualTwoAlleles &operator=(const IndividualTwoAlleles &lhs);
    IndividualTwoAlleles &operator=(IndividualTwoAlleles &&rhs);

    virtual void mutate(IMutationStrategy &mutation) override;
    virtual void mate(IndividualBase &lhs, const unsigned &crossingSpot) override;
    virtual unsigned allelesSize() const override;

    std::shared_ptr<IAlleles> alleles_x;
    std::shared_ptr<IAlleles> alleles_y;
};
