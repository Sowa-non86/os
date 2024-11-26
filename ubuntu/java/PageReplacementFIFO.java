import java.util.Scanner;

public class PageReplacementFIFO {
    
    static final int MAX_PAGES = 100;
    static final int MAX_FRAMES = 10;
    
    static int[] pages = new int[MAX_PAGES];
    static int[] frames = new int[MAX_FRAMES];
    static int[] counter = new int[MAX_FRAMES];
    static int pageFaults = 0;
    static int pageHits = 0;

    // Initialize the frames and counters
    static void initialize() {
        for (int i = 0; i < MAX_FRAMES; i++) {
            frames[i] = -1;
            counter[i] = 0;
        }
    }

    // Display the current frame contents
    static void displayFrames(int n) {
        System.out.print("Frames: ");
        for (int i = 0; i < n; i++) {
            if (frames[i] == -1) {
                System.out.print("- ");
            } else {
                System.out.print(frames[i] + " ");
            }
        }
        System.out.println();
    }

    // FIFO page replacement algorithm
    static void fifo(int numFrames, int numPages) {
        initialize();
        int frameIndex = 0;

        for (int i = 0; i < numPages; i++) {
            int page = pages[i];
            boolean found = false;

            // Check if the page is already in any frame
            for (int j = 0; j < numFrames; j++) {
                if (frames[j] == page) {
                    found = true;
                    pageHits++;
                    break;
                }
            }

            // If page is not found in frames, replace the page using FIFO
            if (!found) {
                frames[frameIndex] = page;
                frameIndex = (frameIndex + 1) % numFrames;
                pageFaults++;
            }

            displayFrames(numFrames);
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int numPages, numFrames;
        float hitRatio, faultRatio;

        // Input the number of pages
        System.out.print("Enter number of pages: ");
        numPages = scanner.nextInt();

        // Input the page reference string
        System.out.println("Enter the page reference string:");
        for (int i = 0; i < numPages; i++) {
            pages[i] = scanner.nextInt();
        }

        // Input the number of frames
        System.out.print("Enter number of frames: ");
        numFrames = scanner.nextInt();

        // Run the FIFO algorithm
        fifo(numFrames, numPages);
        
        // Calculate and display results
        hitRatio = (float) pageHits / numPages;
        faultRatio = (float) pageFaults / numPages;

        System.out.println("\nResults:");
        System.out.println("Number of Faults: " + pageFaults);
        System.out.println("Number of Hits: " + pageHits);
        System.out.printf("Hit Ratio: %.2f\n", hitRatio);
        System.out.printf("Fault Ratio: %.2f\n", faultRatio);
        
        scanner.close();
    }
}
