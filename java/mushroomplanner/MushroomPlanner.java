// File: MushroomPlanner.java
// By: Ramanuja Mohanty
// Date: 04/03/2022
// Description: User enters the minimum temperature, minimum rainfall and maximum rainfall.
// user gets back a table with the caps being produced each month, and the total mushroom caps
// the user will get at the end of the time period.

// Imports the Scanner class
import java.util.Scanner;
public class MushroomPlanner
{
    // Method findMaxIndex traverses through an array,
    // and upon finding the greatest value in the array,
    // the method returns the value's index in the array.
    public static int findMaxIndex(int[] arr)
    {
        int maxIndex = 0;
        int maxInt = arr[0];
        for (int ii = 1; ii < arr.length; ++ii)
        {
            if (arr[ii] > maxInt)
            {
                maxIndex = ii;
                maxInt = arr[ii];
            }
        }
        return maxIndex;
    }
    // Main Method
    public static void main(String [] args)
    {
        // Declares object input from the Scanner class
        Scanner input = new Scanner(System.in);
        // Header
        System.out.println("Welcome to the pandemic mushroom tracker!");
        final int NUM_MONTHS = 12; // number of months in a year
        // Prompts the user to enter the lowest and highest
        // desirable rainfall levels
        System.out.print("Enter min and max rainfall for mushrooms: ");
        // Lowest rainfall level is initialized to rainMin
        int rainMin = input.nextInt();
        // Highest rainfall level is initialized to rainMax
        int rainMax = input.nextInt();
        // Prompts the user to enter the minimum temperature
        // for mushrooms to appear.
        System.out.print("Enter min temperature for mushrooms: ");
        // Initializes the value to minTemp
        int minTemp = input.nextInt();
        // Average temperatures from January to December
        int[] avgTemperature = {46, 48, 49, 50, 51, 53, 54, 55, 56, 55, 51, 47};
        // Average rainfall from January to December
        int[] avgRainfall = {5, 3, 3, 1, 1, 0, 0, 0, 0, 1, 3, 4};
        // Declares an int array newCaps of size 12
        int[] newCaps = new int[NUM_MONTHS];
        // Declares an int array totalCaps of size 12
        int[] totalCaps = new int[NUM_MONTHS];
        // Prints out the header with month, avg temp,
        // avg rainfall, new caps & total caps titles
        System.out.println("Month\tAvg Temp\tAvg Rainfall\tNew Caps\tTotal Caps");
        // Goes through newCaps and arrayCaps, assigning values to them
        for (int ii = 0; ii < NUM_MONTHS; ++ii)
        {
            // If avgRainfall is greater than the max or less than the min,
            // newCaps is set to -1.
            if (avgRainfall[ii] < rainMin || avgRainfall[ii] > rainMax)
            {
                newCaps[ii] = -1;
            }
            // Else newCaps is set to the difference of the month's avgTemperature and minTemp
            else
            {
                newCaps[ii] = avgTemperature[ii] - minTemp;
            }

            // If the current month is zero, the month's newCaps is equal to the month's totalCaps
            if (ii < 1)
            {
                totalCaps[ii] = newCaps[ii];
            }
            // Else, the month's totalCaps is set to the previous month's totalCaps plus this month's newCaps
            else
            {
                totalCaps[ii] = totalCaps[ii - 1] + newCaps[ii];
            }
            // If a month's totalCaps is less than zero, then that month's totalCaps is set to zero.
            if (totalCaps[ii] < 0)
            {
                totalCaps[ii] = 0;
            }
            // Prints out the month, avg temp, avg rainfall
            // new caps and total caps
            System.out.println(ii + "\t\t" + avgTemperature[ii] + "\t\t\t" + avgRainfall[ii] + "\t\t\t\t" + newCaps[ii] + "\t\t\t" + totalCaps[ii]);
        }
        // Extra credit
        System.out.println("Extra credit: ");
        // Prints out the greatest number of caps in the 12 months,
        // and prints out the respective month
        System.out.println("Max mushroom caps = " + totalCaps[findMaxIndex(totalCaps)] + " in month " + findMaxIndex(totalCaps));
        // Closes the input object
        input.close();
    }
}
