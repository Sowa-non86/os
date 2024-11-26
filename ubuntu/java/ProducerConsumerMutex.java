import java.util.Random;
import java.util.Scanner;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ProducerConsumerMutex {

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

    // Lock and conditions
    private Lock lock = new ReentrantLock();
    private Condition notFull = lock.newCondition();   // Condition for producers
    private Condition notEmpty = lock.newCondition();  // Condition for consumers

    // Constructor
    public Buffer(int capacity) {
        this.capacity = capacity;
        this.buffer = new int[capacity];
    }

    // Method for producing
    public void produce(int item, int producerId) throws InterruptedException {
        lock.lock(); // Acquire the lock
        try {
            // Wait if buffer is full
            while (count == capacity) {
                System.out.println("Producer" + producerId + " blocked ... buffer full");
                notFull.await(); // Wait until not full
            }

            // Add item to buffer
            buffer[in] = item;
            System.out.println("Producer" + producerId + " inserting " + item + " in slot " + (in + 1));
            in = (in + 1) % capacity; // Circular buffer index
            count++;

            // Signal consumers that buffer is not empty
            notEmpty.signal();
        } finally {
            lock.unlock(); // Release the lock
        }
    }

    // Method for consuming
    public int consume(int consumerId) throws InterruptedException {
        lock.lock(); // Acquire the lock
        try {
            // Wait if buffer is empty
            while (count == 0) {
                System.out.println("Consumer" + consumerId + " blocked ... buffer empty");
                notEmpty.await(); // Wait until not empty
            }

            // Remove item from buffer
            int item = buffer[out];
            System.out.println("Consumer" + consumerId + " consuming " + item + " from slot " + (out + 1));
            out = (out + 1) % capacity; // Circular buffer index
            count--;

            // Signal producers that buffer is not full
            notFull.signal();
            return item;
        } finally {
            lock.unlock(); // Release the lock
        }
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
