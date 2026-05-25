#pragma once

#include <vector>
#include <memory>

#include "department.h"
#include "patient.h"
#include "workday.h"
#include "observer.h"

class Hospital
{
    std::vector<Department> departments;
    std::vector<std::shared_ptr<Patient>> waitingQueue;
    std::vector<std::shared_ptr<Patient>> emergencyCallsQueue;
    std::vector<std::shared_ptr<Patient>> callsByHour[9];
    std::vector<std::shared_ptr<Patient>> appointmentsByHour[9];
    std::vector<std::shared_ptr<Staff>> staff;

    WorkDay<int> moneyWastedPerHour;
    WorkDay<std::vector<std::string>> inactiveStaffPerHour;

    Hospital();

    void loadDoctors(const std::string& filename);
    void loadNurses(const std::string& filename);
    void loadAdmins(const std::string& filename);
    void loadEmergencyOperators(const std::string& filename);
    void loadPatients(const std::string& filename);
    void loadCalls(const std::string& filename);
    void loadAppointments(const std::string& filename);
    std::shared_ptr<Patient> readPatientFromLine(std::ifstream& fin, bool hasHour, int& hour);
    void processAppointments(int hour);
    void processCalls(int hour);
    std::vector<std::shared_ptr<HospitalObserver>> observers;

public:
    Hospital(const Hospital&) = delete;
    Hospital& operator=(const Hospital&) = delete;

    static Hospital& getInstance();

    void addDepartment(const Department& department);
    std::vector<Department>& getDepartments();
    void addPatient(std::shared_ptr<Patient> patient);
    std::vector<std::shared_ptr<Patient>>& getWaitingQueue();

    void addObserver(std::shared_ptr<HospitalObserver> observer);
    void notifyObservers(const std::string& message);

    void simulateDay();
    void printFinalReport() const;
    
};