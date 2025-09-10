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
void __fastcall TForm2::FormCreate(TObject *Sender)
{
	Application->MessageBox(L"Создание второго окна", L"Заголовок", MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormActivate(TObject *Sender)
{
	Application->MessageBox(L"Активация второго окна", L"Заголовок", MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
	Application->MessageBox(L"Закрытие второго окна", L"Заголовок", MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormDestroy(TObject *Sender)
{
	Application->MessageBox(L"Удаление второго окна", L"Заголовок", MB_OK);
}
//---------------------------------------------------------------------------
