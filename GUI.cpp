#pragma once
#include "QHBoxLayout"
#include "GUI.h"
#include "Repository.h"
#include "Validator.h"
#include "Domain.h"
#include "QMessageBox.h"
#include "QFormLayout.h"
#include "QLabel.h"
#include "QListView.h"


/**
 initCient-metoda privata a clasei GUI
 initializeaza fereastra care asigura interfata cu clientul
 */
void GUI::initClient() {
    // creează un obiect QHBoxLayout numit "layoutFinal" îi atribuie o nouă instanță a clasei QHBoxLayout.
    // acest layout va fi folosit pentru a organiza componentele în fereastra principală.
    QHBoxLayout* layoutFinal = new QHBoxLayout(this);

    //layout se imparte in doua parti: stanga (in care se va afisa detaliat un electricScooter si drepata in care se va afisa tabelul)
    QVBoxLayout* dreapta = new QVBoxLayout(this);
    QFormLayout* stanga = new QFormLayout;

    //in layout stanga adaugam label-uri si QLineEdit-uri pt a incarca un electric scooter selectat din tabel
    stanga->addRow(new QLabel("Id:"), idTxt); // primește două argumente: o etichetă (QLabel) și un widget.
                                              // creeaza o noua linie in layout si plaseaza eticheta si widget-ul
    stanga->addRow(new QLabel("Model:"), modelTxt);
    stanga->addRow(new QLabel("Kilometers:"), kilometersTxt);
    stanga->addRow(new QLabel("LastLocation:"), lastLocationTxt);
    stanga->addRow(new QLabel("CurrentState:"), currentStateTxt);
    stanga->addRow(new QLabel("CommissioningDataYear:"), commissioningDataYearTxt);
    stanga->addRow(new QLabel("CommissioningDataMonth:"), commissioningDataMonthTxt);
    stanga->addRow(new QLabel("CommissioningDataDay:"), commissioningDataDayTxt);
    //in layout stanga adaugam label pt nume fisier
    stanga->addRow(new QLabel("FileName:"), fisierTxt);

    //in layout stanga adaugam butoane pentru client
    stanga->addWidget(buttonUse);
    stanga->addWidget(buttonReserve);
    stanga->addWidget(buttonPark);

    //OLineEdit pt nume fisier, contine implicit filename din main
    string fileName="date.txt";
    QString fileNameQ = QString::fromStdString(fileName);
    fisierTxt->setText(fileNameQ);


    //in layout-ul din dreapta se va adauga tabelul cu toate electricScooters
    tableView = new QTableView;
    //setam modelul pt tabel
    tableView->setModel(model);
    //dreapta->addWidget(new QLabel("ElectricScooters:"));
    dreapta->addWidget(tableView);

    //in layout-ul din dreapta se vor adauga butoane de sort
    dreapta->addWidget(buttonSortId);
    dreapta->addWidget(buttonSortModel);
    dreapta->addWidget(buttonSortCommissioningData);
    dreapta->addWidget(buttonSortKilometers);
    dreapta->addWidget(buttonSortLastLocation);
    dreapta->addWidget(buttonSortCurrentState);

    //la layout final adaugam cele doua layout-uri stanga si dreapta
    layoutFinal->addLayout(stanga);
    layoutFinal->addLayout(dreapta);

    //incarcam in tabela lista cu toate electricScooters preluata de la controller
    model->setElectricScooters(controller.getAll());

    //setam ca layout activ layoutFinal
    setLayout(layoutFinal);
}


/**
 initManager-metoda privata a clasei GUI
 initializeaza fereastra care asigura interfata cu managerul
 */
void GUI::initManager() {
    // creează un obiect QHBoxLayout numit "layoutFinal" îi atribuie o nouă instanță a clasei QHBoxLayout.
    // acest layout va fi folosit pentru a organiza componentele în fereastra principală.
    QHBoxLayout* layoutFinal = new QHBoxLayout(this);

    //layout se imparte in doua parti: stanga (in care se va afisa detaliat un electricScooter si drepata in care se va afisa tabelul)
    QVBoxLayout* dreapta = new QVBoxLayout(this);
    QFormLayout* stanga = new QFormLayout;


    //in layout stanga adaugam label-uri si QLineEdit-uri pt a incarca un electric scooter selectat din tabel
    stanga->addRow(new QLabel("Id:"), idTxt); // primește două argumente: o etichetă (QLabel) și un widget.
        // creeaza o noua linie in layout si plaseaza eticheta si widget-ul
    stanga->addRow(new QLabel("Model:"), modelTxt);
    stanga->addRow(new QLabel("Kilometers:"), kilometersTxt);
    stanga->addRow(new QLabel("LastLocation:"), lastLocationTxt);
    stanga->addRow(new QLabel("CurrentState:"), currentStateTxt);
    stanga->addRow(new QLabel("CommissioningDataYear:"), commissioningDataYearTxt);
    stanga->addRow(new QLabel("CommissioningDataMonth:"), commissioningDataMonthTxt);
    stanga->addRow(new QLabel("CommissioningDataDay:"), commissioningDataDayTxt);
    //in layout stanga adaugam label pt nume fisier
    stanga->addRow(new QLabel("FileName:"), fisierTxt);

    //in layout stanga adaugam butoane pt manager
    stanga->addWidget(buttonAdd);
    stanga->addWidget(buttonDelete);
    stanga->addWidget(buttonUpdate);

    //OLineEdit pt nume fisier, contine implicit filename din main
    string fileName="date.txt";
    QString fileNameQ = QString::fromStdString(fileName);
    fisierTxt->setText(fileNameQ);


    //in layout-ul din dreapta se va adauga tabelul cu toate electricScooters
    tableView = new QTableView;
    //setam modelul pt tabel
    tableView->setModel(model);
    //dreapta->addWidget(new QLabel("ElectricScooters:"));
    dreapta->addWidget(tableView);

    //in layout-ul din dreapta se vor adauga butoane de sort
    dreapta->addWidget(buttonSortId);
    dreapta->addWidget(buttonSortModel);
    dreapta->addWidget(buttonSortCommissioningData);
    dreapta->addWidget(buttonSortKilometers);
    dreapta->addWidget(buttonSortLastLocation);
    dreapta->addWidget(buttonSortCurrentState);

    //la layout final adaugam cele doua layout-uri stanga si dreapta
    layoutFinal->addLayout(stanga);
    layoutFinal->addLayout(dreapta);

    //incarcam in tabela lista cu toate electricScooters preluata de la controller
    model->setElectricScooters(controller.getAll());

    //setam ca layout activ layoutFinal
    setLayout(layoutFinal);
}


/**
 metoda privata a clasei GUI care va realiza actiunile se selectare a unui linii din tabela si actiunile butoanelor
 */
void GUI::initConnect(){

    //la selectarea unui id din tabela se vor incarca atributele electricScooter-ului selectat in QLineEdit-urile din stanga
    QObject::connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged,[&](){
        //se selecteaza un id din tabela
        auto selectedIndex=tableView->selectionModel()->selectedIndexes().at(0);

        //se preia id-ul selectat in variabila id de tip string
        string id=model->data(selectedIndex).toString().toStdString();

        //se cauta id-ul selectat in lista de electricScooters
        for(auto& electricScooter:controller.getAll()){
            if(id==electricScooter.getId()){
                //cand gaseste id-ul, incarca atributele in QLineEdit-uri
                idTxt->setText(QString::fromStdString(electricScooter.getId()));
                modelTxt->setText(QString::fromStdString(electricScooter.getModel()));
                kilometersTxt->setText(QString::fromStdString(to_string(electricScooter.getKilometers())));
                lastLocationTxt->setText(QString::fromStdString(electricScooter.getLastLocation()));
                currentStateTxt->setText(QString::fromStdString(electricScooter.getCurrentState()));
                commissioningDataYearTxt->setText(QString::fromStdString(to_string(electricScooter.getCommissioningDate().year)));
                commissioningDataMonthTxt->setText(QString::fromStdString(to_string(electricScooter.getCommissioningDate().month)));
                commissioningDataDayTxt->setText(QString::fromStdString(to_string(electricScooter.getCommissioningDate().day)));
                break;
            }
        }
    });


    //la click pe butonul sortId se va incarca in tabela lista de electricScooters sortate dupa id, primita de la controller
    QObject::connect(buttonSortId, &QPushButton::clicked,[&](){
        model->setElectricScooters(controller.sortById());
    });


    //la click pe butonul sortModel se va incarca in tabela lista de electricScooters sortate dupa model, primita de la controller
    QObject::connect(buttonSortModel, &QPushButton::clicked,[&](){
        model->setElectricScooters(controller.sortByModel());
    });


    //la click pe butonul sortCommissioningData se va incarca in tabela lista de electricScooters sortate dupa commissioningData, primita de la controller
    QObject::connect(buttonSortCommissioningData, &QPushButton::clicked,[&](){
        model->setElectricScooters(controller.sortByCommissioningDate());
    });


    //la click pe butonul sortKilometers se va incarca in tabela lista de electricScooters sortate dupa kilometers, primita de la controller
    QObject::connect(buttonSortKilometers, &QPushButton::clicked,[&](){
        model->setElectricScooters(controller.sortByKilometers());
    });


    //la click pe butonul sortLastLocation se va incarca in tabela lista de electricScooters sortate dupa lastLocation, primita de la controller
    QObject::connect(buttonSortLastLocation, &QPushButton::clicked,[&](){
        model->setElectricScooters(controller.sortByLastLocation());
    });


    //la click pe butonul sortCurrentState se va incarca in tabela lista de electricScooters sortate dupa currentState, primita de la controller
    QObject::connect(buttonSortCurrentState, &QPushButton::clicked,[&](){
        model->setElectricScooters(controller.sortByCurrentState());
    });


    //la click pe buttonAdd se vor prelua datele din QLineEdit-uri si se vor trimite la controller sa le adauge
    QObject::connect(buttonAdd, &QPushButton::clicked,[&](){
        string id, modeles, lastLocation, currentState;
        int kilometers;
        Data commissioningData;
        //preia date din QLineEdit
        id=idTxt->text().toStdString();
        modeles=modelTxt->text().toStdString();
        lastLocation=lastLocationTxt->text().toStdString();
        currentState=currentStateTxt->text().toStdString();
        kilometers=kilometersTxt->text().toInt();
        commissioningData.year=commissioningDataYearTxt->text().toInt();
        commissioningData.month=commissioningDataMonthTxt->text().toInt();
        commissioningData.day=commissioningDataDayTxt->text().toInt();
        //trimite la controller pt a fi adaugate
        controller.addController(id, modeles, kilometers, lastLocation, currentState,commissioningData);
        //face refresh la tabela
        model->setElectricScooters(controller.getAll());
    });


    //la click pe buttonDelete se va sterge electricScooters cu id-ul selectat
    QObject::connect(buttonDelete, &QPushButton::clicked,[&](){
        QModelIndexList selection =tableView->selectionModel()->selectedIndexes();
        auto firstSelected=selection.at(0);
        string id=model->data(firstSelected).toString().toStdString();

        controller.deleteController(id);
        model->setElectricScooters(controller.getAll());
    });


    //la click pe buttonUpdate se va modifica electricScooter-ul selectat cu noile date din QLineEdit
    QObject::connect(buttonUpdate, &QPushButton::clicked,[&](){
        QModelIndexList selection =tableView->selectionModel()->selectedIndexes();
        auto firstSelected=selection.at(0);

        string id, modeles, lastLocation, currentState;
        int kilometers;
        Data commissioningData;

        //preia date din QLineEdit in variabile
        id=model->data(firstSelected).toString().toStdString();
        modeles=modelTxt->text().toStdString();
        lastLocation=lastLocationTxt->text().toStdString();
        currentState=currentStateTxt->text().toStdString();
        kilometers=kilometersTxt->text().toInt();
        commissioningData.year=commissioningDataYearTxt->text().toInt();
        commissioningData.month=commissioningDataMonthTxt->text().toInt();
        commissioningData.day=commissioningDataDayTxt->text().toInt();

        //trimite datele la controller pt a fi modificate
        controller.updateController(id,modeles,kilometers,lastLocation,currentState,commissioningData);
        model->setElectricScooters(controller.getAll());
    });


    //la click pe buttonUse se va schima current state a obiectului selectat in inUse
    QObject::connect(buttonUse, &QPushButton::clicked,[&](){
        QModelIndexList selection =tableView->selectionModel()->selectedIndexes();
        auto firstSelected=selection.at(0);
        string id;
        id=model->data(firstSelected).toString().toStdString();
        controller.useController(id);
        model->setElectricScooters(controller.getAll());
    });


    //la click pe buttonReserve se va schima current state a obiectului selectat in inReserved
    QObject::connect(buttonReserve, &QPushButton::clicked,[&](){
        QModelIndexList selection =tableView->selectionModel()->selectedIndexes();
        auto firstSelected=selection.at(0);
        string id;
        id=model->data(firstSelected).toString().toStdString();
        controller.reserveController(id);
        model->setElectricScooters(controller.getAll());
    });


    //la click pe buttonPark se va schima current state a obiectului selectat in parked
    QObject::connect(buttonPark, &QPushButton::clicked,[&](){
        QModelIndexList selection =tableView->selectionModel()->selectedIndexes();
        auto firstSelected=selection.at(0);
        string id, lastLocation;
        id=model->data(firstSelected).toString().toStdString();
        lastLocation=lastLocationTxt->text().toStdString();
        controller.parkController(id,lastLocation);
        model->setElectricScooters(controller.getAll());
    });

}


//functie care incarca toate electricScoterele in tabela
void GUI::loadListaElectricScooters(const vector<ElectricScooter> &allElectricScooters){
    model->setElectricScooters(allElectricScooters);
}
