#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Roslina.h"
#include "Organizm.h"
#include "Swiat.h"
#include "WilczeJagody.h"

WilczeJagody::WilczeJagody(Swiat* swiat, Pozycja pozycja): Roslina(swiat, pozycja)
{
	this->setGatunekOrganizmu("Wilcze Jagody");
	this->setZnak('J');
	this->sila = 99;
}

void WilczeJagody::zasiej(Pozycja pozycja)
{
	WilczeJagody* noweJagody = new WilczeJagody(this->swiat, pozycja);
	this->getSwiat()->dodajOrganizmNaPlansze(noweJagody);
}


void WilczeJagody::reagujNaKolizje(Organizm* napastnik)
{
	Pozycja pozycjaObroncy = *this->getPozycja();
	string komunikat = napastnik->getGatunekOrganizmu() + " zjadl " + this->getGatunekOrganizmu() + " na pozycji (" + to_string(pozycjaObroncy.x) + "," + to_string(pozycjaObroncy.y) + ") i zatruwa sie smiertelnie";
	napastnik->gin();
}
