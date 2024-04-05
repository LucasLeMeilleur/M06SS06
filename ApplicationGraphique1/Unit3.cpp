//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;


  using namespace std;



  

//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TForm3::Button1Click(TObject *Sender)
{
	Timer1->Enabled = false;
	Form3->Hide();
	Form1->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Addr1Click(TObject *Sender)
{
	Form1->ComboCapteur->Text = Addr1->Caption;
	Form1->BoutonConfigClick(this);
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Addr2Click(TObject *Sender)
{
   Form1->ComboCapteur->Text = Addr2->Caption;
   Form1->BoutonConfigClick(this);
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Addr3Click(TObject *Sender)
{
Form1->ComboCapteur->Text = Addr3->Caption;
Form1->BoutonConfigClick(this);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Addr4Click(TObject *Sender)
{
Form1->ComboCapteur->Text = Addr4->Caption;
Form1->BoutonConfigClick(this);
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Timer1Timer(TObject *Sender)
{
	String truc = "";
	LabelDate->Caption = Date()+Time();
	Form1->sniffer.EnvoyerRequeteCapteur(Form1->ChaineHexaVersInt(AnsiString(Addr1->Caption).c_str(),4), 0x10);
	unsigned char * reponse=Form1->sniffer.Reponse();
	if (reponse[2] == 1) {
		Image1->Visible = true;
		Shape1->Brush->Color = clRed;
	}
	else{
		Image1->Visible = false;
        Shape1->Brush->Color = clLime;

	 }

	Form1->sniffer.EnvoyerRequeteCapteur(Form1->ChaineHexaVersInt(AnsiString(Addr2->Caption).c_str(),4), 0x10);
	reponse=Form1->sniffer.Reponse();
	if (reponse[2] == 1) {
		Image2->Visible = true;
		Shape3->Brush->Color = clRed;
	}
	else{
		Image2->Visible = false;
        Shape3->Brush->Color = clLime;

	 }


	Form1->sniffer.EnvoyerRequeteCapteur(Form1->ChaineHexaVersInt(AnsiString(Addr3->Caption).c_str(),4), 0x10);
	reponse=Form1->sniffer.Reponse();
	if (reponse[2] == 1) {
		Image3->Visible = true;
		Shape5->Brush->Color = clRed;
	}
	else{
		Image3->Visible = false;
		Shape5->Brush->Color = clLime;

	 }


	Form1->sniffer.EnvoyerRequeteCapteur(Form1->ChaineHexaVersInt(AnsiString(Addr4->Caption).c_str(),4), 0x10);
	reponse=Form1->sniffer.Reponse();
	if (reponse[2] == 1) {
		Image4->Visible = true;
		Shape7->Brush->Color = clRed;
	}
	else{
		Image4->Visible = false;
        Shape7->Brush->Color = clLime;

	 }




}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormClose(TObject *Sender, TCloseAction &Action)
{
	Form1->Close();
}
//---------------------------------------------------------------------------
