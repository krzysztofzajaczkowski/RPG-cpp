#pragma once
#include <iostream>
#include <cstdlib>
#include "Organizm.h"
#include "Zwierze.h"
#include "Swiat.h"
#include <string>

class Czlowiek: public Zwierze{
public:
	Czlowiek(Swiat* swiat, Pozycja pozycja);
	Czlowiek(Swiat* swiat, Pozycja pozycja, int sila);
	void akcja() override;
	void kolizja(Pozycja docelowaPozycja) override;
	void reagujNaKolizje(Organizm* napastnik) override;
};
