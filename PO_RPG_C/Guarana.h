#pragma once
#include <iostream>
#include <cstdlib>
#include "Organizm.h"
#include "Roslina.h"
#include "Swiat.h"
#include <string>

class Guarana: public Roslina{
public:
	Guarana(Swiat* swiat, Pozycja pozycja);
	void zasiej(Pozycja pozycjaDziecka) override;
	void reagujNaKolizje(Organizm* napastnik) override;
	void zwiekszSileNapastnika(Organizm* napastnik);
};
