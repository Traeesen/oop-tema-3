#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "misc.h"

template <typename T>
class WorkDay
{
private:
    std::vector<T> hourlyValues;

public:
    void addHourResult(const T& value)
    {
        hourlyValues.push_back(value);
    }

    const std::vector<T>& getValues() const
    {
        return hourlyValues;
    }

    template<typename Printer>
    void printReport(const std::string& title, Printer printer) const
    {
        std::cout << "\n" << title << ":\n";

        for(int i = 0; i < hourlyValues.size(); i++)
        {
            std::cout << "Hour " << i + 1 << ": ";
            printer(hourlyValues[i]);
            std::cout << '\n';
        }
    }
};