#pragma once

#include "Domain.h"
#include <vector>
#include <string>
#include <ostream>
#include <fstream>

using std::vector;
using std::string;
using std::ostream;


/**
 CLASA CRUDRepository
 CRUD = Create, Read, Update, Delete
 Clasa abstracta
 contine metode virtuale, care vor fi suprascrise in clasele derivate
*/
class CRUDRepository {
    vector<ElectricScooter> allElectricScooters;

public:



    virtual void addRepo(const ElectricScooter &electricScooter) = 0;

    virtual void deleteRepo(const ElectricScooter &electricScooter) = 0;

    virtual void updateRepo(const ElectricScooter &electricScooter) = 0;

    virtual const int find(string id) const = 0;

    virtual const ElectricScooter &findElectricScooter(string id) const=0;

    virtual void reserveRepo(const string &id) = 0;

    virtual void parkRepo(const string &id, const string &location) = 0;
};


/**
 CLASA InMemoryRepository
 CRUD = Create, Read, Update, Delete
 Aici se fac adaugari, cautari, modificari si stergeri, in memoria RAM
 Suprascrie metodele vituale din CRUDRepository
 Arunca erori de tip repoError (in cazul in care de exemplu vrem sa adaugam un electricScooter care deja exista
 sau daca vrem sa modificam sau sa stergem un electricScooter care nu exista)
*/
class InMemoryRepository : public CRUDRepository {
    vector<ElectricScooter> allElectricScooters;

public:
    //constructor implicit
    InMemoryRepository() = default;

    //nu permitem copierea de obiecte
    InMemoryRepository(const InMemoryRepository &other) = delete;

    void addRepo(const ElectricScooter &electricScooter) override;

    void deleteRepo(const ElectricScooter &electricScooter) override;

    void updateRepo(const ElectricScooter &electricScooter) override;

    void reserveRepo(const string &id) override;

    void useRepo(const string &id);

    void parkRepo(const string &id, const string &location) override;

    const int find(string id) const;

    const ElectricScooter &findElectricScooter(string id) const override;

    const vector<ElectricScooter> &getAll() const noexcept;

};


/**
 CLASA FileRepository
 Aici se fac adaugari, cautari, modificari si stergeri, in fisier
 Suprascrie metodele din InMemoryRepository
 si permite dupa fiecare operatie reactualizarea fisierului
 Citeste datele din fisier si le pune in allElectricScooters
 Scrie datele in fisier din allElectricScooters
*/
class FileRepository : public InMemoryRepository {
private:
    std::string fileName;

    //metode private
    void readDataFromFile();

    void writeDataToFile() const;

public:

    //constructor
    FileRepository(std::string fileName) : InMemoryRepository(), fileName{fileName} {
        readDataFromFile();//incarcam datele din fisier
    }

//    ElectricScooter findElectricScooter(string id) const override{
//        ElectricScooter electricScooter=InMemoryRepository::findElectricScooter(id);
//        return electricScooter;
//    }
    //suprascrie metoda addRepo
    void addRepo(const ElectricScooter &electricScooter) override {
        InMemoryRepository::addRepo(electricScooter);  //apelam metoda din clasa de baza
        writeDataToFile(); //scriem datele in fisier
    }

    //suprascrie metoda deleteRepo
    void deleteRepo(const ElectricScooter &electricScooter) override {
        InMemoryRepository::deleteRepo(electricScooter);  //apelam metoda din clasa de baza
        writeDataToFile();  //scriem datele in fisier
    }

    //suprascrie metoda updateRepo
    void updateRepo(const ElectricScooter &electricScooter) override {
        InMemoryRepository::updateRepo(electricScooter); //apelam metoda din clasa de baza
        writeDataToFile();  //scriem datele in fisier
    }

    //suprascrie metoda reserveRepo
    void reserveRepo(const string &id) override {
        InMemoryRepository::reserveRepo(id);  //apelam metoda din clasa de baza
        writeDataToFile();  //scriem datele in fisier
    }


    //suprascrie metoda parkRepo
    void parkRepo(const string &id, const string &locatie) override {
        InMemoryRepository::parkRepo(id, locatie);  //apelam metoda din clasa de baza
        writeDataToFile();  //scriem datele in fisier
    }

};


/**
 CLASA RepoException
 folosita pentru a semnala situatii exceptionale care pot aparea in repository
*/
class RepoException {
    string message;
public:
    RepoException(string m) : message{m} {}

    //functie friend (vreau sa folosesc membru privat mesagge)
    friend ostream &operator<<(ostream &out, const RepoException &ex);
};

ostream &operator<<(ostream &out, const RepoException &ex);


