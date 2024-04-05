//---------------------------------------------------------------------------

#pragma hdrstop
#include <iostream>
#include "IRSnifferCirpark.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include <fstream>
#include <iomanip>


IRSnifferCirpark::IRSnifferCirpark()
{

}

bool IRSnifferCirpark::ParametrerLeServeurCirpark(std::string adresseIP, unsigned short port){

	adresseIPServeurCirpark = adresseIP;
	portServeurCirpark = port;
	bool retour = clientCirpark.OuvrirLaSocketDeCommunication(adresseIPServeurCirpark, portServeurCirpark);
 	return retour;
}

bool IRSnifferCirpark::DetecterUnCapteur(unsigned short adresseCapteur){

	char requete[4];
	char reponse[20];
    unsigned char cle[2] = {0xA3, 0xC5};
	unsigned char requete_chiffre[4];
	unsigned char rep_dechiffre[4];






	requete[0] = adresseCapteur >> 8;
	requete[1] = (char)adresseCapteur & 0xFF;
	requete[2] = 0x05;
	requete[3] = (requete[0] + requete[1] + requete[2])%256;


	for(int i = 0; i < 4 ; i++) requete_chiffre[i] = requete[i] ^ cle[i%2];


	clientCirpark.EnvoyerDesOctets(requete_chiffre,4);


	int nbOctet = clientCirpark.RecevoirDesOctets((unsigned char *)reponse,20,20);

   	for(int i = 0; i < 4 ; i++) rep_dechiffre[i] = reponse[i] ^ cle[i%2];




	if(nbOctet > 1) return 1;
	return 0;

}





int IRSnifferCirpark::DetecterLesCapteurs(unsigned short adresseCapteurDepart, unsigned short adresseCapteurFin){

	nbCapteurs = 0;

	for (int i=0; i < NBCAPTMAX; i++) {
		tabCapteurs[i] = 0;
	}

	unsigned short tot = adresseCapteurFin - adresseCapteurDepart;

	for (int adr = 0; adr < tot; adr++) {
		bool rep = DetecterUnCapteur((adresseCapteurDepart + (unsigned short)adr));
		if (rep == 1){
			tabCapteurs[nbCapteurs]=(unsigned short)adr+adresseCapteurDepart;
			nbCapteurs++;
		}
	}

	return nbCapteurs;

}




void IRSnifferCirpark::EnregistrerSous(std::string nomFichier){

	std::ofstream Fichier;
	Fichier.open(nomFichier);
	for (int i = 0; i < nbCapteurs; i++) {
		if(Fichier.is_open()) Fichier << std::uppercase << std::hex << std::setw(4) << std::setfill('0') << tabCapteurs[i] << std::endl;
		else {std::cout<< "Erreur ouverture du fichier " << std::endl; break;}
  }
	Fichier.close();
}



