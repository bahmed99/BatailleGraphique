#include "card.h"

Card::Card()
{
    valeur = 0;
    symbole = "";
}



int Card::getValeur() const
{
    return valeur;
}

QString Card::getSymbole() const
{
    return symbole;
}

void Card::setValeur(int a)
{
    valeur = a;
}

void Card::setSymbole(QString c)
{
    symbole = c;
}



int Card::comparer(Card &c2) {

    if (valeur > c2.valeur) { return 1; }
    else if (valeur < c2.valeur) { return 2; }
    else { return 0; }
}

void Card::operator=(const Card& ct)
{
    valeur = ct.valeur;
    symbole = ct.symbole;
}

Card::~Card(void)
{
}


