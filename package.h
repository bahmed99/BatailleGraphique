#ifndef PACKAGE_H
#define PACKAGE_H


#include <iostream>


#include "hand.h"
using namespace std;

class Package
{
    Card Pack[52];
public :

    Package(void);


    void distribuer(Hand&, Hand&); // distribuer les cartes entre 2 joueurs


    ~Package(void);


};
#endif // PACKAGE_H
