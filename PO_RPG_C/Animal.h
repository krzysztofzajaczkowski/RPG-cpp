#pragma once
#include <iostream>
#include <cstdlib>
#include "Organizm.h"

class Animal: public Organizm{
public:
	Animal();
	int akcja() override;
	int kolizja() override;
	void rysuj() override;
	int getAge();
};
