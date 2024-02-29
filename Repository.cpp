#include "Repository.h"
#include "Validator.h"
#include "Domain.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using std::ostream;
using std::stringstream;
using std::fstream;
using namespace std;

/**
 CLASA InMemoryRepository
 CRUD = Create, Read, Update, Delete
 aici se fac adaugari, cautari, modificari si stergeri
 arunca erori de tip repoError (in cazul in care de exemplu vrem sa adaugam un electricScooter care deja exista
 sau daca vrem sa modificam sau sa stergem un electricScooter care nu exista)
*/


/**
 Primeste de la controller un obiect de tip ElectricScooter
 il cauta in lista de electricScooters
 daca nu  il gaseste il adauga in lista
 altfel arunca o repoExceptie
 */
void InMemoryRepository::addRepo(const ElectricScooter &electricScooter) {
    int index = find(electricScooter.getId());
    if (index != -1)
        throw RepoException("Already exists!");
    else
        allElectricScooters.push_back(electricScooter);
}


/**
 Primeste de la controller un obiect de tip ElectricScooter
 il cauta in lista de electricScooters
 daca il gaseste il sterge
 altfel arunca o repoExceptie
 */
void InMemoryRepository::deleteRepo(const ElectricScooter &electricScooter) {

    int index = find(electricScooter.getId());
    if (index != -1)
        allElectricScooters.erase(allElectricScooters.begin() + index);
    else
        throw RepoException("Doesn't exist!");
}


/**
 Primeste de la controller un obiect de tip ElectricScooter
 il cauta in lista de electricScooters
 daca il gaseste il modifica cu noile date
 altfel arunca o repoExceptie
 */
void InMemoryRepository::updateRepo(const ElectricScooter &electricScooter) {
    int index = find(electricScooter.getId());
    if (index != -1)
        allElectricScooters[index] = electricScooter;
    else
        throw RepoException("Doesn't exist!");
}


/**
 Primeste de la controller id-ul unui electricScooter
 il cauta in lista de electricScooters
 daca il gaseste il rezerva, prin modificarea starii curente in "reserved"
 altfel arunca o repoExceptie
 */
void InMemoryRepository::reserveRepo(const string &id) {
    int index = find(id);
    if (index != -1) {
        allElectricScooters[index].setCurrentState("reserved");
        allElectricScooters[index].setCurrentStateMap("reserved");
    } else
        throw RepoException("Doesn't exist!");
}


/**
 Primeste de la controller id-ul unui electricScooter
 il cauta in lista de electricScooters
 daca il gaseste il utilizeaza, prin modificarea starii curente in "in use"
 altfel arunca o repoExceptie
 */
void InMemoryRepository::useRepo(const string &id) {
    int index = find(id);
    if (index != -1) {
        allElectricScooters[index].setCurrentState("in use");
        //allElectricScooters[index].setCurrentStateMap("in use");
    } else
        throw RepoException("Doesn't exist!");
}


/**
 Primeste de la controller id-ul unui electricScooter si ultima locatie
 il cauta in lista de electricScooters
 daca il gaseste il parcheaza, prin modificarea starii curente in "parked" si a ultimei locatii in location
 altfel arunca o repoExceptie
 */
void InMemoryRepository::parkRepo(const string &id, const string &location) {
    int index = find(id);
    if (index != -1) {
        allElectricScooters[index].setCurrentState("parked");
        allElectricScooters[index].setLastLocation(location);
        //allElectricScooters[index].setCurrentStateMap("parked");
    } else
        throw RepoException("Doesn't exist!");
}


/**
 Cauta dupa id un obiect de tip electricScooter in lista de electricScooters
 daca il gaseste returneaza pozitia/indexul din lista
 altfet returneaza -1
 */
const int InMemoryRepository::find(string id) const {
    for (int i = 0; i < allElectricScooters.size(); i++) {
        if (allElectricScooters[i].getId() == id) {
            return i;
        }
    }
    return -1;
}


/**
 Cauta dupa id un obiect de tip electricScooter in lista de electricScooters
 daca il gaseste il returneaza
 altfet arunca o repoExceptie
 */
const ElectricScooter &InMemoryRepository::findElectricScooter(string id) const {
    for (const auto &electricScooter: allElectricScooters) {
        if (electricScooter.getId() == id) {
            return electricScooter;
        }
    }
    //daca nu exista arunc o exceptie
    throw RepoException("Doesn't exist !");
}


/**
returneaza toata lista de electricScooters
 */
const vector<ElectricScooter> &InMemoryRepository::getAll() const noexcept {
    return allElectricScooters;
}


/**
 Functie care trimite mesajele din exceptii
 Suprascrie operatorul <<
 */
ostream &operator<<(ostream &out, const RepoException &ex) {
    out << ex.message;
    return out;
}


/**
 Functia split primește un șir de caractere și un caracter separator
 și returnează un vector de cuvinte obținute prin separarea șirului în funcție de caracterul separator.
 */
std::vector<std::string> split(const std::string &s, char separator) {
    //result va fi vectorul de cuvinte obtinut din s
    std::vector<std::string> result;

    //Funcția utilizează clasa std::stringstream pentru a transforma șirul s într-un flux de caractere, folosit pentru a extrage cuvintele
    std::stringstream ss(s);

    //in stringul cuv se va extrage cate un cuvant
    std::string cuv;

    //În interiorul buclei while, se utilizează funcția getline pentru a extrage un cuvânt din fluxul de caractere ss.
    //getline primește trei argumente: fluxul de caractere (ss), obiectul cuv în care se va stoca cuvântul extras și caracterul separator.
    while (getline(ss, cuv, separator)) {
        result.push_back(cuv);
    }

    //După ce toate cuvintele au fost extrase și adăugate în vector, acesta este returnat ca rezultat al funcției.
    return result;
}


/**
 Functia citeste date din fisier linie cu linie
 Fiecare line este separata cu ajutorul functiei split
 Creaza un obiect de tip ElectricScooter pe care il adauga in allElectricScooters, folosind functia addRepo
 */
void FileRepository::readDataFromFile() {
    //deschide fisierul pentru citire
    ifstream f(fileName);
    //daca nu poate fi deschis, arunca o eroare
    if (!f.is_open()) {
        throw std::runtime_error("Failed to open file: " + fileName);
    }

    std::string line;

    //citeste pe rand, cate o linie din fisier
    while (std::getline(f, line)) {
        // Foloseste functia split pt a separa linia line
        std::vector<std::string> vCuvinte = split(line,
                                                  ',');  //in vCuvinte separ cuvintele din line, separatorul este ,
        std::vector<std::string> vData = split(vCuvinte[2],
                                               '-'); //in VData separ an,luna,zi din data, separatorul este -

        string id, model, lastLocation, currentState;
        int kilometers;
        Data commissioningDate;
        id = vCuvinte[0];
        model = vCuvinte[1];
        commissioningDate.year = stoi(vData[0]); // stoi transforma un string in int
        commissioningDate.month = stoi(vData[1]);
        commissioningDate.day = stoi(vData[2]);
        kilometers = stoi(vCuvinte[3]);
        lastLocation = vCuvinte[4];
        currentState = vCuvinte[5];

        //creaza un obiect ElectricScooter
        ElectricScooter electricScooter(id, model, kilometers, lastLocation, currentState, commissioningDate);

        // Adauga obiectul la repository folosind functia addRepo()
        addRepo(electricScooter);

        if (f.eof()) break; // in caz ca sunt randuri libere in fisier
    }

    //inchide fisierul
    f.close();
}


/**
 Functia scrie datele din allElectricScooters in fisier, linie cu linie
 Din fiecare obiect de tip ElectricScooters extrage atributele cu ajutorul getterilor
 Afiseaza fiecare obiect pe cate o linie in fisier, folosind acelasi format
 */
void FileRepository::writeDataToFile() const {
    //deschide fisierul pentru scriere in el
    std::ofstream g(fileName);
    //daca nu poate fi deschis arunca o eroare
    if (!g.is_open()) {
        throw std::runtime_error("Failed to open file: " + fileName);
    }

    //preia toata lista allElectricScooters
    const std::vector<ElectricScooter> &allElectricScooters = getAll();

    //parcurge lista allElectricScooters
    for (const ElectricScooter &electricScooter: allElectricScooters) {
        // Scrie un obiect electricScooter in fisier pe cate o linie
        // Respecta formatul folosit
        // Functia to_string transporma un int intr-un string
        g << electricScooter.getId() << "," << electricScooter.getModel() << ","
          << electricScooter.getCommissioningDate().year << '-'
          << to_string(electricScooter.getCommissioningDate().month) << '-'
          << to_string(electricScooter.getCommissioningDate().day) << ',' << to_string(electricScooter.getKilometers())
          << ',' << electricScooter.getLastLocation() << ',' << electricScooter.getCurrentState() << endl;
    }

    //inchide fisierul
    g.close();
}


