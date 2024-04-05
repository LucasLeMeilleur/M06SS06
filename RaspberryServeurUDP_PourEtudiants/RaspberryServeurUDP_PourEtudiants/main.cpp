#include <iostream>
#include "IRServeurUDP.h"

using namespace std;

int main()
{
    char Reponse[1000];
	IRServeurUDP serveur;
	serveur.OuvrirLaSocketDEcoute(10111)
    serveur.RecevoirDesOctets(Reponse, 1000);
    std::cout << Reponse;
	return 0;
}