#include "historique.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QSqlQueryModel>
#include <QString>
#include <QObject>
#include<QDate>
Historique::Historique()
{

}
Historique::Historique(QString operation, int id, QString nom){
    this->operation=operation;
    this->id=id;
    this->nom=nom;
}

void Historique::Ajouter()
{
    QSqlQuery query;
    query.prepare("insert into HISTORIQUE_Clients values (HISTORIQUE_CLIENTS_SEQ.nextval,   sysdate, :operation, :id, :nom);");
    query.bindValue(":operation",operation);
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.exec();
}
QSqlQueryModel * Historique::Afficher()
{
  QSqlQueryModel * model= new QSqlQueryModel();
       model->setQuery("select DATE_HIS, TYPE_OPERATION, id_client, nom_client FROM HISTORIQUE_Clients;");
       model->setHeaderData(0, Qt::Horizontal,QObject:: tr("Date"));
       model->setHeaderData(1, Qt::Horizontal,QObject:: tr("Type d'opération"));
       model->setHeaderData(2, Qt::Horizontal,QObject:: tr("Numéro Client"));
       model->setHeaderData(3, Qt::Horizontal,QObject:: tr("Nom Client"));
 return model;
}
