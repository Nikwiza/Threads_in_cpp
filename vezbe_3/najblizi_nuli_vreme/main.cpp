/*
Napraviti konkurentni program koji pronalazi element najbliži broju 0 u zadatom vektoru brojeva.

Pretragu podeliti u 3 programske niti. Ulazni vektor brojeva treba da sadrži 900.000 slučajno generisanih brojeva.

Za svaku nit, evidentirati trenutke kada je izvršavanje počelo i kada se završilo. Na kraju programa, ispisati koliko je trajalo izvršavanje svake niti u milisekundama.
*/

#include <iostream>
#include <thread>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;
using namespace chrono;

typedef vector<double>::const_iterator cit;

struct vreme {
    system_clock::time_point pocetak;
    system_clock::time_point kraj;
};

void f(cit pocetak, cit kraj, double & min, struct vreme * v) {
	// Implementirati...
    system_clock::time_point start = system_clock::now();
    min = abs(*pocetak);
    for(cit it = pocetak+1; it!=kraj; it++){
        if(abs(*it) < abs(min)){
            min = *it;
        }
    }
    system_clock::time_point ende = system_clock::now();
    v->pocetak = start;
    v->kraj = ende;
}

const int BROJ_NITI = 3;
const int DUZINA = 900000;

int main() {
    int SEGMENT = DUZINA / BROJ_NITI;

    srand(time(NULL));   // Postavljamo seme random generatora na trenutno vreme, što dovodi do kvalitetnijeg izbora slučajnih brojeva.

    vector<double> v(DUZINA);
    // Puni se vektor pseudo-slučajnim brojevima
    for (int i = 0; i < DUZINA; i++)
	v[i] = rand();

    double minimumi[BROJ_NITI];  // Niz elemenata najbližih nuli - svaka programska nit će dati svoj međurezltat
    struct vreme vremena[BROJ_NITI]; // Niz struktura u koji će biti upisani podaci o trajanju izvršavanja svake niti

    thread niti[BROJ_NITI];
    cit pocetak = v.begin();
    cit kraj = v.begin()+SEGMENT;

    for(int i = 0; i<BROJ_NITI; i++){
        niti[i] = thread(f, pocetak, kraj, ref(minimumi[i]), &vremena[i]);
        pocetak = kraj;
        kraj += SEGMENT;
    }

    for(int i = 0; i<BROJ_NITI; i++){
        niti[i].join();
    }

    duration<double, milli> dur;
    double naj_min = minimumi[0];
    for(int i = 0; i<BROJ_NITI; i++){
        dur = vremena[i].kraj-vremena[i].pocetak;
        cout<<"Vreme ["<<i<<"]te niti je:"<<dur.count()<<endl;
        cout<<"A najblizi nuli za tu nit je : "<<minimumi[i]<<endl;
        if(abs(minimumi[i])<abs(naj_min)){
            naj_min = minimumi[i];
        }
    }
    cout<<"A broj najblizi nuli je : "<<naj_min;

}

