#pragma once
#include "graf.h"
#include "pch.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>

static int pusty = 1000;
class MacierzGraf : public Graf
{
	int** macierz;

public:
	void dodajWierzcholek(int w_poczatek, int w_koniec, int w_waga);
	void Wyswietl();
	bool CzyIstnieje(int w_poczatek, int w_koniec);
	void WypelnijLosowymi();
	void ZapiszDoPliku(int poczatek);
	int WczytajzPliku();

	const int& getWaga(int i, int j) const { return macierz[i][j]; }

	MacierzGraf(int il_wierzch, double gestosc) : Graf()
	{
		this->il_wierzch = il_wierzch;
		this->gestosc = gestosc;
		this->il_krawedzi = gestosc*(il_wierzch*(il_wierzch - 1));
		macierz = new int *[il_wierzch];
		for (int i = 0; i < il_wierzch; i++) {
			macierz[i] = new int[il_wierzch];
			for (int j = 0; j < il_wierzch; j++)
				macierz[i][j] = pusty;
		}
	};
	MacierzGraf() {};
	~MacierzGraf() { delete[] macierz; };
};