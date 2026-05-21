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

    void printReport(const std::string& title) const
    {
        std::cout << "\n" << title << ":\n";

        for(int i = 0; i < hourlyValues.size(); i++)
        {
            std::cout << "Hour " << i + 1 << ": ";
            std::cout << hourlyValues[i] << "\n";
        }
    }
    void printReportCollection(const std::string& title) const
    {
        std::cout << "\n" << title << ":\n";

        for(int i = 0; i < hourlyValues.size(); i++)
        {
            std::cout << "Hour " << i + 1 << ": ";

            if(hourlyValues[i].empty())
                std::cout << "none\n";
            else
                printCollection(hourlyValues[i]);
            std::cout << '\n';
        }
    }
};