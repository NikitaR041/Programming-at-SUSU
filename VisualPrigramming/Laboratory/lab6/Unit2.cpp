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
	DrawStar(PaintBox1->Canvas, PaintBox1->Width/2, PaintBox1->Height/2, 250);
}
//---------------------------------------------------------------------------
void TForm2::DrawStar(TCanvas *c, int cx, int cy, int R)
{
    const double pi = 3.1415926535;

    // 5 точек
    TPoint p[5];

    for (int i = 0; i < 5; i++)
    {
		double angle = -pi / 2 + i * 2 * pi / 5; // старт сверху
		p[i].x = cx+ R * cos(angle);
		p[i].y = cy + R * sin(angle);
	}

	c->Pen->Color = clRed;
	c->Pen->Width = 3;

	// Рисуем звезду: каждая точка соединяется с точкой через одну
	c->MoveTo(p[0].x, p[0].y);

	int order[6] = {0, 2, 4, 1, 3, 0}; // порядок обхода вершин

	for (int i = 1; i < 6; i++)
	{
		c->LineTo(p[order[i]].x, p[order[i]].y);
	}
}

