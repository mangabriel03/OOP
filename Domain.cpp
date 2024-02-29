#include "Domain.h"
#include<sstream>
#include<iostream>
#include <string>

/**
 Clasa ElectricScooter
 pe langa atributele date, am mai folosit un dictionar currentStateMap  care retine pentru fiecare stare
 (parked, reserved, in use, under maintenance, decommissioned) 1 daca starea respectiva e activa pentru obiectul curent sau 0 altfel
 */

//constructor
ElectricScooter::ElectricScooter(const string id, const string model, const int kilometers, const string lastLocation, const string currentState, const Data commissioningDate){
    this->id = id;
    this->model= model;
    this->kilometers = kilometers;
    this->lastLocation = lastLocation;
    this->currentState = currentState;
    this->commissioningDate=commissioningDate;  //parked, reserved, in use, under maintenance, decommissioned)
    this->currentStateMap["parked"]=0;
    this->currentStateMap["reserved"]=0;
    this->currentStateMap["inUse"]=0;
    this->currentStateMap["underMaintenance"]=0;
    this->currentStateMap["decommissioned"]=0;
    if(currentState=="parked")
        this->currentStateMap["parked"]=1;
    else
        if(currentState=="reserved")
            this->currentStateMap["reserved"]=1;
        else
            if(currentState=="in use")
                this->currentStateMap["inUse"]=1;
            else
                if(currentState=="under maintenance")
                    this->currentStateMap["underMaintenance"]=1;
                else
                    if(currentState=="decommissioned")
                        this->currentStateMap["decommissioned"]=1;
}

//copy constructor
ElectricScooter::ElectricScooter(const ElectricScooter& other){
    this->id = other.id;
    this->model= other.model;
    this->kilometers = other.kilometers;
    this->lastLocation = other.lastLocation;
    this->currentState = other.currentState;
    this->commissioningDate=other.commissioningDate;
    this->currentStateMap=other.currentStateMap;
}

//get-eri
string ElectricScooter::getId() const{
    return this->id;
}

string ElectricScooter::getModel() const{
    return this->model;
}

int ElectricScooter::getKilometers() const{
    return this->kilometers;
}

string ElectricScooter::getLastLocation() const{
    return this->lastLocation;
}

string ElectricScooter::getCurrentState() const{
    return this->currentState;
}

Data ElectricScooter::getCommissioningDate() const{
    return this->commissioningDate;
}

//set-eri
void ElectricScooter::setId(string value){
    this->id = value;
}

void ElectricScooter::setModel(string value) {
    this->model = value;
}

void ElectricScooter::setKilometers(int value) {
    this->kilometers = value;
}

void ElectricScooter::setLastLocation(string value) {
    this->lastLocation= value;
}

void ElectricScooter::setCurrentState(string value) {
    this->currentState = value;
}

/**
 Set-er care schimba valorile cheilor din dictionar, in functie de starea curenta a obiectului:
 valoarea starii curente va fi 1, restul 0
 */
void ElectricScooter::setCurrentStateMap(string currentState) {
    this->currentStateMap["parked"]=0;
    this->currentStateMap["reserved"]=0;
    this->currentStateMap["inUse"]=0;
    this->currentStateMap["underMaintenance"]=0;
    this->currentStateMap["decommissioned"]=0;
    if(currentState=="parked")
        this->currentStateMap["parked"]=1;
    else
        if(currentState=="reserved")
            this->currentStateMap["reserved"]=1;
        else
            if(currentState=="in use")
                this->currentStateMap["inUse"]=1;
            else
                if(currentState=="under maintenance")
                    this->currentStateMap["underMaintenance"]=1;
                else
                    if(currentState=="decommissioned")
                        this->currentStateMap["decommissioned"]=1;
}


/**
 Metoda toString() creează și returnează un șir de caractere care conține informații despre un obiect ElectricScooter
 (id, model, kilometers, lastLocation, currentState, commissioning data)
 Aceasta este realizată prin utilizarea unui obiect stringstream pentru a concatena informațiile și a forma un șir de caractere coerent.
 */
string ElectricScooter::toString() const
{
    stringstream buffer;
    buffer << "Identifier: " << this->id << endl
           << "Model: " << this->model << endl
           <<"Kilometers: " << this->kilometers << endl
           <<"Last location: " << this->lastLocation << endl
           <<"Current state: " << this->currentState << endl
           <<"Commissioning date: " << this->commissioningDate.day<<"."<<this->commissioningDate.month<<"."<<this->commissioningDate.year<< endl<<endl;
    return buffer.str();
}


/**
  Compara doua obiecte de tip ElectricScooters dupa commissioning data
 */
int cmpCommissioningData(const ElectricScooter& electricScooter1, const ElectricScooter& electricScooter2){
    if(electricScooter1.getCommissioningDate().year < electricScooter2.getCommissioningDate().year)
        return -1;
    else
        if(electricScooter1.getCommissioningDate().year > electricScooter2.getCommissioningDate().year)
            return 1;
        else
            if(electricScooter1.getCommissioningDate().month < electricScooter2.getCommissioningDate().month)
                return -1;
            else
                if(electricScooter1.getCommissioningDate().month > electricScooter2.getCommissioningDate().month)
                    return 1;
                else
                    if(electricScooter1.getCommissioningDate().day < electricScooter2.getCommissioningDate().day)
                        return -1;
                    else
                        if(electricScooter1.getCommissioningDate().day > electricScooter2.getCommissioningDate().day)
                            return 1;
                        else
                            return 0;
}

int cmpId(const ElectricScooter& electricScooter1, const ElectricScooter& electricScooter2){
                        if(electricScooter1.getId() < electricScooter2.getId())
                            return -1;
                        else
                            return 1;
}

int cmpModel(const ElectricScooter& electricScooter1, const ElectricScooter& electricScooter2){
                        if(electricScooter1.getModel() < electricScooter2.getModel())
                            return -1;
                        else
                            return 1;
}

int cmpKilometers(const ElectricScooter& electricScooter1, const ElectricScooter& electricScooter2){
                        if(electricScooter1.getKilometers() < electricScooter2.getKilometers())
                            return -1;
                        else
                            return 1;
}

int cmpLastLocation(const ElectricScooter& electricScooter1, const ElectricScooter& electricScooter2){
                        if(electricScooter1.getLastLocation() < electricScooter2.getLastLocation())
                            return -1;
                        else
                            return 1;
}

int cmpCurrentState(const ElectricScooter& electricScooter1, const ElectricScooter& electricScooter2){
                        if(electricScooter1.getCurrentState() < electricScooter2.getCurrentState())
                            return -1;
                        else
                            return 1;
}
