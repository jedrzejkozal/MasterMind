#pragma once

#include "../../src/individual/Individual.hpp"
#include "../testables/DefaultAllelesTestable.hpp"

std::function<float(const Individual &)> getSimpleFitnessFunc() noexcept;