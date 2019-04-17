#pragma once
#include <iostream>
#include <cstdlib>
#include "Organizm.h"

class Zwierze: public Organizm {
protected:
	int krok;
public:
	virtual ~Zwierze() = default;
	Zwierze(Swiat* swiat, Pozycja pozycja, int krok);
	void dodajOrganizmNaPlansze();
	void ustawNowaPozycje(Pozycja pozycja);
	void akcja() override;
	void kolizja(Pozycja docelowaPozycja) override;
	void wykonajRuch(Pozycja pozycja);
	Organizm* getOrganizmNaPlanszy(Pozycja pozycja);
	void reagujNaKolizje(Organizm* napastnik) override;
};
