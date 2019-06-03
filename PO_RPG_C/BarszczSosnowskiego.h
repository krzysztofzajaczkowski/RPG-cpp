#pragma once
#include <iostream>
#include <cstdlib>
#include "Organizm.h"
#include "Roslina.h"
#include "Swiat.h"
#include <string>

class BarszczSosnowskiego: public Roslina{
public:
	BarszczSosnowskiego(Swiat* swiat, Pozycja pozycja);
	void reagujNaKolizje(Organizm* napastnik) override;
	void zabijJesliZwierze(Pozycja pozycja);
	void zabijSasiadujace();
	void akcja() override;
	void zasiej(Pozycja pozycja) override;
};
