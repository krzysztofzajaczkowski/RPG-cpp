#ifndef __WORLD_H
#define __WORLD_H
#pragma once
#include <iostream>
#include <list>

struct Pozycja;

class Organizm;

using namespace std;

class Swiat
{
protected:
	list<Organizm*> listaInicjatywy;
	int rozmiarX, rozmiarY;
	string rejestr[5];
	Organizm*** polaPlanszy = nullptr;
public:
	Swiat();
	bool wykonajOpcje(char wybor);
	bool czySwiatIstnieje();
	void menu();
	void zniszczSwiat();
	void zapiszGre();
	void wczytajGre();
	void rysujGre();
	void nowaGra();
	void stworzSwiat(int rozmiarX, int rozmiarY);
	void wykonuj();
	void zapelnijSwiat();
	void stworzCzlowieka(int polozenieX, int polozenieY);
	void stworzCzlowieka();
	void stworzOrganizm(string gatunekOrganizmu, int polozenieX, int polozenieY, int sila, int cooldownMocySpecjalnej);
	void stworzOrganizm(int kreatorOrganizmu, int polozenieX, int polozenieY);
	void wyswietlMenu();
	void wybierzOpcje();
	void createZajete();
	list<Organizm*>::iterator zniszczOrganizm(list<Organizm*>::iterator iterator);
	void usunOrganizmZPlanszy(Organizm* organizm);
	Organizm*** getZajete();
	void dodajOrganizmNaPlansze(Organizm* organizm);
	int sprawdzCzyPoleOkupowane(Pozycja pozycja);
	Organizm* getOrganizmNaPlanszy(Pozycja pozycja);
	void clearRejestr();
	void dodajKomunikatWRejestrze(string komunikat);
	int getRozmiarX();
	int getRozmiarY();
	void rysujNaglowek();
	void rysujPlansze();
	void rysujLegende();
	void rysujPanelGracza(Pozycja pozycjaGracza, int cooldownMocySpecjalnej, string akcja);
	void rysujRejestr();
	void rysujSwiat();
	int dodajOrganizmDoSwiata(Organizm* organizm);
	void sortujListeInicjatywy();
	void wykonajRunde();
	void setRozmiar(int x, int y);
	void rysujNaPolu(Pozycja pozycja, char znak);
};
#endif
