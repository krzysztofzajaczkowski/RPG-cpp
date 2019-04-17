#pragma once
#include <iostream>
#include <cstdlib>
#include "Organizm.h"

class Zwierze: public Organizm{
protected:
	int krok;
public:
	Zwierze(Swiat* swiat, Pozycja pozycja, int krok);
	void usunOrganizmZPlanszy();
	void dodajOrganizmNaPlansze();
	void akcja() override;
	int kolizja() override;
	void rysuj() override;
	Zwierze();
	void wykonajRuch(int kierunek) override;
	int getId();
};
