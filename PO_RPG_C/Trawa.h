#pragma once
#include <iostream>
#include <cstdlib>
#include "Organizm.h"
#include "Roslina.h"
#include "Swiat.h"
#include <string>

class Trawa: public Roslina{
public:
	Trawa(Swiat* swiat, Pozycja pozycja);
	void zasiej(Pozycja pozycja) override;
};
