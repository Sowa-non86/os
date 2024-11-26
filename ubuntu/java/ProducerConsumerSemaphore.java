import java.util.Random;
import java.util.Scanner;
import java.util.concurrent.Semaphore;

public class ProducerConsumerSemaphore {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Input for number of producers, consumers, and buffer size
        System.out.print("Enter number of producers: ");
        int numProducers = scanner.nextInt();

        System.out.print("Enter number of consumers: ");
        int numConsumers = scanner.nextInt();

        System.out.print("Enter buffer size: ");
        int bufferSize = scanner.nextInt();

        // Shared buffer
        Buffer buffer = new Buffer(bufferSize);

        // Create and start producer threads
        for (int i = 1; i <= numProducers; i++) {
            new Thread(new Producer(buffer, i), "Producer" + i).start();
        }

        // Create and start consumer threads
        for (int i = 1; i <= numConsumers; i++) {
            new Thread(new Consumer(buffer, i), "Consumer" + i).start();
        }

        scanner.close();
    }
}

// Shared buffer class
class Buffer {
    private int[] buffer;  // Fixed-size buffer array
    private int capacity;  // Maximum capacity of the buffer
    private int in = 0;    // Index for the next insertion
    private int out = 0;   // Index for the next removal
    private int count = 0; // Current count of items in the buffer

    // Semaphores
    private Semaphore full = new Semaphore(0); // Initially empty
    private Semaphore empty;
    private Semaphore mutex = new Semaphore(1); // To protect critical section

    // Constructor
    public Buffer(int capacity) {
        this.capacity = capacity;
        this.buffer = new int[capacity];
        empty = new Semaphore(capacity); // Initially all slots are empty
    }

    // Method for producing
    public void produce(int item, int producerId) throws InterruptedException {
        if (empty.availablePermits() == 0) {
            System.out.println("Producer" + producerId + " blocked ... buffer full");
        }
        empty.acquire(); // Wait if buffer is full
        mutex.acquire(); // Enter critical section

        // Add item to buffer
        buffer[in] = item;
        System.out.println("Producer" + producerId + " inserting " + item + " in slot " + (in + 1));
        in = (in + 1) % capacity; // Circular buffer index
        synchronized (this) {
            count++;
        }

        mutex.release(); // Leave critical section
        full.release();  // Signal that an item is available
    }

    // Method for consuming
    public int consume(int consumerId) throws InterruptedException {
        if (full.availablePermits() == 0) {
            System.out.println("Consumer" + consumerId + " blocked ... buffer empty");
        }
        full.acquire();  // Wait if buffer is empty
        mutex.acquire(); // Enter critical section

        // Remove item from buffer
        int item = buffer[out];
        System.out.println("Consumer" + consumerId + " consuming " + item + " from slot " + (out + 1));
        out = (out + 1) % capacity; // Circular buffer index
        synchronized (this) {
            count--;
        }

        mutex.release(); // Leave critical section
        empty.release(); // Signal that a slot is available
        return item;
    }
}

// Producer class
class Producer implements Runnable {
    private Buffer buffer;
    private int id;
    private Random random = new Random();

    public Producer(Buffer buffer, int id) {
        this.buffer = buffer;
        this.id = id;
    }

    @Override
    public void run() {
        while (true) {
            try {
                int item = random.nextInt(100); // Produce a random item
                buffer.produce(item, id);
                Thread.sleep(random.nextInt(1000)); // Simulate production time
            } catch (InterruptedException e) {
                System.out.println("Producer" + id + " interrupted.");
                break;
            }
        }
    }
}

// Consumer class
class Consumer implements Runnable {
    private Buffer buffer;
    private int id;

    public Consumer(Buffer buffer, int id) {
        this.buffer = buffer;
        this.id = id;
    }

    @Override
    public void run() {
        while (true) {
            try {
                buffer.consume(id);
                Thread.sleep(new Random().nextInt(1000)); // Simulate consumption time
            } catch (InterruptedException e) {
                System.out.println("Consumer" + id + " interrupted.");
                break;
            }
        }
    }
}
