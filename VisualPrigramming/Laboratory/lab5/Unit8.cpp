//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit8.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm8 *Form8;
//---------------------------------------------------------------------------
__fastcall TForm8::TForm8(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm8::FormActivate(TObject *Sender)
{
TTreeNode *Tn1, *Tn2, *Tn3, *Tn4;
Tn1 = TreeView1->Items->Add(NULL, "Дневная");
Tn1->SelectedIndex = 1;

Tn2 = TreeView1->Items->AddChild(Tn1, "Бух.учет и аудит");
Tn2->SelectedIndex = 1;
Tn2 = TreeView1->Items->AddChild(Tn1, "Информатика в экономике");
Tn2->SelectedIndex = 1;

Tn3 = TreeView1->Items->AddChild(Tn2, "1 курс");
Tn3->SelectedIndex = 1;
Tn4 = TreeView1->Items->AddChild(Tn3, "ЕТ-112");
Tn4->SelectedIndex = 1;
Tn4 = TreeView1->Items->AddChild(Tn3, "ЕТ-113");
Tn4->SelectedIndex = 1;

Tn3 = TreeView1->Items->AddChild(Tn2, "2 курс");
Tn3->SelectedIndex = 1;
Tn4 = TreeView1->Items->AddChild(Tn3, "ЕТ-212");
Tn4->SelectedIndex = 1;
Tn4 = TreeView1->Items->AddChild(Tn3, "ЕТ-213");
Tn4->SelectedIndex = 1;
Tn3 = TreeView1->Items->AddChild(Tn2, "3 курс");
Tn3->SelectedIndex = 1;

Tn4 = TreeView1->Items->AddChild(Tn3, "ЕТ-312");
Tn4->SelectedIndex = 1;
Tn4 = TreeView1->Items->AddChild(Tn3, "ЕТ-313");
Tn4->SelectedIndex = 1;

Tn3 = TreeView1->Items->AddChild(Tn2, "4 курс");
Tn3->SelectedIndex = 1;
Tn4 = TreeView1->Items->AddChild(Tn3, "ЕТ-412");
Tn4->SelectedIndex = 1;
Tn4 = TreeView1->Items->AddChild(Tn3, "ЕТ-413");
Tn4->SelectedIndex = 1;

Tn3 = TreeView1->Items->AddChild(Tn2, "5 курс");


Tn2 = TreeView1->Items->AddChild(Tn1, "Менеджмент");
Tn2->SelectedIndex = 1;
Tn2 = TreeView1->Items->AddChild(Tn1, "Финансы и кредит");
Tn2->SelectedIndex = 1;
Tn2 = TreeView1->Items->AddChild(Tn1, "Экономика");
Tn2->SelectedIndex = 1;

Tn1 = TreeView1->Items->Add(NULL, "Вечерняя");
Tn1->SelectedIndex = 1;
Tn1 = TreeView1->Items->Add(NULL, "Заочная");
Tn1->SelectedIndex = 1;
}
//---------------------------------------------------------------------------

