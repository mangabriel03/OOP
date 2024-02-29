#pragma once
#include "QHBoxLayout"
#include "GUI.h"
#include "Login.h"
#include "Repository.h"
#include "Validator.h"
#include "Domain.h"
#include "QMessageBox.h"
#include "QFormLayout.h"
#include "QLabel.h"
#include "QListView.h"

/**
 init-metoda privata a clasei Login
 initializeaza fereastra care asigura interfata cu utilizatorul
 */
void Login::initLogin() {
    //layout se imparte in doua parti: stanga (in care se va afisa detaliat un electricScooter si drepata in care se va afisa tabelul)

    //QVBoxLayout *layoutLogin = new QVBoxLayout;
    QFormLayout* layoutLogin = new QFormLayout(this);

//    QLabel *titleLabel = new QLabel("Login Page");
//    titleLabel->setFont(QFont("Arial", 18, QFont::Bold));

    //in layout-ul din stanga inseram label-uri si text-box-uri pt a incarca un electric scooter selectat din tabel
    layoutLogin->addRow(new QLabel("UserName:"), nameTxt); // primește două argumente: o etichetă (QLabel) și un widget.
        // creeaza o noua linie in layout si plaseaza eticheta si widget-ul
    layoutLogin->addRow(new QLabel("Password:"), passwordTxt);
    passwordTxt->setEchoMode(QLineEdit::Password);

    layoutLogin->addWidget(buttonLogin);
    connect(buttonLogin, &QPushButton::clicked, this, &Login::login);

    layoutLogin->addRow(new QLabel("FileName:"), fisierTxt);

    string fileName="date.txt";
    QString fileNameQ = QString::fromStdString(fileName);
    fisierTxt->setText(fileNameQ);


    setLayout(layoutLogin);
    setWindowTitle("Login Page");
}
