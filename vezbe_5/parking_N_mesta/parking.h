#ifndef PARKING_H_INCLUDED
#define PARKING_H_INCLUDED

#include <mutex>
#include <condition_variable>

#include "automobil.h"

using namespace std;

class Parking {
    mutex m;
    condition_variable c;
    int slobodnih_mesta;
private:
    Automobil& automobil;

public:
    Parking(Automobil& a, int kapacitet) : automobil(a), slobodnih_mesta(kapacitet) {
        // Proširiti po potrebi ...
    }

    // Metoda koju poziva nit koja simulira kretanje automobila kako bi automobil pokušao da se parkira.
    // Ako je parking zauzet, izvršenje ove metode će trajati dok se parking ne oslobodi i auto se parkira.
    //
    // rbr - Redni broj automobila
    //
    // Potrebno je pozvati metodu automobil.ceka kada je parking zauzet i auto ne može da se parkira.
    // Potrebno je pozvati metodu automobil.parkira kada auto uspe da se parkira.
    void udji(int rbr) {
        unique_lock<mutex> l(m);
        while(slobodnih_mesta <= 0){
            automobil.ceka(rbr);
            c.wait(l);
        }
        automobil.parkira(rbr);
        slobodnih_mesta--;
    }

    // Metoda koju poziva nit koja simulira kretanje automobila kada auto izlazi sa parkinga (nakon što je bio parkiran).
    //
    // rbr - Redni broj automobila
    //
    // Potrebno je pozvati metodu automobil.napusta kada auto napušta parking mesto.
    void izadji(int rbr) {
        unique_lock<mutex> l(m);
        automobil.napusta(rbr);
        slobodnih_mesta++;
        c.notify_one();
    }
};

#endif // PARKING_H_INCLUDED
