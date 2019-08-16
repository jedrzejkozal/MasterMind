#pragma once

#include <algorithm>

#include "../../src/mutation/DefaultMutation.hpp"

class DefaultAllelesTestable : public DefaultAlleles
{
public:
    DefaultAllelesTestable(std::initializer_list<unsigned> allelesArg)
        : DefaultAlleles(1, 0, 1)
    {
        alleles = allelesArg;
    }

    DefaultAllelesTestable(std::vector<unsigned> allelesArg)
        : DefaultAlleles(1, 0, 1)
    {
        alleles = allelesArg;
    }

    virtual std::shared_ptr<IAlleles> copy() override
    {
        return std::make_shared<DefaultAllelesTestable>(*this);
    }

    bool allelesEqual(std::initializer_list<unsigned> expected)
    {
        auto expected_vec = std::vector<unsigned>(expected);
        return std::equal(alleles.begin(), alleles.end(), expected_vec.begin());
    }

    unsigned countOnes()
    {
        return std::count_if(alleles.begin(), alleles.end(), [](const unsigned &lhs) { return lhs == 1; });
    }
};