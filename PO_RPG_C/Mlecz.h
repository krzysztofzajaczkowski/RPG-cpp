#pragma once
#include <iostream>
#include <cstdlib>
#include "Organizm.h"
#include "Roslina.h"
#include "Swiat.h"
#include <string>

class Mlecz: public Roslina{
public:
	Mlecz(Swiat* swiat, Pozycja pozycja);
	void zasiej(Pozycja pozycja) override;
	void akcja() override;
};
