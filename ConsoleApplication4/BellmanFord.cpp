#include "pch.h"
#include "BellmanFord.h"

void WyswietlTablice(int dystans[], int n)
{
	printf("Wierzcholek   Dystans od zrodla\n");
	for (int i = 0; i < n; ++i)
		printf("%d \t\t %d\n", i, dystans[i]);
}

void WyswietlTablice2(int tab[], int n)
{
	for (int i = 0; i < n; i++)
		std::cout << tab[i] << " ";
	std::cout << std::endl;
}

//wypelnia tablice zerami
void zeruj(int tab[], int n)
{
	for (int i = 0; i < n; i++)
		tab[i] = 0;
}

//kopiuje tablice o tych samych wymiarach
void kopiuj(int tab[], int tab2[], int n)
{
	for (int i = 0; i < n; i++)
		tab[i] = tab2[i];
}

//zlicza elementy niezerowe w tablicy
int zlicz(int tab[], int n)
{
	int suma=0;
	for (int i = 0; i < n; i++) {
		if (tab[i] != 0)
			suma++;
	}
	return suma;
}

void ZapiszDoPliku(int** historia, int dystans[], int n, int start)
{
	std::fstream plik("wynik.txt", std::ios::out);
	if (plik.good())
	{
		plik << "Wierzcholek poczatkowy: " << start << std::endl;
		plik << "Cel,  " << "Dystans,  " << "Droga" << std::endl;
		plik.flush();
		for (int i = 0; i < n; i++) {
			plik << i << "\t" << dystans[i] << "\t" << start;
			plik.flush();

			//petle ponizej sluza do wypisania drogi w prawidlowej kolejnosci
			for (int k = 1; k <= n; k++) {
				for (int j = 0; j < n; j++) {
					if (historia[i][j] == k)
						plik  << "->" << j;
					plik.flush();
				}
			}
			plik << std::endl;
		}
		plik << std::endl;
		plik.close();
	}
}

double BellmanFord(class ListaGraf* graf, int start, bool czyzapisac)
{
	auto czas_start = std::chrono::high_resolution_clock::now();
	int w_il_wierzch = graf->getW(), w_il_krawedzi = graf->getK();

	int* dystans = new int[w_il_wierzch];

	//inicjowanie tablicy ktora przechowa droge
	int** historia = new int*[w_il_wierzch];
	for (int a = 0; a < w_il_wierzch; a++) {
		historia[a] = new int[w_il_wierzch];
		zeruj(historia[a], w_il_wierzch);
	}

	for (int i = 0; i < w_il_wierzch; i++)
		dystans[i] = pusty;
	dystans[start] = 0;

	/**********Wlasciwy algorytm Bellmana-Forda**********/
	for (int i = 1; i < w_il_wierzch - 1; i++) {
		for (int j = 0; j < w_il_krawedzi; j++) {
			int u = graf->getPoczatek(j);
			int v = graf->getKoniec(j);
			int w_waga = graf->getWaga(j);

			if (dystans[u] != pusty && dystans[u] + w_waga < dystans[v]) 
			{
				dystans[v] = dystans[u] + w_waga;
				/**********tworzenie historii dotarcia do wierzcholkow**********/
				kopiuj(historia[v], historia[u], w_il_wierzch);        //Kopiuje droge dotarcia do wierzcholka zrodlowego
				historia[v][v] = zlicz(historia[v], w_il_wierzch)+1;   //Liczba wpisana w wierzcholek docelowy reprezentuje kolejnosc
																	   //przechodzenia przez poszczegolne wierzcholki
			}
		}
	}
	/**********Szukanie ujemnych cyklow**********
	for (int i = 1; i < w_il_wierzch - 1; i++) {
		for (int j = 0; j < w_il_krawedzi; j++) {
			int u = graf->getPoczatek(j);
			int v = graf->getKoniec(j);
			int w_waga = graf->getWaga(j);

			if (dystans[u] != pusty && dystans[u] + w_waga < dystans[v]) {
				dystans[v] = pusty;														  
			}
		}
	}*/
	if (czyzapisac)
		ZapiszDoPliku(historia, dystans, w_il_wierzch, start);
	/* wyswietlenie wynikow w programie
		std::cout << std::endl;
		WyswietlTablice(dystans, w_il_wierzch);
		std::cout << std::endl;
		for (int i = 0; i < w_il_wierzch; i++)
			WyswietlTablice2(historia[i], w_il_wierzch);
	*/
	auto czas_stop = std::chrono::high_resolution_clock::now();
	return std::chrono::duration<double, std::milli>(czas_stop - czas_start).count();
}

double BellmanFord(class MacierzGraf* graf, int start, bool czyzapisac)
{
	auto czas_start = std::chrono::high_resolution_clock::now();
	int w_il_wierzch = graf->getW(), w_il_krawedzi = graf->getK();

	int* dystans = new int[w_il_wierzch];

	//inicjowanie tablicy ktora przechowa droge
	int** historia = new int*[w_il_wierzch];
	for (int a = 0; a < w_il_wierzch; a++) {
		historia[a] = new int[w_il_wierzch];
		zeruj(historia[a], w_il_wierzch);
	}

	for (int i = 0; i < w_il_wierzch; i++)
		dystans[i] = pusty;
	dystans[start] = 0;

	/**********Wlasciwy algorytm Bellmana-Forda**********/
	for (int i = 1; i < w_il_wierzch; i++) {
		for (int j = 0; j < w_il_wierzch; j++) {
			for (int k = 0; k < w_il_wierzch; k++) {
				int u = j;
				int v = k;
				int w_waga = graf->getWaga(j, k);

				if (dystans[u] != pusty && dystans[u] + w_waga < dystans[v])
				{
					dystans[v] = dystans[u] + w_waga;
					/**********tworzenie historii dotarcia do wierzcholkow**********/
					kopiuj(historia[v], historia[u], w_il_wierzch);				//Kopiuje droge dotarcia do wierzcholka zrodlowego
					historia[v][v] = zlicz(historia[v], w_il_wierzch) + 1;		//Liczba wpisana w wierzcholek docelowy reprezentuje kolejnosc
																				//przechodzenia przez poszczegolne wierzcholki
				}
			}
		}
	}

	/**********Szukanie ujemnych cyklow**********
	for (int i = 1; i < w_il_wierzch; i++) {
		for (int j = 0; j < w_il_wierzch; j++) {
			for (int k = 0; k < w_il_wierzch; k++) {
				int u = j;
				int v = k;
				int w_waga = graf->getWaga(j, k);

				if (dystans[u] != pusty && dystans[u] + w_waga < dystans[v])
				{
					dystans[v] = pusty;
																				
				}
			}
		}
	}
	*/
	if (czyzapisac)
		ZapiszDoPliku(historia, dystans, w_il_wierzch, start);
	/* wyswietlenie wynikow w programie
		std::cout << std::endl;
		WyswietlTablice(dystans, w_il_wierzch);
		std::cout << std::endl;
		for (int i = 0; i < w_il_wierzch; i++)
			WyswietlTablice2(historia[i], w_il_wierzch);
			*/
	auto czas_stop = std::chrono::high_resolution_clock::now();
	return std::chrono::duration<double, std::milli>(czas_stop - czas_start).count();
}
