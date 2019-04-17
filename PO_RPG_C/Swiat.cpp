#include <iostream>
#include <conio.h>
#include <string>
#include "Swiat.h"
#include "Organizm.h"
#include <algorithm>

using namespace std;

Swiat::Swiat()
{
    this->setRozmiar();
    this->setZajete();
}

void Swiat::setZajete()
{
    this->polaPlanszy = new Organizm**[this->rozmiarY];
    for (int i = 0; i < this->rozmiarY; ++i)
    {
        this->polaPlanszy[i] = new Organizm*[this->rozmiarX];
        for (int j = 0; j < this->rozmiarX; ++j)
        {
            this->polaPlanszy[i][j] = nullptr;
        }
    }
}

void Swiat::zniszczOrganizm(Organizm* organizm)
{
	delete organizm;
}

void Swiat::usunOrganizmZPlanszy(Organizm* organizm)
{
	Pozycja* pozycjaOrganizmu = organizm->getPozycja();
	this->zniszczOrganizm(organizm);
    this->getZajete()[pozycjaOrganizmu->y][pozycjaOrganizmu->x] = nullptr;
	
}


void Swiat::dodajOrganizmNaPlansze(Organizm* organizm)
{
	Pozycja* pozycjaOrganizmu = organizm->getPozycja();
    this->getZajete()[pozycjaOrganizmu->y][pozycjaOrganizmu->x] = organizm;
}

int Swiat::sprawdzCzyPoleOkupowane(Pozycja pozycja)
{
	int czyZajete = false;
	if ( this->getZajete()[pozycja.y][pozycja.x])
	{
		czyZajete = true;
	}
	return czyZajete;

}


Organizm*** Swiat::getZajete()
{
    return this->polaPlanszy;
}

void Swiat::setRejestr()
{
    for ( int i = 0; i < sizeof(this->rejestr)/sizeof(this->rejestr[0]) ; ++i)
    {
        this->rejestr[i] == "";
    }
}

void Swiat::dodajRejestr(string rejestr)
{
    for (int i = 0; i < sizeof(this->rejestr)/sizeof(this->rejestr[0]) - 1; ++i)
    {
        this->rejestr[i] = this->rejestr[i+1];
    }
    this->rejestr[sizeof(this->rejestr)/sizeof(this->rejestr[0]) - 1] = rejestr;
}


int Swiat::getRozmiarX()
{
    return this->rozmiarX;
}

int Swiat::getRozmiarY()
{
    return this->rozmiarY;
}

void Swiat::rysujNaglowek()
{
    cout << "Krzysztof Zajaczkowski 175489" << endl;
}


void Swiat::rysujPlansze()
{
    cout << (char)201;
    for ( int i = 0 ; i < rozmiarX ; ++i )
    {
        cout << (char)205;
    }
    cout << (char)187 << endl;
    for ( int i = 0 ; i < rozmiarY ; ++i )
    {
        cout << (char)186;
        for ( int j = 0; j < rozmiarX ; ++j )
        {
            cout << " ";
        }
        cout << (char)186 << endl;
    }
    cout << (char)200;
    for ( int i = 0 ; i < rozmiarX ; ++i )
    {
        cout << (char)205;
    }
    cout << (char)188 << endl;
}

void Swiat::rysujLegende()
{
    
}

void Swiat::rysujRejestrWalk()
{
    for (int i = 0; i < sizeof(this->rejestr)/sizeof(this->rejestr[0]); ++i)
    {
        cout << this->rejestr[i] << endl;
    }
}

void Swiat::rysujSwiat()
{
    // rysuj swiat with legend and combat log
    //rysujPlansze();
    //rysujLegende();
    //rysujRejestrWalk
}

void Swiat::wykonajRunde()
{
    /*
     * Iterate through organisms, perform their akcja
     * If multiplication happened:
     *      append animal
     */
}

int Swiat::dodajOrganizm(Organizm *organizm)
{
    /*
     * Append organizm to list
     */
    return true;
}

int Swiat::sortujListeInicjatywy()
{
    /*
     * Sort listaInicjatywy by inicjatywa / age
     */
    return true;
}

void Swiat::setRozmiar()
{
    cout << "Podaj rozmiary planszy n x m: " << endl;
    cin >> this->rozmiarX;
    cin >> this->rozmiarY;
}

