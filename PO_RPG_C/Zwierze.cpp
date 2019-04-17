#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Zwierze.h"
#include "Organizm.h"
#include "Swiat.h"


Zwierze::Zwierze(Swiat* swiat, Pozycja pozycja, int krok): Organizm(swiat, pozycja), krok(krok)
{
	id = this->liczbaStworzonychOrganizmow++;
	this->setTypOrganizmu("Zwierze");
	this->getSwiat()->dodajOrganizmNaPlansze(this);
}

void Zwierze::usunOrganizmZPlanszy()
{
	this->getSwiat()->usunOrganizmZPlanszy(this);
}

void Zwierze::dodajOrganizmNaPlansze()
{
	this->getSwiat()->dodajOrganizmNaPlansze(this);
}

void Zwierze::ustawNowaPozycje(Pozycja pozycja)
{
	*this->pozycja = pozycja;
}

void Zwierze::wykonajRuch(Pozycja pozycja)
{
	this->usunOrganizmZPlanszy();
	this->ustawNowaPozycje(pozycja);
	this->dodajOrganizmNaPlansze();
}

Organizm* Zwierze::getOrganizmNaPlanszy(Pozycja pozycja)
{
	return this->getSwiat()->getOrganizmNaPlanszy(pozycja);
}



void Zwierze::akcja()
{
	int kierunek = this->losujKierunek();
	Pozycja* pozycja = this->getPozycja();
	if ( this->czyMoznaWykonacRuch(kierunek) )
	{
		Pozycja nowaPozycja = this->computeNowaPozycja(kierunek);
		if ( this->czyKolizja(nowaPozycja) )
		{
			this->kolizja(nowaPozycja);
		}
		this->wykonajRuch(nowaPozycja);
	}
}

void Zwierze::kolizja(Pozycja docelowaPozycja)
{
	Organizm* organizmNaDocelowejPozycji = this->getOrganizmNaPlanszy(docelowaPozycja);
	if ( organizmNaDocelowejPozycji->getGatunekOrganizmu() == this->getGatunekOrganizmu() )
	{
		//TODO animal reproducing
		this->rozmnozSie(organizmNaDocelowejPozycji);
	}
	organizmNaDocelowejPozycji->bronSie(this);
}

void Zwierze::rysuj()
{
	/*
	 * Draw Zwierze on position
	 */
}

int Zwierze::getId()
{
	return this->id;
}
