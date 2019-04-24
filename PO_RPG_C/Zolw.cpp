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
	int szansaNaRuch = rand()%100 + 1;
	if (szansaNaRuch > 75)
	{
		Zwierze::akcja();
	}
}

void Zolw::kolizja(Pozycja docelowaPozycja)
{
	Organizm* organizmNaDocelowejPozycji = this->getOrganizmNaPlanszy(docelowaPozycja);
	if ( organizmNaDocelowejPozycji->getGatunekOrganizmu() == this->getGatunekOrganizmu() )
	{
		this->rozmnozSie(organizmNaDocelowejPozycji);
	}
	else
	{
		if ( !this->czyOdpieraAtak(organizmNaDocelowejPozycji) )
		{
			
			organizmNaDocelowejPozycji->reagujNaKolizje(this);
		}
		else
		{
			string komunikat = "Zolw atakujac odpycha " + organizmNaDocelowejPozycji->getGatunekOrganizmu() + " na pozycji (" + to_string(organizmNaDocelowejPozycji->getPozycja()->x) + "," + to_string(organizmNaDocelowejPozycji->getPozycja()->y) + ")";
			this->dodajKomunikatWRejestrzeSwiata(komunikat);
		}
	}
}

int Zolw::czyOdpieraAtak(Organizm* przeciwnik)
{
	return ( przeciwnik->getSila() < 5 ) && ( przeciwnik->getTypOrganizmu() == "Zwierze" );
}


void Zolw::reagujNaKolizje(Organizm* napastnik)
{
	if ( !czyOdpieraAtak(napastnik) )
	{
		Zwierze::reagujNaKolizje(napastnik);
	}
	else
	{
		string komunikat = "Zolw broniac sie odpycha " + napastnik->getGatunekOrganizmu() + " na pozycji (" + to_string(this->getPozycja()->x) + "," + to_string(this->getPozycja()->y) + ")";
		this->dodajKomunikatWRejestrzeSwiata(komunikat);
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
		string komunikat = "Zolw rodzi sie na (" + to_string(pozycjaDziecka->x) + ", " + to_string(pozycjaDziecka->y) + ")";
		this->dodajKomunikatWRejestrzeSwiata(komunikat);
		Organizm* dziecko = new Zolw(swiat, *pozycjaDziecka);
		this->urodzDziecko(dziecko);
	}
}





