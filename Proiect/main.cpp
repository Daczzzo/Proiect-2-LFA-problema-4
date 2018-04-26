#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
char stare_init, stari_fin[10];
char cuvant[100];
int v[100], pozitie_cur;
ifstream f("date.in");
struct tranzitie {
    char actual;
    char car;
    char urm;
} tranz[20];

/**
*
*@param stare_act reprezinta starea in care este programul in acest moment
*@param cuvant reprezinta un string care se modifica de la o apelare recursiva la alta
*eliminand prima litera a cuvantului la fiecare pas
*@param nr_muchii este numarul total de tranzitii, fiecare tranzitie fiind reprezentata de o litera
*@param nr_fin este numarul de stari finale ale automatului
*/

void gramatica_regulata(char stare_act, char cuvant[100], int nr_tranzitii, int nr_fin) {
    int i, OK = 0;
    char copie_cuvant[100];
    if (cuvant[0] == NULL) {
        for (i = 0; i < nr_fin; i++)
            if (stare_act == stari_fin[i]) {
                v[pozitie_cur] = 1;
                pozitie_cur++;
                OK = 1;
            }
        if (OK == 0) {
            v[pozitie_cur] = 0;
            pozitie_cur++;
        }
    }
    for (i = 0; i < nr_tranzitii; i++)
        if (tranz[i].actual == stare_act && cuvant[0] == tranz[i].car) {
            strcpy(copie_cuvant, cuvant + 1);
            gramatica_regulata(tranz[i].urm, copie_cuvant, nr_tranzitii, nr_fin);
        }

}

int main() {
    int nr_tranzitii, nr_fin = 0;
    int i, OK = 0;
    f >> nr_tranzitii;
    for (i = 0; i < nr_tranzitii; i++) {
        f >> tranz[i].actual;
        if (i == 0)
            stare_init = tranz[0].actual;
        f >> tranz[i].car;
        f >> tranz[i].urm;
    }
    for (i = 0; i < nr_tranzitii; i++)
        if (tranz[i].car == '#') {
            stari_fin[nr_fin] = tranz[i].actual;
            nr_fin++;
        }

    cout << "Introduceti cuvantul:" << endl;
    cin >> cuvant;
    cout << endl;
    gramatica_regulata(stare_init, cuvant, nr_tranzitii, nr_fin);
    for (i = 0; i < pozitie_cur; i++)
        if (v[i] == 1 && OK == 0) {
            OK = 1;
            cout << "cuvantul apartine" << endl;
        }
    if (OK == 0)
        cout << "cuvantul nu apartine";
    return 0;
}
