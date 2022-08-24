#include "login.h"

login::login()
{

}
login::login(QString username, QString password,QString email, QString role)
{
    this->username= username;
    this->password=password;
    this->email=email;
    this->role=role;

}
QSqlQueryModel * login::Afficher()
{
  QSqlQueryModel * model= new QSqlQueryModel();
       model->setQuery("select * from users;");
 return model;
}

QSqlQuery login::seConnecter(){
    QSqlQuery query;
    query.prepare("SELECT TYPE_USER, USERNAME FROM USERS WHERE USERNAME = :username AND PASSWORD_USER = :password");
     query.bindValue(":username", username);
     query.bindValue(":password", password);
    return query;
}
QSqlQuery login::enregisterC(){
    QSqlQuery query;
    query.prepare("insert into USERS values (USERS_SEQ.nextval , :username, :mdp, :email,:role)");
     query.bindValue(":username", username);
     query.bindValue(":mdp", password);
     query.bindValue(":email", email);
     query.bindValue(":role", role);
    return query;
}
bool login::supprimer(int num){
    QSqlQuery query;
    QString res = QString::number(num);
    query.prepare("delete from users where id_user = :num");
    query.bindValue(":num", res);
    return query.exec();
}
