import java.util.Scanner;

public class BankersAlgorithm {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Input number of processes and resources
        System.out.print("Enter the number of processes: ");
        int n = sc.nextInt();

        System.out.print("Enter the number of resources: ");
        int m = sc.nextInt();

        // Initialize matrices and arrays
        int[][] alloc = new int[n][m];  // Allocation Matrix
        int[][] max = new int[n][m];    // Maximum Matrix
        int[] avail = new int[m];       // Available Resources

        // Input Allocation Matrix
        System.out.println("Enter the Allocation Matrix:");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                alloc[i][j] = sc.nextInt();
            }
        }

        // Input Maximum Matrix
        System.out.println("Enter the Maximum Matrix:");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                max[i][j] = sc.nextInt();
            }
        }

        // Input Available Resources
        System.out.println("Enter the Available Resources:");
        for (int j = 0; j < m; j++) {
            avail[j] = sc.nextInt();
        }

        // Initializing flags and arrays
        int[] f = new int[n];  // Finish array
        int[] ans = new int[n]; // Safe Sequence array
        int ind = 0;

        // Initialize finish flags to 0 (unfinished)
        for (int i = 0; i < n; i++) {
            f[i] = 0;
        }

        // Need Matrix calculation
        int[][] need = new int[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                need[i][j] = max[i][j] - alloc[i][j];
            }
        }

        // Banker's algorithm for safe sequence
        int y = 0;
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                if (f[i] == 0) {
                    int flag = 0;
                    for (int j = 0; j < m; j++) {
                        if (need[i][j] > avail[j]) {
                            flag = 1;
                            break;
                        }
                    }

                    if (flag == 0) {
                        ans[ind++] = i;  // Add to the safe sequence
                        for (y = 0; y < m; y++) {
                            avail[y] += alloc[i][y]; // Update available resources
                        }
                        f[i] = 1; // Mark the process as finished
                    }
                }
            }
        }

        // Checking if all processes were finished (safe state)
        int flag = 1;
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
                flag = 0;
                System.out.println("The following system is not safe");
                break;
            }
        }

        // If the system is safe, print the safe sequence
        if (flag == 1) {
            System.out.print("Following is the SAFE Sequence\n");
            for (int i = 0; i < n - 1; i++) {
                System.out.print(" P" + ans[i] + " ->");
            }
            System.out.println(" P" + ans[n - 1]);
        }
    }
}
