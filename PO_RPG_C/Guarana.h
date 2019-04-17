#pragma once
#include <iostream>
#include <cstdlib>
#include "Organizm.h"
#include "Roslina.h"
#include "Swiat.h"
#include <string>

class Guarana: protected Roslina{
public:
	Guarana(Swiat* swiat, Pozycja pozycja);
	void zasiej(Pozycja pozycja) override;
	void kolizja(Pozycja docelowaPozycja) override;
	void zwiekszSileNapastnika(Organizm* napastnik);
};
