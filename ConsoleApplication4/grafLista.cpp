#include "pch.h"
#include "grafLista.h"

void ListaGraf::dodajWierzcholek(int w_poczatek, int w_koniec, int w_waga, int id)
{
	wierzcholek[id].poczatek = w_poczatek;
	wierzcholek[id].koniec = w_koniec;
	wierzcholek[id].waga = w_waga;
}

void ListaGraf::Wyswietl()
{
	for (int w_poczatek = 0; w_poczatek < il_wierzch; w_poczatek++) {
		for (int krawedz = 0; krawedz < il_krawedzi; krawedz++) {
			if (wierzcholek[krawedz].poczatek == w_poczatek)
				std::cout << "[" << w_poczatek << ", " << wierzcholek[krawedz].koniec << ", " << wierzcholek[krawedz].waga << "]" << std::endl;
		}
	}
}

bool ListaGraf::CzyIstnieje(int w_poczatek, int w_koniec)
{
	for (int i = 0; i < il_krawedzi; i++){
		if (wierzcholek[i].poczatek == w_poczatek && wierzcholek[i].koniec == w_koniec)
			return true;
	}
	return false;
}


void ListaGraf::WypelnijLosowymi()
{
	int w_waga, w_poczatek, w_koniec, i = 0;

	//gdy gestosc jest rowna 1
	if (gestosc == 1)
	{
		for (w_poczatek = 0; w_poczatek < il_wierzch; w_poczatek++) {
			for (w_koniec = 0; w_koniec < il_wierzch; w_koniec++) {
				if (w_poczatek != w_koniec)
				{
					w_waga = rand() % 10;
					dodajWierzcholek(w_poczatek, w_koniec, w_waga, i);
					i++;
				}
			}
		}
		return;
	}

	//w pozostalych przypadkach
	while(i<il_krawedzi)
	{
		w_poczatek = rand() % il_wierzch;
		w_koniec = rand() % il_wierzch;
		if (!CzyIstnieje(w_poczatek, w_koniec) && w_poczatek != w_koniec)
		{
			w_waga = rand() % 10;
			dodajWierzcholek(w_poczatek, w_koniec, w_waga, i);
			i++;
		}
	}
}

void ListaGraf::ZapiszDoPliku(int start)
{
	std::fstream plik("plik.txt", std::ios::out);
	if (plik.good())
	{
		plik << il_krawedzi << " " << il_wierzch << " " << start << " " << std::endl;
		plik.flush();
		//petle ponizej zapewniaja odpowiednia kolejnosc zapisu i tym samym kompatybilnosc ze struktura macierzowa
		for (int w_poczatek = 0; w_poczatek < il_wierzch; w_poczatek++) {
			for (int w_koniec = 0; w_koniec < il_wierzch; w_koniec++) {
				for (int krawedz = 0; krawedz < il_krawedzi; krawedz++) {
					if (wierzcholek[krawedz].poczatek == w_poczatek && wierzcholek[krawedz].koniec == w_koniec) {
						plik << wierzcholek[krawedz].poczatek << " " << wierzcholek[krawedz].koniec << " " << wierzcholek[krawedz].waga << " " << std::endl;
						plik.flush();
					}
				}
			}
		}
		plik.close();
	}
}

int ListaGraf::WczytajzPliku()
{
	std::ifstream plik("plik.txt", std::ios::out);
	int poczatek, koniec, waga, start;
	if (plik.good())
	{
		plik >> il_krawedzi >> il_wierzch >> start;
		wierzcholek = new Wierzcholek[il_krawedzi];

		for (int i = 0; i < il_krawedzi; i++)
		{
			plik >> poczatek >> koniec >> waga;
			dodajWierzcholek(poczatek, koniec, waga, i);
		}
		plik.close();
	}
	return start;
}