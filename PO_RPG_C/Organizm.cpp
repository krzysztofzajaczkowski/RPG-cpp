#include "Organizm.h"
#include "Swiat.h"
#include <cstdlib>
#include <ctime>

int Organizm::liczbaStworzonychOrganizmow = 1;

Organizm::Organizm(Swiat* swiat, Pozycja pozycja): swiat(swiat)
{
	this->pozycja = new Pozycja(pozycja.x, pozycja.y);
}

void Organizm::setSila(int sila)
{
	this->sila = sila;
}

int Organizm::getSila()
{
	return this->sila;
}

void Organizm::setInicjatywa(int inicjatywa)
{
	this->inicjatywa = inicjatywa;
}

void Organizm::wykonajRuch(Pozycja pozycja)
{
	this->usunOrganizmZPlanszy();
	this->ustawNowaPozycje(pozycja);
	this->dodajOrganizmNaPlansze();
}

void Organizm::dodajOrganizmNaPlansze()
{
	this->getSwiat()->dodajOrganizmNaPlansze(this);
}

void Organizm::ustawNowaPozycje(Pozycja pozycja)
{
	*this->pozycja = pozycja;
}

int Organizm::getInicjatywa()
{
	return this->inicjatywa;
}

void Organizm::setElementListyInicjatywy(int numerElementu)
{
	this->elementListyInicjatywy = numerElementu;
}

void Organizm::usunOrganizmZPlanszy()
{
	this->getSwiat()->usunOrganizmZPlanszy(this);
}

void Organizm::setZnak(char znak)
{
	this->znak = znak;
}

char Organizm::getZnak()
{
	return this->znak;
}

void Organizm::gin()
{
	//TODO remove Organizm from listaInicjatywy
	this->usunOrganizmZPlanszy();
}

string Organizm::getGatunekOrganizmu()
{
	return this->gatunekOrganizmu;
}

void Organizm::setGatunekOrganizmu(string rodzajOrganizmu)
{
	this->gatunekOrganizmu = rodzajOrganizmu;
}

string Organizm::getTypOrganizmu()
{
	return this->typOrganizmu;
}

void Organizm::setTypOrganizmu(string typOrganizmu)
{
	this->typOrganizmu = typOrganizmu;
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

int Organizm::getRozmiarSwiataX()
{
	return this->getSwiat()->getRozmiarX();
}

int Organizm::getRozmiarSwiataY()
{
	return this->getSwiat()->getRozmiarY();
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

int Organizm::sprawdzCzyPoleOkupowane(Pozycja pozycja)
{
	return this->getSwiat()->sprawdzCzyPoleOkupowane(pozycja);
}

int Organizm::czyKolizja(Pozycja docelowaPozycja)
{
	return this->sprawdzCzyPoleOkupowane(docelowaPozycja);
	
}

void Organizm::dodajKomunikatWRejestrzeSwiata(string komunikat)
{
	this->getSwiat()->dodajKomunikatWRejestrze(komunikat);
}

Pozycja* Organizm::znajdzSasiednieWolnePole()
{
	int i = 0, kierunek, czyPoleZajete = 1;
	Pozycja* nowaPozycja = new Pozycja(-1,-1);
	while( (i < 6) && (czyPoleZajete) )
	{
		int kierunek = this->losujKierunek();
		*nowaPozycja = this->computeNowaPozycja(kierunek);
		czyPoleZajete = this->sprawdzCzyPoleOkupowane(*nowaPozycja);
		++i;
	}
	if ( czyPoleZajete )
	{
		for (kierunek = 0; i < 4; ++i)
		{
			*nowaPozycja = this->computeNowaPozycja(kierunek);
			czyPoleZajete = this->sprawdzCzyPoleOkupowane(*nowaPozycja);
			if ( !czyPoleZajete )
			{
				kierunek = 4;
			}
		}
	}
	if (czyPoleZajete)
	{
		delete nowaPozycja;
		return nullptr;
	}
	return nowaPozycja;
}

void Organizm::zwiekszSile(int bonus)
{
	this->sila += bonus;
}


bool Organizm::czyMoznaWykonacRuch(int kierunek)
{
	bool czyMoznaWykonacRuch = 1;
	if ( kierunek == 0 )
	{
		if (this->getPozycja()->y < 1 )
		{
			czyMoznaWykonacRuch = 0;
		}
	}
	if ( kierunek == 1 )
	{
		if (this->getPozycja()->x > this->getSwiat()->getRozmiarX() - 2)
		{	
			czyMoznaWykonacRuch = 0;
		}
	}
	if ( kierunek == 2 )
	{
		if (this->getPozycja()->y > this->getSwiat()->getRozmiarY() - 2)
		{	
			czyMoznaWykonacRuch = 0;
		}
	}
	if ( kierunek == 3 )
	{
		if (this->getPozycja()->x < 1)
		{
			czyMoznaWykonacRuch = 0;
		}
	}
	return czyMoznaWykonacRuch;
}

int Organizm::getId()
{
	return this->id;
}

void Organizm::rysuj()
{
	this->getSwiat()->rysujNaPolu(*this->getPozycja(), this->getZnak());
}
