//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit6.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm6 *Form6;
//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm6::ListBox1Click(TObject *Sender)
{
	TColor Colors[ ] = {clBlack, clWhite, clRed, clGreen, clBlue, clYellow};
	Label1->Font->Color = Colors[ListBox1-> ItemIndex];
}
//---------------------------------------------------------------------------
