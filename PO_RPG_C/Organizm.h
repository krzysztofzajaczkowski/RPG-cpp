#ifndef __ORGANISM_H
#define __ORGANISM_H
#pragma once
#include <iostream>
#include <string>

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
	char znak;
	Pozycja* pozycja;
	Swiat* swiat;
	static int liczbaStworzonychOrganizmow;
	int id;
	int elementListyInicjatywy;
	int krok = 1;
public:
	Organizm(Swiat* swiat, Pozycja pozycja);
	void setSila(int sila);
	void setElementListyInicjatywy(int numerElementu);
	void gin();
	void usunOrganizmZPlanszy();
	void setZnak(char znak);
	char getZnak();
	virtual int losujKierunek();
	int getRozmiarSwiataX();
	virtual void reagujNaKolizje(Organizm* napastnik) = 0;
	int getRozmiarSwiataY();
	Pozycja computeNowaPozycja(int kierunek);
	int getSila();
	void setInicjatywa(int inicjatywa);
	int getInicjatywa();
	int sprawdzCzyPoleOkupowane(Pozycja pozycja);
	virtual int czyKolizja(Pozycja docelowaPozycja);
	void dodajOrganizmNaPlansze();
	void ustawNowaPozycje(Pozycja pozycja);
	void dodajKomunikatWRejestrzeSwiata(string komunikat);
	virtual bool czyMoznaWykonacRuch(int kierunek);
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
	virtual void rozmnozSie(Organizm* partner) = 0;
	int getId();
};
#endif
