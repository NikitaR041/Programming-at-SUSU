//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TEdit *Edit1;
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N11;
	TMenuItem *MouseandPaintBox1;
	TMenuItem *imerandPaintBox1;
	TMenuItem *ClientSocketandServerSocket1;
	TMenuItem *WebBrouser1;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall N11Click(TObject *Sender);
	void __fastcall MouseandPaintBox1Click(TObject *Sender);
	void __fastcall imerandPaintBox1Click(TObject *Sender);
	void __fastcall ClientSocketandServerSocket1Click(TObject *Sender);
	void __fastcall WebBrouser1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
