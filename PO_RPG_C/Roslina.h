#pragma once
#include <iostream>
#include <cstdlib>
#include "Organizm.h"

class Roslina: protected Organizm{
public:
	Roslina(Swiat* swiat, Pozycja pozycjak);
	void usunOrganizmZPlanszy();
	void akcja() override;
	void kolizja(Pozycja pozycja) override;
	void rysuj() override;
	void reagujNaKolizje(Organizm* napastnik) override;
	void rozmnozSie(Organizm* partner) override;
	bool losujCzyRozmnozenie();
	Organizm* getOrganizmNaPlanszy(Pozycja pozycja);
	int getId();
};
