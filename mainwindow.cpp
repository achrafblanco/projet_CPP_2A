#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_Username->setText("");
    ui->lineEdit_Password->setText("");
    ui->tableViewUP->setModel(L.Afficher());
     ui->tableViewClients->setModel(CL.afficher());
     ui->tableViewHistorique->setModel(H.Afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}
// Début login
void MainWindow::on_pushButtonSeConnecter_clicked()
{
    QString nickname;
    QString UserName = ui->lineEdit_Username->text();
    QString Password = ui->lineEdit_Password->text();
    login l(UserName, Password,"","");
    QSqlQuery querry = l.seConnecter();
   // querry.prepare("SELECT TYPE_USER, USERNAME FROM USERS WHERE USERNAME = '"+UserName+"' AND PASSWORD_USER = '"+Password+"'");
    if (querry.exec()){
            int counter = 0;
            while (querry.next()){ // lignes
                counter++;
                role = querry.value(0).toString(); // column
                nickname = querry.value(1).toString();
            }
            ui->lineEditidNickname->setText(nickname);
            getChat();
            if (counter<1)
                QMessageBox::critical(this, tr("Error::"), "Compte n'existe pas");


            if (counter==1){
                QMessageBox::information(nullptr, QObject::tr("Database Open"),
                                          QObject::tr("Connecté"),
                                          QMessageBox::Ok
                                          );
            if (role=="admin"){
                ui->stackedWidget->setCurrentIndex(1);
            }else if (role=="clients"){
                ui->stackedWidget->setCurrentIndex(4);
            }else if (role=="parking"){
                 ui->stackedWidget->setCurrentIndex(5);
            }

            }
            if (counter >1)
                QMessageBox::critical(this, tr("Error::"), "Duplicate");

        }else{
            QMessageBox::critical(this, tr("Error::"), querry.lastError().text());
        }
}

void MainWindow::on_pushButton_ENR_clicked()
{

    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_supp_up_clicked()
{
    int ID = ui->lineEdit_Username_UP_sup->text().toInt();
    /*QSqlQuery querry;
    querry.prepare("delete from users where id_user = "+ID+"");*/
    bool test = L.supprimer(ID);
    if (test){
        ui->tableViewUP->setModel(L.Afficher());
        QMessageBox::information(nullptr, QObject::tr("Database Open"),
                                  QObject::tr("Compte supprimé"),
                                  QMessageBox::Ok
                                  );
        ui->tableViewUP->setModel(L.Afficher());
    }else{
        QMessageBox::critical(this, tr("Error::"), "");
    }
}

void MainWindow::on_pushButtonRetour_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButtonRetourMPrincipale_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_Username->setText("");
    ui->lineEdit_Password->setText("");
}

void MainWindow::on_pushButton_Retourrrr_clicked()
{
    if (role=="admin"){
        ui->stackedWidget->setCurrentIndex(1);
    }else if (role=="clients"){
        ui->stackedWidget->setCurrentIndex(4);
    }else if (role=="parking"){
        ui->stackedWidget->setCurrentIndex(5);
    }
}
//fin login
// Début chatbox
void MainWindow::getChat(){
    QString date;
    QString Conversation = ui->lineEdit_Conversation->text();
    QString nickname, msgForTextEdit, text;
    QSqlQuery querySelect;
    querySelect.prepare("select  nickname, msg, TO_CHAR(date_sent, 'dy HH24:MI') from CHATBOX where conversation like "+Conversation+" order by date_sent;");
    if (querySelect.exec()){
        ui->textEdit->clear();
        while (querySelect.next()){
            nickname = querySelect.value(0).toString();
            msgForTextEdit = querySelect.value(1).toString();
            date = querySelect.value(2).toString();
            text = date + "    " +  nickname + ": " + msgForTextEdit;
            ui->textEdit->append(text);
        }
    }else{
        QMessageBox::critical(this, tr("Error::"), querySelect.lastError().text());
    }
    // end affichage chat
}
void MainWindow::on_pushButton_actualiser_chat_clicked()
{
    getChat();
}

void MainWindow::on_pushButton_envoyer_clicked()
{
    QString nickname = ui->lineEditidNickname->text();
    QString Conversation = ui->lineEdit_Conversation->text();
    QString message_sent = ui->lineEdit_massage->text();
    QSqlQuery query;
    query.prepare("insert into CHATBOX values ('"+nickname+"', "+Conversation+", CHATBOX_SEQ.nextval, '"+message_sent+"', sysdate); ");
    if (query.exec()){
            getChat();
        }else{
        QMessageBox::critical(this, tr("Error::"), query.lastError().text());
    }
}

void MainWindow::on_pushButtonChatboxAccess_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
// fin chatbox

//Début Clients
void MainWindow::on_pushButton_gestionclients_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_cht_Clients_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_RPCC_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_RMPC_clicked()
{
    if (role == "admin"){
        ui->stackedWidget->setCurrentIndex(1);
    }else{
        QMessageBox::critical(this, tr("Error::"), "Vous n'etes pas un admin pour visionner cette page");
    }
}

void MainWindow::on_pushButton_Ajouter_Clients_clicked()
{
    QString nom, prenom, email, sexe, type;
    int cin, age;
    nom = ui->lineEdit_Clients_Nom->text();
    prenom = ui->lineEdit_Clients_Prenom->text();
    email = ui->lineEdit_Clients_Email->text();
    cin = ui->lineEdit_Clients_CIN->text().toInt();
    age = ui->lineEdit_Clients_Age->text().toInt();
    if (ui->radioButton_Homme->isChecked()){
        sexe = "Homme";
    }
    if (ui->radioButton_Femme->isChecked()){
        sexe = "Femme";
    }
    if (ui->radioButton_VIP->isChecked()){
        type = "VIP";

    }
    if (ui->radioButton_Fidel->isChecked()){
        type = "Fidele";
    }
    if (ui->radioButton_Passage->isChecked()){
        type = "Passage";
    }
    Clients C(nom, prenom, email, sexe, type, cin, age, 0);
    bool test = C.ajouter();
    if (test){
        //Historique
        int last_inserted_id = 0;
        QSqlQuery querry;
        querry.prepare("SELECT * FROM (SELECT id FROM g_clients ORDER BY id DESC) WHERE ROWNUM = 1;");
        if (querry.exec()){
                while (querry.next()){
                    last_inserted_id = querry.value(0).toInt();
                }
        }
        QString operation = "Ajout";
        Historique h(operation, last_inserted_id, nom);
        h.Ajouter();
        ui->tableViewClients->setModel(CL.afficher());
        ui->tableViewHistorique->setModel(H.Afficher());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Ajout effectué"),
                              QMessageBox::Ok
                              );
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Ajouter non effectué"),
                              QMessageBox::Cancel
                              );
    }
}

void MainWindow::on_pushButton_Actualiser_clients_clicked()
{
    ui->tableViewClients->setModel(CL.afficher());
}

void MainWindow::on_tableViewClients_activated(const QModelIndex &index)
{
    QString val = ui->tableViewClients->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select * from G_CLIENTS where (ID) LIKE "+val+" ");
    if (query.exec()){
        while (query.next()){
            clientId = query.value(0).toInt();
            ui->lineEdit_Suppression_ID_Clients->setText(query.value(0).toString());
            ui->lineEdit_Clients_Nom->setText(query.value(1).toString());
            ui->lineEdit_Clients_Prenom->setText(query.value(2).toString());
            ui->lineEdit_Clients_CIN->setText(query.value(3).toString());
            ui->lineEdit_Clients_Email->setText(query.value(4).toString());
            ui->lineEdit_Clients_Age->setText(query.value(7).toString());
            if ((query.value(5).toString()) == "Homme"){
                ui->radioButton_Homme->setChecked(1);
            }
            if ((query.value(5).toString()) == "Femme"){
                ui->radioButton_Femme->setChecked(1);
            }
            if ((query.value(6).toString()) == "VIP"){
                ui->radioButton_VIP->setChecked(1);
            }
            if ((query.value(6).toString()) == "Fidele"){
                ui->radioButton_Fidel->setChecked(1);
            }
            if ((query.value(6).toString()) == "Passage"){
                ui->radioButton_Passage->setChecked(1);
            }
        }
    }else{
        QMessageBox::critical(this, tr("Error::"), query.lastError().text());
    }
}

void MainWindow::on_pushButton_Modifier_Clients_clicked()
{
    QString nom, prenom, email, sexe, type;
    int cin, age;
   // id = ui->line
    nom = ui->lineEdit_Clients_Nom->text();
    prenom = ui->lineEdit_Clients_Prenom->text();
    email = ui->lineEdit_Clients_Email->text();
    cin = ui->lineEdit_Clients_CIN->text().toInt();
    age = ui->lineEdit_Clients_Age->text().toInt();
    if (ui->radioButton_Homme->isChecked()){
        sexe = "Homme";
    }
    if (ui->radioButton_Femme->isChecked()){
        sexe = "Femme";
    }
    if (ui->radioButton_VIP->isChecked()){
        type = "VIP";

    }
    if (ui->radioButton_Fidel->isChecked()){
        type = "Fidele";
    }
    if (ui->radioButton_Passage->isChecked()){
        type = "Passage";
    }
    Clients C(nom, prenom, email, sexe, type, cin, age, clientId);
    bool test = C.modifier();

    if (test){
        //Historique
        QString operation = "Modification";
        Historique h(operation, clientId, nom);
        h.Ajouter();
        ui->tableViewHistorique->setModel(H.Afficher());
        ui->tableViewClients->setModel(CL.afficher());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Modification effectué"),
                              QMessageBox::Ok
                              );
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Modification non effectué"),
                              QMessageBox::Cancel
                              );
    }
}

void MainWindow::on_pushButton_Supprimer_Cleints_clicked()
{
    QString nom = ui->lineEdit_Clients_Nom->text();
    int id = ui->lineEdit_Suppression_ID_Clients->text().toInt();
    bool test = CL.supprimer(id);
    if (test){
     ui->tableViewClients->setModel(CL.afficher());
     //Historique
     QString operation = "Suppression";
     Historique h(operation, clientId, nom);
     h.Ajouter();
     ui->tableViewHistorique->setModel(H.Afficher());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Suppression effectué"),
                              QMessageBox::Ok
                              );
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Suppression non effectué"),
                              QMessageBox::Cancel
                              );
    }
}

void MainWindow::on_pushButton_Trier_Clients_clicked()
{
    QString type_of_tri;
    QString tri_par;
    if (ui->radioButton_Tri_Asc_Clients->isChecked()){
        type_of_tri = "asc";
    }
    if (ui->radioButton_Tri_Desc_Clients->isChecked()){
        type_of_tri = "desc";
    }
    tri_par = ui->comboBox_Tri_Clients->currentText();
    ui->tableViewClients->setModel(CL.trier(type_of_tri, tri_par));
}

void MainWindow::on_pushButton_Chercher_Clients_clicked()
{
    QString rech_field = ui->lineEdit_Recherche_Clients->text();
    ui->tableViewClients->setModel(CL.recherche(rech_field));
}

void MainWindow::on_pushButton_Chercher_Clients_2_clicked()
{
    QString rech_field = ui->lineEdit_ID_RECH_ID_Cleints->text();
    ui->tableViewClients->setModel(CL.rechercheID(rech_field));
}

void MainWindow::on_pushButtonActualiserHistorique_clicked()
{
    ui->tableViewHistorique->setModel(H.Afficher());
}

void MainWindow::on_pushButtonHistorique_clicked()
{
            QSqlQueryModel * model= new QSqlQueryModel();
            model->setQuery("select * from g_clients where type like ('Fidele')");
            float taille=model->rowCount();
            model->setQuery("select * from g_clients where type like ('VIP')");
            float taillee=model->rowCount();
            model->setQuery("select * from g_clients where type like ('Passage')");
            float tailleee=model->rowCount();
            float total=taille+taillee+tailleee;
            QString a=QString("Clients fidéle: "+QString::number((taille*100)/total,'f',2)+"%" );
            QString b=QString("Clients VIP: "+QString::number((taillee*100)/total,'f',2)+"%" );
            QString c=QString("Clients passagé: "+QString::number((tailleee*100)/total,'f',2)+"%" );
            QPieSeries *series = new QPieSeries();
            series->append(a,taille);
            series->append(b,taillee);
            series->append(c,tailleee);
            if (taille!=0)
            {QPieSlice *slice = series->slices().at(0);
                slice->setLabelVisible();
                slice->setPen(QPen());}
            if ( taillee!=0)
            {
                // Add label, explode and define brush for 2nd slice
                QPieSlice *slice1 = series->slices().at(1);
                //slice1->setExploded();
                slice1->setLabelVisible();
            }
            if(tailleee!=0)
            {
                // Add labels to rest of slices
                QPieSlice *slice2 = series->slices().at(2);
                //slice1->setExploded();
                slice2->setLabelVisible();
            }
            // Create the chart widget
            QChart *chart = new QChart();
            // Add data to chart with title and hide legend
            chart->addSeries(series);
            chart->setTitle("Distribution des clients avec le nombre total des clients: "+ QString::number(total));
            chart->legend()->hide();
            // Used to display the chart
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->resize(1000,500);
            chartView->show();
}

void MainWindow::on_pushButton_14_clicked()
{

     QString username = ui->lineEdit_Username_UP->text();
        QString mdp = ui->lineEdit_MDP_UP->text();
        QString email = ui->lineEdit_email_UP->text();
        QString role = ui->lineEdit_role_up->text();
        login l (username, mdp,email,role);
         QSqlQuery querry = l.enregisterC() ;
        //querry.prepare("insert into USERS values (USERS_SEQ.nextval, '"+role+"', '"+username+"', '"+mdp+"', '"+email+"')");
        if (querry.exec()){
            ui->tableViewUP->setModel(L.Afficher());
            QMessageBox::information(nullptr, QObject::tr("Database Open"),
                                      QObject::tr("Compte enregistré"),
                                      QMessageBox::Ok
                                      );
        }else{
            QMessageBox::critical(this, tr("Error::"), querry.lastError().text());
        }



}

void MainWindow::on_pushButton_gestionParking_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

}
