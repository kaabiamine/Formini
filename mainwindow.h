#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "connection.h"
#include "formateur.h"
#include "formation.h"
#include <QMainWindow>
#include <QStandardItemModel>
#include <QMovie>
#include <QThread>
#include <QLabel>
#include <QMessageBox>
#include <QMainWindow>
#include <QSqlQueryModel>
#include <QStringListModel>
#include <QCalendarWidget>
#include <QGraphicsSimpleTextItem>
#include <QVariant>
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

     Q_OBJECT





private slots:



    //---------------------------------------------------------FORMATIONS------------------------------------------------------//





    //------------------------------------------------------------------------------------------------------------------------------//



    //------------------------------------------------------INVITES-----------------------------------------------------------------//



    //-------------------------------------------------------------------------------------------------------------------------------//





    void on_pushButton_Ajout_Formateur_clicked();

    void on_pushButton_Annuler_Formateur_clicked();
    void afficherTableDesFormateurs();
    void on_pushButton_updateFormation_clicked();
    void searchFormateursByName(const QString &name);
    void sortFormateursByName();
    void sortFormateursByFirstName();
    void AfficherEtmettreAJourPieChartSpecialites();

    void on_pushButton_deleteFormation_clicked();

    void on_pushButton_Suppression_Formateur_clicked();

    void on_pushButton_Modification_Formateur_clicked();

    void on_pushButton_exportationFormatExcel_Formateur_clicked();

    void on_pushButton_ajouterFormation_clicked();

    void on_pushButton_annulerFormation_clicked();

    void afficherTableDesFormations();
    void searchFormateursByTITRE(const QString &titre);
    void sortFormationByDuree();

    void on_pushButton_exporterFormateur_clicked();
    void AfficherEtmettreAJourPieChartDuree();

private:
    QSqlQueryModel *modelI; // Declare a member variable for the model
    Ui::MainWindow *ui;
    QStandardItemModel *model; // Déclaration du modèle ici

};
#endif // MAINWINDOW_H

