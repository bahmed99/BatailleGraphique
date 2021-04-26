#include "player.h"



Player::Player():prenom("")
{

}



void Player::setPrenom(QString prenom)
{
    this->prenom = prenom;
}

QString Player::getPrenom()
{
    return prenom;
}

Hand& Player::getHand()
{
    return hand;
}

void Player::setHand(Hand& h)
{
    hand = h;
}

Player::~Player(void)
{
}
