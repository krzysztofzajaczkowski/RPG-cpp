#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Roslina.h"
#include "Organizm.h"
#include "Swiat.h"


Roslina::Roslina(Swiat* swiat, Pozycja pozycja): Organizm(swiat, pozycja)
{
	id = this->liczbaStworzonychOrganizmow++;
	this->setTypOrganizmu("Roslina");
	this->setInicjatywa(0);
	this->getSwiat()->dodajOrganizmNaPlansze(this);
}

bool Roslina::losujCzyRozmnozenie()
{
	int szansaNaRozmnozenie = rand()%100 + 1;
	return szansaNaRozmnozenie > 90;
}


void Roslina::rozmnozSie(Organizm* partner)
{
	Pozycja* pozycjaDziecka = NULL;
	pozycjaDziecka = this->znajdzSasiednieWolnePole();
	if ( pozycjaDziecka != nullptr)
	{
		if ( pozycjaDziecka->czyPrawidlowa() )
		{
			this->zasiej(*pozycjaDziecka);
		}
	}
	delete pozycjaDziecka;
}


void Roslina::akcja()
{
	if ( this->losujCzyRozmnozenie() )
	{
		this->rozmnozSie(nullptr);
	}
}

void Roslina::kolizja(Pozycja docelowaPozycja)
{
	Organizm* napastnik = this->getOrganizmNaPlanszy(docelowaPozycja);
	this->reagujNaKolizje(napastnik);
}

void Roslina::reagujNaKolizje(Organizm* napastnik)
{
	Pozycja pozycjaObroncy = *this->getPozycja();
	string komunikat = napastnik->getGatunekOrganizmu() + " zjadl " + this->getGatunekOrganizmu() + " na pozycji (" + to_string(pozycjaObroncy.x) + "," + to_string(pozycjaObroncy.y) + ")";
	this->dodajKomunikatWRejestrzeSwiata(komunikat);
	napastnik->wykonajRuch(pozycjaObroncy);
	this->gin();
}