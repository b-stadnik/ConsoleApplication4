#pragma once
#include <chrono>
#include <string>
#include "grafLista.h"
#include "grafMacierz.h"
double BellmanFord(class ListaGraf* graf, int start, bool czyzapisac);
double BellmanFord(class MacierzGraf* graf, int start, bool czyzapisac);