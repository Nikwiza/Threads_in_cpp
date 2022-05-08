/*
Napraviti konkurentni program koji u funkciji visina pita korisnika koliko je visok.
 Nakon toga korisnik unosi svoju visinu. Na kraju u funkciji se ispisuje uneta visina.

Sprečiti štetno preplitanje na terminalu korišćenjem klase mutex.

Kreirati 2 niti od date funkcije. Ispratiti ispis.
*/
#include<stdio.h>
#include<iostream>
#include<mutex>
#include <thread>

using namespace std;
mutex m;

void visina(){
    float visina;
    unique_lock<mutex> l(m);
    cout<<"Koja vam je visina? :";
    cin>>visina;
    cout<<endl<<"Vasa visina je: "<<visina<<endl;
}

int main(){
    thread t(visina);
    thread t1(visina);
    t.join();
    t1.join();
    return 0;

}


