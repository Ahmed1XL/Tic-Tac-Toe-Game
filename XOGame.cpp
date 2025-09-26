#include <iostream>
#include <vector>
#include <random>
using namespace std;

enum Difficulty
{
	Easy,
	Hard,
};

class Board
{
private:
	const int size;
	vector<vector<char>> grid;

public:
	Board(int s = 3) : size(s)
	{
		grid = vector<vector<char>>(size, vector<char>(size, ' '));
	}

	void display() const
	{
		cout << "\n  ";
		for (int i = 0; i < size; i++)
		{
			cout << "  " << i << " ";
		}
		cout << "\n";

		for (int i = 0; i < size; i++)
		{
			cout << i << " ";
			for (int j = 0; j < size; j++)
			{
				cout << "| " << grid[i][j] << " ";
			}
			cout << "|\n";

			if (i < size - 1)
			{
				cout << "  ";
				for (int j = 0; j < size; j++)
				{
					cout << "+---";
				}
				cout << "+\n";
			}
		}
		cout << "\n";
	}

	bool makeMove(int row, int col, char symbol)
	{
		if (isValidMove(row, col))
		{
			grid[row][col] = symbol;
			return true;
		}
		return false;
	}

	bool isValidMove(int row, int col) const
	{
		return row >= 0 && row < size && col >= 0 && col < size && grid[row][col] == ' ';
	}

	bool checkWin(char symbol) const
	{
		// Check rows
		for (int i = 0; i < size; i++)
		{
			bool rowWin = true;
			for (int j = 0; j < size; j++)
			{
				if (grid[i][j] != symbol)
				{
					rowWin = false;
					break;
				}
			}
			if (rowWin)
				return true;
		}

		// Check columns
		for (int j = 0; j < size; j++)
		{
			bool colWin = true;
			for (int i = 0; i < size; i++)
			{
				if (grid[i][j] != symbol)
				{
					colWin = false;
					break;
				}
			}
			if (colWin)
				return true;
		}

		// Main diagonal
		bool mainDiag = true;
		for (int i = 0; i < size; i++)
			if (grid[i][i] != symbol)
				mainDiag = false;
		if (mainDiag)
			return true;

		// Anti-diagonal
		bool antiDiag = true;
		for (int i = 0; i < size; i++)
			if (grid[i][size - 1 - i] != symbol)
				antiDiag = false;
		if (antiDiag)
			return true;

		return false; // no win found
	}

	bool isFull() const
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (grid[i][j] == ' ')
				{
					return false;
				}
			}
		}
		return true;
	}

	char getCell(int row, int col) const
	{
		return grid[row][col];
	}

	int getSize() const
	{
		return size;
	}

	void reset()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				grid[i][j] = ' ';
			}
		}
	}
	void undoMove(int row, int col)
	{
		grid[row][col] = ' ';
	}
};

class Player
{
protected:
	string name;
	char symbol;

public:
	Player(const string &name, char symbol)
	{
		this->name = name;
		this->symbol = symbol;
	}
	virtual void getMove(int &row, int &col) = 0;
	virtual ~Player() {};
	string getName() const
	{
		return name;
	}
	char getSymbol() const
	{
		return symbol;
	}
	void setName(const string &name)
	{
		this->name = name;
	}
};

class AIPlayer : public Player
{
private:
	Difficulty difficulty;
	Board *currentBoard;

public:
	AIPlayer(const string &name, char symbol, Difficulty difficulty)
		: Player(name, symbol), difficulty(difficulty), currentBoard(nullptr) {}

	void setBoard(Board *board)
	{
		currentBoard = board;
	}

	void setDifficulty(Difficulty diff)
	{
		difficulty = diff;
	}

	void getMove(int &row, int &col) override
	{
		if (!currentBoard)
			return;

		if (difficulty == Easy)
		{
			getRandomMove(*currentBoard, row, col);
		}
		else
		{
			getBestMove(currentBoard, row, col);
		}

		currentBoard->makeMove(row, col, symbol);
	}

	void getRandomMove(const Board &board, int &row, int &col) const
	{
		int size = board.getSize();
		default_random_engine gen;
		uniform_int_distribution<int> dist(0, size - 1);
		do
		{
			row = dist(gen);
			col = dist(gen);
		} while (!board.isValidMove(row, col));
	}

	void getBestMove(Board *board, int &row, int &col) const
	{
		int bestScore = INT_MIN;
		int bestRow = -1, bestCol = -1;

		for (int i = 0; i < board->getSize(); ++i)
		{
			for (int j = 0; j < board->getSize(); ++j)
			{
				if (board->isValidMove(i, j))
				{
					board->makeMove(i, j, symbol);
					int score = minimax(*board, false);
					board->undoMove(i, j);

					if (score > bestScore)
					{
						bestScore = score;
						bestRow = i;
						bestCol = j;
					}
				}
			}
		}

		row = bestRow;
		col = bestCol;
	}

	int minimax(Board board, bool Turn) const
	{
		int result = evaluateBoard(board);
		if (result != 0 || board.isFull())
		{
			return result;
		}
		if (Turn)
		{
			int bestscore = -INT_MAX;
			for (int i = 0; i < board.getSize(); i++)
			{
				for (int j = 0; j < board.getSize(); j++)
				{
					if (board.isValidMove(i, j))
					{
						char currentSymbol = Turn ? symbol : (symbol == 'x' ? 'o' : 'x');
						board.makeMove(i, j, currentSymbol);
						int score = minimax(board, !Turn);
						board.undoMove(i, j);
						bestscore = max(score, bestscore);
					}
				}
			}
			return bestscore;
		}
		else
		{
			int bestScore = INT_MAX;
			for (int i = 0; i < board.getSize(); i++)
			{
				for (int j = 0; j < board.getSize(); j++)
				{
					if (board.isValidMove(i, j))
					{
						char currentSymbol = Turn ? symbol : (symbol == 'x' ? 'o' : 'x');
						board.makeMove(i, j, currentSymbol);
						int score = minimax(board, !Turn);
						board.undoMove(i, j);
						bestScore = min(bestScore, score);
					}
				}
			}
			return bestScore;
		}
	}

	int evaluateBoard(const Board &board) const
	{
		char opponent = (symbol == 'x') ? 'o' : 'x';

		if (board.checkWin(symbol))
			return 1;
		if (board.checkWin(opponent))
			return -1;

		return 0;
	}
};

class HumanPlayer : public Player
{
public:
	HumanPlayer(const string &name, char symbol) : Player(name, symbol) {}
	void getMove(int &row, int &col) override
	{
		// Loop until the move is valid on the board
		while (true)
		{
			cout << name << " (" << symbol << "), enter your move (row col): ";
			cin >> row >> col;

			if (cin.fail()) // invalid input
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input. Please enter numbers.\n";
				continue;
			}
			break;
		}
	}
};

class Game
{
private:
	Board board;
	Player *player1;
	Player *player2;
	Player *currentPlayer;

public:
	Game() : board(3), player1(nullptr), player2(nullptr), currentPlayer(nullptr) {}

	void start()
	{

		showMenu();
		board.display();

		while (!checkGameEnd())
		{
			if (AIPlayer *ai = dynamic_cast<AIPlayer *>(currentPlayer))
			{
				ai->setBoard(&board);
				handleAIMove(*ai);
			}
			else
			{
				handleHumanMove(*currentPlayer);
			}
			board.display();
			if (!checkGameEnd())
				switchPlayer();
		}

		displayResult();
		reset();
	}

	void showMenu()
	{

		cout << "Welcome to Tic Tac Toe!\n";
		cout << "1. Player vs Player\n";
		cout << "2. Player vs Computer\n";
		cout << "Choose mode: ";
		int choice;
		cin >> choice;

		if (choice == 1)
			setupPvP();
		else if (choice == 2)
		{
			cout << "Select difficulty: 1. Easy  2. Hard : ";
			int diffChoice;
			cin >> diffChoice;
			Difficulty diff = (diffChoice == 2) ? Hard : Easy;
			setupPvC(diff);
		}
		else
		{
			cout << "Invalid choice. Defaulting to PvP.\n";
			setupPvP();
		}
	}

	void setupPvP()
	{
		string name1, name2;
		cout << "Enter name for Player 1 (X): ";
		cin >> name1;
		cout << "Enter name for Player 2 (O): ";
		cin >> name2;

		player1 = new HumanPlayer(name1, 'X');
		player2 = new HumanPlayer(name2, 'O');
		currentPlayer = player1;
	}

	void setupPvC(Difficulty difficulty)
	{
		string name;
		cout << "Enter your name (X): ";
		cin >> name;

		// Create human player
		player1 = new HumanPlayer(name, 'X');

		// Create AI player
		AIPlayer *ai = new AIPlayer("Computer", 'O', difficulty);
		ai->setBoard(&board); // set board once
		player2 = ai;

		currentPlayer = player1;
	}

	void switchPlayer()
	{
		currentPlayer = (currentPlayer == player1) ? player2 : player1;
	}

	void handleHumanMove(Player &player)
	{
		int row, col;
		do
		{
			player.getMove(row, col);
		} while (!board.isValidMove(row, col));

		board.makeMove(row, col, player.getSymbol());
	}

	void handleAIMove(AIPlayer &aiPlayer)
	{
		int row, col;
		aiPlayer.getMove(row, col);
		cout << aiPlayer.getName() << " (" << aiPlayer.getSymbol() << ") chooses: "
			 << row << " " << col << endl;
	}

	bool checkGameEnd()
	{
		return board.checkWin(currentPlayer->getSymbol()) || board.isFull();
	}

	void displayResult() const
	{
		if (board.checkWin(currentPlayer->getSymbol()))
		{
			cout << currentPlayer->getName() << " wins!\n";
		}
		else
		{
			cout << "It's a draw!\n";
		}
	}

	void reset()
	{
		board.reset();
		delete player1;
		delete player2;
		player1 = player2 = currentPlayer = nullptr;
	}
};

int main()
{
	Game g;
	g.start();

	return 0;
}
