#pragma once
#include <string>
#include <iostream>

class HospitalObserver
{
public:
    virtual void onHospitalEvent(const std::string& message) = 0;
};

class ConsoleObserver : public HospitalObserver
{
public:
    void onHospitalEvent(const std::string& message) override
    {
        std::cout << message << "\n";
    }
};