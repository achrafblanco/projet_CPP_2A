#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include "connection.h"
#include "QSqlQuery"
#include <QSqlError>
#include "login.h"
#include "clients.h"
#include<QDebug>
#include "historique.h"
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonSeConnecter_clicked();

    void on_pushButton_ENR_clicked();

    void on_pushButton_supp_up_clicked();

    void on_pushButtonRetour_clicked();

    void on_pushButtonRetourMPrincipale_clicked();


    void on_pushButton_Retourrrr_clicked();

    void on_pushButton_actualiser_chat_clicked();

    void on_pushButton_envoyer_clicked();

    void on_pushButtonChatboxAccess_clicked();

    void on_pushButton_gestionclients_clicked();

    void on_pushButton_cht_Clients_clicked();

    void on_pushButton_RPCC_clicked();

    void on_pushButton_RMPC_clicked();

    void on_pushButton_Ajouter_Clients_clicked();

    void on_pushButton_Actualiser_clients_clicked();

    void on_tableViewClients_activated(const QModelIndex &index);

    void on_pushButton_Modifier_Clients_clicked();

    void on_pushButton_Supprimer_Cleints_clicked();

    void on_pushButton_Trier_Clients_clicked();

    void on_pushButton_Chercher_Clients_clicked();

    void on_pushButton_Chercher_Clients_2_clicked();

    void on_pushButtonActualiserHistorique_clicked();

    void on_pushButtonHistorique_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_gestionParking_clicked();

private:
    Ui::MainWindow *ui;
    login L;
    QString role;
    void getChat();
    Clients CL;
    int clientId;
    Historique H;
};
#endif // MAINWINDOW_H
