#include "exceptions.h"

// HospitalException

HospitalException::HospitalException(const std::string& message) : message(message)
{
}

const char* HospitalException::what() const noexcept
{
    return message.c_str();
}

// InvalidAgeException

InvalidAgeException::InvalidAgeException() : HospitalException("Invalid patient age.")
{
}

// InvalidSalaryException

InvalidSalaryException::InvalidSalaryException() : HospitalException("Invalid staff salary.")
{
}

// FileOpenException

FileOpenException::FileOpenException(const std::string& filename)
    : HospitalException("Could not open file: " + filename)
{
}