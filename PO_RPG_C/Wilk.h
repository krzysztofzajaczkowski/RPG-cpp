#pragma once
#include <iostream>
#include <cstdlib>
#include "Organizm.h"
#include "Zwierze.h"
#include "Swiat.h"
#include <string>

class Wilk: protected Zwierze{
public:
	Wilk(Swiat* swiat, Pozycja pozycja);
};
