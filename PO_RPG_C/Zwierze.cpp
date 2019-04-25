#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Zwierze.h"
#include "Organizm.h"
#include "Swiat.h"


Zwierze::Zwierze(Swiat* swiat, Pozycja pozycja, int krok): Organizm(swiat, pozycja)
{
	this->setKrok(krok);
	id = this->liczbaStworzonychOrganizmow++;
	this->setTypOrganizmu("Zwierze");
	this->getSwiat()->dodajOrganizmNaPlansze(this);
}

Zwierze::Zwierze(Swiat* swiat, Pozycja pozycja): Organizm(swiat, pozycja)
{
	id = this->liczbaStworzonychOrganizmow++;
	this->setTypOrganizmu("Zwierze");
	this->getSwiat()->dodajOrganizmNaPlansze(this);
}

void Zwierze::urodzDziecko(Organizm* dziecko)
{
	this->getSwiat()->dodajOrganizmDoSwiata(dziecko);
}

void Zwierze::reagujNaKolizje(Organizm* napastnik)
{
	Pozycja pozycjaObroncy = *this->getPozycja();
	Pozycja pozycjaNapastnika = *napastnik->getPozycja();
	string komunikat;
	if ( napastnik->getSila() >= this->getSila())
	{
		komunikat = napastnik->getGatunekOrganizmu() + " wygral z " + this->getGatunekOrganizmu() + " na pozycji (" + to_string(pozycjaObroncy.x) + "," + to_string(pozycjaObroncy.y) + ")";
		this->dodajKomunikatWRejestrzeSwiata(komunikat);
		napastnik->wykonajRuch(pozycjaObroncy);
		this->gin();
	}
	else
	{
		komunikat = napastnik->getGatunekOrganizmu() + " przegral z " + this->getGatunekOrganizmu() + " na pozycji (" + to_string(pozycjaObroncy.x) + "," + to_string(pozycjaObroncy.y) + ")";
		this->dodajKomunikatWRejestrzeSwiata(komunikat);
		napastnik->gin();
		this->wykonajRuch(pozycjaNapastnika);
		
	}
	
}

void Zwierze::akcja()
{
	int kierunek = this->losujKierunek();
	if ( this->czyMoznaWykonacRuch(kierunek) )
	{
		Pozycja nowaPozycja = this->computeNowaPozycja(kierunek);
		if ( this->czyKolizja(nowaPozycja) )
		{
			this->kolizja(nowaPozycja);
		}
		else
		{
			this->wykonajRuch(nowaPozycja);
		}
	}
}

void Zwierze::kolizja(Pozycja docelowaPozycja)
{
	Organizm* organizmNaDocelowejPozycji = this->getOrganizmNaPlanszy(docelowaPozycja);
	if ( organizmNaDocelowejPozycji->getGatunekOrganizmu() == this->getGatunekOrganizmu() )
	{
		this->rozmnozSie(organizmNaDocelowejPozycji);
	}
	else
	{
		organizmNaDocelowejPozycji->reagujNaKolizje(this);
	}
}
