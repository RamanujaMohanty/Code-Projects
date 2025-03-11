import java.util.Scanner;
public class doubleIncrements
{
        public static void main(String[] args)
        {
                Scanner scanner = new Scanner(System.in);
                System.out.print("Enter low and high: ");
                double low = scanner.nextDouble();
                double high = scanner.nextDouble();
                for (double ii = low; ii <= high; ii += 0.5)
                {
                        System.out.println(ii);
                }
                scanner.close();
        }
}
