//---------------------------------------------------------------------------

#ifndef Unit11H
#define Unit11H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm11 : public TForm
{
__published:	// IDE-managed Components
	TScrollBar *ScrollBar2;
	TScrollBar *ScrollBar3;
	TScrollBar *ScrollBar1;
	TGroupBox *GroupBox1;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
	TComboBox *ComboBox1;
	TShape *Shape1;
	TGroupBox *GroupBox2;
	TRadioButton *BlackRB;
	TRadioButton *RedRB;
	TRadioButton *GreenRB;
	TRadioButton *BlueRB;
	TRadioButton *YellowRB;
	TRadioButton *RedBlueRB;
	TRadioButton *WhiteBlueRB;
	TRadioButton *WhiteRB;
	void __fastcall ScrollBar1Change(TObject *Sender);
	void __fastcall ScrollBar2Change(TObject *Sender);
	void __fastcall BlackRBClick(TObject *Sender);
	void __fastcall RedRBClick(TObject *Sender);
	void __fastcall GreenRBClick(TObject *Sender);
	void __fastcall BlueRBClick(TObject *Sender);
	void __fastcall YellowRBClick(TObject *Sender);
	void __fastcall RedBlueRBClick(TObject *Sender);
	void __fastcall WhiteBlueRBClick(TObject *Sender);
	void __fastcall WhiteRBClick(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall CheckBox2Click(TObject *Sender);
	void __fastcall CheckBox3Click(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall ScrollBar3Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm11(TComponent* Owner);
    void __fastcall UpdateUI();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm11 *Form11;
//---------------------------------------------------------------------------
#endif
