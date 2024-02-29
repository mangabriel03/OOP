#pragma once
#include "Domain.h"
#include "Repository.h"
#include <string>
#include <vector>
#include <functional>
#include "Validator.h"

using std::vector;
using std::function;

class Controller {
    InMemoryRepository& repository;
    Validator& validator;

public:
    Controller(InMemoryRepository& repository, Validator& validator) :repository{ repository }, validator{ validator } {
    }

    //nu permitem copierea de obiecte PetStore
    //Controller(const Controller& other) = delete;


    const vector<ElectricScooter>& getAll() noexcept{
        {
            return repository.getAll();
        }
    }

    ElectricScooter &findElectricScooterController(const string& id);


    void addController(const string& id, const string& model, const int& kilometers, const string& lastLocation, const string& currentState,const Data& commissioningDate);


    void deleteController(const string& id);

    void updateController(const string& id, const string& model, const int& kilometers, const string& lastLocation, const string& currentState,const Data& commissioningDate);

    void reserveController(const string& id);

    void useController(const string& id);

    void parkController(const string& id, const string& location);

    vector<ElectricScooter> sortByCommissioningDate();
    vector<ElectricScooter> sortById();
    vector<ElectricScooter> sortByModel();
    vector<ElectricScooter> sortByLastLocation();
    vector<ElectricScooter> sortByCurrentState();
    vector<ElectricScooter> sortByKilometers();

    vector<ElectricScooter> filterByLocation(string location);

    vector<ElectricScooter> filterByLocationAndCurrentState(string location);

    vector<ElectricScooter> filterByReserved();

};
//void testController();
