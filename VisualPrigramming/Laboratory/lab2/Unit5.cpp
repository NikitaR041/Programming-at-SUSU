//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm5::BlackRBClick(TObject *Sender)
{
	if (BlackRB->Checked) Label1->Font->Color = clBlack;
	if (WhiteRB->Checked) Label1->Font->Color = clWhite;
	if (RedRB->Checked) Label1->Font->Color = clRed;
	if (GreenRB->Checked) Label1->Font->Color = clGreen;
	if (BlueRB->Checked) Label1->Font->Color = clBlue;
	if (YellowRB->Checked) Label1->Font->Color = clYellow;
}
//---------------------------------------------------------------------------
