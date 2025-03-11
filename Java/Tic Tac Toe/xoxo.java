import java.util.Scanner;

public class xoxo {
    public static void main(String[] args) {

        // create scanner to read user input
        // create char[] array to store board values
        // set positions of board from 1 to 9
        // 2 players: 'X' and 'O', start with 'X'
        Scanner input = new Scanner(System.in);
        char board[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        char player = 'X';

        // display the playing board in 3x3 layout
        display(board);

        // play game until gameOver is true
        boolean gameOver = false;
        while (!gameOver) {
            // get current player choice, and update board value
            receiveUserChoice(player, input, board);
            // display the updated board
            display(board);
            // switch player 'X' -> 'O' or 'O' -> 'X'
            player = (player == 'X') ? 'O' : 'X';
            // check for winner, draw or game is not over yet
            gameOver = isGameOver(board);

            // ** important ** remove the following statement
            // I added it to avoid infinite loop
            // gameOver value should return from isGameOver() method as above

        }
    }


    // display board in 3x3 layout
    // note that array indices from 0 to 8 = positions from 1 to 9
    public static void display(char[] board) {
        System.out.println("");
        System.out.println(board[0] + " | " + board[1] + " | " + board[2]);
        System.out.println(board[3] + " | " + board[4] + " | " + board[5]);
        System.out.println(board[6] + " | " + board[7] + " | " + board[8]);
        System.out.println("");
    }


    // get current player choice, and update board value
    public static void receiveUserChoice(char player, Scanner input, char[] board) {
        // Step 1: get user input, a position from 1 to 9
        // Step 2: make sure it is a valid position, and the position is not taken yet
        //    2.1: if it is valid input, mark the board position with the current player
        //    2.2: if it is not valid, print message repeat Step 1. until a valid input is obtained

        // TODO: Add statements
        while (true) {
            System.out.println("Enter a position from 1 - 9: ");
            int i = input.nextInt();
            if (i <= 10 && i >= 0 && board[i-1] != 'X' && board[i-1] != 'O') {
                board[i-1] = player;
                break;
            } else
                System.out.println("Not Valid");
        }
    }


    // check for winner, draw or game is not over yet
    public static boolean isGameOver(char[] board) {
        // Step 1: if there is a winner, print winner message, return true
        // Step 2: if it is a draw, print draw message, return true
        // Step 3: else the game is not over yet, return false

        // TODO: Add statements
        if (board[0] == board[1] && board[1] == board[2]) {
            return winner();
        }
        if (board[0] == board[3] && board[3] == board[6]) {
            return winner();
        }
        if (board[0] == board[4] && board[4] == board[8]) {
            return winner();
        }
        if (board[1] == board[4] && board[4] == board[7]) {
            return winner();
        }
        if (board[2] == board[5] && board[5] == board[8]) {
            return winner();
        }
        if (board[3] == board[4] && board[4] == board[5]) {
            return winner();
        }
        if (board[6] == board[7] && board[7] == board[8]) {
            return winner();
        }
        if (board[2] == board[4] && board[4] == board[6]) {
            return winner();
        }
        for (char c : board) {
            if (c != 'X' && c != 'O') {
                return false;
            }
        } // If its a draw
        System.out.println("It's a draw !");

        return true; // TODO: change this to correct value!
    }

    public static boolean winner() { // method to utilize return winner
        System.out.println("Congratulations You have won !");
        return true;
    }
} // Final Result & Code Executed
