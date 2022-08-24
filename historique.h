#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Historique
{
public:
    Historique();
    Historique(QString, int id, QString nom);
    void Ajouter();
    QSqlQueryModel * Afficher();
private:
    QString operation, nom;
    int id;
};

#endif // HISTORIQUE_H
