#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{



public:
    Connection();
     bool createconnect();
     void closeConnection();

     QSqlDatabase db;
     bool insertDataFormation(const QString &titre, const QString &description, const QString &dateDebut, const QString &duree, int &idFormateur );
     bool insertDataFormateur(const QString &nom, const QString &prenom, const QString &specialite, const QString &email,const QString &telephone);

};

#endif // CONNECTION_H

