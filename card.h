#ifndef CARD_H
#define CARD_H

#include<QString>
#include <iostream>
#include <string>
using namespace std;


class Card
{
    int valeur;
    QString symbole;
public :

    Card(void);


    int getValeur()const;  // retourner la valeur de la carte

    QString getSymbole()const; // retourner la symbole de la carte

    void setValeur(int);  //Affectuer la valeur de la carte

    void setSymbole(QString);  // Affectuer le symbole de la carte

    int comparer(Card&); //comparer les valeurs de deux cartes

    void operator=(const Card&);

    ~Card(void);
};

#endif // CARD_H
