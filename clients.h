#ifndef CLIENTS_H
#define CLIENTS_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
class Clients
{
public:
    Clients();
    Clients (QString, QString, QString, QString ,QString, int, int, int);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * trier(QString, QString);
    QSqlQueryModel * recherche(QString);
    QSqlQueryModel * rechercheID(QString);
private:
    QString nom, prenom, email, sexe, type;
    int cin, age, id;
};

#endif // CLIENTS_H
