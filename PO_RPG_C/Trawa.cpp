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

void Trawa::zasiej(Pozycja pozycjaDziecka)
{
	string komunikat = "Trawa rosnie na (" + to_string(pozycjaDziecka.x) + ", " + to_string(pozycjaDziecka.y) + ")";
	this->dodajKomunikatWRejestrzeSwiata(komunikat);
	Trawa* nowaTrawa = new Trawa(this->swiat, pozycjaDziecka);
	this->getSwiat()->dodajOrganizmDoSwiata(nowaTrawa);
}
