//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Thread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important : Les m�thodes et les propri�t�s des objets de la VCL peuvent seulement �tre
//   utilis�es dans une m�thode appel�e avec Synchronize, par exemple :
//
//      Synchronize(&UpdateCaption);
//
//   o� UpdateCaption pourrait ressembler � :
//
//      void __fastcall ThRecherche::UpdateCaption()
//      {
//        Form1->Caption = "Mis � jour dans un thread";
//      }
//---------------------------------------------------------------------------

__fastcall ThRecherche::ThRecherche(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall ThRecherche::Execute()
{
	//---- Placer le code du thread ici ----
    Form1->monSniffer.DetecterLesCapteurs(adresseDeb,adresseFin);
	Form1->Label1->Caption=(String)Form1->monSniffer.NombreCapteurTrouve()+" capteurs d�tect�s";
	Form1->monSniffer.EnregistrerSous("fichierCapteurs.txt");
	if(Form1->monSniffer.NombreCapteurTrouve())
	{	std::ifstream f; f.open("fichierCapteurs.txt");
		char adresseC[5];
		for(int i=0;i<Form1->monSniffer.NombreCapteurTrouve();i++)
		{	f>>adresseC;
			Form1->ComboBox1->AddItem(adresseC,this);
			if(i==0) Form3->Label1->Caption=adresseC;
			if(i==1) Form3->Label2->Caption=adresseC;
			if(i==2) Form3->Label3->Caption=adresseC;
			if(i==3) Form3->Label4->Caption=adresseC;
		}
	Form1->ComboBox1->Text=Form3->Label1->Caption;
	f.close();
	if(Form1->Label1->Caption!="... capteurs d�tect�s")Form1->Button3->Enabled=true;
}

}
//---------------------------------------------------------------------------
