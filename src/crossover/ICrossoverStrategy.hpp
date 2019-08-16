#include <vector>

#include "../Individual.hpp"

template <typename IndividualType = Individual>
class ICrossoverStrategy
{
public:
    virtual ~ICrossoverStrategy() = default;

    virtual void cross(std::vector<IndividualType> &matingPool) = 0;
};
