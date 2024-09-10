#ifndef FORMATION_H
#define FORMATION_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableWidget>
#include <QCalendarWidget>


class Formation
{
public:
    //constructeurs
    Formation();
    Formation(int,QString,QString,QString,QString,int);

    //setters
    void settitre(QString n){titre=n;}
    void setdescription(QString n){description=n;}
    void setdatedebut(QString n){datedebut=n;}
    void setduree(QString n){duree=n;}
    void setidformateur(int n){idformateur=n;}

    //getters
    QString get_titre(){return titre;}
    QString get_description(){return description;}
    QString get_datedebut(){return datedebut;}
    QString get_duree(){return duree;}
    int get_idformateur(){return idformateur;}


    //CRUD
    bool ajouterFormation();
    void afficherFormation(QTableWidget *tableWidget);
    bool supprimerFormation(int);
    bool modifierFormation(int id, const QString &titre, const QString &description, const QString &datedebut, const QString &duree, const QString &idformateur);

    //Fonctionnalites
    void rechercherFormation(const QString &searchTerm, QTableWidget *tableWidget);
    bool trierParDuree(QTableWidget *tableWidget);
    bool exportToPDF(const QString &filePath, QTableWidget *tableWidget);


private:
    int id,idformateur;
    QString titre,description,datedebut,duree;
};

#endif // FORMATION_H
