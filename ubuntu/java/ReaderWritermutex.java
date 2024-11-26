import java.util.Scanner;

public class ReaderWritermutex {
    // Shared variables
    private static int readerCount = 0; // Number of active readers
    private static boolean writerActive = false; // Indicates if a writer is active
    private static final Object lock = new Object(); // Lock for synchronization

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

        while (true) {
            // Randomly start writers and readers
            for (int i = 0; i < numWriters; i++) {
                int writerId = i + 1;
                new Thread(() -> writer(writerId)).start();
            }

            for (int i = 0; i < numReaders; i++) {
                int readerId = i + 1;
                new Thread(() -> reader(readerId)).start();
            }

            // Increment the shared clock
            synchronized (lock) {
                incrementClock();
            }

            try {
                Thread.sleep(1000); // Simulate 1-second delay
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                break;
            }
        }

        System.out.println("\nProcess stopped by the user.");
    }

    // Reader function
    private static void reader(int readerId) {
        synchronized (lock) {
            // Wait if a writer is active, readers can go if no writer is writing
            while (writerActive) {
                try {
                    lock.wait(); // Wait until no writer is active
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    return;
                }
            }

            readerCount++; // Increment reader count
        }

        // Simulate reading
        String timeStr = getTimeString();
        System.out.printf("Reader%d reads clock %s\n", readerId, timeStr);

        simulateDelay(100);

        synchronized (lock) {
            readerCount--; // Decrement reader count
            if (readerCount == 0) {
                lock.notifyAll(); // Notify writers waiting for readers to finish
            }
        }

        // Exiting message for reader
        System.out.printf("Reader%d exiting clock %s\n", readerId, timeStr);
    }

    // Writer function
    private static void writer(int writerId) {
        synchronized (lock) {
            // Wait if any reader is active or another writer is writing
            while (writerActive || readerCount > 0) {
                try {
                    lock.wait(); // Wait until no readers are active and no writer is writing
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    return;
                }
            }

            writerActive = true; // Mark writer as active
        }

        // Simulate writing
        String timeStr = getTimeString();
        System.out.printf("Writer%d writes clock %s\n", writerId, timeStr);

        simulateDelay(200);

        synchronized (lock) {
            writerActive = false; // Mark writer as inactive
            lock.notifyAll(); // Notify readers and writers
        }

        // Exiting message for writer
        System.out.printf("Writer%d exiting clock %s\n", writerId, timeStr);
    }

    // Increment clock logic
    private static void incrementClock() {
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
