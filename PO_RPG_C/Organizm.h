#ifndef __ORGANISM_H
#define __ORGANISM_H
#pragma once
#include <iostream>
#include <string>
#include "Zwierze.h"

using namespace std;

class Swiat;

struct Pozycja
{
	Pozycja(int x, int y): x(x), y(y) {};
	int x;
	int y;
};

class Organizm
{
private:
	string typOrganizmu;
	string gatunekOrganizmu;
protected:
	int sila;
	int inicjatywa;
	Pozycja* pozycja;
	Swiat* swiat;
	static int liczbaStworzonychOrganizmow;
	int id;
	int elementListyInicjatywy;
	int krok = 1;
public:
	Organizm(Swiat* swiat, Pozycja pozycja);
	void setElementListyInicjatywy(int numerElementu);
	void gin();
	void usunOrganizmZPlanszy();
	virtual int losujKierunek();
	int getRozmiarSwiataX();
	int getRozmiarSwiataY();
	Pozycja computeNowaPozycja(int kierunek);
	int getSila();
	virtual void reagujNaKolizje(Organizm* napastnik);
	int sprawdzCzyPoleOkupowane(Pozycja pozycja);
	virtual int czyKolizja(Pozycja docelowaPozycja);
	void dodajKomunikatWRejestrzeSwiata(string komunikat);
	virtual bool czyMoznaWykonacRuch(int kierunek);
	virtual Pozycja* getPozycja();
	virtual Swiat* getSwiat();
	string getTypOrganizmu();
	void setTypOrganizmu(string typOrganizmu);
	string getGatunekOrganizmu();
	void setGatunekOrganizmu(string rodzajOrganizmu);
	virtual void kolizja(Pozycja pozycja) = 0;
	virtual void akcja() = 0;
	virtual void rysuj() = 0;
	virtual void wykonajRuch(Pozycja pozycja) = 0;
	virtual Pozycja* znajdzWolnePoleNaDziecko();
	virtual void rozmnozSie(Organizm* partner) = 0;
};
#endif
