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

Organizm* Zwierze::getOrganizmNaPlanszy(Pozycja pozycja)
{
	return this->getSwiat()->getOrganizmNaPlanszy(pozycja);
}

void Zwierze::reagujNaKolizje(Organizm* napastnik)
{
	Pozycja pozycjaObroncy = *this->getPozycja();
	Pozycja pozycjaNapastnika = *napastnik->getPozycja();
	if ( napastnik->getSila() >= this->getSila())
	{
		string komunikat = napastnik->getGatunekOrganizmu() + " wygral z " + this->getGatunekOrganizmu() + " na pozycji (" + to_string(pozycjaObroncy.x) + "," + to_string(pozycjaObroncy.y) + ")";
		//TODO execute move on winner
		this->gin();
	}
	string komunikat = this->getGatunekOrganizmu() + " wygral z " + napastnik->getGatunekOrganizmu() + " na pozycji (" + to_string(pozycjaObroncy.x) + "," + to_string(pozycjaObroncy.y) + ")";
	napastnik->gin();
	this->dodajKomunikatWRejestrzeSwiata(komunikat);
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
	else
	{
		organizmNaDocelowejPozycji->reagujNaKolizje(this);
	}
}
