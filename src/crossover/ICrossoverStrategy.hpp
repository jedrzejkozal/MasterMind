#include <vector>

#include "../Individual.hpp"

class ICrossoverStrategy
{
public:
    virtual ~ICrossoverStrategy() = default;

    virtual void cross(std::vector<Individual> &matingPool) = 0;
};
