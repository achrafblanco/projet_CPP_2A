#ifndef LOGIN_H
#define LOGIN_H
#include <QSqlQueryModel>
#include <QSqlQuery>
class login
{
public:
    login();
    login(QString, QString, QString, QString);
        QSqlQuery seConnecter();
         QSqlQuery enregisterC();
         bool supprimer(int);

    QSqlQueryModel * Afficher();
private:
    QString username, password,email,role;
};

#endif // LOGIN_H
