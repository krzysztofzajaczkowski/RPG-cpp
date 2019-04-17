#ifndef __ORGANISM_H
#define __ORGANISM_H
#pragma once
#include <iostream>

class Swiat;

struct pos
{
	int x;
	int y;
};

class Organizm
{
protected:
	int strength;
	int initiative;
	// Point position; Implement Point structure (x,y)
	Swiat* world;
	static int numberOfInstantiatedOrganisms;
	int id;
public:
	virtual int action() = 0;
	virtual int collision() = 0;
	virtual void draw() = 0;
};
#endif
