#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Zwierze.h"
#include "Antylopa.h"
#include "Swiat.h"

Antylopa::Antylopa(Swiat* swiat, Pozycja pozycja): Zwierze(swiat, pozycja, 1)
{
	this->setGatunekOrganizmu("Antylopa");
	this->setZnak('A');
	this->setSila(4);
	this->setInicjatywa(4);
}

void Antylopa::akcja()
{
	int kierunek = this->losujKierunek();
	Pozycja* nowaPozycja = nullptr;
	for ( int i = 0; i < 2 ; i++)
	{
		if ( this->czyMoznaWykonacRuch(kierunek) )
		{
			*nowaPozycja = this->computeNowaPozycja(kierunek);
		}
	}
	if ( this->czyKolizja(*nowaPozycja) )
		{
			this->kolizja(*nowaPozycja);
		}
		this->wykonajRuch(*nowaPozycja);
	delete nowaPozycja;
}

void Antylopa::reagujNaKolizje(Organizm* napastnik)
{
	srand(time(NULL));
	int szansaNaUcieczke = rand()%100 + 1;
	int czyUcieczka = 0;
	if (szansaNaUcieczke > 50)
	{
		Pozycja* pozycjaUcieczki = this->znajdzSasiednieWolnePole();
		if ( pozycjaUcieczki != nullptr)
		{
			czyUcieczka = 1;
			Pozycja pozycjaObroncy = *this->getPozycja();
			napastnik->wykonajRuch(pozycjaObroncy);
			this->ucieczka(*pozycjaUcieczki, napastnik);
			delete pozycjaUcieczki;
		}
	}
	if ( !czyUcieczka )
	{
		Zwierze::reagujNaKolizje(napastnik);
	}
}

void Antylopa::ucieczka(Pozycja pozycjaUcieczki, Organizm* napastnik)
{
	Pozycja pozycjaObroncy = *this->getPozycja();
	string komunikat = this->getGatunekOrganizmu() + " uciekla przed " + napastnik->getGatunekOrganizmu() + " na pozycji (" + to_string(pozycjaObroncy.x) + "," + to_string(pozycjaObroncy.y) + ")";
	this->dodajKomunikatWRejestrzeSwiata(komunikat);
	this->wykonajRuch(pozycjaUcieczki);
}






