#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Zwierze.h"
#include "Antylopa.h"
#include "Swiat.h"

Antylopa::Antylopa(Swiat* swiat, Pozycja pozycja): Zwierze(swiat, pozycja, 2)
{
	this->setGatunekOrganizmu("Antylopa");
	this->setZnak('A');
	this->setSila(4);
	this->setInicjatywa(4);
}

void Antylopa::akcja()
{
	int kierunek = this->losujKierunek();
	Pozycja nowaPozycja = *this->getPozycja();
	int ruchWykonany = 0;
	int krokProby = this->getKrok();
	while((!ruchWykonany) && (krokProby > 0))
	{
		if ( this->czyMoznaWykonacRuch(kierunek, krokProby) )
		{
			ruchWykonany = 1;
			nowaPozycja = this->computeNowaPozycja(kierunek, krokProby);
		}
		--krokProby;
	}
	if ( ruchWykonany )
	{
		if ( this->czyKolizja(nowaPozycja) )
		{
			this->kolizja(nowaPozycja);
		}
		else
		{
			Pozycja staraPozycja = *this->getPozycja();
			this->wykonajRuch(nowaPozycja);
		}
	}
}

void Antylopa::reagujNaKolizje(Organizm* napastnik)
{
	int czyProbaUcieczki = this->czyUcieczka();
	int czyUcieczkaUdana = 0;
	if (czyProbaUcieczki)
	{
		this->usunOrganizmZPlanszy();
		Pozycja* pozycjaUcieczki = this->znajdzSasiednieWolnePole();
		if ( pozycjaUcieczki != nullptr)
		{
			czyUcieczkaUdana = 1;
			Pozycja pozycjaObroncy = *this->getPozycja();
			napastnik->wykonajRuch(pozycjaObroncy);
			this->ucieczka(*pozycjaUcieczki, napastnik);
			delete pozycjaUcieczki;
		}
	}
	if ( !czyUcieczkaUdana )
	{
		Zwierze::reagujNaKolizje(napastnik);
	}
}

int Antylopa::czyUcieczka()
{
	return (rand()%100 + 1) > 50;
}

void Antylopa::ucieczka(Pozycja pozycjaUcieczki, Organizm* napastnik)
{
	Pozycja pozycjaObroncy = *this->getPozycja();
	string komunikat = this->getGatunekOrganizmu() + " uciekla przed " + napastnik->getGatunekOrganizmu() + " na pozycji (" + to_string(pozycjaObroncy.x) + "," + to_string(pozycjaObroncy.y) + ")";
	this->dodajKomunikatWRejestrzeSwiata(komunikat);
	this->wykonajRuch(pozycjaUcieczki);
	napastnik->rysuj();
}

void Antylopa::rozmnozSie(Organizm* partner)
{
	Pozycja* pozycjaDziecka = this->znajdzSasiednieWolnePole();
	if ( pozycjaDziecka == nullptr )
	{
		pozycjaDziecka = partner->znajdzSasiednieWolnePole();
	}
	if ( pozycjaDziecka != nullptr )
	{
		string komunikat = "Antylopa rodzi sie na (" + to_string(pozycjaDziecka->x) + ", " + to_string(pozycjaDziecka->y) + ")";
		this->dodajKomunikatWRejestrzeSwiata(komunikat);
		Organizm* dziecko = new Antylopa(swiat, *pozycjaDziecka);
		this->urodzDziecko(dziecko);
	}
}




