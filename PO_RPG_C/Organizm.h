#ifndef __ORGANISM_H
#define __ORGANISM_H
#pragma once
#include <iostream>

class Swiat;

struct Pozycja
{
	Pozycja(int x, int y): x(x), y(y) {};
	int x;
	int y;
};

class Organizm
{
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
	virtual int losujKierunek();
	int getRozmiarSwiataX();
	int getRozmiarSwiataY();
	Pozycja computeNowaPozycja(int kierunek);
	virtual int czyKolizja(int kierunek);
	virtual bool czyMoznaWykonacRuch(int kierunek);
	virtual Pozycja* getPozycja();
	virtual Swiat* getSwiat();
	virtual int kolizja() = 0;
	virtual void akcja() = 0;
	virtual void rysuj() = 0;
	virtual void wykonajRuch(int kierunek) = 0;
};
#endif
