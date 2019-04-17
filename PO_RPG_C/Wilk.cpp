#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Zwierze.h"
#include "Wilk.h"
#include "Swiat.h"

Wilk::Wilk(Swiat* swiat, Pozycja pozycja): Zwierze(swiat, pozycja, 1)
{
	this->setGatunekOrganizmu("Wilk");
	this->setZnak('W');
	this->setSila(9);
	this->setInicjatywa(5);
}



