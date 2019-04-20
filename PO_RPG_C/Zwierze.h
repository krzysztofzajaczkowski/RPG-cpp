#pragma once
#include "Organizm.h"

class Zwierze: public Organizm {
protected:
	int krok;
public:
	virtual ~Zwierze() = default;
	Zwierze(Swiat* swiat, Pozycja pozycja, int krok);
	void akcja() override;
	void kolizja(Pozycja docelowaPozycja) override;
	Organizm* getOrganizmNaPlanszy(Pozycja pozycja);
	void urodzDziecko(Organizm* dziecko);
	void reagujNaKolizje(Organizm* napastnik) override;
};
