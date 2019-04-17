#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Roslina.h"
#include "Organizm.h"
#include "Swiat.h"
#include "Trawa.h"

Trawa::Trawa(Swiat* swiat, Pozycja pozycja): Roslina(swiat, pozycja)
{
	this->setGatunekOrganizmu("Trawa");
	this->setZnak('T');
}

void Trawa::zasiej(Pozycja pozycja)
{
	Trawa* nowaTrawa = new Trawa(this->swiat, pozycja);
	this->getSwiat()->dodajOrganizmNaPlansze(nowaTrawa);
}


