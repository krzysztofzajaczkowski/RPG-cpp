#include <iostream>
#include <conio.h>
#include <string>
#include "Swiat.h"
#include "Organizm.h"
#include "Trawa.h"
#include "Roslina.h"
#include <algorithm>
#include <windows.h>

COORD coord={0,0};


struct CompareOrganizmy
{
    bool operator()(Organizm* lewy, Organizm* prawy) const
    {
        int czyWiekszy = 0;
        if ( lewy->getInicjatywa() > prawy->getInicjatywa() )
        {
            czyWiekszy = 1;
        }
        if ( lewy->getInicjatywa() == prawy->getInicjatywa() && lewy->getId() < prawy->getId())
        {
            czyWiekszy = 1;
        }
        return czyWiekszy;
    }
};


void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

using namespace std;

Swiat::Swiat()
{
    this->setRozmiar();
    this->createZajete();
}



void Swiat::createZajete()
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

 list<Organizm*>::iterator Swiat::zniszczOrganizm( list<Organizm*>::iterator iterator)
{
	list<Organizm*>::iterator tempIterator = iterator;
    iterator = next(iterator);
	Organizm* organizmPtr = (*tempIterator);
    this->listaInicjatywy.erase(tempIterator);
	delete organizmPtr;
	return iterator;
}

void Swiat::usunOrganizmZPlanszy(Organizm* organizm)
{
    Pozycja pozycjaOrganizmu = *organizm->getPozycja();
    this->getZajete()[pozycjaOrganizmu.y][pozycjaOrganizmu.x] = nullptr;
    this->rysujNaPolu(pozycjaOrganizmu, ' ');
}


void Swiat::dodajOrganizmNaPlansze(Organizm* organizm)
{
    Pozycja pozycjaOrganizmu = *organizm->getPozycja();
    this->getZajete()[pozycjaOrganizmu.y][pozycjaOrganizmu.x] = organizm;
    this->rysujNaPolu(pozycjaOrganizmu, organizm->getZnak());
}

int Swiat::sprawdzCzyPoleOkupowane(Pozycja pozycja)
{
    int czyZajete = false;
    if ( this->getZajete()[pozycja.y][pozycja.x] != nullptr)
    {
        czyZajete = true;
    }
    return czyZajete;

}

Organizm* Swiat::getOrganizmNaPlanszy(Pozycja pozycja)
{
    if ( this->polaPlanszy[pozycja.y][pozycja.x] != nullptr )
    {
        return this->polaPlanszy[pozycja.y][pozycja.x];
    }
    return nullptr;
}


Organizm*** Swiat::getZajete()
{
    return this->polaPlanszy;
}

void Swiat::clearRejestr()
{
    for ( int i = 0; i < sizeof(this->rejestr)/sizeof(this->rejestr[0]) ; ++i)
    {
        this->rejestr[i] = "";
    }
}

void Swiat::dodajKomunikatWRejestrze(string komunikat)
{
    for (int i = 0; i < sizeof(this->rejestr)/sizeof(this->rejestr[0]) - 1; ++i)
    {
        this->rejestr[i] = this->rejestr[i+1];
    }
    this->rejestr[sizeof(this->rejestr)/sizeof(this->rejestr[0]) - 1] = komunikat;
    rysujRejestr();
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
	int naglowekX = 2*this->rozmiarX + 7;
    int naglowekY = 1;
	gotoxy(naglowekX, naglowekY);
    cout << "Krzysztof Zajaczkowski 175489" << endl;
}

void Swiat::rysujNaPolu(Pozycja pozycja, char znak)
{
    gotoxy(2*pozycja.x+5, pozycja.y+2);
    _putch(znak);
}



void Swiat::rysujPlansze()
{
    printf("%5s", "");
    for (int i = 0; i < rozmiarX; ++i)
    {
        cout << i%10 << " ";
    }
    cout << endl;
    //cout << 0 << (char)201;
    printf("%3s %c", "" , 201);
    for ( int i = 0 ; i < 2*rozmiarX ; ++i )
    {
        cout << (char)205;
    }
    cout << (char)187 << endl;
    for ( int i = 0 ; i < rozmiarY ; ++i )
    {
        printf("%3d %c", i , 186);
        for ( int j = 0; j < 2*rozmiarX ; ++j )
        {
            cout << " ";
        }
        cout << (char)186 << endl;
    }
    //cout << this->rozmiarY+1 << (char)200;
    printf("%3s %c", "" , 200);
    for ( int i = 0 ; i < 2*rozmiarX ; ++i )
    {
        cout << (char)205;
    }
    cout << (char)188 << endl;
}

void Swiat::rysujLegende()
{
    int legendaX = 2*this->rozmiarX + 7;
    int legendaY = 2;
    gotoxy(legendaX, legendaY++);
    cout << "A - Antylopa";
    gotoxy(legendaX, legendaY++);
    cout << "B - Barszcz Sosnowskiego";
    gotoxy(legendaX, legendaY++);
    cout << "C - Czlowiek";
    gotoxy(legendaX, legendaY++);
    cout << "G - Guarana";
    gotoxy(legendaX, legendaY++);
    cout << "J - Wilcze Jagody";
    gotoxy(legendaX, legendaY++);
    cout << "L - Lis";
    gotoxy(legendaX, legendaY++);
    cout << "M - Mlecz";
    gotoxy(legendaX, legendaY++);
    cout << "O - Owca";
    gotoxy(legendaX, legendaY++);
    cout << "T - Trawa";
    gotoxy(legendaX, legendaY++);
    cout << "W - Wilk";
    gotoxy(legendaX, legendaY++);
    cout << "Z - Zolw";
    gotoxy(legendaX, legendaY++);
    cout << "Strzalki - wybor ruchu";
    gotoxy(legendaX, legendaY++);
    cout << "F - umiejetnosc specjalna";
    gotoxy(legendaX, legendaY++);
    cout << "Spacja - zatwierdzenie ruchu";
    gotoxy(legendaX, legendaY++);
    cout << "S - zapisanie gry";
    gotoxy(legendaX, legendaY);
    cout << "W - wczytanie gry";

}

void Swiat::rysujRejestr()
{
    int rejestrX = 2*this->rozmiarX + 7;
    int rejestrY = 19;
    for (int i = 0; i < sizeof(this->rejestr)/sizeof(this->rejestr[0]); ++i)
    {
        gotoxy(rejestrX, rejestrY++);
        printf("%50s", this->rejestr[i].c_str());
    }
}

void Swiat::rysujSwiat()
{

    /*
     * for (int i = 0; i < this->getRozmiarY(); ++i)
    {
        for (int j = 0; j < this->getRozmiarX(); ++j)
        {
            if (this->getZajete()[i][j] != nullptr)
            {
                this->getZajete()[i][j]->rysuj();
            }
        }
    }
     */
    // rysuj swiat with legend and combat log
    this->rysujPlansze();
    for (Organizm* i: listaInicjatywy)
    {
        i->rysuj();
    }
	this->rysujNaglowek();
    this->rysujLegende();
    this->rysujRejestr();
}

void Swiat::wykonajRunde()
{
    list<Organizm*>::iterator tempIterator;
    for ( list<Organizm*>::iterator it = this->listaInicjatywy.begin(); it != this->listaInicjatywy.end(); )
    {
        if ( (*it)->czyDoZabicia() )
        {
			it = this->zniszczOrganizm(it);
        }
        else
        {
            (*it)->akcja();
            it = next(it);
        }
    }
    this->sortujListeInicjatywy();
    gotoxy(2, this->rozmiarY+5);
    printf("%3zd", this->listaInicjatywy.size());
}

int Swiat::dodajOrganizmDoSwiata(Organizm *organizm)
{
    this->dodajOrganizmNaPlansze(organizm);
    this->listaInicjatywy.push_back(organizm);
    organizm->rysuj();
    return true;
}

void Swiat::sortujListeInicjatywy()
{
    this->listaInicjatywy.sort(CompareOrganizmy());
}

void Swiat::setRozmiar()
{
    cout << "Podaj rozmiary planszy n x m: " << endl;
    cin >> this->rozmiarX;
    cin >> this->rozmiarY;
}

