//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::PaintBox1Paint(TObject *Sender)
{
	PaintBox1->Canvas->Pen->Color = clBlue;
	PaintBox1->Canvas->Pen->Width = 5;
	PaintBox1->Canvas->MoveTo(0, 0);
	PaintBox1->Canvas->LineTo(PaintBox1->Width, PaintBox1->Height);
	PaintBox1->Canvas->MoveTo(PaintBox1->Width, 0);
	PaintBox1->Canvas->LineTo(0, PaintBox1->Height);
}
//---------------------------------------------------------------------------
