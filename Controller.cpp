#include "Controller.h"
#include <functional>
#include <algorithm>
#include <assert.h>
#include <string.h>
using namespace std;
/**
 CLASA CONTROLLER
 primeste date de la UI
 isi creeaza un obiect
 il trimite la validator si apoi la repo pentru a fi adaugat/sters/modificat
 sortari, filtrari
 se arunca erori de tip validError (de ex cand introduc o data numerica negativa, un string vid, o data calendaristica nevalida, o stare nevalida, etc)
*/

/**
 Primeste date de la Ui
 creeaza un obiect de tip ElectricScooter
 il trimite la validator
 il trimite la repo, pentru a fi adaugat
*/

ElectricScooter & Controller::findElectricScooterController(const string& id){
    ElectricScooter electricScooter=repository.findElectricScooter(id);
    return electricScooter;
}

void Controller::addController(const string& id, const string& model, const int& kilometers, const string& lastLocation, const string&  currentState, const Data& commissioningDate){
    ElectricScooter electricScooter{ id,model,kilometers,lastLocation,currentState,commissioningDate};
    //validator.validate(electricScooter);
    repository.addRepo(electricScooter);
}


/**
 Primeste date de la UI
 creeaza un obiect de tip ElectricScooter
 il trimite la validator
 il trimite la repo, pentru a fi sters
*/
void Controller::deleteController(const string& id){
    ElectricScooter electricScooter=repository.findElectricScooter(id);
    validator.validate(electricScooter);
    repository.deleteRepo(electricScooter);
}


/**
 Primeste date de la UI
 creeaza un obiect de tip ElectricScooter
 il trimite la validator
 il trimite la repo, pentru a fi modificat
*/
void Controller::updateController(const string& id, const string& model, const int& kilometers, const string& lastLocation, const string& currentState,const Data& commissioningDate){
    ElectricScooter electricScooter{ id,model,kilometers,lastLocation,currentState,commissioningDate};
    validator.validate(electricScooter);
    repository.updateRepo(electricScooter);
}


/**
 Primeste de la Ui id-ul unui obiect de tip electricScooter si il trimite la repo pentru a fi rezervat
 */
void Controller::reserveController(const string& id){
    repository.reserveRepo(id);
}


/**
 Primeste de la Ui id-ul unui obiect de tip electricScooter si il trimite la repo pentru a fi folosit
 */
void Controller::useController(const string& id){
    repository.useRepo(id);
}


/**
 Primeste de la Ui id-ul unui obiect de tip electricScooter si ultima locatie apoi le trimite la repo pentru a fi parcat
 */
void Controller::parkController(const string& id, const string& location){
    repository.parkRepo(id,location);
}


/**
 Primeste de la repository lista cu toate electricScooters (getAll)
 le ordoneaza dupa commissioning data si returneaza lista sortata
*/
vector<ElectricScooter> Controller::sortByCommissioningDate(){
    vector<ElectricScooter> electricScootersList = repository.getAll();//fac o copie
    for (int i = 0; i < electricScootersList.size(); i++) {
        for (int j = i + 1; j < electricScootersList.size(); j++) {
            if (cmpCommissioningData(electricScootersList[i], electricScootersList[j]) == 1) { // crescator dupa data
                ElectricScooter aux = electricScootersList[i];
                electricScootersList[i] = electricScootersList[j];
                electricScootersList[j] =  aux;
            }
        }
    }
    return electricScootersList;
}

vector<ElectricScooter> Controller::sortById(){
    vector<ElectricScooter> electricScootersList = repository.getAll();//fac o copie
    for (int i = 0; i < electricScootersList.size(); i++) {
        for (int j = i + 1; j < electricScootersList.size(); j++) {
            if (cmpId(electricScootersList[i], electricScootersList[j]) == 1) { // crescator dupa id
                ElectricScooter aux = electricScootersList[i];
                electricScootersList[i] = electricScootersList[j];
                electricScootersList[j] =  aux;
            }
        }
    }
    return electricScootersList;
}

vector<ElectricScooter> Controller::sortByModel(){
    vector<ElectricScooter> electricScootersList = repository.getAll();//fac o copie
    for (int i = 0; i < electricScootersList.size(); i++) {
        for (int j = i + 1; j < electricScootersList.size(); j++) {
            if (cmpModel(electricScootersList[i], electricScootersList[j]) == 1) { // crescator dupa data
                ElectricScooter aux = electricScootersList[i];
                electricScootersList[i] = electricScootersList[j];
                electricScootersList[j] =  aux;
            }
        }
    }
    return electricScootersList;
}

vector<ElectricScooter> Controller::sortByLastLocation(){
    vector<ElectricScooter> electricScootersList = repository.getAll();//fac o copie
    for (int i = 0; i < electricScootersList.size(); i++) {
        for (int j = i + 1; j < electricScootersList.size(); j++) {
            if (cmpLastLocation(electricScootersList[i], electricScootersList[j]) == 1) { // crescator dupa data
                ElectricScooter aux = electricScootersList[i];
                electricScootersList[i] = electricScootersList[j];
                electricScootersList[j] =  aux;
            }
        }
    }
    return electricScootersList;
}

vector<ElectricScooter> Controller::sortByCurrentState(){
    vector<ElectricScooter> electricScootersList = repository.getAll();//fac o copie
    for (int i = 0; i < electricScootersList.size(); i++) {
        for (int j = i + 1; j < electricScootersList.size(); j++) {
            if (cmpCurrentState(electricScootersList[i], electricScootersList[j]) == 1) { // crescator dupa data
                ElectricScooter aux = electricScootersList[i];
                electricScootersList[i] = electricScootersList[j];
                electricScootersList[j] =  aux;
            }
        }
    }
    return electricScootersList;
}

vector<ElectricScooter> Controller::sortByKilometers(){
    vector<ElectricScooter> electricScootersList = repository.getAll();//fac o copie
    for (int i = 0; i < electricScootersList.size(); i++) {
        for (int j = i + 1; j < electricScootersList.size(); j++) {
            if (cmpKilometers(electricScootersList[i], electricScootersList[j]) == 1) { // crescator dupa data
                ElectricScooter aux = electricScootersList[i];
                electricScootersList[i] = electricScootersList[j];
                electricScootersList[j] =  aux;
            }
        }
    }
    return electricScootersList;
}



/**
 Primeste de la repository lista cu toate electricScooters (getAll) le filtreaza dupa locatie
 Creaza o noua lista cu electricScooters care au lastLocation egala cu locatia data
 returneaza lista rezultata
*/
vector<ElectricScooter> Controller::filterByLocation(string location){
    vector<ElectricScooter> electricScooterFiltered;
    vector<ElectricScooter> electricScootersList = repository.getAll();//fac o copie
    for (int i = 0; i < electricScootersList.size(); i++) {
        if (location==electricScootersList[i].getLastLocation())
            electricScooterFiltered.push_back(electricScootersList[i]);
    }
    return electricScooterFiltered;
}


/**
 Primeste de la repository lista cu toate electricScooters (getAll) le filtreaza dupa locatie si starea curenta="parked"
 Creaza o noua lista cu electricScooters filtrate
 returneaza lista rezultata
*/
vector<ElectricScooter> Controller::filterByLocationAndCurrentState(string location){
    vector<ElectricScooter> electricScooterFiltered;
    vector<ElectricScooter> electricScootersList = repository.getAll();//fac o copie
    for (int i = 0; i < electricScootersList.size(); i++) {
        if (location==electricScootersList[i].getLastLocation() && electricScootersList[i].getCurrentState()=="parked")
            electricScooterFiltered.push_back(electricScootersList[i]);
    }
    return electricScooterFiltered;
}


vector<ElectricScooter> Controller::filterByReserved(){
    vector<ElectricScooter> electricScooterFiltered;
    vector<ElectricScooter> electricScootersList = repository.getAll();//fac o copie
    for (int i = 0; i < electricScootersList.size(); i++) {
        if (electricScootersList[i].getCurrentState()=="reserved")
            electricScooterFiltered.push_back(electricScootersList[i]);
    }
    return electricScooterFiltered;
}

