#ifndef FORMATEUR_H
#define FORMATEUR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableWidget>
#include "mainwindow.h"

class Formateur
{
public:
    //constructeurs
    Formateur();
    Formateur(int,QString,QString,QString,QString,QString);

    //setters
    void set_nom(QString n);
    void set_prenom(QString n);
    void set_specialite(QString n);
    void set_email(QString n);
    void set_telephone(QString n);
    bool ajouter();
    bool supprimer(int);
    QSqlQueryModel* afficher();


    //getters
    QString get_nom();
    QString get_prenom();
    QString get_specialite();
    QString get_email();
    QString get_telephone();
    Formateur(QString,QString,QString,QString,QString);

    //CRUD
    bool ajouterFormateur();
    void afficherFormateur(QTableWidget *tableWidget);
    bool supprimerFormateur(int);
    bool modifierFormateur(int id, const QString &modeDePaiement, const QString &type, const QString &categorie, const QString &dateTransaction, const QString &montant);

    //NOTIFICATIONS
    void envoyerNotificationFormateur(QString, QString);

private:

    int id;
    QString nom,prenom,specialite,email,telephone;


};
#endif // FORMATION_H
