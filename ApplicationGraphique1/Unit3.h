//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// Composants g�r�s par l'EDI
	TShape *Shape1;
	TShape *Shape2;
	TShape *Shape3;
	TShape *Shape4;
	TShape *Shape5;
	TShape *Shape6;
	TShape *Shape7;
	TShape *Shape8;
	TLabel *LabelDate;
	TShape *Shape9;
	TShape *Shape10;
	TShape *Shape11;
	TShape *Shape12;
	TImage *Image1;
	TImage *Image2;
	TImage *Image3;
	TImage *Image4;
	TButton *Button1;
	TLabel *Addr1;
	TLabel *Addr2;
	TLabel *Addr3;
	TLabel *Addr4;
	TTimer *Timer1;
	TLabel *Label1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Addr1Click(TObject *Sender);
	void __fastcall Addr2Click(TObject *Sender);
	void __fastcall Addr3Click(TObject *Sender);
	void __fastcall Addr4Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);


private:	// D�clarations utilisateur
public:		// D�clarations utilisateur
	__fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
