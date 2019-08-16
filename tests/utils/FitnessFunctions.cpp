#include "FitnessFunctions.hpp"

std::function<float(const Individual &)> getSimpleFitnessFunc() noexcept
{
    return [](const Individual &i) {
        auto alleles_iterators = dynamic_cast<DefaultAllelesTestable *>(i.alleles.get())->iterators();
        return float(*std::get<0>(alleles_iterators));
    };
}