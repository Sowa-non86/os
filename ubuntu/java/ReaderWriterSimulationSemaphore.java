import java.util.Scanner;
import java.util.concurrent.Semaphore;

public class ReaderWriterSimulationSemaphore {
    // Shared variables
    private static int readerCount = 0; // Number of active readers
    private static Semaphore mutex = new Semaphore(1); // Protects readerCount
    private static Semaphore writerLock = new Semaphore(1); // Ensures writers get exclusive access

    // Time variables
    private static int hours, minutes, seconds;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Input the number of readers and writers
        System.out.print("Enter the number of readers: ");
        int numReaders = scanner.nextInt();
        System.out.print("Enter the number of writers: ");
        int numWriters = scanner.nextInt();

        // Input the clock start time
        System.out.print("Enter clock start (hh:mm:ss): ");
        String startTime = scanner.next();
        String[] timeParts = startTime.split(":");
        hours = Integer.parseInt(timeParts[0]);
        minutes = Integer.parseInt(timeParts[1]);
        seconds = Integer.parseInt(timeParts[2]);

        System.out.println("Press Ctrl+C to stop the process.");

        // Infinite loop to keep the program running
        while (true) {
            // Randomly create threads for writers
            for (int i = 0; i < numWriters; i++) {
                int writerId = i + 1;
                new Thread(() -> writer(writerId)).start();
            }

            // Randomly create threads for readers
            for (int i = 0; i < numReaders; i++) {
                int readerId = i + 1;
                new Thread(() -> reader(readerId)).start();
            }

            // Increment the shared clock
            incrementClock();

            try {
                Thread.sleep(1000); // Simulate 1-second delay for the clock
            } catch (InterruptedException e) {
                System.out.println("\nProcess interrupted by user.");
                break;
            }
        }
    }

    // Reader function
    private static void reader(int readerId) {
        try {
            // Protect readerCount updates
            mutex.acquire();
            readerCount++;
            if (readerCount == 1) {
                // First reader locks the writer
                writerLock.acquire();
            }
            mutex.release();

            // Simulate reading
            String timeStr = getTimeString();
            System.out.printf("Reader%d reads clock %s\n", readerId, timeStr);

            simulateDelay(100);

            // Protect readerCount updates
            mutex.acquire();
            readerCount--;
            if (readerCount == 0) {
                // Last reader unlocks the writer
                writerLock.release();
            }
            mutex.release();

            // Exiting message for reader
            System.out.printf("Reader%d exiting clock %s\n", readerId, timeStr);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    // Writer function
    private static void writer(int writerId) {
        try {
            // Ensure exclusive access for the writer
            writerLock.acquire();

            // Simulate writing
            String timeStr = getTimeString();
            System.out.printf("Writer%d writes clock %s\n", writerId, timeStr);

            simulateDelay(200);

            // Release writer lock
            writerLock.release();

            // Exiting message for writer
            System.out.printf("Writer%d exiting clock %s\n", writerId, timeStr);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    // Increment clock logic
    private static synchronized void incrementClock() {
        seconds++;
        if (seconds == 60) {
            seconds = 0;
            minutes++;
        }
        if (minutes == 60) {
            minutes = 0;
            hours++;
        }
        if (hours == 24) {
            hours = 0;
        }
    }

    // Get current time as string
    private static String getTimeString() {
        return String.format("%02d:%02d:%02d", hours, minutes, seconds);
    }

    // Simulate delay for a given duration
    private static void simulateDelay(int iterations) {
        for (int i = 0; i < iterations * 100000; i++) {
            // Busy-wait to simulate delay
        }
    }
}
