#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Roslina.h"
#include "Swiat.h"
#include "Mlecz.h"

Mlecz::Mlecz(Swiat* swiat, Pozycja pozycja): Roslina(swiat, pozycja)
{
	this->setGatunekOrganizmu("Mlecz");
	this->setZnak('M');
}

void Mlecz::zasiej(Pozycja pozycjaDziecka)
{
	string komunikat = "Mlecz rosnie na (" + to_string(pozycjaDziecka.x) + ", " + to_string(pozycjaDziecka.y) + ")";
	this->dodajKomunikatWRejestrzeSwiata(komunikat);
	Mlecz* nowyMlecz = new Mlecz(this->swiat, pozycjaDziecka);
	this->getSwiat()->dodajOrganizmDoSwiata(nowyMlecz);
}

void Mlecz::akcja()
{
	for (int i = 0; i < 3; ++i)
	{
		Roslina::akcja();
	}
}



