#include <iostream>
#include <conio.h>
#include <string>
#include "Swiat.h"
#include "Organizm.h"
#include "Trawa.h"
#include "Roslina.h"
#include <algorithm>
#include <windows.h>
#include "Antylopa.h"
#include "BarszczSosnowskiego.h"
#include "Guarana.h"
#include "Lis.h"
#include "Mlecz.h"
#include "Zolw.h"
#include "Wilk.h"
#include "WilczeJagody.h"
#include "Owca.h"
#include <fstream>

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

}

bool Swiat::wykonajOpcje(char wybor)
{
	bool czyWykonanoAkcje = false;
	if ( wybor == 'n' || wybor == 'N' )
	{
		this->nowaGra();
		czyWykonanoAkcje = true;
	}
	if ( wybor == 'l' || wybor == 'L' )
	{
		this->wczytajGre();
		czyWykonanoAkcje = true;
	}
	if ( wybor == 's' || wybor == 'S' )
	{
		this->zapiszGre();
		czyWykonanoAkcje = true;

	}
	if ( wybor == 'q' || wybor == 'Q' )
	{
		if ( this->czySwiatIstnieje() )
		{
			this->rysujGre();
		}
		else
		{
			delete this;
		}
	}
	return czyWykonanoAkcje;
}

bool Swiat::czySwiatIstnieje()
{
	bool czySwiatIstnieje = true;
	if ( this->listaInicjatywy.size() == 0 )
	{
		czySwiatIstnieje = false;
	}
	if ( this->polaPlanszy == nullptr )
	{
		czySwiatIstnieje = false;
	}
	return czySwiatIstnieje;
}

void Swiat::menu()
{
	this->wyswietlMenu();
	this->wybierzOpcje();
}

void Swiat::zniszczSwiat()
{
	for ( list<Organizm*>::iterator it = this->listaInicjatywy.begin(); it != this->listaInicjatywy.end(); )
    {
		it = this->zniszczOrganizm(it);
    }
	for ( int i = 0; i < this->rozmiarY; ++i )
	{
		delete this->polaPlanszy[i];
	}
	delete []this->polaPlanszy;
	this->polaPlanszy = nullptr;
	this->clearRejestr();
}

void Swiat::zapiszGre()
{
	system("cls");
	string nazwaPliku = "";
	fstream plik;
	bool zapisywanieZakonczone =  false, czyBlad = false;;
	cout << " Zapisywanie stanu gry " << endl;
	cout << "Q lub q - wyjœcie z menu zapisywania gry " << endl;
	cout << "Podaj nazwe zapisu: ";
	while( ( nazwaPliku != "Q" ) && ( nazwaPliku != "q" ) && ( !zapisywanieZakonczone ))
	{
		if ( czyBlad )
		{
			cout << "Nie udalo sie otworzyc pliku, sprobuj ponownie: ";
		}
		cin >> nazwaPliku;
		if ( ( nazwaPliku != "Q" ) && ( nazwaPliku != "q" ) )
		{
			plik.open(nazwaPliku, ios::out);
			if ( plik.is_open() )
			{
				Pozycja pozycjaOrganizmu;
				plik << this->rozmiarX;
				plik << " ";
				plik << this->rozmiarY << endl;
				for ( list<Organizm*>::iterator it = this->listaInicjatywy.begin(); it != this->listaInicjatywy.end(); it = next(it) )
			    {
			        if ( !(*it)->czyDoZabicia() )
			        {
						pozycjaOrganizmu = *(*it)->getPozycja();
						plik << (*it)->getGatunekOrganizmu();
						plik << " ";
						plik << pozycjaOrganizmu.x;
						plik << " ";
						plik << pozycjaOrganizmu.y;
						plik << " ";
						plik << (*it)->getSila();
						plik << " " << (*it)->getCooldown();
						plik << endl;
			        }
			    }
				plik.close();
				zapisywanieZakonczone = true;
			}
			else
			{
				czyBlad = true;
			}
		}
	}
	if ( this->czySwiatIstnieje() )
	{
		this->rysujGre();
	}
	else
	{
		this->wyswietlMenu();
	}
}

void Swiat::wczytajGre()
{
	system("cls");
	bool wczytywanieZakonczone = false, czyBlad = false;
	int rozmiarX, rozmiarY, polozenieX, polozenieY, sila, cooldownMocySpecjalnej;
	string gatunekOrganizmu, nazwaPliku = "";
	fstream plik;
	cout << " Wczytywanie stanu gry " << endl;
	cout << "Q lub q - wyjœcie z menu wczytywania gry " << endl;
	cout << "Podaj nazwe pliku, ktory chcesz wczytac: ";
	while( ( nazwaPliku != "Q" ) && ( nazwaPliku != "q" ) && ( !wczytywanieZakonczone ))
	{
		if ( czyBlad )
		{
			cout << "Nie udalo sie otworzyc pliku, sprobuj ponownie: ";
		}
		cin >> nazwaPliku;
		if ( ( nazwaPliku != "Q" ) && ( nazwaPliku != "q" ) )
		{
			plik.open(nazwaPliku);
			if ( plik.is_open() )
			{
				if ( this->czySwiatIstnieje() )
				{
					this->zniszczSwiat();
				}
				czyBlad = false;
				plik >> rozmiarX;
				plik >> rozmiarY;
				this->setRozmiar( rozmiarX, rozmiarY );
				this->createZajete();
				this->clearRejestr();
				while( !plik.eof() )
				{
					plik >> gatunekOrganizmu;
					plik >> polozenieX;
					plik >> polozenieY;
					plik >> sila;
					plik >> cooldownMocySpecjalnej;
					this->stworzOrganizm( gatunekOrganizmu, polozenieX, polozenieY, sila, cooldownMocySpecjalnej );
				}
				plik.close();
				this->rysujGre();
				wczytywanieZakonczone = true;
			}
			else
			{
				czyBlad = true;
			}
		}
	}
	if ( this->czySwiatIstnieje() )
	{
		this->rysujGre();
	}
	else
	{
		this->wyswietlMenu();
	}
}

void Swiat::rysujGre()
{
	system("cls");
	this->rysujSwiat();
	this->wykonuj();
}

void Swiat::nowaGra()
{
	system("cls");
	int rozmiarX = 0, rozmiarY = 0;
	cout << "Podaj wymiary planszy" << endl;
	cout << "Podaj szerokosc: ";
	cin >> rozmiarX;
	while( ( !cin.good() ) || ( rozmiarX < 1 ) )
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Podano zla szerokosc!" << endl;
		cout << "Podaj szerokosc: ";
		cin >> rozmiarX;
	}
	cout << "Podaj wysokosc: ";
	cin >> rozmiarY;
	while( ( !cin.good() ) || ( rozmiarY < 1 ) )
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Podano zla wysokosc!" << endl;
		cout << "Podaj wysokosc: ";
		cin >> rozmiarY;
	}
	if ( this->czySwiatIstnieje() )
	{
		this->zniszczSwiat();
	}
	this->stworzSwiat( rozmiarX, rozmiarY );
	
}

void Swiat::stworzSwiat(int rozmiarX, int rozmiarY)
{
	system("cls");
	this->setRozmiar( rozmiarX, rozmiarY);
	this->createZajete();
	this->zapelnijSwiat();
	this->rysujSwiat();
	this->wykonuj();
}

void Swiat::wykonuj()
{
	system("cls");
	this->rysujSwiat();
	char wybor = ' ';
	while(true)
	{
		wybor = _getch();
		if( !(this->wykonajOpcje(wybor)) )
		{
			this->wykonajRunde();
		}
		/*if ( wybor == 's' || wybor == 'S' )
		{
			this->zapiszGre();
		}*/
		
	}
}

void Swiat::zapelnijSwiat()
{
	bool czyCzlowiekNaPlanszy = false;
	bool czySymulacja = true;
	int kreatorOrganizmu;
	for ( int polozenieY = 0; polozenieY < this->rozmiarY; ++polozenieY )
	{
		for ( int polozenieX = 0 ; polozenieX < this->rozmiarX; ++polozenieX )
		{
			kreatorOrganizmu = rand() % 50 + 1;
			cout << kreatorOrganizmu << endl;
			if ( kreatorOrganizmu > 25 )
			{
				this->stworzOrganizm(kreatorOrganizmu, polozenieX, polozenieY);
			}
			else if ( !czySymulacja && !czyCzlowiekNaPlanszy )
			{
				// this->dodajOrganizmDoSwiata( new Czlowiek( this, Pozycja( polozenieX, polozenieY ) ) );
				czyCzlowiekNaPlanszy = true;
			}
			
		}
	}
	//TODO remove debug comments
	//this->dodajOrganizmDoSwiata(new Antylopa(this ,Pozycja(0,0)));
	//this->dodajOrganizmDoSwiata(new Antylopa(this ,Pozycja(0,1)));
	//this->dodajOrganizmDoSwiata(new BarszczSosnowskiego(this ,Pozycja(1,1)));
	//this->dodajOrganizmDoSwiata(new BarszczSosnowskiego(this ,Pozycja(0,2)));
	//this->dodajOrganizmDoSwiata(new BarszczSosnowskiego(this ,Pozycja(6,8)));
}

void Swiat::stworzCzlowieka(int polozenieX, int polozenieY)
{
	//TODO uncomment adding Human
	// this->dodajOrganizmDoSwiata( new Czlowiek( this, Pozycja( polozenieX, polozenieY ) ) );
}

void Swiat::stworzCzlowieka()
{
	bool czyCzlowiekNaPlanszy = false;
	for ( int polozenieY = 0; polozenieY < this->rozmiarY; ++polozenieY )
	{
		for ( int polozenieX = 0 ; polozenieX < this->rozmiarX; ++polozenieX )
		{
			if ( !czyCzlowiekNaPlanszy && !this->sprawdzCzyPoleOkupowane(Pozycja( polozenieX, polozenieY ) ) )
			{
				//TODO uncomment adding Human
				// this->stworzCzlowieka( polozenieX, polozenieY );
				czyCzlowiekNaPlanszy = true;
			}
		}
	}
}

void Swiat::stworzOrganizm(string gatunekOrganizmu, int polozenieX, int polozenieY, int sila, int cooldownMocySpecjalnej=-1)
{
	Pozycja pozycjaOrganizmu( polozenieX, polozenieY );
	if ( gatunekOrganizmu == "Antylopa")
	{
		this->dodajOrganizmDoSwiata( new Antylopa(this, pozycjaOrganizmu, sila ) );
	}
	if ( gatunekOrganizmu == "BarszczSosnowskiego")
	{
		this->dodajOrganizmDoSwiata( new BarszczSosnowskiego(this, pozycjaOrganizmu ) );
	}
	if ( gatunekOrganizmu == "Guarana")
	{
		this->dodajOrganizmDoSwiata( new Guarana(this, pozycjaOrganizmu ) );
	}
	if ( gatunekOrganizmu == "Lis")
	{
		this->dodajOrganizmDoSwiata( new Lis(this, pozycjaOrganizmu, sila ) );
	}
	if ( gatunekOrganizmu == "Mlecz")
	{
		this->dodajOrganizmDoSwiata( new Mlecz(this, pozycjaOrganizmu ) );
	}
	if ( gatunekOrganizmu == "Owca")
	{
		this->dodajOrganizmDoSwiata( new Owca(this, pozycjaOrganizmu, sila ) );
	}
	if ( gatunekOrganizmu == "Trawa")
	{
		this->dodajOrganizmDoSwiata( new Trawa(this, pozycjaOrganizmu ) );
	}
	if ( gatunekOrganizmu == "Wilcze Jagody")
	{
		this->dodajOrganizmDoSwiata( new WilczeJagody(this, pozycjaOrganizmu ) );
	}
	if ( gatunekOrganizmu == "Wilk")
	{
		this->dodajOrganizmDoSwiata( new Wilk(this, pozycjaOrganizmu, sila ) );
	}
	if ( gatunekOrganizmu == "Zolw")
	{
		this->dodajOrganizmDoSwiata( new Zolw(this, pozycjaOrganizmu, sila ) );
	}
	if ( gatunekOrganizmu == "Czlowiek")
	{
		//TODO uncomment Human constructing
		//this->dodajOrganizmDoSwiata( new Czlowiek(this, pozycjaOrganizmu, sila, cooldownMocySpecjalnej ) );
	}


}

void Swiat::stworzOrganizm(int kreatorOrganizmu, int polozenieX, int polozenieY)
{
	if ( 50 - kreatorOrganizmu < 2) // 2
	{
		this->dodajOrganizmDoSwiata( new Antylopa( this, Pozycja( polozenieX, polozenieY ) ) );
	}
	else if ( 50 - kreatorOrganizmu < 4 ) // 2
	{
		this->dodajOrganizmDoSwiata( new BarszczSosnowskiego( this, Pozycja( polozenieX, polozenieY ) ) );
	}
	else if ( 50 - kreatorOrganizmu < 7 ) // 3
	{
		this->dodajOrganizmDoSwiata( new Guarana( this, Pozycja( polozenieX, polozenieY ) ) );
	}
	else if ( 50 - kreatorOrganizmu < 9 ) // 2
	{
		this->dodajOrganizmDoSwiata( new Lis( this, Pozycja( polozenieX, polozenieY ) ) );
	}
	else if ( 50 - kreatorOrganizmu < 10 ) // 1
	{
		this->dodajOrganizmDoSwiata( new Mlecz( this, Pozycja( polozenieX, polozenieY ) ) );
	}
	else if ( 50 - kreatorOrganizmu < 14 ) // 4
	{
		this->dodajOrganizmDoSwiata( new Owca( this, Pozycja( polozenieX, polozenieY ) ) );
	}
	else if ( 50 - kreatorOrganizmu < 18 ) // 4
	{
		this->dodajOrganizmDoSwiata( new Trawa( this, Pozycja( polozenieX, polozenieY ) ) );
	}
	else if ( 50 - kreatorOrganizmu < 20 ) // 2
	{
		this->dodajOrganizmDoSwiata( new WilczeJagody( this, Pozycja( polozenieX, polozenieY ) ) );
	}
	else if ( 50 - kreatorOrganizmu < 23 ) // 3
	{
		this->dodajOrganizmDoSwiata( new Wilk( this, Pozycja( polozenieX, polozenieY ) ) );
	}
	else if ( 50 - kreatorOrganizmu < 25 ) // 2
	{
		this->dodajOrganizmDoSwiata( new Zolw( this, Pozycja( polozenieX, polozenieY ) ) );
	}
}

void Swiat::wyswietlMenu()
{
	//system("cls");
	cout << "Wybierz opcje: " << endl;
	cout << "N - Nowa gra " << endl;
	cout << "L - Wczytaj gre " << endl;
	cout << "Q - Wyjdz z gry " << endl;
	
}

void Swiat::wybierzOpcje()
{
	char wybor = ' ';
	while ( ( wybor != 'q' ) && ( wybor != 'Q' ) )
	{
		wybor = _getch();
		this->wykonajOpcje(wybor);
	}
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
	Organizm* organizmNaPolu = this->getOrganizmNaPlanszy(pozycjaOrganizmu);
    if ( organizm == organizmNaPolu )
    {
	    this->getZajete()[pozycjaOrganizmu.y][pozycjaOrganizmu.x] = nullptr;
		this->rysujNaPolu(pozycjaOrganizmu, ' ');
    }
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
    gotoxy(2*pozycja.x+5, pozycja.y+4);
    _putch(znak);
}



void Swiat::rysujPlansze()
{
	gotoxy(0,2);
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
    cout << "R - umiejetnosc specjalna";
    gotoxy(legendaX, legendaY++);
    cout << "Spacja - zatwierdzenie ruchu";
    gotoxy(legendaX, legendaY++);
    cout << "S - zapisanie gry";
    gotoxy(legendaX, legendaY);
    cout << "W - wczytanie gry";

}

void Swiat::rysujPanelGracza( Pozycja pozycjaGracza, int cooldownMocySpecjalnej, string akcja)
{
	int panelGraczaX = 2*this->rozmiarX + 7;
	int panelGraczaY = 19;
	gotoxy( panelGraczaX, panelGraczaY++ );
	cout << "Pozycja gracza: (" << pozycjaGracza.x << "," << pozycjaGracza.y << ") ";
	cout << "Odnowienie umiejetnosci za " << cooldownMocySpecjalnej << " tur";
	gotoxy( panelGraczaX, panelGraczaY );
	cout << "Wybrana akcja: " << akcja << endl; 
}

void Swiat::rysujRejestr()
{
    int rejestrX = 2;
    int rejestrY = this->rozmiarY + 6;
	if ( rejestrY < 21 )
	{
		rejestrY = 21;
	}
    for (int i = 0; i < sizeof(this->rejestr)/sizeof(this->rejestr[0]); ++i)
    {
        gotoxy(rejestrX, rejestrY++);
        printf("%-80s", this->rejestr[i].c_str());
        //printf("%s", this->rejestr[i].c_str());
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
	this->rysujNaglowek();
    this->rysujPlansze();
    for (Organizm* i: listaInicjatywy)
    {
        i->rysuj();
    }
    this->rysujLegende();
    this->rysujRejestr();
}

void Swiat::wykonajRunde()
{
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
    //printf("%3zd", this->listaInicjatywy.size());
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

void Swiat::setRozmiar(int x, int y)
{
	this->rozmiarX = x;
    this->rozmiarY = y;
}

