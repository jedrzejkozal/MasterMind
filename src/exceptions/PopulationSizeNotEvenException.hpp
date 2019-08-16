#include <exception>

class PopulationSizeNotEvenException : public std::exception
{
public:
    const char *what() const noexcept
    {
        return "Population size is not even";
    }
};