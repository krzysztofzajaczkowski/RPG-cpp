#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Zwierze.h"
#include "Lis.h"
#include "Swiat.h"

Lis::Lis(Swiat* swiat, Pozycja pozycja): Zwierze(swiat, pozycja, 1)
{
	this->setGatunekOrganizmu("Lis");
	this->setZnak('L');
	this->setSila(3);
	this->setInicjatywa(7);
}

Lis::Lis(Swiat* swiat, Pozycja pozycja, int sila): Zwierze(swiat, pozycja, 1)
{
	this->setGatunekOrganizmu("Lis");
	this->setZnak('L');
	this->setSila(sila);
	this->setInicjatywa(7);
}


int Lis::czyBezpieczne(Pozycja pozycja)
{
	Organizm* napastnik = this->getOrganizmNaPlanszy(pozycja);
	if ( napastnik != nullptr)
	{
		return this->getSila() >= napastnik->getSila();
	}
	return 1;
}

Pozycja Lis::znajdzDowolneBezpiecznePole()
{
	for ( int i = 0; i < 4; ++i )
	{
		int kierunek = i;
		Pozycja* pozycja = this->getPozycja();
		if ( this->czyMoznaWykonacRuch(kierunek) )
		{
			Pozycja nowaPozycja = this->computeNowaPozycja(kierunek);
			if ( this->czyKolizja(nowaPozycja) )
			{
				if ( this->czyBezpieczne(nowaPozycja) )
				{
					return nowaPozycja;
				}
			}
			else
			{
				return nowaPozycja;
			}

		}
	}
	return *this->getPozycja();
}

Pozycja Lis::znajdzBezpiecznePole()
{
	int kierunek = this->losujKierunek();
	Pozycja* pozycja = this->getPozycja();
	if ( this->czyMoznaWykonacRuch(kierunek) )
	{
		Pozycja nowaPozycja = this->computeNowaPozycja(kierunek);
		if ( this->czyKolizja(nowaPozycja) )
		{
			if ( this->czyBezpieczne(nowaPozycja) )
			{
				return nowaPozycja;
			}
			else
			{
				return this->znajdzDowolneBezpiecznePole();
			}
		}
		return nowaPozycja;
	}
	return *this->getPozycja();
}


void Lis::akcja()
{
	Pozycja nowaPozycja = this->znajdzBezpiecznePole();
	if ( nowaPozycja != *this->getPozycja() )
	{
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

void Lis::rozmnozSie(Organizm* partner)
{
	//TODO Lis is born on wrong coordinates, fix that
	// Debug by writing all X position and all Y positions on board, because something's not right
	Pozycja* pozycjaDziecka = this->znajdzSasiednieWolnePole();
	if ( pozycjaDziecka == nullptr )
	{
		Pozycja* pozycjaDziecka = partner->znajdzSasiednieWolnePole();
	}
	if ( pozycjaDziecka != nullptr )
	{
		string komunikat = "Lis rodzi sie na (" + to_string(pozycjaDziecka->x) + ", " + to_string(pozycjaDziecka->y) + ")";
		this->dodajKomunikatWRejestrzeSwiata(komunikat);
		Organizm* dziecko = new Lis(swiat, *pozycjaDziecka);
		this->urodzDziecko(dziecko);
	}
}