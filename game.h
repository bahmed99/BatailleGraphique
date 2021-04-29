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
    void on_pushButton_2_clicked();


    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_mute_clicked();

    void on_pushButton_4_clicked();

    void affichage(Card c1,Card c2, int i );

private:
    Ui::Game *ui;
    Player p1,p2;
    static int index ;
    QSound *son,*son1,*son2;



};
#endif // GAME_H
