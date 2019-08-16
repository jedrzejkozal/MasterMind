#include <exception>

class AllelesSizeToSmallException : public std::exception
{
public:
    const char *what() const noexcept
    {
        return "Alleles size should be at least 2";
    }
};