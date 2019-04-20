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


int Lis::czyBezpieczne(Pozycja pozycja)
{
	Organizm* napastnik = this->getOrganizmNaPlanszy(pozycja);
	return this->getSila() >= napastnik->getSila();
}

int Lis::znajdzDowolneBezpiecznePole()
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
					return 1;
				}
			}
		}
	}
	return -1;
}

int Lis::znajdzBezpiecznePole()
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
				return kierunek;
			}
			else
			{
				return this->znajdzDowolneBezpiecznePole();
			}
		}
		return kierunek;
	}
	return -1;
}


void Lis::akcja()
{
	int kierunek = this->znajdzBezpiecznePole();
	Pozycja nowaPozycja = this->computeNowaPozycja(kierunek);
	if ( this->czyKolizja(nowaPozycja) )
	{
		this->kolizja(nowaPozycja);
	}
	this->wykonajRuch(nowaPozycja);
}

void Lis::rozmnozSie(Organizm* partner)
{
	Pozycja* pozycjaDziecka = this->znajdzSasiednieWolnePole();
	if ( pozycjaDziecka == nullptr )
	{
		Pozycja* pozycjaDziecka = partner->znajdzSasiednieWolnePole();
	}
	if ( pozycjaDziecka != nullptr )
	{
		Organizm* dziecko = new Lis(swiat, *pozycjaDziecka);
		this->urodzDziecko(dziecko);
	}
}