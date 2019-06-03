#pragma once
#include <iostream>
#include <cstdlib>
#include "Organizm.h"
#include "Zwierze.h"
#include "Swiat.h"
#include <string>

class Antylopa: public Zwierze{
public:
	Antylopa(Swiat* swiat, Pozycja pozycja);
	Antylopa(Swiat* swiat, Pozycja pozycja, int sila);
	void akcja() override;
	void kolizja(Pozycja docelowaPozycja) override;
	void reagujNaKolizje(Organizm* napastnik) override;
	int czyUcieczka();
	void ucieczka(Pozycja pozycjaUcieczki, Organizm* napastnik);
	void rozmnozSie(Organizm* partner);
};
