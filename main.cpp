/*
Numele temei pt review: Pariuri sportive
Nume coleg review: Bugeac Alexandru
*/
#include <fstream>
#include <cstring>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "staff.h"
#include "department.h"
#include "patient.h"
#include "staff.cpp"
#include "patient.cpp"
#include "department.cpp"
#include "exceptions.h"
#include "exceptions.cpp"
#include "hospital.h"
#include "hospital.cpp"
#include "stafffactory.h"
#include "stafffactory.cpp"
#include "workday.h"

int main()
{
    try
    {
        Hospital& hospital = Hospital::getInstance();

        hospital.simulateDay();
        hospital.printFinalReport();

        return 0;
    }
    catch(const HospitalException& e)
    {
        std::cout << "Hospital error: " << e.what() << "\n";
    }
    catch(const std::exception& e)
    {
        std::cout << "Standard error: " << e.what() << "\n";
    }
}