#ifndef NITI_H_INCLUDED
#define NITI_H_INCLUDED

#include <vector>
#include <thread>

#include "suma_vektora.h"

using namespace std;

// v - vektor A čije elemente treba sumirati
// v - vektor B čije elemente treba sumirati
// povratna vrednost - suma korespondentnih elemenata vektora A i B, izračunata pozivanjem dve niti
vector<double> sumiraj(vector<double> a, vector<double> b) {
    // Implementirati ...
    vector<double> suma;
    suma.resize(a.size());
    vector<double>::iterator it;
    it = suma.begin();

    int half = a.size()/2;
    thread t(f, a.begin(), a.begin()+half, b.begin(), it);
    thread t1(f, a.begin() + half, a.end(), b.begin() + half, it + half);
    t1.join();
    t.join();
    return suma;
}

#endif // NITI_H_INCLUDED
