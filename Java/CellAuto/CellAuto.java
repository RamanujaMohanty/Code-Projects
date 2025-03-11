// File: MushroomPlanner.java
// By: Ramanuja Mohanty
// Date: 04/14/2022
// Description: User enters the number of cells (which has to be less than 80),
// the number of cell steps the user wants, and the indices of the cells that
// the user wants to be filled in.

// Imports the Scanner class.
import java.util.Scanner;
public class CellAuto
{
    // Method to display the contents of the cells.
    public static void displayCells(int[] data)
    {
        // Traverses the inputted array.
        for (int ii = 0; ii < data.length; ++ii)
        {
            // If element at index ii is 1, prints #. Else, prints ' '(space).
            if (data[ii] == 1)
            {
                System.out.print('#');
            }
            else
            {
                System.out.print(' ');
            }
        }
        // One line gap.
        System.out.println();
    }
    public static int[] updateCells(int[] data)
    {
        // Creates a new array called result that's a clone of data.
        int[] result = data.clone();
        // Checks that check the position of values in data at indices ii - 1, ii, & ii +1.
        // Based on that, value is assigned to result at index ii.
        for (int ii = 1; ii < result.length - 1; ++ii)
        {
            if (data[ii - 1] == 1 && data[ii] == 1 && data[ii + 1] == 1)
            {
                result[ii] = 0;
            }
            else if (data[ii - 1] == 1 && data[ii] == 1 && data[ii + 1] == 0)
            {
                result[ii] = 1;
            }
            else if (data[ii - 1] == 1 && data[ii] == 0 && data[ii + 1] == 1)
            {
                result[ii] = 1;
            }
            else if (data[ii - 1] == 1 && data[ii] == 0 && data[ii + 1] == 0)
            {
                result[ii] = 1;
            }
            else if (data[ii - 1] == 0 && data[ii] == 1 && data[ii + 1] == 1)
            {
                result[ii] = 0;
            }
            else if (data[ii - 1] == 0 && data[ii] == 1 && data[ii + 1] == 0)
            {
                result[ii] = 1;
            }
            else if (data[ii - 1] == 0 && data[ii] == 0 && data[ii + 1] == 1)
            {
                result[ii] = 1;
            }
            else
            {
                result[ii] = 0;
            }
        }
        // Returns result array.
        return result;
    }
    // Method that prints the header to reference the position of the hashes.
    public static void printHeader(int count)
    {
        // For loop that goes up to count.
        for (int ii = 0; ii < count; ++ii)
        {
            // Prints the value of ii mod 10.
            System.out.print(ii % 10);
        }
        // One line gap.
        System.out.println();
    }
    // Main method.
    public static void main(String[] args)
    {
        // Creates object input from class Scanner.
        Scanner input = new Scanner(System.in);
        // Intro statement.
        System.out.println("Welcome to the 1D cellular automaton simulation!");
        // Prompts user to enter number of cells in array. Value is
        // assigned to cellCount.
        System.out.print("Enter number of cells (<= 80) : ");
        int cellCount = input.nextInt();
        // Declares a new array cells of size cellCount.
        int[] cells = new int[cellCount];
        // Prompts user to enter number of time steps. Value is
        // assigned to stepCount.
        System.out.print("Enter number of time steps: ");
        int stepCount = input.nextInt();
        // Prompts user to enter number of cells in that are filled in
        // at first time step.
        System.out.print("Enter the index of occupied cells (negative index to end) : ");
        // While true, if inputted value is less than 0, or greater than cellCount, break.
        // Else, value at index ii is 1.
        while (true)
        {
            int index = input.nextInt();
            if (index < 0 || index >= cellCount)
            {
                break;
            }
            cells[index] = 1;
        }
        // One line gap.
        System.out.println();
        // Prints the header.
        printHeader(cellCount);
        // Displays the current contents of the array cells.
        displayCells(cells);
        // For loop that runs the number of times that is assigned to stepCount.
        for (int ii = 0; ii < stepCount; ++ii)
        {
            // cells array is updated using the updateCells method.
            cells = updateCells(cells);
            // Displays the new contents of cells.
            displayCells(cells);
        }
        // Closes the input object.
        input.close();
    }
}
