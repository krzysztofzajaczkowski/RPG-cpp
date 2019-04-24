#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Roslina.h"
#include "Organizm.h"
#include "Swiat.h"
#include "BarszczSosnowskiego.h"

BarszczSosnowskiego::BarszczSosnowskiego(Swiat* swiat, Pozycja pozycja): Roslina(swiat, pozycja)
{
	this->setGatunekOrganizmu("Barszcz Sosnowskiego");
	this->setZnak('B');
	this->setSila(10);
}

void BarszczSosnowskiego::zasiej(Pozycja pozycjaDziecka)
{
	string komunikat = "Barszcz Sosnowskiego rosnie na (" + to_string(pozycjaDziecka.x) + ", " + to_string(pozycjaDziecka.y) + ")";
	this->dodajKomunikatWRejestrzeSwiata(komunikat);
	BarszczSosnowskiego* nowyBarszcz = new BarszczSosnowskiego(this->swiat, pozycjaDziecka);
	this->getSwiat()->dodajOrganizmDoSwiata(nowyBarszcz);
}


void BarszczSosnowskiego::reagujNaKolizje(Organizm* napastnik)
{
	Pozycja pozycjaObroncy = *this->getPozycja();
	string komunikat = napastnik->getGatunekOrganizmu() + " zjada " + this->getGatunekOrganizmu() + " na pozycji (" + to_string(pozycjaObroncy.x) + "," + to_string(pozycjaObroncy.y) + ") i zatruwa sie smiertelnie";
	napastnik->gin();
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
			ofiara->gin();
			this->dodajKomunikatWRejestrzeSwiata(komunikat);
		}
	}
}

void BarszczSosnowskiego::zabijSasiadujace()
{
	Pozycja pozycja = *this->getPozycja();
	pozycja.x += 1;
	this->zabijJesliZwierze(pozycja);
	pozycja.x -= 2;
	this->zabijJesliZwierze(pozycja);
	pozycja.x += 1;
	pozycja.y -= 1;
	this->zabijJesliZwierze(pozycja);
	pozycja.y += 2;
	this->zabijJesliZwierze(pozycja);

}

void BarszczSosnowskiego::akcja()
{
	//this->zabijSasiadujace();
	Roslina::akcja();
}

