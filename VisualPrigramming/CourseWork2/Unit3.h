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
	void __fastcall N4Click(TObject *Sender);
private:	// User declarations
	int whiteTime;       // секунды для белых
	int blackTime;       // секунды для чёрных
	int selectedX, selectedY;  // Выбранная ячейка
	bool isSelected;           // Флаг выбора
	int currentPlayer;         // Текущий игрок (WHITE_PAWN или BLACK_PAWN)

	//Функция проверки координат внутри игровой доски
	bool inBounds(int x, int y);

	//Функиця проверки клетки на пустоту
	bool isEmpty(int x, int y);

	//Функция проверки принадлежности шашки игроку
	bool isValideChecker(int x, int y);

	//Функция проверки шашки противника
	bool isOpponentPiece(int x, int y, int myPiece);

	//Функция проверки хода диагональю
	bool isDiagonal(int fromX, int fromY, int toX, int toY);

	//Функция проверки простого хода без взятия шашки
	bool canMoveSimple(int fromX, int fromY, int toX, int toY);

	//Функция проверки хода со взятием шашки противника
	bool canCaptureMove(int fromX, int fromY, int toX, int toY);

	//Функиця проверки возможности захвата с указанной клетки
	bool hasCapture(int x, int y);

	//Функция проверки у игрока хотя бы один возможный ход со взятием
	bool playerHasAnyCapture(int playerPiece);

	//Функция выполняет ход шашки с учетом взятия шашки и правил игры
	void performMove(int fromX, int fromY, int toX, int toY);

	//Функция проверки и выполнения превращение шашки в дамку
	void checkForKing(int x, int y);

	//Функция переключения на другого игрока и включение таймера
	void switchPlayer();

	//Фуникция проверки наличия шашек у игрока
	bool playerHasPieces(int player);

	//Функция проверки наличия хотя бы одного допустимого хода у игрока
	bool playerHasMoves(int player);

	//Функция инициализации игровой доски и расставления шашек
	void InitBoard();

	//Функция перезапуска игры
	void ResetGame();

	//Функция запуска таймера для белых шашек
	void StartWhiteTimer();

	//Функция запуска таймера для черных шашек
	void StartBlackTimer();

	//Функция обновления отображения оставшегося времени хода
	void UpdateTimerLabel(int seconds);

	//Функция обработки поражения игрока по истечении времени
	void LoseByTimeout(int whoLost);

	//Функция обновление метки о текущем ходе
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
