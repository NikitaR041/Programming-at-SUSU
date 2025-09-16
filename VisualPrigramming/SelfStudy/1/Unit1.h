//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TРомановНикитаМаксимович : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TButton *Button1;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TButton *Button2;
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TРомановНикитаМаксимович(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TРомановНикитаМаксимович *РомановНикитаМаксимович;
//---------------------------------------------------------------------------
#endif
