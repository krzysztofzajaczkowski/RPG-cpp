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

void Owca::rozmnozSie(Organizm* partner)
{
	Pozycja* pozycjaDziecka = this->znajdzSasiednieWolnePole();
	if ( pozycjaDziecka == nullptr )
	{
		pozycjaDziecka = partner->znajdzSasiednieWolnePole();
	}
	if ( pozycjaDziecka != nullptr )
	{
		string komunikat = "Owca rodzi sie na (" + to_string(pozycjaDziecka->x) + ", " + to_string(pozycjaDziecka->y) + ")";
		this->dodajKomunikatWRejestrzeSwiata(komunikat);
		Organizm* dziecko = new Owca(swiat, *pozycjaDziecka);
		this->urodzDziecko(dziecko);
	}
}

