#include "CheckersEngine.h"
#include <cmath>

CheckersEngine::CheckersEngine(int size)
{
    SIZE = size;
    board.assign(size, std::vector<int>(size, EMPTY));
}

/Функция, возвращающая логический тип - шашка на шахматной доске?
inline bool CheckersEngine::inBounds(int x, int y) {
	return x >= 0 && x < SIZEBOARD && y >= 0 && y < SIZEBOARD;
}

//Функция, возвращающая логический тип - выбранная ячейка пуста ли ?
bool CheckersEngine::isEmpty(int x, int y) {
	if (!inBounds(x,y)) return false;
	return board[y][x] == EMPTY;
}

//Проверка выбранной шашки - пустая ячейка или не пустая
bool CheckersEngine::isValideChecker(int x, int y){
	if (!inBounds(x,y)) return false;
	if (currentPlayer == WHITE_PAWN) {
		return board[y][x] == WHITE_PAWN || board[y][x] == WHITE_KING;
	} else {
		return board[y][x] == BLACK_PAWN || board[y][x] == BLACK_KING;
	}
}

//Проверка на шашку противника
bool CheckersEngine::isOpponentPiece(int x, int y, int myPiece){
	if (!inBounds(x,y)) return false;
	if (myPiece == WHITE_PAWN || myPiece == WHITE_KING) {
		return board[y][x] == BLACK_PAWN || board[y][x] == BLACK_KING;
	} else {
		return board[y][x] == WHITE_PAWN || board[y][x] == WHITE_KING;
	}
}

bool CheckersEngine::isDiagonal(int fromX, int fromY, int toX, int toY) {
	return std::abs(toX - fromX) == std::abs(toY - fromY);
}

// Функция обработки простого хода (без взятия)
bool CheckersEngine::canMoveSimple(int fromX, int fromY, int toX, int toY) {
	if (!inBounds(fromX, fromY) || !inBounds(toX, toY)) return false;
	if (!isEmpty(toX, toY)) return false;
	if (!isDiagonal(fromX, fromY, toX, toY)) return false;

	int piece = board[fromY][fromX];
	int dx = std::abs(toX - fromX);
	int dy = toY - fromY;

	// Для простоты: дамка может ходить на 1 клетку (ограничение)
	if (piece == WHITE_KING || piece == BLACK_KING) {
		if (dx == 1 && std::abs(dy) == 1) return true;
		return false;
	}

	// Обычные пешки: белые - вверх (y--), черные - вниз (y++)
	int direction = (piece == WHITE_PAWN) ? -1 : 1;
	if (dx == 1 && dy == direction) return true;

	return false;
}

// Функция обработки хода со взятием (перескок через 1 фигуру)
bool CheckersEngine::canCaptureMove(int fromX, int fromY, int toX, int toY) {
	if (!inBounds(fromX, fromY) || !inBounds(toX, toY)) return false;
	if (!isEmpty(toX, toY)) return false;
	if (!isDiagonal(fromX, fromY, toX, toY)) return false;

	int dx = std::abs(toX - fromX);
	int dyAbs = std::abs(toY - fromY);
	if (dx != 2 || dyAbs != 2) return false; // прыжок через одну клетку

	int midX = (fromX + toX) / 2;
	int midY = (fromY + toY) / 2;
	int piece = board[fromY][fromX];

	if (isOpponentPiece(midX, midY, piece)) return true;
	return false;
}

// Функция проверки: с данной клетки возможен ли любой прыжок
bool CheckersEngine::hasCapture(int x, int y) {
	if (!inBounds(x,y)) return false;
	int piece = board[y][x];
	if (piece == EMPTY) return false;

	// Проверяем 4 направлений на прыжок
	const int dx[4] = { -2, 2, -2, 2 };
	const int dy[4] = { -2, -2, 2, 2 };
	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (inBounds(nx, ny) && canCaptureMove(x,y,nx,ny)) return true;
	}
	return false;
}

// Функция проверки: есть ли у текущего игрока вообще возможность бить
bool CheckersEngine::playerHasAnyCapture(int playerPiece) {
	for (int y = 0; y < SIZEBOARD; ++y)
		for (int x = 0; x < SIZEBOARD; ++x) {
			if (playerPiece == WHITE_PAWN) {
				if (board[y][x] == WHITE_PAWN || board[y][x] == WHITE_KING) {
					if (hasCapture(x,y)) return true;
				}
			} else {
				if (board[y][x] == BLACK_PAWN || board[y][x] == BLACK_KING) {
					if (hasCapture(x,y)) return true;
				}
			}
		}
	return false;
}

// Функция обработки хода шашки с (fromX, fromY) на (toX, toY)
void CheckersEngine::performMove(int fromX, int fromY, int toX, int toY) {
	if (!inBounds(fromX, fromY) || !inBounds(toX, toY)) return;

	int piece = board[fromY][fromX];

	// Выполнение перемещения
	board[toY][toX] = piece;
	board[fromY][fromX] = EMPTY;

	bool wasCapture = false;
	// Если это прыжок — удаляем фигуру посредине
	if (std::abs(toX - fromX) == 2) {
		int midX = (fromX + toX) / 2;
		int midY = (fromY + toY) / 2;
		board[midY][midX] = EMPTY;
		wasCapture = true;
	}

	// Проверка превращения в дамку
	checkForKing(toX, toY);

	// Если был прыжок — проверить, есть ли последующие прыжки с новой позиции
	if (wasCapture && hasCapture(toX, toY)) {
		// Оставляем пользователя выбирать дальнейший прыжок с той же шашки
		selectedX = toX;
		selectedY = toY;
		isSelected = true;
		DrawGrid1->Repaint();
		return;
	}

	// Иначе — переход хода
	isSelected = false;
    // --- Проверка победы по отсутствию фигур ---
	int opponent = (currentPlayer == WHITE_PAWN ? BLACK_PAWN : WHITE_PAWN);

	if (!playerHasPieces(opponent))
	{
		if (currentPlayer == WHITE_PAWN ) {
			Application->MessageBox(L"Белые победили! У черных не осталось шашек.", L"", MB_OK);
//			Application->ShowMassageW(L"Белые победили! У черных не осталось шашек.", L"", MB_OK);
		}else{
			Application->MessageBox(L"Черные победили! У белых не осталось шашек.", L"", MB_OK);
//			Application->ShowMassageW(L"Черные победили! У белых не осталось шашек.", L"", MB_OK);
		}
		//ResetGame(); // если есть функция перезапуска
		ResetGame();
		Close();

		//return;
	}
	// --- Проверка: может ли противник сделать ход ---
	else if (!playerHasMoves(opponent))
	{
		if (currentPlayer == WHITE_PAWN) {
			Application->MessageBox(L"Белые победили! У черных нет ходов.", L"", MB_OK);
		}else{
			Application->MessageBox(L"Черные победили! У белых нет ходов.", L"", MB_OK);
		}
		//Close();
		ResetGame();
		Close();
		//		return;
	}

	switchPlayer();
	DrawGrid1->Repaint();
}

// Функция обработки превращения шашки в дамку
void CheckersEngine::checkForKing(int x, int y) {
	if (!inBounds(x,y)) return;
	if (board[y][x] == WHITE_PAWN && y == 0) board[y][x] = WHITE_KING;
	else if (board[y][x] == BLACK_PAWN && y == SIZEBOARD - 1) board[y][x] = BLACK_KING;
}

// Функция обработки смена игрока
void CheckersEngine::switchPlayer() {
    if (currentPlayer == WHITE_PAWN)
    {
        currentPlayer = BLACK_PAWN;
        StartBlackTimer();
    }
    else
    {
        currentPlayer = WHITE_PAWN;
        StartWhiteTimer();
    }
}

bool CheckersEngine::playerHasPieces(int player)
{
    for (int y = 0; y < SIZEBOARD; y++)
    {
        for (int x = 0; x < SIZEBOARD; x++)
        {
            if (player == WHITE_PAWN)
            {
                if (board[y][x] == WHITE_PAWN || board[y][x] == WHITE_KING)
                    return true;
            }
            else
            {
                if (board[y][x] == BLACK_PAWN || board[y][x] == BLACK_KING)
                    return true;
            }
        }
    }
    return false;
}

bool CheckersEngine::playerHasMoves(int player)
{
    for (int y = 0; y < SIZEBOARD; y++)
    {
        for (int x = 0; x < SIZEBOARD; x++)
        {
            int cell = board[y][x];

            // Проверяем шашки игрока
            if (player == WHITE_PAWN)
            {
                if (cell != WHITE_PAWN && cell != WHITE_KING) continue;
            }
            else
            {
                if (cell != BLACK_PAWN && cell != BLACK_KING) continue;
            }

            // Проверяем ВСЕ возможные ходы
            // Для простых шашек
			int dirs[4][2] = {
                {1,  1},
                {1, -1},
                {-1, 1},
                {-1, -1}
            };

            for (int i = 0; i < 4; i++)
            {
                int nx = x + dirs[i][1];
                int ny = y + dirs[i][0];

                if (nx >= 0 && nx < SIZEBOARD &&
                    ny >= 0 && ny < SIZEBOARD)
                {
                    if (board[ny][nx] == EMPTY)
                        return true; // простой ход есть
                }

                // Проверяем взятие
                int jx = x + dirs[i][1] * 2;
                int jy = y + dirs[i][0] * 2;

                if (jx >= 0 && jx < SIZEBOARD &&
                    jy >= 0 && jy < SIZEBOARD)
                {
                    int mx = x + dirs[i][1];
                    int my = y + dirs[i][0];
                    int mid = board[my][mx];

                    if (board[jy][jx] == EMPTY)
                    {
                        // соперник между клетками
                        if (player == WHITE_PAWN)
                        {
                            if (mid == BLACK_PAWN || mid == BLACK_KING)
                                return true;
                        }
                        else
                        {
                            if (mid == WHITE_PAWN || mid == WHITE_KING)
                                return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}
