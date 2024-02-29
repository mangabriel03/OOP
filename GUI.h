#pragma once
#include <qwidget.h>
#include "Controller.h"
#include "Domain.h"
#include "Repository.h"
#include "Validator.h"
#include "Test.h"
#include <qpushbutton.h>
#include <QAbstractTableModel>
#include <vector>
#include "qtableview.h"
#include <qlineedit.h>
#include "qlabel.h"
#include "qheaderview.h"


/**
 Clasa MyTableModel
 -seteaza numarul de randuri, numarul de coloane, capul de tabel(header-ul)
 -stabileste in ce coloane incarca fiecare atribut al unui electricScooter
 -returneaza obiectul electricScooter selectat din tabela
 -face refresh la tabela
 */
class MyTableModel:public QAbstractTableModel{

    Q_OBJECT
    vector <ElectricScooter> allElectricScooters;

public:
    //constructorul
    MyTableModel(){}


    //functie care returneaza numarul de randuri din tabela=cate electricScootere avem
    int rowCount(const QModelIndex &parent=QModelIndex()) const override{
        return allElectricScooters.size();
    }


    //functie care returneaza numarul de coloane din tabela
    int columnCount(const QModelIndex &parent=QModelIndex()) const override{
        return 8;
    }


    //setearea capului de tabel(header-ului)
    QVariant headerData(int section, Qt::Orientation orientation, int role) const {
        if(role==Qt::DisplayRole)
        {
            if(orientation==Qt::Horizontal)
            {
                switch(section)
                {
                case 0:
                    return tr("Id");
                case 1:
                    return tr("Model");
                case 2:
                    return tr("Kilometers");
                case 3:
                    return tr("LastLocation");
                case 4:
                    return tr("CurrentState");
                case 5:
                    return tr("CommissioningDataYear");
                case 6:
                    return tr("CommissioningDataMonth");
                case 7:
                    return tr("CommissioningDataDay");
                default:
                        return QString("");
                }
            }
        }
        return QVariant();
    }


    //seteaza ce atribut al unui electricScooter se va incarca in fiecare coloana
    QVariant data(const QModelIndex& index, int role=Qt::DisplayRole)const override{
        if(role==Qt::DisplayRole){
            ElectricScooter electricScooter=allElectricScooters[index.row()];
            if(index.column()==0){
                return QString::fromStdString(electricScooter.getId());
            }
            else
                if(index.column()==1){
                    return QString::fromStdString(electricScooter.getModel());
                }
                else
                    if(index.column()==2){
                        return QString::fromStdString(to_string(electricScooter.getKilometers()));
                    }
                    else
                        if(index.column()==3){
                            return QString::fromStdString(electricScooter.getLastLocation());
                        }
                        else
                            if(index.column()==4){
                                return QString::fromStdString(electricScooter.getCurrentState());
                            }
                            else
                                if(index.column()==5){
                                return QString::fromStdString(to_string(electricScooter.getCommissioningDate().year));
                                }
                            else
                                if(index.column()==6){
                                return QString::fromStdString(to_string(electricScooter.getCommissioningDate().month));
                                }
                                else
                                   if(index.column()==7){
                                    return QString::fromStdString(to_string(electricScooter.getCommissioningDate().day));
                        }


            }
        return QVariant{};
        }

    //returneaza un electricScooter care se selecteaza
    ElectricScooter getElectricScooter(const QModelIndex& index){
        return allElectricScooters[index.row()];
    }

    //primeste lista de electricScooters care se vor incarca in tabela
    void setElectricScooters(const vector<ElectricScooter>& allElectricScooters){
        this->allElectricScooters=allElectricScooters;
        QModelIndex topLeft=createIndex(0,0);
        QModelIndex bottomRight=createIndex(rowCount(),columnCount());
        emit dataChanged(topLeft, bottomRight);
        emit layoutChanged();
    }

};



/**
 Clasa GUI
 asigura interfata cu utilizatorul folosind design QT
 */
class GUI:public QWidget{

private:
    Controller controller;      //gui primeste controller-ul
    int tip;                    //gui primeste tip=1 pt manager, tip=2 pt client

    //tabela
    QTableView* tableView;

    //un obiect model al clasei MyTableModel, folosit pentru tabela
    MyTableModel* model=new MyTableModel;

    //butoanele pt sortare
    QPushButton* buttonSortId=new QPushButton("Sort By Id");
    QPushButton* buttonSortModel=new QPushButton("Sort By Model");
    QPushButton* buttonSortCommissioningData=new QPushButton("Sort By Commissioning Data");
    QPushButton* buttonSortKilometers=new QPushButton("Sort By Kilometers");
    QPushButton* buttonSortLastLocation=new QPushButton("Sort By Last Locationl");
    QPushButton* buttonSortCurrentState=new QPushButton("Sort By Current State");

    //variabile necesare pt a prelua datele din QLineEdit
    string modelES;
    int kilometers;
    string lastLocation;
    string currentState;
    Data commissioningDate;

    //OlineEdit-uri pt toate atributele
    QLineEdit* idTxt=new QLineEdit; // Această linie declară un pointer la obiectul QLineEdit numit "idTxt"
                                    //și îi atribuie o nouă instanță a clasei QLineEdit.
    QLineEdit* modelTxt=new QLineEdit;
    QLineEdit* kilometersTxt=new QLineEdit;
    QLineEdit* lastLocationTxt=new QLineEdit;
    QLineEdit* currentStateTxt=new QLineEdit;
    QLineEdit* commissioningDataYearTxt=new QLineEdit;
    QLineEdit* commissioningDataMonthTxt=new QLineEdit;
    QLineEdit* commissioningDataDayTxt=new QLineEdit;
    //QLineEdit pt nume fisier
    QLineEdit* fisierTxt=new QLineEdit;

    //butoane pt client
    QPushButton* buttonUse=new QPushButton("Use an Electric Scooter");
    QPushButton* buttonReserve=new QPushButton("Reserve an Electric Scooter");
    QPushButton* buttonPark=new QPushButton("Park an Electric Scooter");

    //butoane pt manager
    QPushButton* buttonAdd=new QPushButton("Add an Electric Scooter");
    QPushButton* buttonDelete=new QPushButton("Delete an Electric Scooter");
    QPushButton* buttonUpdate=new QPushButton("Update an Electric Scooter");

    //functii private ale clasei GUI
    void initClient();
    void initManager();
    void initConnect();
    void loadListaElectricScooters(const vector<ElectricScooter>& allElectricScooters);

public:
    //constructorul clasei GUI, primeste controller-ul si tip
    GUI(Controller& controller, int tip):controller{controller},tip{tip}{
        if(tip==1){             //daca tip=1 initializam fereastra pt manager
            initManager();
            initConnect();
        }
        else
            if(tip==2)          //daca tip=2 initializam fereastra pt client
            {
                initClient();
                initConnect();
            }
    }
};
