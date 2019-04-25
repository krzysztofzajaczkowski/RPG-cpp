#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Roslina.h"
#include "Organizm.h"
#include "Swiat.h"
#include "BarszczSosnowskiego.h"

BarszczSosnowskiego::BarszczSosnowskiego(Swiat* swiat, Pozycja pozycja): Roslina(swiat, pozycja)
{
	this->setGatunekOrganizmu("Barszcz_Sosnowskiego");
	this->setZnak('B');
	this->setSila(10);
}

void BarszczSosnowskiego::zasiej(Pozycja pozycjaDziecka)
{
	string komunikat = "Barszcz_Sosnowskiego rosnie na (" + to_string(pozycjaDziecka.x) + ", " + to_string(pozycjaDziecka.y) + ")";
	this->dodajKomunikatWRejestrzeSwiata(komunikat);
	BarszczSosnowskiego* nowyBarszcz = new BarszczSosnowskiego(this->swiat, pozycjaDziecka);
	this->getSwiat()->dodajOrganizmDoSwiata(nowyBarszcz);
}


void BarszczSosnowskiego::reagujNaKolizje(Organizm* napastnik)
{
	Pozycja pozycjaObroncy = *this->getPozycja();
	string komunikat = napastnik->getGatunekOrganizmu() + " zjada " + this->getGatunekOrganizmu() + " na pozycji (" + to_string(pozycjaObroncy.x) + "," + to_string(pozycjaObroncy.y) + ") i zatruwa sie smiertelnie";
	this->dodajKomunikatWRejestrzeSwiata(komunikat);
	napastnik->gin();
	this->gin();
}

void BarszczSosnowskiego::zabijJesliZwierze(Pozycja pozycja)
{
	Organizm* ofiara = this->getOrganizmNaPlanszy(pozycja);
	if ( ofiara != nullptr )
	{
		if ( ofiara->getTypOrganizmu() == "Zwierze" )
		{
			Pozycja pozycjaOfiary = *ofiara->getPozycja();
			string komunikat = this->getGatunekOrganizmu() + " zabija " + ofiara->getGatunekOrganizmu() + " na pozycji (" + to_string(pozycjaOfiary.x) + "," + to_string(pozycjaOfiary.y) + ")";
			this->dodajKomunikatWRejestrzeSwiata(komunikat);
			ofiara->gin();
		}
	}
}

void BarszczSosnowskiego::zabijSasiadujace()
{
	Pozycja pozycja = *this->getPozycja();
	if ( this->czyMoznaWykonacRuch(0) )
	{
		this->zabijJesliZwierze(Pozycja( pozycja.x, pozycja.y - 1 ) );
	}
	if ( this->czyMoznaWykonacRuch(1) )
	{
		this->zabijJesliZwierze(Pozycja( pozycja.x + 1, pozycja.y ) );
	}
	if ( this->czyMoznaWykonacRuch(2) )
	{
		this->zabijJesliZwierze(Pozycja( pozycja.x, pozycja.y + 1 ) );
	}
	if ( this->czyMoznaWykonacRuch(3) )
	{
		this->zabijJesliZwierze(Pozycja( pozycja.x - 1, pozycja.y ) );
	}
}

void BarszczSosnowskiego::akcja()
{
	this->zabijSasiadujace();
	Roslina::akcja();
}

