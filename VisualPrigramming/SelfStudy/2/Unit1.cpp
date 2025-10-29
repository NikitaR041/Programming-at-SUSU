//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	CurrentColor = clRed; // цвет по умолчанию
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
			CellColors[i][j] = clWhite; // фон по умолчанию
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N1Click(TObject *Sender)
{
    Form2->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N2Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ListBox1Click(TObject *Sender)
{
    switch (ListBox1->ItemIndex)
    {
        case 0: CurrentColor = clRed; break;
		case 1: CurrentColor = clWebOrange; break;
		case 2: CurrentColor = clYellow; break;
		case 3: CurrentColor = clGreen; break;
		case 4: CurrentColor = clAqua; break;
		case 5: CurrentColor = clBlue; break;
		case 6: CurrentColor = clFuchsia; break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft)
	{
		int ACol, ARow;
		StringGrid1->MouseToCell(X, Y, ACol, ARow);

		// ѕровер€ем, что €чейка не закрашена
        if (CellColors[ACol][ARow] == clWhite) {
            CellColors[ACol][ARow] = CurrentColor;
            StringGrid1->Invalidate(); // перерисовать €чейку
        }
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1DrawCell(TObject *Sender, System::LongInt ACol,
          System::LongInt ARow, TRect &Rect, TGridDrawState State)
{
    // ‘он €чейки
	StringGrid1->Canvas->Brush->Color = CellColors[ACol][ARow];
	StringGrid1->Canvas->FillRect(Rect);
}
//---------------------------------------------------------------------------
