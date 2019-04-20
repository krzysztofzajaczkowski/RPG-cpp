#pragma once
#include <iostream>
#include <cstdlib>
#include "Organizm.h"
#include "Zwierze.h"
#include "Swiat.h"
#include <string>

class Owca: public Zwierze{
public:
	Owca(Swiat* swiat, Pozycja pozycja);
	void rozmnozSie(Organizm* partner);
};
