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
        grid = vector<vector<char>>(size, vector<char>(size));
    }
    void display() const
    {
        // function implementation
    }
    bool makeMove(int row, int col, char symbol)
    {
        // function implementation

        return false; // a Temporary return
    }
    bool isValidMove(int row, int col) const
    {
        // function implementation

        return false; // a Temporary return
    }
    bool checkWin(char symbol) const
    {
        // function implementation

        return false; // a Temporary return
    }
    bool isFull() const
    {
        // function implementation

        return false; // a Temporary return
    }
    char getCell(int row, int col) const
    {
        return grid[row][col];
    }
    int getSize() const
    {
        return grid.size();
    }

    void reset()
    {
        // function implementation
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
public:
    Game()
    {
        // Function Implementation
    }
    void start()
    {
        // Function Implementation
    }
    void showMenu()
    {
        // Function Implementation
    }
    void setupPvP()
    {
        // Function Implementation
    }
    void setupPvC(Difficulty difficulty)
    {
        // Function Implementation
    }
    void switchPlayer()
    {
        // Function Implementation
    }
    void handleHumanMove(Player player)
    {
        // Function Implementation
    }
    void handleAIMove(AIPlayer aiplayer)
    {
        // Function Implementation
    }
    bool checkGameEnd()
    {
        // Function Implementation
        return false; // a Temporary return
    }
    void displayResult() const
    {
        // Function Implementation
    }
    void reset()
    {
        // Function Implementation
    }
};

int main()
{

    return 0;
}