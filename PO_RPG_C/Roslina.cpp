#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Roslina.h"
#include "Organizm.h"
#include "Swiat.h"


Roslina::Roslina(Swiat* swiat, Pozycja pozycja): Organizm(swiat, pozycja)
{
	id = this->liczbaStworzonychOrganizmow++;
	this->setTypOrganizmu("Zwierze");
	this->getSwiat()->dodajOrganizmNaPlansze(this);
}

void Roslina::usunOrganizmZPlanszy()
{
	this->getSwiat()->usunOrganizmZPlanszy(this);
}

bool Roslina::losujCzyRozmnozenie()
{
	srand(time(NULL));
	int szansaNaRozmnozenie = rand()%100 + 1;
	return szansaNaRozmnozenie > 70;
}

void Roslina::rozmnozSie(Organizm* partner)
{
	bool czyRozmnazanieMozliwe = 0;
	int i = 0, kierunek;
	while( (i < 4) && (!czyRozmnazanieMozliwe) )
	{
		kierunek = this->losujKierunek();
		czyRozmnazanieMozliwe = this->czyMoznaWykonacRuch(kierunek);
	}
	Pozycja nowaPozycja = this->computeNowaPozycja(kierunek);
	if ( this->czyKolizja(nowaPozycja) )
	{
		this->kolizja(nowaPozycja);
	}
}

void Roslina::akcja()
{
	if ( this->losujCzyRozmnozenie() )
	{
		this->rozmnozSie(this);
	}
}

Organizm* Roslina::getOrganizmNaPlanszy(Pozycja pozycja)
{
	return this->getSwiat()->getOrganizmNaPlanszy(pozycja);
}

void Roslina::kolizja(Pozycja docelowaPozycja)
{
	Organizm* napastnik = this->getOrganizmNaPlanszy(docelowaPozycja);
	this->reagujNaKolizje(napastnik);
}

void Roslina::rysuj()
{
	/*
	 * Draw Zwierze on position
	 */
}

int Roslina::getId()
{
	return this->id;
}
