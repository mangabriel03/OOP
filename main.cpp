/*
 Erweitern Sie Lösungzu Labor6entsprechendenuntenstehende Anforderungen.Alle Anforderungen aus Labor5+6bleiben gültig,
sofern nicht ersetzt!Weitere AnforderungenW1.Das Programm soll eine Grafische Benutzeroberfläche (GUI) anbieten, dasdie Liste
 aller Scootermit ihren Attributen als Tabelle anzeigt.Diese Tabelle sollte die Möglichkeit bieten nach jeder Spalte zu sortieren.
W2.Der  Benutzer  kann einenScooteraus  der  Listeauszuwählen,  um  die  Attribute  in  einer Detailansicht zu sehen.
W3.Die GUI erlaubt dem Benutzer die CSV-Datei auszuwählen, die als Datenbank dient.Daraus soll die Liste der Scooter geladen werden.
Abgabekriterien
K1.Die abgegebene Lösung muss  aus  allen  notwendigen Dateien  bestehen(Quellcode  und  Build-Dateien, keine
ausführbare Binärdateien).Diese sind als ZIPabzugebenL7_TeamX.zip(X ist die Arbeitsgruppe)(kein RAR, 7z, o.ä.)
K2.Das abgegebene Projektmuss mit CLion oderQtCreatorkompilierbar sein!

BONUS+5pt
B1. Die GUI verlangt eine Anmeldung als Manager
oder Kundemittels Benutzername und Passwort (manager: s8cr8t, kunde: tr1ck).
B2.Der Kunde soll nur verwendbareScooter sehen,
 einen Scooter reservieren, verwenden und parken können.
B3.Manager    sollten alleAttribute    eines Scooters bearbeitenkönnen,einen Scooter löschen und einenneuen Scooter hinzuzufügenkönnen.
B4.     Die Veränderungen an den Scootern sollpersistent in der ausgewählten CSV Datei gespeichert werden.


Extindeți soluția la Labor6 conform cerințelor de mai jos. Toate cerințele de la Labor5+6 rămân valabile dacă nu sunt înlocuite!
Alte cerințe
W1.Programul ar trebui să ofere o interfață grafică cu utilizatorul (GUI) care să afișeze lista tuturor scuterelor cu atributele lor
sub formă de tabel.Acest tabel ar trebui să ofere posibilitatea de sortare pe fiecare coloană.
W2.Utilizatorul poate selecta un scuter din listă pentru a vedea atributele într-o vizualizare detaliată.
W3.Interfața grafică permite utilizatorului să selecteze fișierul CSV care servește ca bază de date.De aici ar trebui să se încarce
lista de scutere.

Criterii de trimitere
K1 .Soluția trimisă trebuie să conțină toate fișierele necesare (codul sursă și fișiere de compilare, fără fișiere binare executabile).
Acestea trebuie trimise ca ZIPL7_TeamX.zip (X este grupul de lucru) (fără RAR, 7z sau similar)
K2 .Proiectul trimis trebuie să fie compilabil cu CLion sau QtCreator!

BONUS+5pt
B1. GUI necesită autentificare ca manager sau client folosind un nume de utilizator și o parolă (manager: s8cr8t, client: tr1ck).
B2. Clientul ar trebui să poată vedea doar scutere utilizabile, să rezerve, să utilizeze și să parcheze un scuter.
B3. Managerii ar trebui să poată vedea a putea edita toate atributele unui scuter, a Șterge un scuter și a adăuga un nou scuter.
B4. Modificările aduse scuterelor ar trebui să fie salvate în mod persistent în fișierul CSV selectat.
 */


#include "mainwindow.h"
#include "GUI.h"
#include "Controller.h"
#include "Repository.h"
#include "Validator.h"
#include "Test.h"
#include "string"
#include "string.h"
#include <fstream>
#include <QApplication>
#include "Login.h"
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //cream un obiect repository de tip FileRepository
    string fileName="C:\\Users\\pc\\Desktop\\Anul 1\\Semester2\\OOP\\Tema7_QT\\date.txt";   //numele fisierului
    FileRepository fileRepository(fileName);
    //cream un obiect validator de tip Validator
    Validator fileValidator;
    Controller controller{fileRepository, fileValidator};
    //cream un obiect ui de tip ConsolUI, care primeste obiectul controller
    GUI gui{controller,1}; // gui pt manager
    GUI gui2{controller,2}; // gui pt client , ambele sunt aceiasi clasa, dar obiecte diferite


    // pagina de login
    QWidget window;
    window.setWindowTitle("Login Page");

    // Create the login widgets
    QLabel* usernameLabel = new QLabel("Username:");
    QLineEdit* usernameLineEdit = new QLineEdit;
    QLabel* passwordLabel = new QLabel("Password:");
    QLineEdit* passwordLineEdit = new QLineEdit;
    passwordLineEdit->setEchoMode(QLineEdit::Password);  // sa nu se vada parola, sa puna bulinute cand introduc parola
    QPushButton* loginButton = new QPushButton("Login");

    // Create a layout and add the widgets
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(usernameLabel);
    layout->addWidget(usernameLineEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordLineEdit);
    layout->addWidget(loginButton);

    // Set the layout on the main window
    window.setLayout(layout);

    // Connect the login button to a slot for handling the login logic
    QObject::connect(loginButton, &QPushButton::clicked, [&]() {
        QString username = usernameLineEdit->text();
        QString password = passwordLineEdit->text();

        // Perform login logic here
        if (username == "manager" && password == "s8cr8t") {
            //QMessageBox::information(&window, "Login", "Login Successful!");
            // Open the main application window or perform any other actions

            gui.show();

        }
        else
            if (username == "kunde" && password == "tr1ck") {
                //QMessageBox::information(&window, "Login", "Login Successful!");
                // Open the main application window or perform any other actions

                gui2.show();

            }
            else
            {
                QMessageBox::warning(&window, "Login", "Invalid Username or Password!");
            }
    });

    // Show the main window
    window.show();
    return a.exec();
}

