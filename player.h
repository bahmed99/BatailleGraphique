#ifndef PLAYER_H
#define PLAYER_H

#include<QString>
#include <iostream>
#include <string>
#include "hand.h"
using namespace std;

class Player
{
    QString prenom;
    Hand hand;
public :
    Player(void);


    void setPrenom(QString); // affectuer prénom du joueur


    QString getPrenom(); // retoruner prénom du joueur


    Hand& getHand(); // retourner "hand" du joueur


    void setHand(Hand& h); //modifier "hand"


    ~Player(void);
};



#endif // PLAYER_H
