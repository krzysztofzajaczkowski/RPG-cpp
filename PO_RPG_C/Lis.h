#pragma once
#include <iostream>
#include <cstdlib>
#include "Organizm.h"
#include "Zwierze.h"
#include "Swiat.h"
#include <string>

class Lis: public Zwierze{
public:
	Lis(Swiat* swiat, Pozycja pozycja);
	Lis(Swiat* swiat, Pozycja pozycja, int sila);
	void akcja() override;
	void rozmnozSie(Organizm* partner);
	Pozycja znajdzBezpiecznePole();
	int czyBezpieczne(Pozycja pozycja);
	Pozycja znajdzDowolneBezpiecznePole();
};
