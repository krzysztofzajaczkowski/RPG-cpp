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

void Zwierze::wykonajRuch(int kierunek)
{
	this->usunOrganizmZPlanszy();
	Pozycja pozycja = this->computeNowaPozycja(kierunek);
	this->ustawNowaPozycje(pozycja);
	this->dodajOrganizmNaPlansze();
}



void Zwierze::akcja()
{
	int kierunek = this->losujKierunek();
	Pozycja* pozycja = this->getPozycja();
	if ( this->czyMoznaWykonacRuch(kierunek) )
	{
		if ( this->czyKolizja(kierunek) )
		{
			this->kolizja();
			//TODO collision for zwierze
		}
		/*
		 *	Jeœli zajête:
		 *		Kolizja
		 *	Jeœli wolne:
		 *		this->wykonajRuch(kierunek);
		 */
		this->getSwiat()->usunOrganizmZPlanszy(this);
		this->wykonajRuch(kierunek);
		pozycja = this->getPozycja();
		if(	this->getSwiat()->sprawdzCzyPoleOkupowane(*pozycja) )
		{
			this->kolizja();
		}
	}
}

int Zwierze::kolizja()
{
	/*
	 * if opponent and defender are the same type:
	 *    perform multiplication
	 *    return true
	 *else:
	 *    return false 
	 */
	return true;
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
