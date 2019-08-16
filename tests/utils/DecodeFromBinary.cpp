#include "DecodeFromBinary.hpp"

unsigned decodeFromBinary(IAlleles *alleles)
{
    unsigned decoded = 0;
    unsigned exponent = 0;
    auto reverseIterators = alleles->reverseIterators();
    auto begin = std::get<0>(reverseIterators);
    auto end = std::get<1>(reverseIterators);
    for (auto bit = begin; bit != end; bit++)
    {
        decoded += *bit * std::pow(2, exponent);
        exponent++;
    }
    return decoded;
};