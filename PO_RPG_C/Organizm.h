#ifndef __ORGANISM_H
#define __ORGANISM_H
#pragma once
#include <iostream>
#include <string>

using namespace std;

class Swiat;

struct Pozycja
{
	Pozycja(int x=-1, int y=-1): x(x), y(y) {};
	int x;
	int y;
	bool czyPrawidlowa()
	{
		return (this->x >= 0) && (this->y >= 0);
	}

	bool operator!=(Pozycja right)
	{
		return ( this->x != right.x ) || ( this->y != right.y );
	}
};

class Organizm
{
private:
	string typOrganizmu;
	string gatunekOrganizmu;
protected:
	int sila;
	int inicjatywa;
	char znak;
	Pozycja* pozycja;
	Swiat* swiat;
	static int liczbaStworzonychOrganizmow;
	bool operator==(Organizm* prawy);
	int id;
	int elementListyInicjatywy;
	int krok;
	int doZabicia = 0;
public:
	Organizm(Swiat* swiat, Pozycja pozycja);
	Organizm(Swiat* swiat, Pozycja pozycja, int krok);
	void setSila(int sila);
	void setDoZabicia();
	int czyDoZabicia();
	void setElementListyInicjatywy(int numerElementu);
	void gin();
	void usunOrganizmZPlanszy();
	void setZnak(char znak);
	char getZnak();
	virtual int losujKierunek();
	int getRozmiarSwiataX();
	virtual void reagujNaKolizje(Organizm* napastnik) = 0;
	int getRozmiarSwiataY();
	Pozycja computeNowaPozycja(int kierunek, int krok = 1);
	int getSila();
	void setInicjatywa(int inicjatywa);
	int getInicjatywa();
	int sprawdzCzyPoleOkupowane(Pozycja pozycja);
	virtual int czyKolizja(Pozycja docelowaPozycja);
	void dodajOrganizmNaPlansze();
	void ustawNowaPozycje(Pozycja pozycja);
	void dodajKomunikatWRejestrzeSwiata(string komunikat);
	int getKrok();
	virtual bool czyMoznaWykonacRuch(int kierunek, int krok = 1);
	virtual Pozycja* getPozycja();
	virtual Swiat* getSwiat();
	string getTypOrganizmu();
	void setTypOrganizmu(string typOrganizmu);
	string getGatunekOrganizmu();
	void setGatunekOrganizmu(string rodzajOrganizmu);
	virtual void kolizja(Pozycja docelowaPozycja) = 0;
	virtual void akcja() = 0;
	void rysuj();
	void wykonajRuch(Pozycja pozycja);
	virtual Pozycja* znajdzSasiednieWolnePole();
	void zwiekszSile(int bonus);
	void setKrok(int krok);
	virtual void rozmnozSie(Organizm* partner) = 0;
	int getId();
};
#endif
