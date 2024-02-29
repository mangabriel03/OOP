#include "Validator.h"
#include "Domain.h"
#include <assert.h>
#include <sstream>

/**
 CLASA VALIDATOR
e folosita de controller pentru a valida un obiect
aici se verifica ca datele de tip string sa nu fie vide si datele numerice sa nu fie negative
arunca exceptii de tip valid error, care vor fi prinse in meniul de UI
 */


/**
functie care valideaza un obiect
 daca datele nu sunt corecte arunca exceptie de tip valid error
 */
void Validator::validate(const ElectricScooter &electricScooter) {
    vector<string> msgs;
    if (electricScooter.getId().size() == 0) msgs.push_back("Invalide identifier!");
    if (electricScooter.getModel().size() == 0) msgs.push_back("Invalide model!");
    if (electricScooter.getKilometers() <= 0) msgs.push_back("Invalide kilometers!");
    if (electricScooter.getLastLocation().size() == 0) msgs.push_back("Invalide location!");
    if (electricScooter.getCurrentState().size() == 0 ||
        (electricScooter.getCurrentState() != "parked" && electricScooter.getCurrentState() != "reserved" &&
         electricScooter.getCurrentState() != "in use" && electricScooter.getCurrentState() != "under maintenance" &&
         electricScooter.getCurrentState() != "decommissioned"))
        msgs.push_back("Invalide current state!");
    if (electricScooter.getCommissioningDate().day <= 0 || electricScooter.getCommissioningDate().day > 31)
        msgs.push_back("Invalide commissioning date day!");
    if (electricScooter.getCommissioningDate().month <= 0 || electricScooter.getCommissioningDate().month > 12)
        msgs.push_back("Invalide commissioning date month!");
    if (electricScooter.getCommissioningDate().year <= 1900 || electricScooter.getCommissioningDate().year > 2033)
        msgs.push_back("Invalide commissioning date year!");
    if (msgs.size() > 0) {
        throw ValidateException(msgs);
    }
}


/**
Această funcție suprascrie operatorul de ieșire a fluxului <<
 pentru a oferi o modalitate de a afișa mesajele conținute într-un obiect
 ValidateException într-un flux de ieșire, cum ar fi consola sau un fișier.
 Funcția iterează prin fiecare mesaj din vectorul msgs al obiectului ValidateException
 și îl afișează în fluxul de ieșire out, separate de un spațiu.
 În cele din urmă, returnează o referință la fluxul de ieșire out.
 Poate concatena mai multe mesaje
 */
ostream &operator<<(ostream &out, const ValidateException &ex) {
    for (const auto &msg: ex.msgs) {
        out << msg << " ";
    }
    return out;
}

/**
 teste pentru validatori
 */
void testValidator() {
    Validator validator;

    ElectricScooter electricScooter{"1", "m1", -1, "avram", "parked", {-1, -1, 202}};
    try {
        validator.validate(electricScooter);
    }
    catch (const ValidateException &ex) {
        std::stringstream sout;
        sout << ex;
        auto mesaj = sout.str();
        assert(mesaj.find(
                   "Invalide kilometers!Invalide commissioning date day!Invalide commissioning date month!Invalide commissioning date year!") >=
               0);
    }
}


