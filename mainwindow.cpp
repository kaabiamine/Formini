#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "formation.h"
#include "formateur.h"
#include "connection.h"
#include <QInputDialog>
#include <QTextStream>
#include <QDesktopServices>
#include <QPdfWriter>
#include <QPainter>
#include <QPrinter>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextDocument>
#include<QUrl>
#include <QString>
#include <QDebug>
#include <QSqlQuery>
#include <QTableWidget>

#include <QKeyEvent>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>

#include <fstream>
#include <QtCharts>
#include <QChartView>

#include <QFont>

#include "xlsxdocument.h"
#include "xlsxformat.h"
#include <QImage>
#include <QBuffer>
#include <QFile>

#include <QProcess>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sponsor.h"
#include "connection.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDialog>
#include <QLabel>
#include <QPrinter>
#include <QFileDialog>
#include <QPdfWriter>
#include <QTextDocument>
#include <QComboBox>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QCoreApplication>
#include <QEvent>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

#include <QtCharts/QPieSlice>
#include <QGeoCodingManager>
#include <QGeoCoordinate>
#include <QGeoAddress>
#include <QGeoServiceProvider>
#include <QQuickItem>
#include <QQuickWidget>

#include <QTcpSocket>
#include <QtCore>
#include <QtNetwork>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QChart>
#include <QSqlRecord>
#include <QPrinter>
#include <QPrintDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

    , ui(new Ui::MainWindow)

{

    //******************************************************************************************************************************************************************//
    //******************************************************************************************************************************************************************//
    //******************************************************************************************************************************************************************//
    //******************************************************************************************************************************************************************//
    //---------------------------------------------------------------LE CONSTRUCTEUR DU MAINWINDOW----------------------------------------------------------------------//
    //******************************************************************************************************************************************************************//
    //******************************************************************************************************************************************************************//
    //******************************************************************************************************************************************************************//
       ui->setupUi(this);




       AfficherEtmettreAJourPieChartSpecialites();
       AfficherEtmettreAJourPieChartDuree();
       connect(this, SIGNAL(dataUpdated()), this, SLOT(updateTableWidget())); // connecter le signal envers le slot
       connect(ui->lineEdit_RechercheParNom_Formateur, &QLineEdit::textChanged, this, &MainWindow::searchFormateursByName);
       connect(ui->lineEdit_rechercherFormation, &QLineEdit::textChanged, this, &MainWindow::searchFormateursByTITRE);
       connect(ui->Button_TrierParNom_Formateur, &QPushButton::clicked, this, &MainWindow::sortFormateursByName);
       connect(ui->Button_trierParPrenom_Formateur, &QPushButton::clicked, this, &MainWindow::sortFormateursByFirstName);
       connect(ui->pushButton_trierFormations, &QPushButton::clicked, this, &MainWindow::sortFormationByDuree);
       ui->table_de_formations->setColumnCount(6);
       QStringList labels{"Titre", "Description", "Date debut", "Duree", "ID. Formateur"};
       ui->table_de_formations->setHorizontalHeaderLabels(labels);
       Connection c;
       if (c.createconnect())
       {
           QString searchTerm =ui->lineEdit_rechercherFormation->text();

       }



//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//








//-------------------------------------------------------------------------FORMATEUR-----------------------------------------------------------------------------//
       //-----------------------------------installation des reflexes selon les signaux--------------------------------//




//--------------------------------Initialisation du tableau et ses champs----------------------------------------------//
       ui->table_de_formateurs->setColumnCount(5);
       QStringList labelsT{"Nom", "Prenom", "Specialite", "Email", "Telephone"};
       ui->table_de_formateurs->setHorizontalHeaderLabels(labelsT);

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//



}




void MainWindow::on_pushButton_Ajout_Formateur_clicked()
{
    AfficherEtmettreAJourPieChartSpecialites();
    QString nom = ui->lineEdit_Nom_Formateur->text();
    QString prenom = ui->lineEdit_Prenom_Formateur->text();
    QString specialite = ui->LineEdit_Specialite_Formateur->currentText();
    QString email = ui->lineEdit_Email_Formateur->text();
    QString telephone = ui->lineEdit_Telephone_Formateur->text();
    Formateur f;
    f.set_nom(nom);
    f.set_prenom(prenom);
    f.set_specialite(specialite);
    f.set_email(email);
    f.set_telephone(telephone);
    Connection c;
    if (c.createconnect())
    {
       f.ajouterFormateur();
       afficherTableDesFormateurs();
    }
}

void MainWindow::on_pushButton_Annuler_Formateur_clicked()
{
    ui->lineEdit_Nom_Formateur->clear();
    ui->lineEdit_Prenom_Formateur->clear();
    ui->lineEdit_Email_Formateur->clear();
    ui->lineEdit_Telephone_Formateur->clear();
}

void MainWindow::afficherTableDesFormateurs()
{
    AfficherEtmettreAJourPieChartSpecialites();
    // Assurez-vous que votre QTableWidget est correctement initialisé
    QTableWidget *tableDesFormateurs = ui->table_de_formateurs;

    // Créez une connexion à la base de données
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A4");
    db.setUserName("louayzorai");
    db.setPassword("louayzorai");

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données :" << db.lastError().text();
        return;
    }

    // Exécutez une requête pour récupérer les données de la table FORMATEUR
    QSqlQuery query(db);  // Utilisez la connexion `db`
    if (!query.exec("SELECT * FROM FORMATEUR")) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        return;
    }

    // Configurez le QTableWidget
    int columnCount = query.record().count();
    tableDesFormateurs->setColumnCount(columnCount);

    // Configurez les en-têtes de colonnes
    QStringList headers;
    for (int i = 0; i < columnCount; ++i) {
        headers << query.record().fieldName(i);
    }
    tableDesFormateurs->setHorizontalHeaderLabels(headers);

    // Remplissez le QTableWidget avec les données
    tableDesFormateurs->setRowCount(0); // Réinitialisez le nombre de lignes
    while (query.next()) {
        int row = tableDesFormateurs->rowCount();
        tableDesFormateurs->insertRow(row);

        for (int i = 0; i < columnCount; ++i) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(i).toString());
            tableDesFormateurs->setItem(row, i, item);
        }
    }

    // Fermez la connexion à la base de données
    db.close();
}






void MainWindow::on_pushButton_Suppression_Formateur_clicked()
{
    AfficherEtmettreAJourPieChartSpecialites();
    QItemSelectionModel *select = ui->table_de_formateurs->selectionModel();
    QModelIndexList selectedIndexes = select->selectedIndexes();

    if (!selectedIndexes.isEmpty())
    {
        int row = selectedIndexes.first().row();
        QTableWidgetItem *item = ui->table_de_formateurs->item(row, 0); // Vérifiez la colonne contenant l'ID après le tri
        if (item) // Vérifiez si l'élément existe
        {
            int idToDelete = item->text().toInt();
            Formateur f;
            if (f.supprimerFormateur(idToDelete))
            {
                // Supprimer les widgets de cellule associés à cette ligne
                for (int c = 0; c < ui->table_de_formateurs->columnCount(); ++c)
                {
                    QWidget *cellWidget = ui->table_de_formateurs->cellWidget(row, c);
                    if (cellWidget)
                    {
                        cellWidget->deleteLater();
                    }
                }
                ui->table_de_formateurs->removeRow(row);

                ui->champ_resultat_CRUD_Formateur->setText("Donnée supprimée avec succès.");
            }
            else
            {
                ui->champ_resultat_CRUD_Formateur->setText("Echec de la suppression !");
                qDebug() << "Suppression failed";
            }
        }
        else
        {
            ui->champ_resultat_CRUD_Formateur->setText("La ligne sélectionnée ne contient pas d'ID.");
        }
    }
    else
    {
        ui->champ_resultat_CRUD_Formateur->setText("Veuillez sélectionner une ligne à supprimer !");
    }

    // Réafficher les données après suppression
    afficherTableDesFormateurs();
}

void MainWindow::on_pushButton_Modification_Formateur_clicked()
{
    AfficherEtmettreAJourPieChartSpecialites();
    QItemSelectionModel *select = ui->table_de_formateurs->selectionModel();
    QModelIndexList selectedIndexes = select->selectedIndexes();

    if (!selectedIndexes.isEmpty())
    {
        int row = selectedIndexes.first().row();
        int idToModify = ui->table_de_formateurs->item(row, 0)->text().toInt();
        QString nom = ui->table_de_formateurs->item(row, 1)->text();
        QString prenom = ui->table_de_formateurs->item(row, 2)->text();
        QString specialite = ui->table_de_formateurs->item(row, 3)->text();
        QString email = ui->table_de_formateurs->item(row, 4)->text();
        QString telephone = ui->table_de_formateurs->item(row, 5)->text();

        Formateur f;
        if (f.modifierFormateur(idToModify, nom, prenom, specialite, email, telephone))
        {
            // Met à jour les cellules du tableau
            ui->table_de_formateurs->setItem(row, 0, new QTableWidgetItem(QString::number(idToModify)));
            ui->table_de_formateurs->setItem(row, 1, new QTableWidgetItem(nom));
            ui->table_de_formateurs->setItem(row, 2, new QTableWidgetItem(prenom));
            ui->table_de_formateurs->setItem(row, 3, new QTableWidgetItem(specialite));
            ui->table_de_formateurs->setItem(row, 4, new QTableWidgetItem(email));
            ui->table_de_formateurs->setItem(row, 5, new QTableWidgetItem(telephone));

            ui->champ_resultat_CRUD_Formateur->setText("Données modifiées avec succès.");
        }
        else
        {
            ui->champ_resultat_CRUD_Formateur->setText("Échec de la modification !");
        }
    }
    else
    {
        ui->champ_resultat_CRUD_Formateur->setText("Veuillez sélectionner une ligne à modifier !");
    }
}

void MainWindow::searchFormateursByName(const QString &name)
{
    // Valider la saisie du nom
    bool nameIsValid = true;
    QString errorMessage;

    // Vous pouvez ajuster l'expression régulière selon vos besoins
    QRegExp nameRegExp("^[A-Za-zÀ-ÖØ-ÿ '\"-]+$"); // Permet les lettres, les espaces, les apostrophes, les guillemets et les tirets
    if (!nameRegExp.exactMatch(name) && !name.isEmpty()) {
        nameIsValid = false;
        errorMessage = "Nom invalide. Veuillez saisir uniquement des lettres, des espaces, des apostrophes, des guillemets et des tirets.";
    }

    // Afficher un message d'erreur si le nom n'est pas valide
    if (!nameIsValid) {
        ui->champ_erreur_rechercheParNom->setText(errorMessage);
        return;
    } else {
        ui->champ_erreur_rechercheParNom->clear();
    }

    // Filtrer les formateurs en fonction du nom valide
    QString filterName = name.isEmpty() ? "" : name;
    for (int row = 0; row < ui->table_de_formateurs->rowCount(); ++row) {
        QString currentName = ui->table_de_formateurs->item(row, 1)->text(); // Supposons que le nom du formateur est dans la première colonne
        bool showRow = currentName.contains(filterName, Qt::CaseInsensitive);

        ui->table_de_formateurs->setRowHidden(row, !showRow);
    }
}

void MainWindow::sortFormateursByName()
{
    // Trier les lignes du tableau par la colonne contenant les noms (colonne 0)
    ui->table_de_formateurs->sortItems(0, Qt::AscendingOrder);
}

void MainWindow::sortFormateursByFirstName()
{
    // Trier les lignes du tableau par la colonne contenant les prénoms (colonne 1)
    ui->table_de_formateurs->sortItems(1, Qt::AscendingOrder);
}


void MainWindow::on_pushButton_exportationFormatExcel_Formateur_clicked()
{
    // Créer un objet Workbook
    QXlsx::Document xlsx;

    // Obtenir le nombre de lignes et de colonnes du QTableWidget
    int rowCount = ui->table_de_formateurs->rowCount();
    int columnCount = ui->table_de_formateurs->columnCount();

    // Ajouter le titre "TABLE DES FORMATEURS" sur 4 lignes et 8 colonnes
    QColor couleurCellule(0, 32, 96);
    xlsx.mergeCells(QXlsx::CellRange(1, 1, 4, 24));
    QXlsx::Format titleFormat; // Déclaration de la variable titleFormat
    titleFormat.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    titleFormat.setVerticalAlignment(QXlsx::Format::AlignVCenter);
    titleFormat.setFontBold(true);
    titleFormat.setFontSize(36);
    titleFormat.setFontColor(Qt::white);
    titleFormat.setPatternBackgroundColor(couleurCellule);
    xlsx.write(1, 1, "TABLE DES FORMATEURS", titleFormat);

    // Sauter 2 lignes après le titre
    xlsx.write(6, 1, ""); // Écrire une cellule vide à la ligne 6

    // Ajouter les noms de colonnes
    QXlsx::Format nomDeColonneFormat; // Déclaration de la variable titleFormat
    nomDeColonneFormat.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    nomDeColonneFormat.setVerticalAlignment(QXlsx::Format::AlignVCenter);
    nomDeColonneFormat.setFontBold(true);
    nomDeColonneFormat.setFontSize(24);
    nomDeColonneFormat.setFontColor(Qt::white);
    QColor couleurCelluleNomColonne(221, 171, 213);
    nomDeColonneFormat.setPatternBackgroundColor(couleurCelluleNomColonne);

    for (int column = 0; column < columnCount; ++column) {
        QTableWidgetItem *headerItem = ui->table_de_formateurs->horizontalHeaderItem(column);
        if (headerItem) {
            xlsx.write(8, column * 4 + 1, headerItem->text(),nomDeColonneFormat);
            xlsx.mergeCells(QXlsx::CellRange(8, column * 4 + 1, 11, column * 4 + 4)); // Étaler sur 4 colonnes et 4 lignes

            // Appliquer le format pour les noms de colonnes
            QXlsx::Format columnNameFormat;
            columnNameFormat.setFontBold(true);
            columnNameFormat.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
            columnNameFormat.setVerticalAlignment(QXlsx::Format::AlignVCenter);
            columnNameFormat.setFontSize(24);
            xlsx.cellAt(8, column * 4 + 1)->format().setFont(columnNameFormat.font());
            xlsx.cellAt(8, column * 4 + 1)->format().setHorizontalAlignment(columnNameFormat.horizontalAlignment());
            xlsx.cellAt(8, column * 4 + 1)->format().setVerticalAlignment(columnNameFormat.verticalAlignment());
            xlsx.cellAt(8, column * 4 + 1)->format().setFontSize(columnNameFormat.fontSize());
        }
    }

    // Parcourir le QTableWidget pour copier les données dans le document Excel
    QXlsx::Format formatCelluleNormale; // Déclaration de la variable titleFormat
    formatCelluleNormale.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    formatCelluleNormale.setVerticalAlignment(QXlsx::Format::AlignVCenter);
    formatCelluleNormale.setFontSize(16);
    formatCelluleNormale.setFontColor(Qt::white);
    formatCelluleNormale.setPatternBackgroundColor(couleurCellule);
    for (int row = 0; row < rowCount; ++row) {
        for (int column = 0; column < columnCount; ++column) {
            // Obtenir le texte de la cellule dans le QTableWidget
            QTableWidgetItem *item = ui->table_de_formateurs->item(row, column);
            if (item) {
                // Insérer le texte de la cellule dans le document Excel
                xlsx.write(row + 12, column * 4 + 1, item->text(),formatCelluleNormale);
                xlsx.mergeCells(QXlsx::CellRange(row + 12, column * 4 + 1, row + 13, column * 4 + 4)); // Étaler sur 4 colonnes et 2 lignes
            }
        }
    }
    // Chemin vers votre image
    QString imagePath = "/tsawer/logo pour excel.png";

    // Charger l'image à partir du chemin
    QImage image(imagePath);

    // Insérer l'image dans le fichier Excel
    xlsx.insertImage(0, 0, image);
    // Sauvegarder le document Excel
    QString filePath = QFileDialog::getSaveFileName(this, tr("Exporter en Excel"), "", tr("Fichiers Excel (*.xlsx)"));
    if (!filePath.isEmpty()) {
        xlsx.saveAs(filePath);
    }
}

void MainWindow::AfficherEtmettreAJourPieChartSpecialites()
{
    // Création de la connexion à la base de données
    Connection c;
    if (!c.createconnect()) {
        qDebug() << "Erreur lors de la connexion à la base de données.";
        return;
    }

    // Variables pour stocker les pourcentages
    float percentInformatique = 0.0;
    float percentGestion = 0.0;
    float percentLeadership = 0.0;
    float percentDevPersonnel = 0.0;

    // Variable pour stocker le total des formateurs
    int totalFormateurs = 0;

    // Obtenir le total des formateurs
    QSqlQuery query;
    if (!query.exec("SELECT COUNT(*) FROM FORMATEUR")) {
        qDebug() << "Erreur lors de l'exécution de la requête pour le total des formateurs.";
        return;
    }

    if (query.next()) {
        totalFormateurs = query.value(0).toInt();
    }

    // Si aucun formateur, afficher un graphique vide
    if (totalFormateurs == 0) {
        QPieSeries *emptySeries = new QPieSeries();
        emptySeries->append("Aucun formateur", 1);
        QChart *chart = new QChart();
        chart->addSeries(emptySeries);
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->setTitle("Statistiques des spécialités des formateurs");
        chart->setTheme(QChart::ChartThemeBlueCerulean);

        // Nettoyer les anciens graphiques
        QList<QChartView *> chartViews = ui->statsSpecialites->findChildren<QChartView *>();
        for (auto view : chartViews) {
            view->deleteLater();
        }

        // Créer un nouveau QChartView et l'ajouter au widget
        QChartView *chartview = new QChartView(chart);
        chartview->setRenderHint(QPainter::Antialiasing);
        chartview->setParent(ui->statsSpecialites);
        chartview->setGeometry(ui->statsSpecialites->rect()); // Ajuste la taille au widget parent
        chartview->show();
        return;
    }

    // Calculer le pourcentage pour chaque spécialité
    auto calculatePercentage = [&](const QString &speciality) -> float {
        if (query.exec(QString("SELECT COUNT(*) FROM FORMATEUR WHERE SPECIALITE = '%1'").arg(speciality))) {
            query.next();
            int count = query.value(0).toInt();
            return (static_cast<float>(count) / totalFormateurs) * 100.0;
        } else {
            qDebug() << "Erreur lors de l'exécution de la requête pour" << speciality;
            return 0.0;
        }
    };

    percentInformatique = calculatePercentage("Informatique");
    percentGestion = calculatePercentage("Gestion");
    percentLeadership = calculatePercentage("Leadership");
    percentDevPersonnel = calculatePercentage("Dev. Personnel");

    // Créer les labels avec les pourcentages
    QString labelInformatique = QString("Informatique %1%").arg(QString::number(percentInformatique, 'f', 2));
    QString labelGestion = QString("Gestion %1%").arg(QString::number(percentGestion, 'f', 2));
    QString labelLeadership = QString("Leadership %1%").arg(QString::number(percentLeadership, 'f', 2));
    QString labelDevPersonnel = QString("Dev. Personnel %1%").arg(QString::number(percentDevPersonnel, 'f', 2));

    // Créer le QPieSeries et ajouter les données
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.3);
    series->append(labelInformatique, percentInformatique);
    series->append(labelGestion, percentGestion);
    series->append(labelLeadership, percentLeadership);
    series->append(labelDevPersonnel, percentDevPersonnel);

    // Rendre les étiquettes visibles si le pourcentage est supérieur à zéro
    for (int i = 0; i < series->slices().count(); ++i) {
        QPieSlice *slice = series->slices().at(i);
        if (slice->value() > 0) {
            slice->setLabelVisible();
        }
    }

    // Créer le graphique et le QChartView
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle("Statistiques des spécialités des formateurs");
    chart->setTheme(QChart::ChartThemeBlueCerulean);

    // Nettoyer les anciens graphiques
    QList<QChartView *> chartViews = ui->statsSpecialites->findChildren<QChartView *>();
    for (auto view : chartViews) {
        view->deleteLater();
    }

    // Créer un nouveau QChartView et l'ajouter au widget
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setParent(ui->statsSpecialites);
    chartview->setGeometry(ui->statsSpecialites->rect()); // Ajuste la taille au widget parent
    chartview->show();
}



















MainWindow::~MainWindow()
{
    delete ui;  // Suppression de l'objet `ui` pour libérer la mémoire
}

void MainWindow::on_pushButton_ajouterFormation_clicked()
{

    QString titre = ui->lineEdit_Titre->text();
    QString description = ui->lineEdit_Description->text();
    QString datedebut = ui->lineEdit_DateDebut->text();
    QString duree = ui->lineEdit_Duree->text();
    int idformateur = ui->lineEdit_ID_Formateur->text().toInt();
    Formation f;
    f.settitre(titre);
    f.setdescription(description);
    f.setdatedebut(datedebut);
    f.setduree(duree);
    f.setidformateur(idformateur);
    Connection c;
    if (c.createconnect())
    {
       f.ajouterFormation();
       afficherTableDesFormations();
       AfficherEtmettreAJourPieChartDuree();
    }
}

void MainWindow::on_pushButton_annulerFormation_clicked()
{
    ui->lineEdit_Titre->clear();
    ui->lineEdit_Description->clear();
    ui->lineEdit_DateDebut->clear();
    ui->lineEdit_Duree->clear();
    ui->lineEdit_ID_Formateur->clear();
}

void MainWindow::afficherTableDesFormations()
{
    // Assurez-vous que votre QTableWidget est correctement initialisé
    QTableWidget *tableDesFormations = ui->table_de_formations;

    // Créez une connexion à la base de données
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A4");
    db.setUserName("louayzorai");
    db.setPassword("louayzorai");

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données :" << db.lastError().text();
        return;
    }

    // Exécutez une requête pour récupérer les données de la table FORMATEUR
    QSqlQuery query(db);  // Utilisez la connexion `db`
    if (!query.exec("SELECT * FROM FORMATION")) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        return;
    }

    // Configurez le QTableWidget
    int columnCount = query.record().count();
    tableDesFormations->setColumnCount(columnCount);

    // Configurez les en-têtes de colonnes
    QStringList headers;
    for (int i = 0; i < columnCount; ++i) {
        headers << query.record().fieldName(i);
    }
    tableDesFormations->setHorizontalHeaderLabels(headers);

    // Remplissez le QTableWidget avec les données
    tableDesFormations->setRowCount(0); // Réinitialisez le nombre de lignes
    while (query.next()) {
        int row = tableDesFormations->rowCount();
        tableDesFormations->insertRow(row);

        for (int i = 0; i < columnCount; ++i) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(i).toString());
            tableDesFormations->setItem(row, i, item);
        }
    }

    // Fermez la connexion à la base de données
    db.close();
}


void MainWindow::on_pushButton_deleteFormation_clicked()
{
    QItemSelectionModel *select = ui->table_de_formations->selectionModel();
    QModelIndexList selectedIndexes = select->selectedIndexes();

    if (!selectedIndexes.isEmpty())
    {
        int row = selectedIndexes.first().row();
        QTableWidgetItem *item = ui->table_de_formations->item(row, 0); // Vérifiez la colonne contenant l'ID après le tri
        if (item) // Vérifiez si l'élément existe
        {
            int idToDelete = item->text().toInt();
            Formation f;
            if (f.supprimerFormation(idToDelete))
            {
                // Supprimer les widgets de cellule associés à cette ligne
                for (int c = 0; c < ui->table_de_formations->columnCount(); ++c)
                {
                    QWidget *cellWidget = ui->table_de_formations->cellWidget(row, c);
                    if (cellWidget)
                    {
                        cellWidget->deleteLater();
                    }
                }
                ui->table_de_formations->removeRow(row);

                ui->champ_resultat_CRUD_Formation->setText("Donnée supprimée avec succès.");
                afficherTableDesFormations();
                AfficherEtmettreAJourPieChartDuree();
            }
            else
            {
                ui->champ_resultat_CRUD_Formation->setText("Echec de la suppression !");
                qDebug() << "Suppression failed";
            }
        }
        else
        {
            ui->champ_resultat_CRUD_Formation->setText("La ligne sélectionnée ne contient pas d'ID.");
        }
    }
    else
    {
        ui->champ_resultat_CRUD_Formation->setText("Veuillez sélectionner une ligne à supprimer !");
    }

    // Réafficher les données après suppression
    afficherTableDesFormations();
}

void MainWindow::on_pushButton_updateFormation_clicked()
{
    QItemSelectionModel *select = ui->table_de_formations->selectionModel();
    QModelIndexList selectedIndexes = select->selectedIndexes();

    if (!selectedIndexes.isEmpty())
    {
        int row = selectedIndexes.first().row();
        int idToModify = ui->table_de_formations->item(row, 0)->text().toInt();
        QString titre = ui->table_de_formations->item(row, 1)->text();
        QString description = ui->table_de_formations->item(row, 2)->text();
        QString datedebut = ui->table_de_formations->item(row, 3)->text();
        QString duree = ui->table_de_formations->item(row, 4)->text();
        QString idformateur = ui->table_de_formations->item(row, 5)->text();

        Formation f;
        if (f.modifierFormation(idToModify, titre, description, datedebut, duree, idformateur))
        {
            // Met à jour les cellules du tableau
            ui->table_de_formations->setItem(row, 0, new QTableWidgetItem(QString::number(idToModify)));
            ui->table_de_formations->setItem(row, 1, new QTableWidgetItem(titre));
            ui->table_de_formations->setItem(row, 2, new QTableWidgetItem(description));
            ui->table_de_formations->setItem(row, 3, new QTableWidgetItem(datedebut));
            ui->table_de_formations->setItem(row, 4, new QTableWidgetItem(duree));
            ui->table_de_formations->setItem(row, 5, new QTableWidgetItem(idformateur));

            ui->champ_resultat_CRUD_Formation->setText("Données modifiées avec succès.");
            afficherTableDesFormations();
            AfficherEtmettreAJourPieChartDuree();
        }
        else
        {
            ui->champ_resultat_CRUD_Formation->setText("Échec de la modification !");
        }
    }
    else
    {
        ui->champ_resultat_CRUD_Formation->setText("Veuillez sélectionner une ligne à modifier !");
    }
}

void MainWindow::searchFormateursByTITRE(const QString &titre)
{
    // Valider la saisie du titre
    bool nameIsValid = true;
    QString errorMessage;

    // Vous pouvez ajuster l'expression régulière selon vos besoins
    QRegExp nameRegExp("^[A-Za-zÀ-ÖØ-ÿ '\"-]+$"); // Permet les lettres, les espaces, les apostrophes, les guillemets et les tirets
    if (!nameRegExp.exactMatch(titre) && !titre.isEmpty()) {
        nameIsValid = false;
        errorMessage = "titre invalide. Veuillez saisir uniquement des lettres, des espaces, des apostrophes, des guillemets et des tirets.";
    }

    // Afficher un message d'erreur si le nom n'est pas valide
    if (!nameIsValid) {
        ui->champ_erreur_rechercheParTitre->setText(errorMessage);
        return;
    } else {
        ui->champ_erreur_rechercheParTitre->clear();
    }

    // Filtrer les formateurs en fonction du nom valide
    QString filterName = titre.isEmpty() ? "" : titre;
    for (int row = 0; row < ui->table_de_formations->rowCount(); ++row) {
        QString currentName = ui->table_de_formations->item(row, 1)->text(); // Supposons que le nom du formateur est dans la première colonne
        bool showRow = currentName.contains(filterName, Qt::CaseInsensitive);

        ui->table_de_formations->setRowHidden(row, !showRow);
    }
}


void MainWindow::sortFormationByDuree()
{
    // Trier les lignes du tableau par la colonne contenant les prénoms (colonne 1)
    ui->table_de_formations->sortItems(4, Qt::AscendingOrder);
}

void MainWindow::on_pushButton_exporterFormateur_clicked()
{
    // Créer un objet Workbook
    QXlsx::Document xlsx;

    // Obtenir le nombre de lignes et de colonnes du QTableWidget
    int rowCount = ui->table_de_formations->rowCount();
    int columnCount = ui->table_de_formations->columnCount();

    // Ajouter le titre "TABLE DES FORMATEURS" sur 4 lignes et 8 colonnes
    QColor couleurCellule(0, 32, 96);
    xlsx.mergeCells(QXlsx::CellRange(1, 1, 4, 24));
    QXlsx::Format titleFormat; // Déclaration de la variable titleFormat
    titleFormat.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    titleFormat.setVerticalAlignment(QXlsx::Format::AlignVCenter);
    titleFormat.setFontBold(true);
    titleFormat.setFontSize(36);
    titleFormat.setFontColor(Qt::white);
    titleFormat.setPatternBackgroundColor(couleurCellule);
    xlsx.write(1, 1, "TABLE DES FORMATEURS", titleFormat);

    // Sauter 2 lignes après le titre
    xlsx.write(6, 1, ""); // Écrire une cellule vide à la ligne 6

    // Ajouter les noms de colonnes
    QXlsx::Format nomDeColonneFormat; // Déclaration de la variable titleFormat
    nomDeColonneFormat.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    nomDeColonneFormat.setVerticalAlignment(QXlsx::Format::AlignVCenter);
    nomDeColonneFormat.setFontBold(true);
    nomDeColonneFormat.setFontSize(24);
    nomDeColonneFormat.setFontColor(Qt::white);
    QColor couleurCelluleNomColonne(221, 171, 213);
    nomDeColonneFormat.setPatternBackgroundColor(couleurCelluleNomColonne);

    for (int column = 0; column < columnCount; ++column) {
        QTableWidgetItem *headerItem = ui->table_de_formations->horizontalHeaderItem(column);
        if (headerItem) {
            xlsx.write(8, column * 4 + 1, headerItem->text(),nomDeColonneFormat);
            xlsx.mergeCells(QXlsx::CellRange(8, column * 4 + 1, 11, column * 4 + 4)); // Étaler sur 4 colonnes et 4 lignes

            // Appliquer le format pour les noms de colonnes
            QXlsx::Format columnNameFormat;
            columnNameFormat.setFontBold(true);
            columnNameFormat.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
            columnNameFormat.setVerticalAlignment(QXlsx::Format::AlignVCenter);
            columnNameFormat.setFontSize(24);
            xlsx.cellAt(8, column * 4 + 1)->format().setFont(columnNameFormat.font());
            xlsx.cellAt(8, column * 4 + 1)->format().setHorizontalAlignment(columnNameFormat.horizontalAlignment());
            xlsx.cellAt(8, column * 4 + 1)->format().setVerticalAlignment(columnNameFormat.verticalAlignment());
            xlsx.cellAt(8, column * 4 + 1)->format().setFontSize(columnNameFormat.fontSize());
        }
    }

    // Parcourir le QTableWidget pour copier les données dans le document Excel
    QXlsx::Format formatCelluleNormale; // Déclaration de la variable titleFormat
    formatCelluleNormale.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    formatCelluleNormale.setVerticalAlignment(QXlsx::Format::AlignVCenter);
    formatCelluleNormale.setFontSize(16);
    formatCelluleNormale.setFontColor(Qt::white);
    formatCelluleNormale.setPatternBackgroundColor(couleurCellule);
    for (int row = 0; row < rowCount; ++row) {
        for (int column = 0; column < columnCount; ++column) {
            // Obtenir le texte de la cellule dans le QTableWidget
            QTableWidgetItem *item = ui->table_de_formateurs->item(row, column);
            if (item) {
                // Insérer le texte de la cellule dans le document Excel
                xlsx.write(row + 12, column * 4 + 1, item->text(),formatCelluleNormale);
                xlsx.mergeCells(QXlsx::CellRange(row + 12, column * 4 + 1, row + 13, column * 4 + 4)); // Étaler sur 4 colonnes et 2 lignes
            }
        }
    }
    // Chemin vers votre image
    QString imagePath = "/tsawer/logo pour excel.png";

    // Charger l'image à partir du chemin
    QImage image(imagePath);

    // Insérer l'image dans le fichier Excel
    xlsx.insertImage(0, 0, image);
    // Sauvegarder le document Excel
    QString filePath = QFileDialog::getSaveFileName(this, tr("Exporter en Excel"), "", tr("Fichiers Excel (*.xlsx)"));
    if (!filePath.isEmpty()) {
        xlsx.saveAs(filePath);
    }
}

void MainWindow::AfficherEtmettreAJourPieChartDuree()
{
    // Création de la connexion à la base de données
    Connection c;
    if (!c.createconnect()) {
        qDebug() << "Erreur lors de la connexion à la base de données.";
        return;
    }

    // Variables pour stocker les pourcentages
    float percentTranche1_5 = 0.0;
    float percentTranche6_20 = 0.0;
    float percentPlus20 = 0.0;

    // Variable pour stocker le total des formations
    int totalFormations = 0;

    // Obtenir le total des formations
    QSqlQuery query;
    if (!query.exec("SELECT COUNT(*) FROM FORMATION")) {
        qDebug() << "Erreur lors de l'exécution de la requête pour le total des formations.";
        return;
    }

    if (query.next()) {
        totalFormations = query.value(0).toInt();
    }

    // Si aucune formation, afficher un graphique vide
    if (totalFormations == 0) {
        QPieSeries *emptySeries = new QPieSeries();
        emptySeries->append("Aucune formation", 1);
        QChart *chart = new QChart();
        chart->addSeries(emptySeries);
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->setTitle("Statistiques des durées des formations");
        chart->setTheme(QChart::ChartThemeBlueCerulean);

        // Nettoyer les anciens graphiques
        QList<QChartView *> chartViews = ui->statsDuree->findChildren<QChartView *>();
        for (auto view : chartViews) {
            view->deleteLater();
        }

        // Créer un nouveau QChartView et l'ajouter au widget
        QChartView *chartview = new QChartView(chart);
        chartview->setRenderHint(QPainter::Antialiasing);
        chartview->setParent(ui->statsDuree);
        chartview->setGeometry(ui->statsDuree->rect()); // Ajuste la taille au widget parent
        chartview->show();
        return;
    }

    // Calculer le pourcentage pour chaque tranche de durée
    auto calculatePercentage = [&](const QString &condition) -> float {
        if (query.exec(QString("SELECT COUNT(*) FROM FORMATION WHERE %1").arg(condition))) {
            query.next();
            int count = query.value(0).toInt();
            return (static_cast<float>(count) / totalFormations) * 100.0;
        } else {
            qDebug() << "Erreur lors de l'exécution de la requête pour" << condition;
            return 0.0;
        }
    };

    percentTranche1_5 = calculatePercentage("Duree BETWEEN 1 AND 5");
    percentTranche6_20 = calculatePercentage("Duree BETWEEN 6 AND 20");
    percentPlus20 = calculatePercentage("Duree > 20");

    // Créer les labels avec les pourcentages
    QString labelTranche1_5 = QString("1-5 jours %1%").arg(QString::number(percentTranche1_5, 'f', 2));
    QString labelTranche6_20 = QString("6-20 jours %1%").arg(QString::number(percentTranche6_20, 'f', 2));
    QString labelPlus20 = QString("> 20 jours %1%").arg(QString::number(percentPlus20, 'f', 2));

    // Créer le QPieSeries et ajouter les données
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.3);
    series->append(labelTranche1_5, percentTranche1_5);
    series->append(labelTranche6_20, percentTranche6_20);
    series->append(labelPlus20, percentPlus20);

    // Rendre les étiquettes visibles si le pourcentage est supérieur à zéro
    for (int i = 0; i < series->slices().count(); ++i) {
        QPieSlice *slice = series->slices().at(i);
        if (slice->value() > 0) {
            slice->setLabelVisible();
        }
    }

    // Créer le graphique et le QChartView
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle("Statistiques des durées des formations");
    chart->setTheme(QChart::ChartThemeBlueCerulean);

    // Nettoyer les anciens graphiques
    QList<QChartView *> chartViews = ui->statsDuree->findChildren<QChartView *>();
    for (auto view : chartViews) {
        view->deleteLater();
    }

    // Créer un nouveau QChartView et l'ajouter au widget
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setParent(ui->statsDuree);
    chartview->setGeometry(ui->statsDuree->rect()); // Ajuste la taille au widget parent
    chartview->show();
}

