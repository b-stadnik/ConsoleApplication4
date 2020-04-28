#include "pch.h"
#include "grafLista.h"
#include "grafMacierz.h"
#include "BellmanFord.h"
#include <iostream>
#include <time.h>
#include <iomanip>
using namespace std;

int ilosc_wierzcholkow[5] = { 10, 25, 50, 75, 100 };
double gestosc_grafu[4] = { 0.25, 0.5, 0.75, 1 };      //liczba z przedzialu <0,1>
int wierzcholek_startowy = 2;		//liczba z przedzialu <0,(ilosc_wierzcholkow-1)>
double czas_lista = 0, czas_macierz = 0, czas = 0;

double testujListe(class ListaGraf* graf)
{
	graf->WczytajzPliku();
		czas_lista = czas_lista + BellmanFord(graf, wierzcholek_startowy, false);
	return czas_lista;
}

double testujMacierz(class MacierzGraf* graf)
{
	graf->WczytajzPliku();
	czas_macierz = czas_macierz + BellmanFord(graf, wierzcholek_startowy, false);
	return czas_macierz;
}

int main()
{
	int loops = 100, i, j, k;
	srand(static_cast<unsigned int>(time(NULL)));
	
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 5; j++) {
			ListaGraf* graf = new ListaGraf(ilosc_wierzcholkow[j], gestosc_grafu[i]);
			for (int k = 0; k < loops; k++) {
				graf->WypelnijLosowymi();
				graf->ZapiszDoPliku(wierzcholek_startowy);
				ListaGraf* graf2 = new ListaGraf(ilosc_wierzcholkow[j], gestosc_grafu[i]);
				MacierzGraf* graf3 = new MacierzGraf(ilosc_wierzcholkow[j], gestosc_grafu[i]);
				testujListe(graf2);
				testujMacierz(graf3);
				delete graf2, graf3;
			}
			czas_lista = czas_lista / loops;
			czas_macierz = czas_macierz / loops;
			cout << "Dla " << ilosc_wierzcholkow[j] << " wierzcholkow, " << gestosc_grafu[i] << " gestosci- czas:" << endl;
			
			cout << "Dla listy " << czas_lista << " ms" << endl;
			cout << "Dla macierzy " << czas_macierz << " ms\n\n";
			czas_lista = 0; czas_macierz = 0;
			delete graf;
		}
		cout << endl << "------------------------------------" << endl;
	}

	//MacierzGraf* graf = new MacierzGraf(ilosc_wierzcholkow[j], gestosc_grafu[i]);
	//graf->WypelnijLosowymi();
	//graf->ZapiszDoPliku(wierzcholek_startowy);
	
	return 0;
	/*
	wierzcholek_startowy = graf->WczytajzPliku();
	for (k = 0; k < loops; k++) {
		czas_macierz = czas_macierz + BellmanFord(graf, wierzcholek_startowy, false);//true jesli chcemy wyniki zapisac do pliku 
															
	}
	czas_macierz = czas_macierz / loops;
	cout << "Czas trwania algorytmu wynosi: " << czas_macierz <<" ms";
	delete graf;
	*/
}