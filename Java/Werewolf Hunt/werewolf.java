//  File: werewolf.java
//  By: Ramanuja Mohanty
//  Date: 4/21/2022
//  Description: Accepts integer commands from the user
//  to dictate where the werewolf will go. If the werewolf reaches the human,
// it will return how many moves it took.

// Imports Scanner class.
import java.util.Scanner;
// Werewolf class.
public class werewolf
{
    // Main method.
    public static void main(String [] args)
    {
        // Side length of 2-D array.
        final int SIDE_WIDTH = 12;
        char[][] points = new char[SIDE_WIDTH][SIDE_WIDTH]; // 12x12 gamescreen
        int[] werewolfLocation = new int[2];   // ii jj location for werewolf
        int[] humanLocation = new int[2];   // ii jj location for werewolf
        // initialize gamescreen
        for (int ii = 0; ii < points.length; ii++)
        {
            for (int jj = 0; jj < points[ii].length; jj++)
            {
                points[ii][jj] = '.';
            }
        }
        // Creates input object from Scanner class.
        Scanner input = new Scanner(System.in);
        // Prompts user to enter location of werewolf & initialize
        // values to elements in werewolfLocation.
        System.out.print("Enter (ii,jj) location of werewolf: ");
        werewolfLocation[0] = input.nextInt();
        werewolfLocation[1] = input.nextInt();
        points[werewolfLocation[0]][werewolfLocation[1]] = 'W';
        // Prompts user to enter location of werewolf & initialize
        // values to elements in humanLocation.
        System.out.print("Enter (ii,jj) location of human: ");
        humanLocation[0] = input.nextInt();
        humanLocation[1] = input.nextInt();
        points[humanLocation[0]][humanLocation[1]] = 'H';
        // Counter for the number of times the werewolf moves.
        int moveCounter = 0;
        // Displays current points array.
        displayPoints(points);
        // While humanLocation does not contain W, the loop will execute.
        while(points[humanLocation[0]][humanLocation[1]] != 'W')
        {
            System.out.print("Enter move (7: j--, 8: i++, 9: i--, 0: j++): ");
            int command = input.nextInt();
            moveWolf(command, werewolfLocation, points);
            displayPoints(points);
            ++moveCounter;
        }
        // Prints out the confirmation message and how many moves it took.
        System.out.println("The werewolf found the human in " + moveCounter + " moves!");
        // Closes input object.
        input.close();
    }
    // The displayPoints. Takes in character 2-D array p.
    public static void displayPoints(char [][] p)
    {
        // The current gamescreen
        System.out.println("Current gamescreen:");
        // Listing of all the characters.
        System.out.println("012345678901");
        // Printing values of p in matrix form.
        for (int ii = 0; ii < p.length; ++ii)
        {
            for (int jj = 0; jj < p[ii].length; ++jj)
            {
                System.out.print(p[ii][jj]);
            }
            System.out.println();
        }
    }
    // The moveWolf method moves the wolf. Takes the command int,
    // wLoc array, & character 2-D array p.
    public static void moveWolf(int command, int[] wLoc, char[][] p)
    {
        // Left
        if (command == 7) --wLoc[1];
        // Down
        else if (command == 8) ++wLoc[0];
        // Up
        else if (command == 9) --wLoc[0];
        // Right
        else if (command == 0) ++wLoc[1];
        // Breaks out if value is not 7 8 9 or 0.
        else
        {
            System.out.println(command + " IS AN INVALID INPUT.");
            System.exit(1);
        }
        // Character at location wLoc[0] & wLoc[1] is W.
        p[wLoc[0]][wLoc[1]] = 'W';
    }
}
