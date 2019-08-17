#pragma once

#include <exception>

class PopulationSizeToSmallException : public std::exception
{
public:
    const char *what() const noexcept
    {
        return "Population size is less then 2";
    }
};