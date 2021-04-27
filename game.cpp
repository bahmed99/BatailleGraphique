#include "game.h"
#include "ui_game.h"
#include<package.h>
#include<QTimer>
#include<QDateTime>



Game::Game(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);

        ui->pushButton_2->setDisabled(true);
       ui->jr1->setPlaceholderText("Taper nom joueur 1");
       ui->jr2->setPlaceholderText("Taper nom joueur 2");

        son=new QSound(":/sound/b.wav");
        son1=new QSound(":/sound/a.wav");


}

Game::~Game()
{
    delete ui;
}





int Game::index = 1;
void Game::on_pushButton_2_clicked()
{



       ui->resultatB->setText("") ;
       Hand h1=p1.getHand();
       Hand h2=p2.getHand();
       Card ct1,ct2;
       stack<Card> aux;
       bool testBataille = false;



QString formatT=tr("<font color='%1'>%2<\font><br>");
QString formatT1=tr("<font color='%1'>%2<\font>");

       ui->Round->setText(QString::number(index));
       ct1 = h1.getHandPlayer().top();
       h1.tirerCard();
       ct2 = h2.getHandPlayer().top();
       h2.tirerCard();
       aux.push(ct1);
       aux.push(ct2);

       if(ct1.getSymbole()=="♥" || ct1.getSymbole()=="♦")
       {
           ui->cartejoueur1->setText(formatT1.arg("red",QString::number(ct1.getValeur()))+formatT.arg("red",ct1.getSymbole()));
       }
       else {
           ui->cartejoueur1->setText(QString::number(ct1.getValeur())+ct1.getSymbole()+"<br>");
       }

        if(ct2.getSymbole()=="♥" || ct2.getSymbole()=="♦"){
       ui->cartejoueur2->setText(formatT1.arg("red",QString::number(ct2.getValeur()))+formatT.arg("red",ct2.getSymbole()));
   }
       else
   {
       ui->cartejoueur2->setText(QString::number(ct2.getValeur())+ct2.getSymbole()+"<br>");
   }





       if (ct1.comparer(ct2) == 1) // premier joueur remporte la manche
                   {
                       h1.setHandPlayer(aux);
                       ui->Resultat->setText(p1.getPrenom()+" a emporté cette manche");
                       index++;
                   }

      else if (ct1.comparer(ct2) ==2) // 2Ã©me joueur remporte la manche
                   {
                       h2.setHandPlayer(aux);
                       ui->Resultat->setText(p2.getPrenom()+" a emporté cette manche");
                       index++;
                   }
       else
       {
           ui->resultatB->setText("BATAILLE") ;
           // Si un de joueurs ne possede plus de carte
           if (h1.getHandPlayer().size() == 0 || h2.getHandPlayer().size() == 0) {

                     if (h1.getHandPlayer().size() == 0) {
                               h2.setHandPlayer(aux);

                           }
                     else {
                               h1.setHandPlayer(aux);

                           }
                       }

           // Si un de joueurs possede une seule carte qui ne le permete pas de continuer la bataille
            else if (h1.getHandPlayer().size() == 1 || h2.getHandPlayer().size() == 1) {

                           if (h1.getHandPlayer().size() == 1) {
                                   aux.push(h1.getHandPlayer().top());
                                   h1.tirerCard();
                                   h2.setHandPlayer(aux);

                               }
                            else {
                                   aux.push(h2.getHandPlayer().top());
                                   h2.tirerCard();
                                   h1.setHandPlayer(aux);

                               }
                       }

           else {
                      do {

                           Card ct3, ct4, ct5, ct6;
                           ct3 = h1.getHandPlayer().top();
                           h1.tirerCard();
                           ct4 = h2.getHandPlayer().top();
                           h2.tirerCard();
                           aux.push(ct3);
                           aux.push(ct4);

                           ui->cartejoueur1->setText(ui->cartejoueur1->text()+formatT1.arg("red","*")+formatT1.arg("black","*"));
                           ui->cartejoueur2->setText(ui->cartejoueur2->text()+formatT1.arg("black","*")+formatT1.arg("red","*"));


                           // si un de joueurs ne possede plus de carte
                           if (h1.getHandPlayer().size() == 0 || h2.getHandPlayer().size() == 0)
                           {
                               if (h1.getHandPlayer().size() == 0)
                               {
                                   h2.setHandPlayer(aux);
                                   ui->Resultat->setText(p2.getPrenom()+" a emporté cette manche");
                                   testBataille = true;
                               }
                               else
                               {
                                   h1.setHandPlayer(aux);
                                   ui->Resultat->setText(p1.getPrenom()+" a emporté cette manche");
                                   testBataille = true;
                               }
                           }


                           else
                           {
                               ct5 = h1.getHandPlayer().top();
                               h1.tirerCard();
                               ct6 = h2.getHandPlayer().top();
                               h2.tirerCard();
                               aux.push(ct5);
                               aux.push(ct6);



                               if(ct5.getSymbole()=="♥" || ct5.getSymbole()=="♦")
                               {
                                   ui->cartejoueur1->setText(ui->cartejoueur1->text()+"<br>"+formatT1.arg("red",QString::number(ct5.getValeur()))+formatT.arg("red",ct5.getSymbole()) +"<br>");
                               }
                               else {
                                   ui->cartejoueur1->setText(ui->cartejoueur1->text()+"<br>"+formatT1.arg("black",QString::number(ct5.getValeur()))+formatT1.arg("black",ct5.getSymbole())+"<br>");
                               }

                                if(ct6.getSymbole()=="♥" || ct6.getSymbole()=="♦")
                                {
                               ui->cartejoueur2->setText(ui->cartejoueur2->text()+"<br>"+formatT1.arg("red",QString::number(ct6.getValeur()))+formatT.arg("red",ct6.getSymbole())+"<br>");
                           }
                               else
                           {
                               ui->cartejoueur2->setText(ui->cartejoueur2->text()+"<br>"+formatT1.arg("black",QString::number(ct6.getValeur()))+formatT1.arg("black",ct6.getSymbole())+"<br>");
                           }



                           qDebug()<<ui->cartejoueur1->text();

                               // premier joueur remporte la manche
                               if (ct5.comparer(ct6) == 1)
                               {
                                   h1.setHandPlayer(aux);

                                   ui->Resultat->setText(p1.getPrenom()+" a emporté cette manche");
                                   index++;

                                   testBataille = true;
                               }

                               // 2éme joueur remporte la manche
                               else if (ct5.comparer(ct6) == 2) {
                                   h2.setHandPlayer(aux);
                                   ui->Resultat->setText(p2.getPrenom()+" a emporté cette manche");
                                   index++;

                                   testBataille = true;
                               }

                               //égalite
                               else
                               {
                                   ui->resultatB->setText(ui->resultatB->text()+"\n"+"BATAILLE") ;
                               }

                  }

              } while (testBataille == false);
           }
       }


       p1.setHand(h1);
       p2.setHand(h2);

       if(p1.getHand().getHandPlayer().size()==0) {
           ui->pushButton_2->setDisabled(true);
           QMessageBox::about(this,"Gagnant",p2.getPrenom()+" a gangné");
           son->play();


       }
       if(p2.getHand().getHandPlayer().size()==0) {
           ui->pushButton_2->setDisabled(true);
           QMessageBox::about(this,"Gagnant",p1.getPrenom()+" a gangné");
           son->play();
       }

qDebug()<<p1.getHand().getHandPlayer().size();
qDebug()<<p2.getHand().getHandPlayer().size();


}


void Game::on_pushButton_clicked()
{

    son1->play();
   QString fontTemplate = tr("<font color='%1'>%2</font>");
   ui->j1->setText(fontTemplate.arg("white",ui->jr1->toPlainText()));
   ui->j2->setText(fontTemplate.arg("white",ui->jr2->toPlainText()));
   p1.setPrenom(ui->jr1->toPlainText());
   p2.setPrenom(ui->jr2->toPlainText());

   ui->jr1->deleteLater();
   ui->jr2->deleteLater();

    Package pq;
    Hand h1,h2;
    pq.distribuer(h1,h2);
    p1.setHand(h1);
    p2.setHand(h2);
    ui->pushButton_2->setDisabled(false);
    ui->pushButton->setDisabled(true);


}

void Game::on_pushButton_3_clicked()
{
   qApp->quit();
   QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

