//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "printers.hpp"
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
void __fastcall TForm1::N12Click(TObject *Sender)
{
    Form2->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N7Click(TObject *Sender)
{
	SaveAsDocument();// В функции пункта меню «Сохранить как»
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N4Click(TObject *Sender)
{
	OpenDocument(); // В функции пункта меню «Создать»
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N9Click(TObject *Sender)
{
	int Rc;
	Rc = PrintDialog1->Execute( );
	if (Rc) {
		TPrinter *Prntr = Printer( );
		Prntr->BeginDoc( );
//		Prntr->Canvas->TextOut(200, 200, L"Тестовая печать документа");
		Prntr->Canvas->TextOut(200, 200, Memo1->Lines->Text);
		Prntr->EndDoc( );
	} // if
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N10Click(TObject *Sender)
{
	PrinterSetupDialog1->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N3Click(TObject *Sender)
{
	Memo1->Clear();
	NewDocument(); // В функции пункта меню «Создать»
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N6Click(TObject *Sender)
{
	SaveDocument();// В функции пункта меню «Сохранить»
}
//---------------------------------------------------------------------------
//--------------------- НИЖЕ ПРИВЕДЕНЫ РЕАЛИЗАЦИИ МЕТОДОВ -------------------
//----- NewDocument(), OpenDocument(), SaveDocument(), SaveAsDocument() -----
void TForm1::NewDocument(void)
{
	int Rc;
	if (Memo1->Modified) {
		Rc = Application->MessageBox(
			L"Текст был изменен\nСохранить изменение?",
			L"Вопрос", MB_YESNOCANCEL | MB_ICONQUESTION);
		if (Rc == IDCANCEL) return;
		if (Rc == IDYES) {
			SaveDocument( );
		} // if
	} // if
	Memo1->Clear( );
	FileName = "";
} // NewDocument

void TForm1::OpenDocument(void)
{
	int Rc;
	if (Memo1->Modified) {
		Rc = Application->MessageBox(
			L"Текст был изменен\nСохранить изменение?",
			L"Вопрос", MB_YESNOCANCEL | MB_ICONQUESTION);

		if (Rc == IDCANCEL) return;
		if (Rc == IDYES) {
			SaveDocument( );
		} // if
	} // if
	Rc = OpenDialog1->Execute( );
	if (Rc) {
		Memo1->Lines->LoadFromFile(OpenDialog1->FileName);
		FileName = OpenDialog1->FileName;
	} // if
} // OpenDocument

void TForm1::SaveDocument(void)
{
	if (FileName.IsEmpty( )) {
		SaveAsDocument( );
	} else {
		Memo1->Lines->SaveToFile(FileName);
	} // else
	Memo1->Modified = false;
} // SaveDocument

void TForm1::SaveAsDocument(void)
{
	int Rc;
	SaveDialog1->FileName = FileName;
	Rc = SaveDialog1->Execute( );
	if (Rc) {
		Memo1->Lines->SaveToFile(SaveDialog1->FileName);
		FileName = SaveDialog1->FileName;
	} // if
	Memo1->Modified = false;
} // SaveAsDocument

