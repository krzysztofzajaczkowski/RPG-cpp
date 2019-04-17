// PO_RPG_C.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <typeinfo>
#include <windows.h>
#include "Swiat.h"
#include "Organizm.h"
#include "Roslina.h"
#include "Zwierze.h"
#include "Trawa.h"
#include "Guarana.h"
#include "Mlecz.h"
#include "WilczeJagody.h"

using namespace std;


/*
 *COORD coord={0,0}; // this is global variable
                                    center of axis is set to the top left cornor of the screen
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
 */

int main()
{
    Swiat* swiat = new Swiat;
    system("cls");
    swiat->rysujPlansze();

    
    Pozycja* pozycja = new Pozycja(1,1);
    Trawa trawa(swiat, *pozycja);
    pozycja->x = pozycja->y = 2;
    Guarana guarana(swiat, *pozycja);
    pozycja->x = pozycja->y = 3;
    Mlecz mlecz(swiat, *pozycja);
    pozycja->x = pozycja->y = 4;
    WilczeJagody wilczeJagody(swiat, *pozycja);
    swiat->rysujSwiat();

    /*
     *system("cls");
    swiat.rysujRejestr();
    swiat.dodajKomunikatWRejestrze("Komunikat #1");
    cout << endl;
    swiat.rysujRejestr();
    swiat.dodajKomunikatWRejestrze("Komunikat #2");
    cout << endl;
    swiat.rysujRejestr();
    swiat.dodajKomunikatWRejestrze("Komunikat #3");
    cout << endl;
    swiat.rysujRejestr();
    swiat.dodajKomunikatWRejestrze("Komunikat #4");
    cout << endl;
    swiat.rysujRejestr();
    swiat.dodajKomunikatWRejestrze("Komunikat #5");
    cout << endl;
    swiat.rysujRejestr();
    swiat.dodajKomunikatWRejestrze("Komunikat #6");
    cout << endl;
    swiat.rysujRejestr();

     *
     */
    

    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
