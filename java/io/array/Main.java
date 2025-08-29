import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        // defining array size
        int size;

        Scanner sc = new Scanner(System.in);
        System.out.print("Enter size of array: ");
        size = sc.nextInt();

        // defining array of size "size"
        int[] numbers = new int[size];

        // using loop to move to every array element
        // and insert the value given by the user
        System.out.print("Enter numbers: ");
        for (int i = 0; i < size; i++) {
            numbers[i] = sc.nextInt();
        }

        // Print the array elements
        System.out.print("The array elements are: ");
        for (int i = 0; i < size; i++) {
            System.out.print(numbers[i] + " ");
        }

        sc.close();
    }
}
