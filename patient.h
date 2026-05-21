#pragma once
#include <iostream>
#include <vector>
#include <string>

class Patient
{
    std::string name;
    int age;
    std::vector<std::string> problems;
    static int nextId;
    const int id;

public:
    void setName(const std::string& newName);
    std::string getName() const;

    void setAge(const int newAge);
    int getAge() const;

    void setProblems(const std::vector<std::string>& newProblems);
    void addProblem(const std::string& newProblem);
    std::vector<std::string> getProblems() const;
    void removeFirstProblem();

    int getId() const;

    Patient();
    Patient(const std::string& name, const int age);
    Patient(const Patient& other);

    ~Patient();

    friend std::ostream& operator<<(std::ostream& os, const Patient& e);
    Patient& operator=(const Patient& other);
};
