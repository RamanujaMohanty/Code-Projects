/****************************************************************
 *
 * File: [tic_tac_toe.cpp]
 * By: [Ramanuja Mohanty]
 * Date: [07/02/25]
 *
 * Description: [Implement the provided methods to determine a
 *		 winner, a draw, display the board, make a move]
 * ****************************************************************/

#include <iostream>
using namespace std;

// Function declarations (asked professor | implemented separately)
bool isWon(char, char[][3]);
bool isDraw(char[][3]);
void displayBoard(char[][3]);
void makeAMove(char[][3], char);

int main() {
	//
	//	PLEASE DO NOT CHANGE function main
	//
	char board[3][3] = { { ' ', ' ', ' ' },{ ' ', ' ', ' ' },{ ' ', ' ', ' ' } };
	displayBoard(board);

	while (true) {

		// The first player makes a move
		makeAMove(board, 'X');
		displayBoard(board);

		if (isWon('X', board)) {
			cout << "X player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}

		// The second player makes a move
		makeAMove(board, 'O');
		displayBoard(board);

		if (isWon('O', board)) {
			cout << "O player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}
	}

	// displayBoard Implementation
	void displayBoard(char board[][3]) {
		cout << "-------------" << endl;
		for (int ii = 0; ii < 3; ++ii) {
			cout << "|";
			for (int jj = 0; jj < 3; ++jj) {
				cout << " " << board[i][j] << " |";
			}
			cout << endl << "-------------" << endl;
		}
	}

	// makeAMove Implementation
	void makeAMove (char board[][3], char player) {
		int row, col;
		cout << "Enter a row (0, 1, 2) for player " << player << "   : ";
	}

	return 0;
} 
