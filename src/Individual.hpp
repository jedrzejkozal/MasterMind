#pragma once

#include <memory>

#include "IndividualBase.hpp"
#include "alleles/IAlleles.hpp"

class Individual : public IndividualBase
{
public:
    Individual(const unsigned &allelesSize);
    Individual(std::shared_ptr<IAlleles> allelesArg);
    Individual(const Individual &lhs);
    Individual(Individual &&rhs);
    virtual ~Individual() = default;
    Individual &operator=(const Individual &lhs);
    Individual &operator=(Individual &&rhs);

    virtual void mutate(IMutationStrategy &mutation) override;
    virtual void mate(IndividualBase &lhs, const unsigned &crossingSpot) override;
    virtual unsigned allelesSize() const override;

    std::shared_ptr<IAlleles> alleles;
};
