#ifndef __WORLD_H
#define __WORLD_H
#pragma once
#include <iostream>
#include <list>

class Organism;

using namespace std;

class Swiat
{
protected:
	list<Organism*> organismQueue;
	int sizeX, sizeY;
public:
	Swiat(int sizeX, int sizeY);
	void drawTitle();
	void drawBoard();
	void drawLegend();
	void drawCombatLog();
	void drawWorld();
	int appendOrganism(Organism &organism);
	int sortQueue();
	void performRound();
};
#endif
