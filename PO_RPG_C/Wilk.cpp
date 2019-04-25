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

Wilk::Wilk(Swiat* swiat, Pozycja pozycja, int sila): Zwierze(swiat, pozycja, 1)
{
	this->setGatunekOrganizmu("Wilk");
	this->setZnak('W');
	this->setSila(sila);
	this->setInicjatywa(5);
}

void Wilk::rozmnozSie(Organizm* partner)
{
	Pozycja* pozycjaDziecka = this->znajdzSasiednieWolnePole();
	if ( pozycjaDziecka == nullptr )
	{
		Pozycja* pozycjaDziecka = partner->znajdzSasiednieWolnePole();
	}
	if ( pozycjaDziecka != nullptr )
	{
		string komunikat = "Wilk rodzi sie na (" + to_string(pozycjaDziecka->x) + ", " + to_string(pozycjaDziecka->y) + ")";
		this->dodajKomunikatWRejestrzeSwiata(komunikat);
		Organizm* dziecko = new Wilk(swiat, *pozycjaDziecka);
		this->urodzDziecko(dziecko);
	}
}



