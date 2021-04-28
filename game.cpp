#include "game.h"
#include "ui_game.h"
#include<package.h>
#include<QTimer>
#include<QDateTime>
#include<QPainter>


Game::Game(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Game)
{

        setFixedSize(836,662);
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
       int i=0;



        QString formatT=tr("<font color='%1'>%2<\font><br>");
        QString formatT1=tr("<font color='%1'>%2<\font>");

       ui->Round->setText(QString::number(index));
       ct1 = h1.getHandPlayer().top();
       h1.tirerCard();
       ct2 = h2.getHandPlayer().top();
       h2.tirerCard();
       aux.push(ct1);
       aux.push(ct2);


       affichage(ct1,ct2,i);
       i++;



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

                           i++;
                           const QPixmap* pixmap1 = ui->cartejoueur1->pixmap();
                           const QPixmap* pixmap2 = ui->cartejoueur2->pixmap();

                           QPixmap *pixmap=new QPixmap(71, 96*(i));
                           pixmap->fill(Qt::transparent);
                           QPainter *painter=new QPainter(pixmap);
                           painter->drawPixmap(0, 0, 71, 96*(i-1), *pixmap1);
                           painter->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/e.gif"));
                           painter->end();
                           ui->cartejoueur1->setPixmap(*pixmap);


                           QPixmap *pixmap3=new QPixmap(71, 96*(i));
                           pixmap3->fill(Qt::transparent);
                           QPainter *painter1 = new QPainter(pixmap3);
                           painter1->drawPixmap(0, 0, 71, 96*(i-1), *pixmap2);
                           painter1->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/e.gif"));
                           painter1->end();
                           ui->cartejoueur2->setPixmap(*pixmap3);


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

                                i++;
                            affichage(ct5,ct6,i);



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


   QString fontTemplate = tr("<font color='%1'>%2</font>");


   if(ui->jr1->toPlainText() =="" || ui->jr2->toPlainText()=="")
   {
       QMessageBox::about(this,"ERREUR","Veuillez entrer vos noms");

   }
else
   {


       ui->j1->setText(fontTemplate.arg("white",ui->jr1->toPlainText()));
       ui->j2->setText(fontTemplate.arg("white",ui->jr2->toPlainText()));
       son1->play();
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

}

void Game::on_pushButton_3_clicked()
{
   qApp->quit();
   QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}


void Game::on_mute_clicked()
{
    son1->stop();
}


void Game::on_pushButton_4_clicked()
{
    son1->play();
}

void Game::affichage(Card c1,Card c2,int i)
{
    const QPixmap* pixmap1 = ui->cartejoueur1->pixmap();
    const QPixmap* pixmap2 = ui->cartejoueur2->pixmap();



    if(c1.getSymbole()=="♥")
    {


            if(c1.getValeur()==11){
                if(i==0){
                ui->cartejoueur1->setPixmap(QPixmap(":/images/Jh"));}
                else {
                    QPixmap *pixmap=new QPixmap(71, 96*(i));
                    pixmap->fill(Qt::transparent);
                    QPainter *painter=new QPainter(pixmap);
                    painter->drawPixmap(0, 0, 71, 96*(i-1), *pixmap1);
                    painter->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Jh"));
                    painter->end();
                    ui->cartejoueur1->setPixmap(*pixmap);

                }
            }
            else if(c1.getValeur()==12){
                if(i==0){
                 ui->cartejoueur1->setPixmap(QPixmap(":/images/Qh"));}
                else{ QPixmap *pixmap=new QPixmap(71, 96*(i));
                    pixmap->fill(Qt::transparent);
                    QPainter *painter=new QPainter(pixmap);
                    painter->drawPixmap(0, 0, 71, 96*(i-1), *pixmap1);
                    painter->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Qh"));
                    painter->end();
                    ui->cartejoueur1->setPixmap(*pixmap);}

            }
            else if(c1.getValeur()==13){
                if(i==0)
                {ui->cartejoueur1->setPixmap(QPixmap(":/images/Kh"));}
                else { QPixmap *pixmap=new QPixmap(71, 96*(i));
                    pixmap->fill(Qt::transparent);
                    QPainter *painter=new QPainter(pixmap);
                    painter->drawPixmap(0, 0, 71, 96*(i-1), *pixmap1);
                    painter->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Kh"));
                    painter->end();
                    ui->cartejoueur1->setPixmap(*pixmap);}
            }
           else
            {
                if(i==0)
                {ui->cartejoueur1->setPixmap(QPixmap(":/images/"+QString::number(c1.getValeur())+"h"));}
                else { QPixmap *pixmap=new QPixmap(71, 96*(i));
                    pixmap->fill(Qt::transparent);
                    QPainter *painter=new QPainter(pixmap);
                    painter->drawPixmap(0, 0, 71, 96*(i-1), *pixmap1);
                    painter->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/"+QString::number(c1.getValeur())+"h"));
                    painter->end();
                    ui->cartejoueur1->setPixmap(*pixmap);}            }


    }
    if(c1.getSymbole()=="♦")
    {


            if(c1.getValeur()==11){
                if(i==0)
                {
                    ui->cartejoueur1->setPixmap(QPixmap(":/images/Jd.gif"));
                }
                else {
                    QPixmap *pixmap=new QPixmap(71, 96*(i));
                                        pixmap->fill(Qt::transparent);
                                        QPainter *painter=new QPainter(pixmap);
                                        painter->drawPixmap(0, 0, 71, 96*(i-1), *pixmap1);
                                        painter->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/"+QString::number(c1.getValeur())+"h"));
                                        painter->end();
                                        ui->cartejoueur1->setPixmap(*pixmap);
                }
            }
            else if(c1.getValeur()==12){
                if(i==0)
                {
                    ui->cartejoueur1->setPixmap(QPixmap(":/images/Qd.gif"));
                }
                else {
                    QPixmap *pixmap=new QPixmap(71, 96*(i));
                                        pixmap->fill(Qt::transparent);
                                        QPainter *painter=new QPainter(pixmap);
                                        painter->drawPixmap(0, 0, 71, 96*(i-1), *pixmap1);
                                        painter->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Qd.gif"));
                                        painter->end();
                                        ui->cartejoueur1->setPixmap(*pixmap);
                }

            }
            else if(c1.getValeur()==13){
                if(i==0)
                {
                    ui->cartejoueur1->setPixmap(QPixmap(":/images/Kd.gif"));
                }
                else {
                    QPixmap *pixmap=new QPixmap(71, 96*(i));
                                        pixmap->fill(Qt::transparent);
                                        QPainter *painter=new QPainter(pixmap);
                                        painter->drawPixmap(0, 0, 71, 96*(i-1), *pixmap1);
                                        painter->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Kd.gif"));
                                        painter->end();
                                        ui->cartejoueur1->setPixmap(*pixmap);
                }
            }
           else
            {if(i==0)

                {
                    ui->cartejoueur1->setPixmap(QPixmap(":/images/"+QString::number(c1.getValeur())+"d.gif"));
                }
                else {
                    QPixmap *pixmap=new QPixmap(71, 96*(i));
                                        pixmap->fill(Qt::transparent);
                                        QPainter *painter=new QPainter(pixmap);
                                        painter->drawPixmap(0, 0, 71, 96*(i-1), *pixmap1);
                                        painter->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/"+QString::number(c1.getValeur())+"d.gif"));
                                        painter->end();
                                        ui->cartejoueur1->setPixmap(*pixmap);
                }
            }



    }
    if(c1.getSymbole()=="♣")
    {


            if(c1.getValeur()==11){
                if(i==0)
                {
                    ui->cartejoueur1->setPixmap(QPixmap(":/images/Jc.gif"));
                }
                else {
                    QPixmap *pixmap=new QPixmap(71, 96*(i));
                                        pixmap->fill(Qt::transparent);
                                        QPainter *painter=new QPainter(pixmap);
                                        painter->drawPixmap(0, 0, 71, 96*(i-1), *pixmap1);
                                        painter->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Jc.gif"));
                                        painter->end();
                                        ui->cartejoueur1->setPixmap(*pixmap);
                }
            }
            else if(c1.getValeur()==12){
                if(i==0)
                {
                    ui->cartejoueur1->setPixmap(QPixmap(":/images/Qc.gif"));
                }
                else {
                    QPixmap *pixmap=new QPixmap(71, 96*(i));
                                        pixmap->fill(Qt::transparent);
                                        QPainter *painter=new QPainter(pixmap);
                                        painter->drawPixmap(0, 0, 71, 96*(i-1), *pixmap1);
                                        painter->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Qc.gif"));
                                        painter->end();
                                        ui->cartejoueur1->setPixmap(*pixmap);
                }

            }
            else if(c1.getValeur()==13){
                if(i==0)
                {
                    ui->cartejoueur1->setPixmap(QPixmap(":/images/Kc.gif"));
                }
                else {
                    QPixmap *pixmap=new QPixmap(71, 96*(i));
                                        pixmap->fill(Qt::transparent);
                                        QPainter *painter=new QPainter(pixmap);
                                        painter->drawPixmap(0, 0, 71, 96*(i-1), *pixmap1);
                                        painter->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Kc.gif"));
                                        painter->end();
                                        ui->cartejoueur1->setPixmap(*pixmap);
                }
            }
           else
            {
                if(i==0)
                {
                    ui->cartejoueur1->setPixmap(QPixmap(":/images/"+QString::number(c1.getValeur())+"c.gif"));
                }
                else {
                    QPixmap *pixmap=new QPixmap(71, 96*(i));
                                        pixmap->fill(Qt::transparent);
                                        QPainter *painter=new QPainter(pixmap);
                                        painter->drawPixmap(0, 0, 71, 96*(i-1), *pixmap1);
                                        painter->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/"+QString::number(c1.getValeur())+"c.gif"));
                                        painter->end();
                                        ui->cartejoueur1->setPixmap(*pixmap);
                }
            }


    }
    if(c1.getSymbole()=="♠")
    {


            if(c1.getValeur()==11){
                if(i==0)
                {
                    ui->cartejoueur1->setPixmap(QPixmap(":/images/Js.gif"));
                }

                else {
                    QPixmap *pixmap=new QPixmap(71, 96*(i));
                                        pixmap->fill(Qt::transparent);
                                        QPainter *painter=new QPainter(pixmap);
                                        painter->drawPixmap(0, 0, 71, 96*(i-1), *pixmap1);
                                        painter->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Js.gif"));
                                        painter->end();
                                        ui->cartejoueur1->setPixmap(*pixmap);
                }
            }
            else if(c1.getValeur()==12){
                if(i==0)
                {
                    ui->cartejoueur1->setPixmap(QPixmap(":/images/Qs.gif"));
                }
                else {
                    QPixmap *pixmap=new QPixmap(71, 96*(i));
                                        pixmap->fill(Qt::transparent);
                                        QPainter *painter=new QPainter(pixmap);
                                        painter->drawPixmap(0, 0, 71, 96*(i-1), *pixmap1);
                                        painter->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Qs.gif"));
                                        painter->end();
                                        ui->cartejoueur1->setPixmap(*pixmap);
                }

            }
            else if(c1.getValeur()==13){
                if(i==0)
                {
                    ui->cartejoueur1->setPixmap(QPixmap(":/images/Ks.gif"));
                }
                else {
                    QPixmap *pixmap=new QPixmap(71, 96*(i));
                                        pixmap->fill(Qt::transparent);
                                        QPainter *painter=new QPainter(pixmap);
                                        painter->drawPixmap(0, 0, 71, 96*(i-1), *pixmap1);
                                        painter->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Ks.gif"));
                                        painter->end();
                                        ui->cartejoueur1->setPixmap(*pixmap);
                }
            }
           else
            {if(i==0)
                {
                    ui->cartejoueur1->setPixmap(QPixmap(":/images/"+QString::number(c1.getValeur())+"s.gif"));
                }
                else {
                    QPixmap *pixmap=new QPixmap(71, 96*(i));
                                        pixmap->fill(Qt::transparent);
                                        QPainter *painter=new QPainter(pixmap);
                                        painter->drawPixmap(0, 0, 71, 96*(i-1), *pixmap1);
                                        painter->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/"+QString::number(c1.getValeur())+"s.gif"));
                                        painter->end();
                                        ui->cartejoueur1->setPixmap(*pixmap);
                }
            }
    }

    if(c2.getSymbole()=="♥")
    {


            if(c2.getValeur()==11){
                if(i==0)
                {
                    ui->cartejoueur2->setPixmap(QPixmap(":/images/Jh"));
                }
                else {
                    QPixmap *pixmap3=new QPixmap(71, 96*(i));
                    pixmap3->fill(Qt::transparent);
                    QPainter *painter1 = new QPainter(pixmap3);
                    painter1->drawPixmap(0, 0, 71, 96*(i-1), *pixmap2);
                    painter1->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Jh"));
                    painter1->end();
                    ui->cartejoueur2->setPixmap(*pixmap3);
                }
            }
            else if(c2.getValeur()==12){
                if(i==0)
                {
                    ui->cartejoueur2->setPixmap(QPixmap(":/images/Qh"));
                }
                else {
                    QPixmap *pixmap3=new QPixmap(71, 96*(i));
                    pixmap3->fill(Qt::transparent);
                    QPainter *painter1 = new QPainter(pixmap3);
                    painter1->drawPixmap(0, 0, 71, 96*(i-1), *pixmap2);
                    painter1->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Qh"));
                    painter1->end();
                    ui->cartejoueur2->setPixmap(*pixmap3);
                }

            }
            else if(c2.getValeur()==13){
                if(i==0)
                {
                    ui->cartejoueur2->setPixmap(QPixmap(":/images/Kh"));
                }
                else {
                    QPixmap *pixmap3=new QPixmap(71, 96*(i));
                    pixmap3->fill(Qt::transparent);
                    QPainter *painter1 = new QPainter(pixmap3);
                    painter1->drawPixmap(0, 0, 71, 96*(i-1), *pixmap2);
                    painter1->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Kh"));
                    painter1->end();
                    ui->cartejoueur2->setPixmap(*pixmap3);
                }
            }
           else
            {if(i==0)

                {
                    ui->cartejoueur2->setPixmap(QPixmap(":/images/"+QString::number(c2.getValeur())+"h"));
                }
                else {
                    QPixmap *pixmap3=new QPixmap(71, 96*(i));
                    pixmap3->fill(Qt::transparent);
                    QPainter *painter1 = new QPainter(pixmap3);
                    painter1->drawPixmap(0, 0, 71, 96*(i-1), *pixmap2);
                    painter1->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/"+QString::number(c2.getValeur())+"h"));
                    painter1->end();
                    ui->cartejoueur2->setPixmap(*pixmap3);
                }
            }


    }
    if(c2.getSymbole()=="♦")
    {


            if(c2.getValeur()==11){
                if(i==0)
                {
                    ui->cartejoueur2->setPixmap(QPixmap(":/images/Jd.gif"));
                }
                else {
                    QPixmap *pixmap3=new QPixmap(71, 96*(i));
                    pixmap3->fill(Qt::transparent);
                    QPainter *painter1 = new QPainter(pixmap3);
                    painter1->drawPixmap(0, 0, 71, 96*(i-1), *pixmap2);
                    painter1->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Jd.gif"));
                    painter1->end();
                    ui->cartejoueur2->setPixmap(*pixmap3);
                }
            }
            else if(c2.getValeur()==12){
                if(i==0)
                {
                    ui->cartejoueur2->setPixmap(QPixmap(":/images/Qd.gif"));
                }
                else {
                    QPixmap *pixmap3=new QPixmap(71, 96*(i));
                    pixmap3->fill(Qt::transparent);
                    QPainter *painter1 = new QPainter(pixmap3);
                    painter1->drawPixmap(0, 0, 71, 96*(i-1), *pixmap2);
                    painter1->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Qd.gif"));
                    painter1->end();
                    ui->cartejoueur2->setPixmap(*pixmap3);
                }

            }
            else if(c2.getValeur()==13){
                if(i==0)
                {
                    ui->cartejoueur2->setPixmap(QPixmap(":/images/Kd.gif"));
                }
                else {
                    QPixmap *pixmap3=new QPixmap(71, 96*(i));
                    pixmap3->fill(Qt::transparent);
                    QPainter *painter1 = new QPainter(pixmap3);
                    painter1->drawPixmap(0, 0, 71, 96*(i-1), *pixmap2);
                    painter1->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Kd.gif"));
                    painter1->end();
                    ui->cartejoueur2->setPixmap(*pixmap3);
                }
            }
           else
            {
                if(i==0)
                {
                    ui->cartejoueur2->setPixmap(QPixmap(":/images/"+QString::number(c2.getValeur())+"d.gif"));
                }
                else {
                    QPixmap *pixmap3=new QPixmap(71, 96*(i));
                    pixmap3->fill(Qt::transparent);
                    QPainter *painter1 = new QPainter(pixmap3);
                    painter1->drawPixmap(0, 0, 71, 96*(i-1), *pixmap2);
                    painter1->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/"+QString::number(c2.getValeur())+"d.gif"));
                    painter1->end();
                    ui->cartejoueur2->setPixmap(*pixmap3);
                }
            }



    }
    if(c2.getSymbole()=="♣")
    {


            if(c2.getValeur()==11){
                if(i==0)
                {
                    ui->cartejoueur2->setPixmap(QPixmap(":/images/Jc.gif"));
                }
                else {
                    QPixmap *pixmap3=new QPixmap(71, 96*(i));
                    pixmap3->fill(Qt::transparent);
                    QPainter *painter1 = new QPainter(pixmap3);
                    painter1->drawPixmap(0, 0, 71, 96*(i-1), *pixmap2);
                    painter1->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Jc.gif"));
                    painter1->end();
                    ui->cartejoueur2->setPixmap(*pixmap3);
                }
            }
            else if(c2.getValeur()==12){
                if(i==0)
                {
                    ui->cartejoueur2->setPixmap(QPixmap(":/images/Qc.gif"));
                }
                else {
                    QPixmap *pixmap3=new QPixmap(71, 96*(i));
                    pixmap3->fill(Qt::transparent);
                    QPainter *painter1 = new QPainter(pixmap3);
                    painter1->drawPixmap(0, 0, 71, 96*(i-1), *pixmap2);
                    painter1->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Qc.gif"));
                    painter1->end();
                    ui->cartejoueur2->setPixmap(*pixmap3);
                }

            }
            else if(c2.getValeur()==13){
                if(i==0)
                {
                    ui->cartejoueur2->setPixmap(QPixmap(":/images/Kc.gif"));
                }
                else {
                    QPixmap *pixmap3=new QPixmap(71, 96*(i));
                    pixmap3->fill(Qt::transparent);
                    QPainter *painter1 = new QPainter(pixmap3);
                    painter1->drawPixmap(0, 0, 71, 96*(i-1), *pixmap2);
                    painter1->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Kc.gif"));
                    painter1->end();
                    ui->cartejoueur2->setPixmap(*pixmap3);
                }
            }
           else
            {if(i==0)

                {
                    ui->cartejoueur2->setPixmap(QPixmap(":/images/"+QString::number(c2.getValeur())+"c.gif"));
                }
                else {
                    QPixmap *pixmap3=new QPixmap(71, 96*(i));
                    pixmap3->fill(Qt::transparent);
                    QPainter *painter1 = new QPainter(pixmap3);
                    painter1->drawPixmap(0, 0, 71, 96*(i-1), *pixmap2);
                    painter1->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/"+QString::number(c2.getValeur())+"c.gif"));
                    painter1->end();
                    ui->cartejoueur2->setPixmap(*pixmap3);
                }
            }


    }
    if(c2.getSymbole()=="♠")
    {


            if(c2.getValeur()==11){
                if(i==0)
                {
                    ui->cartejoueur2->setPixmap(QPixmap(":/images/Js.gif"));
                }
                else {
                    QPixmap *pixmap3=new QPixmap(71, 96*(i));
                    pixmap3->fill(Qt::transparent);
                    QPainter *painter1 = new QPainter(pixmap3);
                    painter1->drawPixmap(0, 0, 71, 96*(i-1), *pixmap2);
                    painter1->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Js.gif"));
                    painter1->end();
                    ui->cartejoueur2->setPixmap(*pixmap3);
                }
            }
            else if(c2.getValeur()==12){
                if(i==0)
                {
                    ui->cartejoueur2->setPixmap(QPixmap(":/images/Qs.gif"));
                }
                else {
                    QPixmap *pixmap3=new QPixmap(71, 96*(i));
                    pixmap3->fill(Qt::transparent);
                    QPainter *painter1 = new QPainter(pixmap3);
                    painter1->drawPixmap(0, 0, 71, 96*(i-1), *pixmap2);
                    painter1->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Qs.gif"));
                    painter1->end();
                    ui->cartejoueur2->setPixmap(*pixmap3);
                }

            }
            else if(c2.getValeur()==13){
                if(i==0)
                {
                    ui->cartejoueur2->setPixmap(QPixmap(":/images/Ks.gif"));
                }
                else {
                    QPixmap *pixmap3=new QPixmap(71, 96*(i));
                    pixmap3->fill(Qt::transparent);
                    QPainter *painter1 = new QPainter(pixmap3);
                    painter1->drawPixmap(0, 0, 71, 96*(i-1), *pixmap2);
                    painter1->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/Ks.gif"));
                    painter1->end();
                    ui->cartejoueur2->setPixmap(*pixmap3);
                }
            }
           else
            {
                if(i==0)
                {
                    ui->cartejoueur2->setPixmap(QPixmap(":/images/"+QString::number(c2.getValeur())+"s.gif"));
                }
                else {
                    QPixmap *pixmap3=new QPixmap(71, 96*(i));
                    pixmap3->fill(Qt::transparent);
                    QPainter *painter1 = new QPainter(pixmap3);
                    painter1->drawPixmap(0, 0, 71, 96*(i-1), *pixmap2);
                    painter1->drawPixmap(0, 20*i, 71, 96, QPixmap(":/images/"+QString::number(c2.getValeur())+"s.gif"));
                    painter1->end();
                    ui->cartejoueur2->setPixmap(*pixmap3);
                }
            }
    }











}






