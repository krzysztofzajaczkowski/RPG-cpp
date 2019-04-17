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
	//TODO tablica polaPlanszy bool -> Organizm
	/*
	 * Wypierdoli� booleany i zrobi� z tego tablic� Organizm�w
	 * CzyKolizja zwraca null je�li puste, Organizm je�li zaj�te
	 * TRAWA MA ZAWSZE ID 0, WIEC CZYKOLIZJA SPRAWDZA CZY ORGANIZM MA ID WIEKSZE OD 0, JE�LI NIE, TO JEST TO TRAWA I JEST PUSTE
	 */
public:
	Swiat();
	void setZajete();
	void zniszczOrganizm(Organizm* organizm);
	void usunOrganizmZPlanszy(Organizm* organizm);
	Organizm*** getZajete();
	void dodajOrganizmNaPlansze(Organizm* organizm);
	int sprawdzCzyPoleOkupowane(Pozycja pozycja);
	void setRejestr();
	void dodajRejestr(string rejestr);
	int getRozmiarX();
	int getRozmiarY();
	void rysujNaglowek();
	void rysujPlansze();
	void rysujLegende();
	void rysujRejestrWalk();
	void rysujSwiat();
	int dodajOrganizm(Organizm* organizm);
	int sortujListeInicjatywy();
	void wykonajRunde();
	void setRozmiar();
};
#endif
