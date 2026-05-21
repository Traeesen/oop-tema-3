#pragma once
#include <exception>
#include <string>

class HospitalException : public std::exception
{
    std::string message;

public:
    HospitalException(const std::string& message);

    const char* what() const noexcept override;
};

class InvalidAgeException : public HospitalException
{
public:
    InvalidAgeException();
};

class InvalidSalaryException : public HospitalException
{
public:
    InvalidSalaryException();
};

class FileOpenException : public HospitalException
{
public:
    FileOpenException(const std::string& filename);
};