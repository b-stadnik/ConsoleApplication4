#pragma once
#include "graf.h"
#include "pch.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>


struct Wierzcholek
{
	int poczatek, koniec, waga;
};

class ListaGraf : public Graf
{
	Wierzcholek* wierzcholek;

public:
	void dodajWierzcholek(int w_poczatek, int w_koniec, int w_waga, int id);
	void Wyswietl();
	bool CzyIstnieje(int w_poczatek, int w_koniec);
	void WypelnijLosowymi();

	void ZapiszDoPliku(int start);
	int WczytajzPliku();

	const int& getPoczatek(int id) const { return wierzcholek[id].poczatek; }
	const int& getKoniec(int id) const { return wierzcholek[id].koniec; }
	const int& getWaga(int id) const { return wierzcholek[id].waga; }

	ListaGraf(int il_wierzch, double gestosc) : Graf() 
	{
		this->il_wierzch = il_wierzch;
		this->gestosc = gestosc;
		this->il_krawedzi = gestosc *(il_wierzch*(il_wierzch - 1));
		wierzcholek = new Wierzcholek[il_krawedzi];
	};
	ListaGraf() {};
	~ListaGraf() { delete[] wierzcholek; };
};