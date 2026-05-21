#include <iostream>
#include <vector>
#include "patient.h"
#include "exceptions.h"

//setter-e/getter-e

void Patient::setName(const std::string& newName)
{
    name = newName;
}
std::string Patient::getName() const
{
    return name;
}
void Patient::setAge(const int newAge)
{
    if(newAge < 0 || newAge > 120) throw InvalidAgeException();
    age = newAge;
}
int Patient::getAge() const
{
    return age;
}

void Patient::setProblems(const std::vector<std::string>& newProblems)
{
    problems = newProblems;
}
void Patient::addProblem(const std::string& newProblem)
{
    problems.push_back(newProblem);
}
std::vector<std::string> Patient::getProblems() const
{
    return problems;
}
void Patient::removeFirstProblem()
{
    if (!problems.empty())
    {
        problems.erase(problems.begin());
    }
}


int Patient::getId() const
{
    return id;
}

//constructori

int Patient::nextId = 1;

Patient::Patient() : name(""), age(0), id(nextId++)
{
}

Patient::Patient(const std::string& name, const int age) : name(name), age(age), id(nextId++)
{
    if(age < 0 || age > 120) throw InvalidAgeException();
}

Patient::Patient(const Patient& other) : name(other.name), age(other.age), problems(other.problems), id(nextId++)
{
}

//destructor

Patient::~Patient()
{
}

//operatori

Patient& Patient::operator=(const Patient& other)
{
    if (this == &other)
        return *this;

    name = other.name;
    age = other.age;
    problems = other.problems;

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Patient& e)
{
    os << "Name: " << e.name << ", Age: " << e.age << ", ID: " << e.id;
    return os;
}