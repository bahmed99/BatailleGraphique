#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include<QSound>


#include "player.h"
#include<QMessageBox>

#include <QDebug>
#include<QSound>


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

private:
    Ui::Game *ui;
    Player p1,p2;
    static int index ;
    QSound *son,*son1;

};
#endif // GAME_H
