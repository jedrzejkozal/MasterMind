#include <iostream>
#include "src/Population.hpp"

int main()
{
    auto loss = [](const Individual &) { return 0.0; };
    auto pop = Population(10, 5, 0.1, 0.8, loss);
    std::cout << "Its working" << std::endl;
    return 0;
}