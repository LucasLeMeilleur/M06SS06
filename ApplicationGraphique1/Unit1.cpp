//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "ThreadClass.h"

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

#include <fstream>


#include "Unit3.h"


#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <stdio.h>
#include <iostream>
#include <iomanip>

using namespace std;
std::string TForm1::IntVersChaineHexa(unsigned int nombre, int nbCar)//(65535,4)->"FFFF"   (10,4)->"000A"   (10,2)->"0A"
{	char chaineHexa[9];
	for(int i=0; i<nbCar; i++)
	{	int quartet=(nombre>>(4*((7-(8-nbCar))-i)))&0xf;
		if(quartet>=10)
		{	chaineHexa[i]='A'-10+quartet;
		}
		else
		{	chaineHexa[i]='0'+quartet;
		}
	}
	chaineHexa[nbCar]=0;
	return chaineHexa;
}


unsigned int TForm1::ChaineHexaVersInt(char *chaineHexa, int nbCar)   //("FFFF",4)->65535   ("ffff",4)->65535
{	int nombre=0,j;
	char caractere;
	for(j=0;j<nbCar;j++)
	{ 	caractere=chaineHexa[j];
		if(caractere>='0' && caractere<='9')
		{ 	 nombre=nombre+((caractere-'0')<<(4*(nbCar-j-1)));
		}
		else
		{   char a;
			if(caractere>='a') a='a';
			else a='A';
			nombre=nombre+((caractere-a+10)<<(4*(nbCar-j-1)));
		}
	}
	return nombre;
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	sniffer.ParametrerLeServeurCirpark(AnsiString(Form1->InputIp->Text).c_str(),10001);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BoutonRechClick(TObject *Sender)
{
	 maThread = new ThRecherche(false);



}
//---------------------------------------------------------------------------

void __fastcall TForm1::BoutonConfigClick(TObject *Sender)
{
	Form3->Enabled = true;
	ChaineHexaVersInt(AnsiString(ComboCapteur->Text).c_str(),4);
	sniffer.LireConfigurationCapteur(ChaineHexaVersInt(AnsiString(ComboCapteur->Text).c_str(),4));
	Label14->Caption=sniffer.Mode().c_str();
	if (sniffer.Etat() == 1) {
		Label21->Caption = "Occupé" + (String)sniffer.Etat();
        Shape1->Brush->Color = clRed;
	}
	else {
		Label21->Caption = "Libre";
        Shape1->Brush->Color = clGreen;
    }


}
//---------------------------------------------------------------------------



void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
	Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	if(TrackBar1->Position<160)donnee=0x08;
	else if(TrackBar1->Position<180)donnee=0x09;
	else if(TrackBar1->Position<190)donnee=0x0A;
	else if(TrackBar1->Position<210)donnee=0x0B;
	else if(TrackBar1->Position<230)donnee=0x0C;
	else if(TrackBar1->Position<250)donnee=0x0D;
	else if(TrackBar1->Position<270)donnee=0x0E;
	else if(TrackBar1->Position<280)donnee=0x0F;
	else if(TrackBar1->Position<300)donnee=0x10;
	else if(TrackBar1->Position<320)donnee=0x11;
	else if(TrackBar1->Position<340)donnee=0x12;
	else if(TrackBar1->Position<360)donnee=0x13;
	else if(TrackBar1->Position<380)donnee=0x14;
	else if(TrackBar1->Position<400)donnee=0x15;
	else donnee=0x16;

	Timer1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Shape4ContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled)

{
	sniffer;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{

    Form1->Hide();
	Form3->Show();

	Form3->Timer1->Enabled = true;


}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
	sniffer.EnvoyerRequeteCapteur(ChaineHexaVersInt(AnsiString(ComboCapteur->Text).c_str()),0x19);
}
//---------------------------------------------------------------------------

