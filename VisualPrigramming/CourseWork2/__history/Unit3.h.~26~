//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TDrawGrid *DrawGrid1;
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *N8;
	TMenuItem *N9;
	TLabel *LabelTurn;
	TTimer *TimerWhite;
	TLabel *LabelTimer;
	TTimer *TimerBlack;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall DrawGrid1DrawCell(TObject *Sender, System::LongInt ACol, System::LongInt ARow,
          TRect &Rect, TGridDrawState State);
	void __fastcall DrawGrid1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N9Click(TObject *Sender);
	void __fastcall TimerWhiteTimer(TObject *Sender);
	void __fastcall TimerBlackTimer(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
private:	// User declarations
	int whiteTime;       // секунды для белых
	int blackTime;       // секунды для чёрных
	int selectedX, selectedY;  // Выбранная ячейка
	bool isSelected;           // Флаг выбора
	int currentPlayer;         // Текущий игрок (WHITE_PAWN или BLACK_PAWN)

	// Проверки координат
	bool inBounds(int x, int y);
	bool isEmpty(int x, int y);

	// Проверка принадлежности шашки игроку
	bool isValideChecker(int x, int y);

	// Проверка шашки противника
	bool isOpponentPiece(int x, int y, int myPiece);

	// Геометрия хода
	bool isDiagonal(int fromX, int fromY, int toX, int toY);

	// Простой ход (без взятия)
	bool canMoveSimple(int fromX, int fromY, int toX, int toY);

	// Ход со взятием
	bool canCaptureMove(int fromX, int fromY, int toX, int toY);

	// Проверка возможности взятия для клетки
	bool hasCapture(int x, int y);

	// Проверка возможности взятия у текущего игрока
	bool playerHasAnyCapture(int playerPiece);

	// Выполнение хода
	void performMove(int fromX, int fromY, int toX, int toY);

	// Проверка превращения в дамку
	void checkForKing(int x, int y);

	// Смена игрока
	void switchPlayer();

	bool playerHasPieces(int player);
    bool playerHasMoves(int player);

	// Инициализация доски
	void InitBoard();
    //
	void ResetGame();

	// Запуск таймера для белых и черных
	void StartWhiteTimer();
	void StartBlackTimer();
	// Обновление метки с информацией о текущем ходе
	void UpdateTimerLabel(int seconds);
	// Обработка проигрыша по истечении времени
	void LoseByTimeout(int whoLost);
	// Обновление метки таймера в формате MM:SS
	void UpdateTurnLabel();

public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//Константные свойства игры
enum Piece {
	EMPTY = 0,       // пустая клетка
	WHITE_PAWN = 1,  // белая шашка
	BLACK_PAWN = 2,  // чёрная шашка
	WHITE_KING = 3,  // белая дамка
	BLACK_KING = 4   // чёрная дамка
};
const int SIZEBOARD = 8;

extern int board[SIZEBOARD][SIZEBOARD];
//---------------------------------------------------------------------------
#endif
