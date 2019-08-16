#pragma once

#include "../../src/Individual.hpp"
#include "../testables/DefaultAllelesTestable.hpp"

std::function<float(const Individual &)> getSimpleFitnessFunc() noexcept;