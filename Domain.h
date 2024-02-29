#pragma once
#include <string>
#include <map>
#include <iostream>
using namespace std;

struct Data{
    int day;
    int month;
    int year;
};

/**
 Clasa ElectricScooter
 pe langa atributele date, am mai folosit un dictionar currentStateMap  care retine pentru fiecare stare
 (parked, reserved, in use, under maintenance, decommissioned) 1 daca starea respectiva e activa pentru obiectul curent sau 0 altfel
 */

class ElectricScooter {
    string id;
    string model;
    int kilometers;
    string lastLocation;
    string currentState;
    Data commissioningDate;
    //dictionar unde cheile reprezinta starile date ca stringuri (parked, reserved, in use, under maintenance, decommissioned)
    //si valorile sunt 1 daca starea e activa pentru obiectul curent sau 0 altfel
    std::map<string, int> currentStateMap = {
        { "parked", 0 },
        { "reserved", 0},
        { "inUse", 0 },
        { "underMaintenance", 0 },
        { "decommissioned", 0 },
        };

public:
    //contructor
    ElectricScooter(const string id, const string model, const int kilometers,const string lastLocation,const string currentState,const Data commissioningDate);
    //copy constructor
    ElectricScooter(const ElectricScooter& other);

    string getId() const;

    string getModel() const;

    int getKilometers() const;

    string getLastLocation() const;

    string getCurrentState() const;

    Data getCommissioningDate() const;

    void setId(string value);

    void setModel(string value);

    void setKilometers(int value);

    void setLastLocation(string value);

    void setCurrentState(string value);

    void setCurrentStateMap(string value);

    string toString() const;

};

int cmpCommissioningData(const ElectricScooter& electricScooter1, const ElectricScooter& electricScooter2);
int cmpId(const ElectricScooter& electricScooter1, const ElectricScooter& electricScooter2);
int cmpModel(const ElectricScooter& electricScooter1, const ElectricScooter& electricScooter2);
int cmpKilometers(const ElectricScooter& electricScooter1, const ElectricScooter& electricScooter2);
int cmpLastLocation(const ElectricScooter& electricScooter1, const ElectricScooter& electricScooter2);
int cmpCurrentState(const ElectricScooter& electricScooter1, const ElectricScooter& electricScooter2);




