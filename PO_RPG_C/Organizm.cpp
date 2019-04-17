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
	//TODO usunac organizm z listy
	//TODO usunac organizm z planszy
	this->getSwiat()->usunOrganizmZPlanszy(this);
	delete this;
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
		pozycja.y -= this->krok;
		if ( pozycja.y < 0 )
		{
			pozycja.y = 0;
		}
	}
	if ( kierunek == 1 )
	{
		pozycja.x += this->krok;
		if ( pozycja.x > this->getRozmiarSwiataX() - 1 )
		{
			pozycja.x = this->getRozmiarSwiataX() - 1;
		}
	}
	if ( kierunek == 2 )
	{
		pozycja.y += 1;
		if ( pozycja.y > this->getRozmiarSwiataY() - 1 )
		{
			pozycja.y = this->getRozmiarSwiataY() - 1;
		}
	}
	if ( kierunek == 3 )
	{
		pozycja.x -= 1;
		if ( pozycja.x < 0 )
		{
			pozycja.x = 0;
		}
	}
	return pozycja;
}

int Organizm::getSila()
{
	return this->sila;
}

int Organizm::bronSie(Organizm* napastnik)
{
	Pozycja pozycjaObroncy = *this->getPozycja();
	Pozycja pozycjaNapastnika = *napastnik->getPozycja();
	if ( napastnik->getSila() >= this->getSila())
	{
		return 1;
		string komunikat = napastnik->getGatunekOrganizmu() + " wygral z " + this->getGatunekOrganizmu() + " na pozycji (" + to_string(pozycjaObroncy.x) + "," + to_string(pozycjaObroncy.y) + ")";
		this->gin();
	}
	string komunikat = this->getGatunekOrganizmu() + " wygral z " + napastnik->getGatunekOrganizmu() + " na pozycji (" + to_string(pozycjaObroncy.x) + "," + to_string(pozycjaObroncy.y) + ")";
	napastnik->gin();
	this->dodajKomunikatWRejestrzeSwiata(komunikat);
	return 0;
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

Pozycja* Organizm::znajdzWolnePoleNaDziecko()
{
	int i = 0, kierunek, czyPoleZajete = 1;
	Pozycja* nowaPozycja;
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
		return nullptr;
	}
	return nowaPozycja;
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

