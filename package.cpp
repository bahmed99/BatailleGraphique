#include "package.h"

#include"card.h"


#include<random>

QString const Symboles[4] = {"♥","♦","♣","♠"};




Package::Package(void)
{
    int i = 0;

    Card aux; // pile pour permutation

    // Donner pour chaque carte du "pack" sa valeur et son symbole

    for (int symb = 0; symb < 4; symb++) {
        for (int val = 1; val <= 13; val++)
        {
            Pack[i].setValeur(val);
            Pack[i].setSymbole(Symboles[symb]);
            i++;

        }
    }


 // MÃ©langer le "Pack"
    for (int j = 0; j < 52; j++) {
        int random = rand() % 52;
        aux=Pack[j];
        Pack[j]=Pack[random];
        Pack[random]=aux;
    }

}

void Package::distribuer(Hand &h1, Hand &h2)
{
    stack <Card> hand1, hand2;
    int cpt = 0;
    for (int i = 0; i < 26; i++)
    {
        hand1.push(Pack[cpt]);
        cpt++;
        hand2.push(Pack[cpt]);
        cpt++;
    }
    h1.setHandPlayer(hand1);
    h2.setHandPlayer(hand2);
}


Package::~Package(void)
{
}
