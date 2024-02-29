//#ifndef LOGIN_H
//#define LOGIN_H

//#endif // LOGIN_H
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
#include "GUI.h"
#include "Controller.h"
#include "Repository.h"
#include "Validator.h"
#include "Test.h"
#include "string"
#include "string.h"
#include <fstream>

/**
 Clasa Login
 asigura interfata cu utilizatorul folosind design QT
 */
class Login:public QWidget{
private:

    //Controller controller;
    //GUI gui;
    QPushButton* buttonLogin=new QPushButton("Login");


    QLineEdit* nameTxt=new QLineEdit; // Această linie declară un pointer la obiectul QLineEdit numit "idTxt"
        //și îi atribuie o nouă instanță a clasei QLineEdit.
    QLineEdit* passwordTxt=new QLineEdit;


    QLineEdit* fisierTxt=new QLineEdit;


    void initLogin();


public:

    //Login(Controller& controller):controller{controller}
    //Login(GUI& gui):gui{gui}
    Login()
    {
        initLogin();

    }

public slots:
    //cream un obiect repository de tip FileRepository


    void login() {



        // Perform login logic here
        QString username = nameTxt->text();
        QString password = passwordTxt->text();

        if (username == "manager" && password == "s8cr8t") {
            //QMessageBox::information(this, "Login", "Login Successful!");
        } else
            if (username == "client" && password == "tr1ck")
        {

//            //this.hide();

//            string fileName="C:\\Users\\pc\\Desktop\\Anul 1\\Semester2\\OOP\\Tema7_QT\\date.txt";   //numele fisierului
//            FileRepository fileRepository(fileName);
//            //cream un obiect validator de tip Validator
//            Validator fileValidator;
//            Controller controller{fileRepository, fileValidator};
//            //cream un obiect ui de tip ConsolUI, care primeste obiectul controller
//            GUI gui{controller};
//            //constructorul clasei GUI, primeste controller-ul
           // gui.show();
            parentWidget()->hide();
            //QMessageBox::warning(this, "Login", "Invalid Username or Password!");
        }
        else
        {
            //QMessageBox::warning(this, "Login", "Invalid Username or Password!");
        }
    }


};
