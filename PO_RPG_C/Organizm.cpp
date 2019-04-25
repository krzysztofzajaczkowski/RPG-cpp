#include "Organizm.h"
#include "Swiat.h"
#include <cstdlib>
#include <ctime>

int Organizm::liczbaStworzonychOrganizmow = 1;

bool Organizm::operator==(Organizm* prawy)
{
	return ( this->getId() == prawy->getId() );
}


Organizm::Organizm(Swiat* swiat, Pozycja pozycja): swiat(swiat)
{
	this->krok = 1;
	this->pozycja = new Pozycja(pozycja.x, pozycja.y);
}

Organizm::Organizm(Swiat* swiat, Pozycja pozycja, int krok): swiat(swiat), krok(krok)
{
	this->pozycja = new Pozycja(pozycja.x, pozycja.y);
}

void Organizm::setSila(int sila)
{
	this->sila = sila;
}

void Organizm::setDoZabicia()
{
	this->doZabicia = 1;
}

int Organizm::czyDoZabicia()
{
	return this->doZabicia;
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

Organizm* Organizm::getOrganizmNaPlanszy(Pozycja pozycja)
{
	return this->getSwiat()->getOrganizmNaPlanszy(pozycja);
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

void Organizm::setCooldown(int cooldown)
{
	this->cooldownMocySpecjalnej = cooldown;
}

int Organizm::getCooldown()
{
	return this->cooldownMocySpecjalnej;
}

char Organizm::getZnak()
{
	return this->znak;
}

void Organizm::gin()
{
	//TODO delete debug comments
	//string komunikat = this->getGatunekOrganizmu() + " zostaje ustawiony na smierc na pozycji (" + to_string(this->pozycja->x) + "," + to_string(this->pozycja->y) + ")";
	//this->dodajKomunikatWRejestrzeSwiata(komunikat);
	this->setDoZabicia();
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

Pozycja Organizm::computeNowaPozycja(int kierunek, int krok)
{
	Pozycja pozycja = *this->getPozycja();
	if (kierunek == 0)
	{
		pozycja.y -= krok;
	}
	if ( kierunek == 1 )
	{
		pozycja.x += krok;
	}
	if ( kierunek == 2 )
	{
		pozycja.y += krok;
	}
	if ( kierunek == 3 )
	{
		pozycja.x -= krok;
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
	Pozycja* nowaPozycja = new Pozycja;
	while( (i < 6) && (czyPoleZajete) )
	{
		int kierunek = this->losujKierunek();
		if ( this->czyMoznaWykonacRuch(kierunek, 1) )
		{
			*nowaPozycja = this->computeNowaPozycja(kierunek, 1);
			czyPoleZajete = this->sprawdzCzyPoleOkupowane(*nowaPozycja);
		}
		++i;
	}
	if ( czyPoleZajete )
	{
		for (kierunek = 0; kierunek < 4; ++kierunek)
		{
			if ( this->czyMoznaWykonacRuch(kierunek, 1) )
			{
				*nowaPozycja = this->computeNowaPozycja(kierunek, 1);
				czyPoleZajete = this->sprawdzCzyPoleOkupowane(*nowaPozycja);
			}
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
	else
	{
		return nowaPozycja;
	}
	
}

void Organizm::zwiekszSile(int bonus)
{
	this->sila = this->sila + bonus;
}

void Organizm::setKrok(int krok)
{
	this->krok = krok;
}

int Organizm::getKrok()
{
	return this->krok;
}


bool Organizm::czyMoznaWykonacRuch(int kierunek, int krok)
{
	bool czyMoznaWykonacRuch = 1;
	if ( kierunek == 0 )
	{
		if (this->getPozycja()->y - krok < 0 )
		{
			czyMoznaWykonacRuch = 0;
		}
	}
	if ( kierunek == 1 )
	{
		if (this->getPozycja()->x + krok > this->getSwiat()->getRozmiarX() - 1)
		{	
			czyMoznaWykonacRuch = 0;
		}
	}
	if ( kierunek == 2 )
	{
		if (this->getPozycja()->y + krok > this->getSwiat()->getRozmiarY() - 1)
		{	
			czyMoznaWykonacRuch = 0;
		}
	}
	if ( kierunek == 3 )
	{
		if (this->getPozycja()->x - krok < 0)
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
