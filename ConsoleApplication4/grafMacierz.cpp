#include "pch.h"
#include "grafMacierz.h"

//wszystkie funkcje maja identyczne zastosowanie co w grafLista
//maja te same nazwy i sa przystosowane do dzialania pod struktura macierzowa

void MacierzGraf::dodajWierzcholek(int w_poczatek, int w_koniec, int w_waga)
{
	macierz[w_poczatek][w_koniec] = w_waga;
}

void MacierzGraf::Wyswietl()
{
	for (int w_poczatek = 0; w_poczatek < il_wierzch; w_poczatek++)
	{
		for (int w_koniec = 0; w_koniec < il_wierzch; w_koniec++)
		{
			std::cout << macierz[w_poczatek][w_koniec] << " ";
		}
		std::cout << std::endl;
	}
}

bool MacierzGraf::CzyIstnieje(int w_poczatek, int w_koniec)
{
	if (macierz[w_poczatek][w_koniec]!=pusty)
		return true;
	return false;
}


void MacierzGraf::WypelnijLosowymi()
{
	int w_waga, w_poczatek, w_koniec, i = 0;

	if (gestosc == 1)
	{
		for (w_poczatek = 0; w_poczatek < il_wierzch; w_poczatek++) {
			for (w_koniec = 0; w_koniec < il_wierzch; w_koniec++) {
				if (w_poczatek != w_koniec)
				{
					w_waga = rand() % 10;
					dodajWierzcholek(w_poczatek, w_koniec, w_waga);

					i++;
				}
			}
		}
		return;
	}
	while (i < il_krawedzi)
	{
		w_poczatek = rand() % il_wierzch;
		w_koniec = rand() % il_wierzch;
		if (!CzyIstnieje(w_poczatek, w_koniec) && w_poczatek != w_koniec)
		{
			w_waga = rand() % 10;
			dodajWierzcholek(w_poczatek, w_koniec, w_waga);
			i++;
		}
	}
}

void MacierzGraf::ZapiszDoPliku(int poczatek)
{
	std::fstream plik("plik.txt", std::ios::out);
	if (plik.good())
	{
		plik << il_krawedzi << " " << il_wierzch << " " << poczatek << std::endl;
		plik.flush();
		for (int i = 0; i < il_wierzch; i++) {
			for (int j = 0; j < il_wierzch; j++)
			{
				if (macierz[i][j] != pusty) {
					plik << i << " " << j << " " << macierz[i][j] << std::endl;
					plik.flush();
				}
			}
		}
		plik.close();
	}
}

int MacierzGraf::WczytajzPliku()
{
	std::ifstream plik("plik.txt", std::ios::out);
	int poczatek, koniec, waga, start;
	if (plik.good())
	{
		plik >> il_krawedzi >> il_wierzch >> start;

		for (int i = 0; i < il_wierzch; i++){
			for (int j = 0; j < il_wierzch; j++) {
				plik >> poczatek >> koniec >> waga;
				dodajWierzcholek(poczatek, koniec, waga);
			}
		}
		plik.close();
	}
	return start;
}