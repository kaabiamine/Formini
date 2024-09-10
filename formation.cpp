#include "formation.h"
#include <QTableWidget>
#include <QDebug>
#include "connection.h"
#include <QMessageBox>
#include "mainwindow.h"
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QTextTableCell>
#include <QTextTableFormat>
#include <QTextCharFormat>
#include <QSqlQuery>
#include <QCalendarWidget>

/*-------------------------------------------Constructeur Par Defaut------------------------------------------------------*/
Formation::Formation()
{
    titre="";
    description="";
    datedebut="";
    duree="";
    idformateur=0;

}
/*-------------------------------------------Constructeur Parametré------------------------------------------------------*/

Formation::Formation(int id, QString titre, QString description, QString datedebut, QString duree, int idformateur)
{
    this->id=id;
    this->titre=titre;
    this->description=description;
    this->datedebut=datedebut;
    this->duree=duree;
    this->duree=idformateur;
}
/*-------------------------------------------AJOUT------------------------------------------------------*/
bool Formation::ajouterFormation()
{
    Connection c;
    return c.createconnect() && c.insertDataFormation(titre, description, datedebut, duree, idformateur);
}

/*-------------------------------------------AFFICHAGE------------------------------------------------------*/

void Formation::afficherFormation(QTableWidget *tableWidget)
{
    Connection c;
    if (!c.createconnect()) return;

    QSqlQuery query(c.db);
    if (query.exec("SELECT * FROM FORMATION"))
    {
        tableWidget->setColumnCount(6);
        tableWidget->setHorizontalHeaderLabels({"ID", "titre", "description", "datedebut", "duree", "idformateur"});
        int RowNumber = 0;
        while (query.next())
        {
            tableWidget->insertRow(RowNumber);
            for (int col = 0; col < 6; ++col)
            {
                QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
                tableWidget->setItem(RowNumber, col, item);
            }
            RowNumber++;
        }
    }
    c.db.close();
}
/*-------------------------------------------SUPPRESSION------------------------------------------------------*/

bool Formation::supprimerFormation(int id)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database not open";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM FORMATION WHERE ID = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error deleting FORMATION:" << query.lastError().text();
        return false;
    }

    return true;
}
/*-------------------------------------------MODIFICATION------------------------------------------------------*/

bool Formation::modifierFormation(int id, const QString &titre, const QString &description, const QString &datedebut, const QString &duree, const QString &idformateur)
{

    // Assurez-vous que la connexion à la base de données est bien établie
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database not open";
        return false;
    }

    // Préparation de la requête
    QSqlQuery query(db);  // Utilisation de la connexion `db`
    query.prepare("UPDATE FORMATION SET TITRE = :titre, DESCRIPTION = :description, DATEDEBUT = :datedebut, DUREE = :duree, IDFORMATEUR = :idformateur WHERE ID = :id");
    query.bindValue(":id", id);
    query.bindValue(":titre", titre);
    query.bindValue(":description", description);
    query.bindValue(":datedebut", datedebut);
    query.bindValue(":duree", duree);
    query.bindValue(":idformateur", idformateur);


    // Exécution de la requête et gestion des erreurs
    if (!query.exec()) {
        qDebug() << "Error updating formateur:" << query.lastError().text();
        qDebug() << "Error details:" << query.lastError().databaseText();
        qDebug() << "Driver error:" << query.lastError().driverText();
        return false;
    }

    return true;
}
/*-------------------------------------------RECHERCHE------------------------------------------------------*/

void Formation::rechercherFormation(const QString &searchTerm, QTableWidget *tableWidget)
{
    Connection c;
    if (!c.createconnect()) return;

    QSqlQuery query(c.db);
    query.prepare("SELECT * FROM FORMATION WHERE NOM LIKE :searchTerm");
    query.bindValue(":searchTerm", "%" + searchTerm + "%");

    if (query.exec())
    {
        tableWidget->setColumnCount(6);
        tableWidget->setHorizontalHeaderLabels({"ID", "titre", "description", "datedebut", "duree", "idformateur"});

        int RowNumber = 0;
        while (query.next())
        {
            tableWidget->insertRow(RowNumber);
            for (int col = 0; col < 6; ++col)
            {
                QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
                tableWidget->setItem(RowNumber, col, item);
            }
            RowNumber++;
        }
    }
    c.db.close();
}
/*-------------------------------------------TRI PAR NBABONNES------------------------------------------------------*/
bool Formation::trierParDuree(QTableWidget *tableWidget)
{
    Connection c;
    if (!c.createconnect()) return false;

    QSqlQuery query(c.db);
    query.prepare("SELECT * FROM INVITE ORDER BY DUREE ASC");


    if (query.exec())
    {
        tableWidget->clearContents();  // Clear existing contents
        tableWidget->setRowCount(0);  // Clear existing rows

        tableWidget->setColumnCount(6);
        tableWidget->setHorizontalHeaderLabels({"ID", "titre", "description", "datedebut", "duree", "idformateur"});



        int RowNumber = 0;
        while (query.next())
        {
            tableWidget->insertRow(RowNumber);
            for (int col = 0; col < 6; ++col)
            {
                QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
                tableWidget->setItem(RowNumber, col, item);
            }
            RowNumber++;
        }

        c.db.close();
        return true;
    }
    else
    {
        c.db.close();
        return false;
    }
}







