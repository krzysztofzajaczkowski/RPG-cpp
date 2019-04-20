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
		Pozycja* pozycjaDziecka = partner->znajdzSasiednieWolnePole();
	}
	if ( pozycjaDziecka != nullptr )
	{
		Organizm* dziecko = new Owca(swiat, *pozycjaDziecka);
		this->urodzDziecko(dziecko);
	}
}

