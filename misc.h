#pragma once

#include <vector>
#include <memory>
#include <iostream>

template<typename T>
void printCollection(const std::vector<T>& items)
{
    for(const auto& item : items)
    {
        std::cout << item << ' ';
    }
}