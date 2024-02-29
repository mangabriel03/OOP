//#ifndef VALIDATOR_H
//#define VALIDATOR_H

//#endif // VALIDATOR_H
#pragma once
#include <string>
#include "Domain.h"
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class ValidateException {
    vector<string> msgs;
public:
    //constructor
    ValidateException(const vector<string>& errors) :msgs{ errors } {}

    //functie friend (vreau sa folosesc membru privat msg)
    friend ostream& operator<<(ostream& out, const ValidateException& ex);
};

ostream& operator<<(ostream& out, const ValidateException& ex);


/**
 CLASA VALIDATOR
 e folosita de controller pentru a valida un obiect
 aici se verifica ca datele de tip string sa nu fie vide si datele numerice sa nu fie negative
 arunca exceptii de tip valid error, care vor fi prinse in meniul de UI
 */

class Validator {
public:
    void validate(const ElectricScooter& electricScooter);
};

void testValidator();
