/* 
Napraviti funkciju:
	
vector<int> min(const vector<int>& a, const vector<int>& b);

Ova funkcija vraća vektor koji sadrži minimume korespodentnih elemenata vektora a i b.
Npr: r[0]=min(a[0],b[0]), r[1]=...
Podrazumeva se: a.size()==b.size()
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef vector<int>::const_iterator IT;

vector<int> min(const vector<int> &a, const vector<int> &b){
    IT ita;
    IT itb;
    vector<int> resenje;

    for(ita = a.begin(), itb = b.begin(); ita!=a.end(); ita++, itb++){
        resenje.push_back(min(*ita, *itb));
    }
    return resenje;
}

int main()
{
    vector<int> a = {3, 4, 2, 15, 66};
    vector<int> b = {1, 5, 777, 5, 662};
    vector<int> c = min(a,b);
    IT it;
    for(it = c.begin(); it!=c.end(); it++){
        cout<<*it<<" ";
    }
    return 0;
}
