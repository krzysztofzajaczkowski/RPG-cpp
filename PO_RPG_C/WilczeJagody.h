#pragma once
#include <iostream>
#include <cstdlib>
#include "Organizm.h"
#include "Roslina.h"
#include "Swiat.h"
#include <string>

class WilczeJagody: public Roslina{
public:
	WilczeJagody(Swiat* swiat, Pozycja pozycja);
	void reagujNaKolizje(Organizm* napastnik) override;
	void zasiej(Pozycja pozycjaDziecka) override;
};
