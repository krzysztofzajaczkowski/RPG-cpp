#pragma once
#include <iostream>
#include <cstdlib>
#include "Organizm.h"
#include "Zwierze.h"
#include "Swiat.h"
#include <string>

class Wilk: public Zwierze{
public:
	Wilk(Swiat* swiat, Pozycja pozycja);
	Wilk(Swiat* swiat, Pozycja pozycja, int sila);
	void rozmnozSie(Organizm* partner) override;
};
