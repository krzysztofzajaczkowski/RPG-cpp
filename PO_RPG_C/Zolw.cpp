#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Zwierze.h"
#include "Zolw.h"
#include "Swiat.h"

Zolw::Zolw(Swiat* swiat, Pozycja pozycja): Zwierze(swiat, pozycja, 1)
{
	this->setGatunekOrganizmu("Zolw");
	this->setZnak('Z');
	this->setSila(2);
	this->setInicjatywa(1);
}

void Zolw::akcja()
{
	srand(time(NULL));
	int szansaNaRuch = rand()%100 + 1;
	if (szansaNaRuch > 75)
	{
		Zwierze::akcja();
	}
}

void Zolw::reagujNaKolizje(Organizm* napastnik)
{
	if ( napastnik->getSila() >= 5)
	{
		Zwierze::reagujNaKolizje(napastnik);
	}
}

void Zolw::rozmnozSie(Organizm* partner)
{
	Pozycja* pozycjaDziecka = this->znajdzSasiednieWolnePole();
	if ( pozycjaDziecka == nullptr )
	{
		Pozycja* pozycjaDziecka = partner->znajdzSasiednieWolnePole();
	}
	if ( pozycjaDziecka != nullptr )
	{
		Organizm* dziecko = new Zolw(swiat, *pozycjaDziecka);
		this->urodzDziecko(dziecko);
	}
}





