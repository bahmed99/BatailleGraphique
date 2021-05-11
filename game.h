#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include<QSound>


#include "player.h"
#include<QMessageBox>

#include <QDebug>

#include<package.h>

#include<QDateTime>
#include<QPainter>



#include<QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class Game; }
QT_END_NAMESPACE

class Game : public QMainWindow
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();

private slots:
    void on_jouer_clicked(); // lancer le jeux

    void on_tirer_clicked(); // tirer une carte

    void on_redemarer_clicked(); // redemarer window

    void on_mute_clicked(); // couper la musique

    void on_playMusic_clicked(); //lancer la musique

    void affichage(Card c1,Card c2, int i ); // affichage des cartes

private:
    Ui::Game *ui;
    Player p1,p2;
    int index ; // indique le numéro de la manche
    QSound *son,*son1,*son2;



};
#endif // GAME_H
