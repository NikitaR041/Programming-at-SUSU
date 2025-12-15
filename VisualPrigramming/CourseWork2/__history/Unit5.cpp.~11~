//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
int board[SIZEBOARD][SIZEBOARD];  //Шахматная доска
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TForm5::FormCreate(TObject *Sender)
{
	//Инициализация игры
	whiteTime = 5 * 60;

	InitBoard();
	isSelected = false;
	selectedX = selectedY = -1;
	currentPlayer = WHITE_PAWN;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm5::N3Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
// Функция инициализации шахматной доски и шахмат/дамков
void TForm5::InitBoard()
{
	for (int y = 0; y < SIZEBOARD; y++) {
		for (int x = 0; x < SIZEBOARD; x++) {
			if ((x + y) % 2 == 1) { // шашки стоят только на тёмных клетках
				if (y < 3) board[y][x] = BLACK_PAWN;
				else if (y > 4) board[y][x] = WHITE_PAWN;
				else board[y][x] = EMPTY;
			} else {
				board[y][x] = EMPTY;
			}
		}
	}
}

void TForm5::ResetGame()
{
	for (int y = 0; y < SIZEBOARD; y++)
		for (int x = 0; x < SIZEBOARD; x++)
			board[y][x] = EMPTY;

	InitBoard();
	isSelected = false;
	selectedX = selectedY = -1;
	currentPlayer = WHITE_PAWN;

}
