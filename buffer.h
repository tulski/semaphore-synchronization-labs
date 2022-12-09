#ifndef KSO_LAB_3_BUFFER_H
#define KSO_LAB_3_BUFFER_H


#include <mutex>
#include "queue.h"

class Buffer {

private:
    // Name of the buffer
    std::string name_;

    // Maximum capacity of the buffer
    int capacity_;

    // Number of elements returned when retrieving from the buffer
    int retrieve_elements_count;

    // Mutex for synchronizing access to the queue
    std::mutex mutex_;

    // Condition variable for controlling access to the queue
    std::condition_variable condition_;

    // Queue containing the elements
    Queue queue_;

public:
    // Constructor
    Buffer(std::string name, int capacity, int numReturned, Queue::QueueType type)
            : name_(std::move(name)), capacity_(capacity), queue_(Queue(type)), retrieve_elements_count(numReturned) {
    }

    // insert an element into the buffer
    void insert(std::vector<int> elements) {
        // Use a semaphore to protect access to the queue
        std::unique_lock<std::mutex> lock(mutex_);

        // Wait for space to become available in the buffer
        condition_.wait(lock, [this] { return queue_.number_of_elements_() < capacity_; });

        // Add the element to the queue depending on its type
        for (auto &element: elements) {
            queue_.add_element(element);
        }

        // Signal that a new element has been received
        condition_.notify_one();
    }

    // retrieve an element from the buffer
    std::vector<int> retrieve() {
        // protect access to the queue
        std::unique_lock<std::mutex> lock(mutex_);

        // wait for elements to become available
        condition_.wait(lock, [this] { return queue_.number_of_elements_() >= retrieve_elements_count; });

        // retrieve the specified number of elements
        std::vector<int> retrieved;
        for (int i = 0; i < retrieve_elements_count; ++i) {
            retrieved.push_back(queue_.get_element());
        }


        // signal that elements have been retrieved
        condition_.notify_one();

        return retrieved;
    }

    std::string to_string() {
        return name_ + " - " + std::to_string(queue_.number_of_elements_()) + "/" + std::to_string(capacity_);
    }

    std::string get_name() {
        return name_;
    }

};

#endif //KSO_LAB_3_BUFFER_H
