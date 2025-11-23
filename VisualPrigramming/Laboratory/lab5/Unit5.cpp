//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm5::Button1Click(TObject *Sender)
{
	Animate1->Play(Animate1-> StartFrame, Animate1-> StopFrame, 1);
	Animate2->Play(Animate2-> StartFrame, Animate2-> StopFrame, 1);
	Animate3->Play(Animate3-> StartFrame, Animate3-> StopFrame, 1);
	Animate4->Play(Animate4-> StartFrame, Animate4-> StopFrame, 1);
	Animate5->Play(Animate5-> StartFrame, Animate5-> StopFrame, 1);
	Animate6->Play(Animate6-> StartFrame, Animate6-> StopFrame, 1);
	Animate7->Play(Animate7-> StartFrame, Animate7-> StopFrame, 1);
	Animate8->Play(Animate8-> StartFrame, Animate8-> StopFrame, 1);
}
//---------------------------------------------------------------------------
