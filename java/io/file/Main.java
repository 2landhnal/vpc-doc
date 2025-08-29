import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        try {
            // Open file
            File file = new File("input.txt");
            Scanner sc = new Scanner(file);

            // Read rows and cols
            int rows = sc.nextInt();
            int cols = sc.nextInt();

            int[][] matrix = new int[rows][cols];

            // Read matrix elements
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    matrix[i][j] = sc.nextInt();
                }
            }

            // Print matrix
            System.out.println("The matrix is:");
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    System.out.print(matrix[i][j] + " ");
                }
                System.out.println();
            }

            sc.close();

            // Open output file
            PrintWriter out = new PrintWriter("output.txt");

            // Write matrix
            out.println("The matrix is:");
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    out.print(matrix[i][j] + " ");
                }
                out.println();
            }

            out.close();
            System.out.println("Matrix written to output.txt");
        } catch (FileNotFoundException e) {
            System.out.println("File not found!");
        }
    }
}
