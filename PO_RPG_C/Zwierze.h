#pragma once
#include "Organizm.h"

class Zwierze: public Organizm {
public:
	virtual ~Zwierze() = default;
	Zwierze(Swiat* swiat, Pozycja pozycja, int krok);
	Zwierze(Swiat* swiat, Pozycja pozycja);
	void akcja() override;
	void kolizja(Pozycja docelowaPozycja) override;
	void urodzDziecko(Organizm* dziecko);
	void reagujNaKolizje(Organizm* napastnik) override;
};
