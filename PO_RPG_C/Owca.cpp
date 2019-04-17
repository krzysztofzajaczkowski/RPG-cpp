#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Zwierze.h"
#include "Owca.h"
#include "Swiat.h"

Owca::Owca(Swiat* swiat, Pozycja pozycja): Zwierze(swiat, pozycja, 1)
{
	this->setGatunekOrganizmu("Owca");
	this->setZnak('O');
	this->setSila(4);
	this->setInicjatywa(4);
}



