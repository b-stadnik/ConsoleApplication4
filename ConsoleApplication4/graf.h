#pragma once
#include "pch.h"
class Graf
{
protected:
	int il_krawedzi, il_wierzch;
	double gestosc;

public:
	const int& getK() const { return il_krawedzi; }
	const int& getW() const { return il_wierzch; }

	Graf() {};
};