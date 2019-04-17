#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Roslina.h"
#include "Organizm.h"
#include "Swiat.h"
#include "Guarana.h"

Guarana::Guarana(Swiat* swiat, Pozycja pozycja): Roslina(swiat, pozycja)
{
	this->setGatunekOrganizmu("Guarana");
	this->setZnak('G');
}

void Guarana::zasiej(Pozycja pozycja)
{
	Guarana* nowaGuarana = new Guarana(this->swiat, pozycja);
	this->getSwiat()->dodajOrganizmNaPlansze(nowaGuarana);
}

void Guarana::zwiekszSileNapastnika(Organizm* napastnik)
{
	napastnik->zwiekszSile(3);
}


void Guarana::kolizja(Pozycja docelowaPozycja)
{
	Organizm* napastnik = this->getOrganizmNaPlanszy(docelowaPozycja);
	this->zwiekszSileNapastnika(napastnik);
	this->reagujNaKolizje(napastnik);
}




