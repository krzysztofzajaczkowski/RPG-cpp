#include <iostream>
#include <conio.h>
#include "Swiat.h"
#include "Organism.h"

using namespace std;

    Swiat::Swiat(int sizeX, int sizeY) : sizeX(sizeX), sizeY(sizeY) {}

    void Swiat::drawTitle()
    {
        cout << "Krzysztof Zajaczkowski 175489" << endl;
    }


    void Swiat::drawBoard()
    {
        cout << (char)201;
        for ( int i = 0 ; i < sizeX ; ++i )
        {
            cout << (char)205;
        }
        cout << (char)187 << endl;
        for ( int i = 0 ; i < sizeY ; ++i )
        {
            cout << (char)186;
            for ( int j = 0; j < sizeX ; ++j )
            {
                cout << " ";
            }
            cout << (char)186 << endl;
        }
        cout << (char)200;
        for ( int i = 0 ; i < sizeX ; ++i )
        {
            cout << (char)205;
        }
        cout << (char)188 << endl;
    }

    void Swiat::drawLegend()
    {
        
    }

    void Swiat::drawCombatLog()
    {
        
    }

    void Swiat::drawWorld()
    {
        // draw world with legend and combat log
        //drawBoard();
        //drawLegend();
        //drawCombatLog
    }

    void Swiat::performRound()
    {
        /*
         * Iterate through organisms, perform their action
         * If multiplication happened:
         *      append animal
         */
    }

    int Swiat::appendOrganism(Organism &organism)
    {
        /*
         * Append organism to list
         */
        return true;
    }

    int Swiat::sortQueue()
    {
        /*
         * Sort organismQueue by initiative / age
         */
        return true;
    }


