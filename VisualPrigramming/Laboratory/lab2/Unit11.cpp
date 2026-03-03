//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit11.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm11 *Form11;
//---------------------------------------------------------------------------
//Для устранение недочета используем глобальные переменнные, чтобы все элементы
//  были синхронизированы между собой
int R = 0, G = 0, B = 0;

//---------------------------------------------------------------------------
__fastcall TForm11::TForm11(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm11::UpdateUI()
{
	// 1) Обновляем цвет
	Shape1->Brush->Color = TColor(RGB(R, G, B));

	// 2) Обновляем ScrollBar
	ScrollBar1->Position = R;
	ScrollBar2->Position = G;
	ScrollBar3->Position = B;

	// 3) Обновляем CheckBox
	CheckBox1->Checked = (R == 255);
	CheckBox2->Checked = (G == 255);
	CheckBox3->Checked = (B == 255);

	// 4) Обновляем RadioButton
	BlackRB->Checked     = (R==0   && G==0   && B==0);
	RedRB->Checked       = (R==255 && G==0   && B==0);
	GreenRB->Checked     = (R==0   && G==255 && B==0);
	BlueRB->Checked      = (R==0   && G==0   && B==255);
	YellowRB->Checked    = (R==255 && G==255 && B==0);
	RedBlueRB->Checked   = (R==255 && G==0   && B==255);
	WhiteBlueRB->Checked = (R==0   && G==255 && B==255);
	WhiteRB->Checked     = (R==255 && G==255 && B==255);

	// 5) Обновляем ComboBox
	if (BlackRB->Checked) ComboBox1->ItemIndex = 0;
	else if (RedRB->Checked) ComboBox1->ItemIndex = 1;
	else if (GreenRB->Checked) ComboBox1->ItemIndex = 2;
	else if (BlueRB->Checked) ComboBox1->ItemIndex = 3;
	else if (YellowRB->Checked) ComboBox1->ItemIndex = 4;
	else if (RedBlueRB->Checked) ComboBox1->ItemIndex = 5;
	else if (WhiteBlueRB->Checked) ComboBox1->ItemIndex = 6;
	else if (WhiteRB->Checked) ComboBox1->ItemIndex = 7;
	else ComboBox1->ItemIndex = -1;
}
//---------------------------------------------------------------------------
void __fastcall TForm11::ScrollBar1Change(TObject *Sender)
{
    R = ScrollBar1->Position;
    G = ScrollBar2->Position;
    B = ScrollBar3->Position;
	UpdateUI();
//	Shape1->Brush->Color = TColor(RGB(ScrollBar1->Position, ScrollBar2->Position, ScrollBar3->Position));

//	Shape1->Brush->Color = RGB(ScrollBar1->Position, ScrollBar2->Position, ScrollBar3->Position);
}
//---------------------------------------------------------------------------
void __fastcall TForm11::ScrollBar2Change(TObject *Sender)
{
    R = ScrollBar1->Position;
    G = ScrollBar2->Position;
    B = ScrollBar3->Position;
	UpdateUI();
//	Shape1->Brush->Color = TColor(RGB(ScrollBar1->Position, ScrollBar2->Position, ScrollBar3->Position));
//	Shape1->Brush->Color = RGB(ScrollBar1->Position, ScrollBar2->Position, ScrollBar3->Position);
}
//---------------------------------------------------------------------------
void __fastcall TForm11::ScrollBar3Change(TObject *Sender)
{
    R = ScrollBar1->Position;
	G = ScrollBar2->Position;
	B = ScrollBar3->Position;
	UpdateUI();
//	Shape1->Brush->Color = TColor(RGB(ScrollBar1->Position, ScrollBar2->Position, ScrollBar3->Position));
//	Shape1->Brush->Color = RGB(ScrollBar1->Position, ScrollBar2->Position, ScrollBar3->Position);
}
//---------------------------------------------------------------------------
void __fastcall TForm11::BlackRBClick(TObject *Sender)
{
	R=0; G=0; B=0;
	UpdateUI();
//	Shape1->Brush->Color = TColor(RGB(0, 0, 0));
}
//---------------------------------------------------------------------------
void __fastcall TForm11::RedRBClick(TObject *Sender)
{
	R=255; G=0; B=0;
	UpdateUI();
//	Shape1->Brush->Color = TColor(RGB(255, 0, 0));
}
//---------------------------------------------------------------------------
void __fastcall TForm11::GreenRBClick(TObject *Sender)
{
	R=0; G=255; B=0;
	UpdateUI();
//	Shape1->Brush->Color = TColor(RGB(0, 255, 0));
}
//---------------------------------------------------------------------------
void __fastcall TForm11::BlueRBClick(TObject *Sender)
{
	R=0; G=0; B=255;
	UpdateUI();
//	Shape1->Brush->Color = TColor(RGB(0, 0, 255));
}
//---------------------------------------------------------------------------
void __fastcall TForm11::YellowRBClick(TObject *Sender)
{
	R=255; G=255; B=0;
	UpdateUI();
//	Shape1->Brush->Color = TColor(RGB(255, 255, 0));
}
//---------------------------------------------------------------------------
void __fastcall TForm11::RedBlueRBClick(TObject *Sender)
{
	R=255; G=0; B=255;
	UpdateUI();
//	Shape1->Brush->Color = TColor(RGB(255, 0, 255));
}
//---------------------------------------------------------------------------
void __fastcall TForm11::WhiteBlueRBClick(TObject *Sender)
{
	R=0; G=255; B=255;
	UpdateUI();
//	Shape1->Brush->Color = TColor(RGB(0, 255, 255));
}
//---------------------------------------------------------------------------
void __fastcall TForm11::WhiteRBClick(TObject *Sender)
{
	R=255; G=255; B=255;
	UpdateUI();
//	Shape1->Brush->Color = TColor(RGB(255, 255, 255));
}
//---------------------------------------------------------------------------
void __fastcall TForm11::CheckBox1Click(TObject *Sender)
{
    R = CheckBox1->Checked ? 255 : 0;
    G = CheckBox2->Checked ? 255 : 0;
    B = CheckBox3->Checked ? 255 : 0;
	UpdateUI();
//	Shape1->Brush->Color = TColor(RGB(255 *CheckBox1->Checked, 255 * CheckBox2->Checked, 255*CheckBox3->Checked));
}
//---------------------------------------------------------------------------
void __fastcall TForm11::CheckBox2Click(TObject *Sender)
{
    R = CheckBox1->Checked ? 255 : 0;
    G = CheckBox2->Checked ? 255 : 0;
    B = CheckBox3->Checked ? 255 : 0;
	UpdateUI();
//	Shape1->Brush->Color = TColor(RGB(255 *CheckBox1->Checked, 255 * CheckBox2->Checked, 255*CheckBox3->Checked));
}
//---------------------------------------------------------------------------
void __fastcall TForm11::CheckBox3Click(TObject *Sender)
{
    R = CheckBox1->Checked ? 255 : 0;
    G = CheckBox2->Checked ? 255 : 0;
    B = CheckBox3->Checked ? 255 : 0;
	UpdateUI();
//    Shape1->Brush->Color = TColor(RGB(255 *CheckBox1->Checked, 255 * CheckBox2->Checked, 255*CheckBox3->Checked));
}
//---------------------------------------------------------------------------
void __fastcall TForm11::ComboBox1Change(TObject *Sender)
{
    switch (ComboBox1->ItemIndex)
    {
		case 0: R=0;   G=0;   B=0; break;
		case 1: R=255; G=0;   B=0; break;
		case 2: R=0;   G=255; B=0; break;
		case 3: R=0;   G=0;   B=255; break;
		case 4: R=255; G=255; B=0; break;
		case 5: R=255; G=0;   B=255; break;
		case 6: R=0;   G=255; B=255; break;
		case 7: R=255; G=255; B=255; break;
	}
	UpdateUI();
//	if (ComboBox1->Text == "Черный") Shape1->Brush->Color = TColor(RGB(0, 0, 0));
//	if (ComboBox1->Text == "Красный") Shape1->Brush->Color = TColor(RGB(255, 0, 0));
//	if (ComboBox1->Text == "Зеленый") Shape1->Brush->Color = TColor(RGB(0, 255, 0));
//	if (ComboBox1->Text == "Синий") Shape1->Brush->Color = TColor(RGB(0, 0, 255));
//	if (ComboBox1->Text == "Желтый") Shape1->Brush->Color = TColor(RGB(255, 255, 0));
//	if (ComboBox1->Text == "Малиновый") Shape1->Brush->Color = TColor(RGB(255, 0, 255));
//	if (ComboBox1->Text == "Голубой") Shape1->Brush->Color = TColor(RGB(0, 255, 255));
//	if (ComboBox1->Text == "Белый") Shape1->Brush->Color = TColor(RGB(255, 255, 255));
}
//---------------------------------------------------------------------------


