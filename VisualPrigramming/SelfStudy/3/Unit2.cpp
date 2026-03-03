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
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if ((Button == mbLeft) && (Shift.Contains(ssCtrl))) {
		TOpenPictureDialog *OpenPictureDialog = new TOpenPictureDialog(this);

		if (OpenPictureDialog->Execute()) {
			Image1->Picture->LoadFromFile(OpenPictureDialog->FileName);
		}
	}
}
//---------------------------------------------------------------------------
