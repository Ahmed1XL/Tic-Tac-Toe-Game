#include <iostream>
#include <vector>
using namespace std;


enum Difficulty
{
	Easy,
	Medium,
	Hard
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
		for (int i = 0; i < size; i++) {
			cout << "  " << i << " ";
		}
		cout << "\n";

		for (int i = 0; i < size; i++) {
			cout << i << " ";
			for (int j = 0; j < size; j++) {
				cout << "| " << grid[i][j] << " ";
			}
			cout << "|\n";

			if (i < size - 1) {
				cout << "  ";
				for (int j = 0; j < size; j++) {
					cout << "+---";
				}
				cout << "+\n";
			}
		}
		cout << "\n";
	}

	bool makeMove(int row, int col, char symbol)
	{
		if (isValidMove(row, col)) {
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
		for (int i = 0; i < size; i++) {
			bool rowWin = true;
			for (int j = 0; j < size; j++) {
				if (grid[i][j] != symbol) {
					rowWin = false;
					break;
				}
			}
			if (rowWin) return true;
		}

		// Check columns
		for (int j = 0; j < size; j++) {
			bool colWin = true;
			for (int i = 0; i < size; i++) {
				if (grid[i][j] != symbol) {
					colWin = false;
					break;
				}
			}
			if (colWin) return true;
		}

		// Check main diagonal
		bool mainDiag = true;
		for (int i = 0; i < size; i++) {
			if (grid[i][i] != symbol) {
				mainDiag = false;
				break;
			}
		}
		if (mainDiag) return true;

		// Check anti-diagonal
		bool antiDiag = true;
		for (int i = 0; i < size; i++) {
			if (grid[i][size - 1 - i] != symbol) {
				antiDiag = false;
				break;
			}
		}
		return antiDiag;
	}

	bool isFull() const
	{
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (grid[i][j] == ' ') {
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
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				grid[i][j] = ' ';
			}
		}
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

public:
	AIPlayer(const string &name, char symbol, Difficulty difficulty) : Player(name, symbol), difficulty(difficulty)
	{
	}
	void getMove(int &row, int &col) override
	{
		// Function Implementation
	}
	void setDifficulty(Difficulty newDifficulty)
	{
		this->difficulty = newDifficulty;
	}
	void getRandomMove(const Board &board, int &row, int &col) const
	{
		// Function Implementation
	}
	void getBestMove(const Board &board, int &row, int &col) const
	{
		// Function Implementation
	}
	int evaluateBoard(const Board &board) const
	{
		// Function Implementation

		return 0; // a Temporary return
	}
};

class Game
{
private:
	Board board;
	Player* player1;
	Player* player2;
	Player* currentPlayer;
public:
	Game() : board(3) {
		player1 = nullptr;
		player2 = nullptr;
		currentPlayer = nullptr;
	}
	void start()
	{
		// Function Implementation
		showMenu();
		board.display();

		while (!checkGameEnd()) {
			if (dynamic_cast<AIPlayer*>(currentPlayer)) {
				handleAIMove(*dynamic_cast<AIPlayer*>(currentPlayer));
			} else {
				handleHumanMove(*currentPlayer);
			}
			board.display();
			if (!checkGameEnd()) switchPlayer();
		}

		displayResult();
		reset();
	}
	void showMenu()
	{
		// Function Implementation
		cout << "Welcome to Tic Tac Toe!\n";
		cout << "1. Player vs Player\n";
		cout << "2. Player vs Computer (Easy)\n";
		cout << "Choose mode: ";
		int choice;
		cin >> choice;

		if (choice == 1) {
			setupPvP();
		} else {
			setupPvC(Easy);
		}
	}
}
void setupPvP()
{
	// Function Implementation
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
	// Function Implementation
	string name;
	cout << "Enter your name (X): ";
	cin >> name;

	player1 = new Player(name, 'X');
	player2 = new AIPlayer("Computer", 'O', difficulty);
	currentPlayer = player1;
}
void switchPlayer()
{
	// Function Implementation
	currentPlayer = (currentPlayer == player1) ? player2 : player1;
}
void handleHumanMove(Player player)
{
	// Function Implementation
	int row, col;
	do {
		cout << player.getName() << " (" << player.getSymbol() << "), enter your move (row col): ";
		cin >> row >> col;
	} while (!board.isValidMove(row, col));

	board.makeMove(row, col, player.getSymbol());
}

}
void handleAIMove(AIPlayer aiplayer)
{
	// Function Implementation
	int row, col;
	aiPlayer.getRandomMove(board, row, col); // simple AI for now
	cout << aiPlayer.getName() << " (" << aiPlayer.getSymbol() << ") chooses: "
			<< row << " " << col << endl;
	board.makeMove(row, col, aiPlayer.getSymbol());

}
bool checkGameEnd()
{
	// Function Implementation
	if (board.checkWin(currentPlayer->getSymbol()) || board.isFull()) {
		return true;
	}
	return false;
}
void displayResult() const
{
	// Function Implementation
	if (board.checkWin(currentPlayer->getSymbol())) {
		cout << currentPlayer->getName() << " wins!\n";
	} else {
		cout << "It's a draw!\n";
	}
}
void reset()
{
	// Function Implementation
	board.reset();
	delete player1;
	delete player2;
	player1 = player2 = currentPlayer = nullptr;
}
};

int main()
{

	return 0;
}
