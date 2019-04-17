#include "Organizm.h"
#include "Swiat.h"
#include <cstdlib>
#include <ctime>

int Organizm::liczbaStworzonychOrganizmow = 1;

Organizm::Organizm(Swiat* swiat, Pozycja pozycja): swiat(swiat)
{
	this->getPozycja()->x = pozycja.x;
	this->getPozycja()->y = pozycja.y;
}

void Organizm::setElementListyInicjatywy(int numerElementu)
{
	this->elementListyInicjatywy = numerElementu;
}

void Organizm::gin()
{
	//TODO wyjebac organizm z listy
	//TODO wyjebac organizm z planszy
	this->getSwiat()->usunOrganizmZPlanszy(this);
	delete this;
}

Swiat* Organizm::getSwiat()
{
	return this->swiat;
}

Pozycja* Organizm::getPozycja()
{
	return this->pozycja;
}

int Organizm::losujKierunek()
{
	srand(time(NULL));
	return rand()%4;
}

Pozycja Organizm::computeNowaPozycja(int kierunek)
{
	Pozycja pozycja = *this->getPozycja();
	if (kierunek == 0)
	{
		pozycja.y -= 1;
	}
	if ( kierunek == 1 )
	{
		pozycja.x += 1;
	}
	if ( kierunek == 2 )
	{
		pozycja.y += 1;
	}
	if ( kierunek == 3 )
	{
		pozycja.x -= 1;
	}
	return pozycja;
}

int Organizm::czyKolizja(int kierunek)
{
	Pozycja pozycja = this->computeNowaPozycja(kierunek);
	return this->getSwiat()->sprawdzCzyPoleOkupowane(pozycja);
}


bool Organizm::czyMoznaWykonacRuch(int kierunek)
{
	bool czyMoznaWykonacRuch = 1;
	if ( kierunek == 0 )
	{
		if (this->getPozycja()->y - 1 < 0 )
		{
			czyMoznaWykonacRuch = 0;
		}
	}
	if ( kierunek == 1 )
	{
		if (this->getPozycja()->x + 1 > this->getSwiat()->getRozmiarX() - 1)
		{	
			czyMoznaWykonacRuch = 0;
		}
	}
	if ( kierunek == 2 )
	{
		if (this->getPozycja()->y + 1 > this->getSwiat()->getRozmiarY() - 1)
		{	
			czyMoznaWykonacRuch = 0;
		}
	}
	if ( kierunek == 3 )
	{
		if (this->getPozycja()->x - 1 < 0)
		{
			czyMoznaWykonacRuch = 0;
		}
	}
	return czyMoznaWykonacRuch;
}

