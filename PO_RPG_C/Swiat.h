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
	Organizm*** polaPlanszy;
public:
	Swiat();
	void createZajete();
	void zniszczOrganizm(Organizm* organizm);
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
	void rysujRejestr();
	void rysujSwiat();
	int dodajOrganizm(Organizm* organizm);
	int sortujListeInicjatywy();
	void wykonajRunde();
	void setRozmiar();
};
#endif
