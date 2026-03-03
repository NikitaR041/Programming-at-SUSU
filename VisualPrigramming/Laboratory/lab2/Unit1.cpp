//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "Unit6.h"
#include "Unit7.h"
#include "Unit8.h"
#include "Unit9.h"
#include "Unit10.h"
#include "Unit11.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N111Click(TObject *Sender)
{
	Application->MessageBoxW(L"Пункт 1.1", L"", MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N3Click(TObject *Sender)
{
	Application->MessageBoxW(L"Пункт 1.2", L"", MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N21Click(TObject *Sender)
{
	Application->MessageBoxW(L"Пункт 2", L"", MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N1Click(TObject *Sender)
{
	//Выход из программы
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Edit3->Text = Edit1->Text.ToInt( ) + Edit2->Text.ToInt( );
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N11Click(TObject *Sender)
{
	Form2->ShowModal();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::N22Click(TObject *Sender)
{
	Form3->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N31Click(TObject *Sender)
{
	Form4->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N41Click(TObject *Sender)
{
	Form5->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N51Click(TObject *Sender)
{
	Form6->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N61Click(TObject *Sender)
{
	Form7->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N71Click(TObject *Sender)
{
    Form8->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N81Click(TObject *Sender)
{
	Form9->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N12Click(TObject *Sender)
{
	Application->MessageBoxW(L"N12 Clicked!", L"Info", MB_OK);
}

void __fastcall TForm1::N91Click(TObject *Sender)
{
	Form10->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N101Click(TObject *Sender)
{
    Form11->ShowModal();
}
//---------------------------------------------------------------------------


