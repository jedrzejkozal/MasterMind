#include "PrintAlleles.hpp"

void printAlleles(const IAlleles &alleles)
{
    auto iterators = alleles.constIterators();
    auto begin = std::get<0>(iterators);
    auto end = std::get<1>(iterators);

    for (auto it = begin; it != end; it++)
        std::cout << *it;
    std::cout << std::endl;
}
