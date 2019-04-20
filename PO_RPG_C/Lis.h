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
	void akcja() override;
	int znajdzBezpiecznePole();
	int czyBezpieczne(Pozycja pozycja);
	int znajdzDowolneBezpiecznePole();
};
