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
	return 0;
}

// isWon Implementation
bool isWon(char player, char board[][3]) {
	// Handles rows & columns
	for (int ii = 0; ii < 3; ++ii) {
		// First conditional checks rows ([ii][0], [ii][1])
		// | Second checks for columns ([0][ii], [1][ii])
		if ((board[ii][0] == player && board[ii][1] == player && board[ii][2] == player) ||
				(board[0][ii] == player && board[1][ii] == player && board[2][ii] == player)) {
			return true;
		}
	}
	// First conditional statement checks L-R diagonal ([0][0] - [2][2])
	// | Second checks for R-L diagonal ([0][2] - [2][0]).
	if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
			(board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
		return true;
	}
	// Base case/case upon failure.
	return false;
}

// isDraw Implementation
/*
 * Checks if every slot on board has been filled.
 * If every slot has been filled while !(isWon), then isDraw
*/
bool isDraw(char board[][3]) {
	// Checks and iterates across x coordinates
	for (int ii = 0; ii < 3; ++ii) {
		// Checks and iterates across y coordinates
		for (int jj = 0; jj < 3; ++jj) {
			// If all spaces on board are not filled
            // Return false
			if (board[ii][jj] == ' ') {
				return false;
			}
		}
	}
	return true;
}

// displayBoard Implementation
void displayBoard(char board[][3]) {
	// Line break for space between displays.
	cout << endl;
	// Upper bar
	cout << "-------------" << endl;
	for (int ii = 0; ii < 3; ++ii) {
		cout << "|"; // Starts of with pipe
		// Follows up with three more pipes to distinguish
		// playable spots.
		for (int jj = 0; jj < 3; ++jj) {
			cout << " " << board[ii][jj] << " |";
		}
		// Divider bar
		cout << endl << "-------------" << endl;
	}
}

// makeAMove Implementation
/*
 * Asks user to enter row and column numbers during their turn
 * If an occupied spot is chosen, a message is printed to inform
 * the user.
 */
void makeAMove (char board[][3], char player) {
	// X & Y coordinates for player.
	int row, col;
	while (true) {
		// Prompts user for row, adds to row
		cout << "Enter a row (0, 1, 2) for player " << player << "   : ";
		cin >> row;
		// Prompts user for column, adds to col
		cout << "Enter a column (0, 1, 2) for player " << player << ": ";
		cin >> col;
		// If spot at [row][col] is empty, add player's symbol
		if (board[row][col] == ' ') {
			board[row][col] = player;
			break;
		}
		// Else notify user of bad position
		else {
			cout << "This cell is already occupied. Try a different cell" << endl;
		}
	}
}
