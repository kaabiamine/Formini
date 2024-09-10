#include <QSqlError>
#include <QTableWidget>
#include <QDebug>
#include <QObject>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "connection.h"
#include "formateur.h"
#include "mainwindow.h"
#include <QDateTime>
#include <QSystemTrayIcon>

//---------------------------------------------------les constructeurs---------------------------------------------------//
Formateur::Formateur()
{
    id=0;
    nom="";
    prenom="";
    specialite="";
    email="";
    telephone="";
}

Formateur::Formateur(int id, QString nom, QString prenom, QString specialite, QString email, QString telephone)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->specialite=specialite;
    this->email=email;
    this->telephone=telephone;
}
//------------------------------------------------------------------------------------------------------------------------//





//---------------------------------------------------fonction d'ajout--------------------------------------------------------//
bool Formateur::ajouterFormateur()
{
    Connection c;
    return (c.insertDataFormateur(nom, prenom, specialite, email, telephone));
}
//---------------------------------------------------------------------------------------------------------------------------//



//---------------------------------------------------fonction d'affichage---------------------------------------------------------//
void Formateur::afficherFormateur(QTableWidget *tableWidget)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A4");
    db.setUserName("louayzorai");
    db.setPassword("louayzorai");
    db.open();
    QSqlQuery query(db);
    QString str = ("SELECT * FROM FORMATEUR");
    if (query.exec(str))
    {
        tableWidget->setColumnCount(6);
        QStringList labels;
        labels<<"Nom"<<"Prenom"<<"Specialite"<<"email"<<"telephone"<<"ID";
        tableWidget->setHorizontalHeaderLabels(labels);
        int RowNumber=0;
        while(query.next())
        {
            tableWidget->insertRow(RowNumber);
            QTableWidgetItem *nom= new QTableWidgetItem;
            QTableWidgetItem *prenom= new QTableWidgetItem;
            QTableWidgetItem *specialite= new QTableWidgetItem;
            QTableWidgetItem *email= new QTableWidgetItem;
            QTableWidgetItem *telephone= new QTableWidgetItem;
            QTableWidgetItem *id= new QTableWidgetItem;

            nom->setText(query.value(0).toString());
            prenom->setText(query.value(1).toString());
            specialite->setText(query.value(2).toString());
            email->setText(query.value(3).toString());
            telephone->setText(query.value(4).toString());
            id->setText(query.value(5).toString());

            tableWidget->setItem(RowNumber,0,nom);
            tableWidget->setItem(RowNumber,1,prenom);
            tableWidget->setItem(RowNumber,2,specialite);
            tableWidget->setItem(RowNumber,3,email);
            tableWidget->setItem(RowNumber,4,telephone);
            tableWidget->setItem(RowNumber,5,id);
            RowNumber++;
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------------------//






//---------------------------------------------------fonction de suppression----------------------------------------------------//
bool Formateur::supprimerFormateur(int id)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database not open";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM FORMATEUR WHERE ID = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error deleting formateur:" << query.lastError().text();
        return false;
    }

    return true;
}
//-----------------------------------------------------------------------------------------------------------------------------//




//---------------------------------------------------fonction de modification----------------------------------------------------//
bool Formateur::modifierFormateur(int id, const QString &nom, const QString &prenom, const QString &specialite, const QString &email, const QString &telephone)
{
    // Assurez-vous que la connexion à la base de données est bien établie
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database not open";
        return false;
    }

    // Préparation de la requête
    QSqlQuery query(db);  // Utilisation de la connexion `db`
    query.prepare("UPDATE FORMATEUR SET NOM = :nom, PRENOM = :prenom, SPECIALITE = :specialite, EMAIL = :email, TELEPHONE = :telephone WHERE ID = :id");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":specialite", specialite);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":id", id);

    // Exécution de la requête et gestion des erreurs
    if (!query.exec()) {
        qDebug() << "Error updating formateur:" << query.lastError().text();
        return false;
    }

    return true;
}

//------------------------------------------------------------------------------------------------------------------------------//




//setters
void Formateur::set_nom(QString n){nom=n;}
void Formateur::set_prenom(QString n){prenom=n;}
void Formateur::set_specialite(QString n){specialite=n;}
void Formateur::set_email(QString n){email=n;}
void Formateur::set_telephone(QString n){telephone=n;}


//getters
QString Formateur::get_nom(){return nom;}
QString Formateur::get_prenom(){return prenom;}
QString Formateur::get_specialite(){return specialite;}
QString Formateur::get_email(){return email;}
QString Formateur::get_telephone(){return telephone;}



