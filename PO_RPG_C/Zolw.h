#pragma once
#include <iostream>
#include <cstdlib>
#include "Organizm.h"
#include "Zwierze.h"
#include "Swiat.h"
#include <string>

class Zolw: public Zwierze{
public:
	Zolw(Swiat* swiat, Pozycja pozycja);
	Zolw(Swiat* swiat, Pozycja pozycja, int sila);
	void akcja() override;
	void kolizja(Pozycja docelowaPozycja) override;
	int czyOdpieraAtak(Organizm* przeciwnik);
	void reagujNaKolizje(Organizm* napastnik) override;
	void rozmnozSie(Organizm* partner);
};
