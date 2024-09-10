#include "connection.h"
#include <QtSql>
#include <QSqlError>
#include <QSqlQuery>
Connection::Connection()
{

}
bool Connection::createconnect()
{bool test=false;


QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A4");
db.setUserName("louayzorai");//inserer nom de l'utilisateur
db.setPassword("louayzorai");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}

void Connection :: closeConnection(){db.close();}

///////////////////////////////////////////////////////FORMATION////////////////////////////////////////////////////////////////////////////
bool Connection::insertDataFormation(const QString &titre, const QString &description, const QString &dateDebut, const QString &duree, int &idFormateur)
{
    QSqlQuery query;
    query.prepare("INSERT INTO FORMATION (TITRE, DESCRIPTION, DATEDEBUT, DUREE, IDFORMATEUR) ""VALUES (:titre, :description, :dateDebut, :duree, :idFormateur)");
    query.bindValue(":titre", titre);
    query.bindValue(":description", description);
    query.bindValue(":dateDebut", dateDebut);
    query.bindValue(":duree", duree);
    query.bindValue(":idFormateur", idFormateur);
    return query.exec();
}


/////////////////////////////////////////////////////////FORMATEUR//////////////////////////////////////////////////////////////////////////////
bool Connection::insertDataFormateur(const QString &nom, const QString &prenom, const QString &specialite, const QString &email, const QString &telephone)
{
    QSqlQuery query;
    query.prepare("INSERT INTO FORMATEUR (NOM, PRENOM, SPECIALITE, EMAIL, TELEPHONE) VALUES (:nom, :prenom, :specialite, :email, :telephone)");
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":specialite", specialite);
        query.bindValue(":email", email);
        query.bindValue(":telephone", telephone);
        return query.exec();
}
