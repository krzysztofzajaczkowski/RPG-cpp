#pragma once
#include <iostream>
#include <cstdlib>
#include "Organizm.h"

class Roslina: public Organizm{
public:
	Roslina(Swiat* swiat, Pozycja pozycja);
	void akcja() override;
	void kolizja(Pozycja docelowaPozycja) override;
	void reagujNaKolizje(Organizm* napastnik) override;
	void rozmnozSie(Organizm* partner) override;
	bool losujCzyRozmnozenie();
	virtual void zasiej(Pozycja pozycjaDziecka)=0;
};
