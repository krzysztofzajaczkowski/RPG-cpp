#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Roslina.h"
#include "Organizm.h"
#include "Swiat.h"
#include "Mlecz.h"

Mlecz::Mlecz(Swiat* swiat, Pozycja pozycja): Roslina(swiat, pozycja)
{
	this->setGatunekOrganizmu("Mlecz");
	this->setZnak('M');
}

void Mlecz::zasiej(Pozycja pozycja)
{
	Mlecz* nowaTrawa = new Mlecz(this->swiat, pozycja);
	this->getSwiat()->dodajOrganizmNaPlansze(nowaTrawa);
}

void Mlecz::akcja()
{
	for (int i = 0; i < 3; ++i)
	{
		Organizm::akcja();
	}
}



