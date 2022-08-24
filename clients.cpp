#include "clients.h"

Clients::Clients()
{

}

Clients::Clients(QString nom, QString prenom, QString email, QString sexe , QString type,  int cin, int age, int id)
{
    this->nom = nom;
    this->prenom = prenom;
    this->email = email;
    this->sexe = sexe;
    this->type = type;
    this->cin = cin;
    this->age = age;
    this->id=id;
}
bool Clients::ajouter(){
    QSqlQuery query;
    query.prepare("insert into G_Clients values (G_CLIENTS_SEQ.nextval, :nom, :prenom , :cin, :email, :sexe, :type, :age)");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":sexe", sexe);
    query.bindValue(":type", type);
    query.bindValue(":cin", cin);
    query.bindValue(":age", age);
    return query.exec();
}

QSqlQueryModel * Clients::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select id, nom, prenom, age, cin, email, sexe, type from G_CLIENTS ");
   /*model->setHeaderData(0,Qt::Horizontal, QObject::tr("Numéro"));*/
    return model;
}
bool Clients::modifier(){
    QSqlQuery query;
    query.prepare("update G_CLIENTS SET nom = :nom, prenom = :prenom, email = :email, sexe = :sexe, type = :type, cin = :cin, age = :age where id like (:id)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":sexe", sexe);
    query.bindValue(":type", type);
    query.bindValue(":cin", cin);
    query.bindValue(":age", age);
    return query.exec();
}
bool Clients::supprimer(int num){
    QSqlQuery query;
    QString res = QString::number(num);
    query.prepare("delete from g_clients where id = :num;");
    query.bindValue(":num", res);
    return query.exec();
}
QSqlQueryModel * Clients::trier(QString type_tri, QString tri_par){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from g_clients order by "+tri_par+" "+type_tri+" ");
    return model;
}
QSqlQueryModel * Clients::recherche(QString rech){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from g_clients where  (id) LIKE '%"+rech+"%' OR (nom) LIKE '%"+rech+"%' OR (prenom) LIKE '%"+rech+"%' OR (cin) LIKE '%"+rech+"%' OR (email) LIKE '%"+rech+"%' OR (sexe) LIKE '%"+rech+"%' OR (type) LIKE '%"+rech+"%' OR (age) LIKE '%"+rech+"%'");
    return model;
}
QSqlQueryModel * Clients::rechercheID(QString rech){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from g_clients where (id) LIKE ("+rech+") ");
    return model;
}
