#include <queue>
#include <thread>
#include "queue.h"
#include "actors.h"
#include "repository.h"

int main() {

    // array with 3 producers and 2 subscribers
    std::thread threads[] = {
            std::move(std::thread(Producer, 11, 6, std::ref(wheel_buffer))),
            std::move(std::thread(Producer, 12, 13, std::ref(wheel_buffer))),
            std::move(std::thread(Subscriber, 13, std::ref(wheel_buffer))),

            std::move(std::thread(Producer, 21, 1, std::ref(body_buffer))),
            std::move(std::thread(Producer, 22, 2, std::ref(body_buffer))),
            std::move(std::thread(Subscriber, 23, std::ref(body_buffer))),

            std::move(std::thread(Producer, 31, 15, std::ref(glass_buffer))),
            std::move(std::thread(Producer, 32, 25, std::ref(glass_buffer))),
            std::move(std::thread(Subscriber, 32, std::ref(glass_buffer))),

            std::move(std::thread(Producer, 41, 30, std::ref(pedal_buffer))),
            std::move(std::thread(Producer, 42, 55, std::ref(pedal_buffer))),
            std::move(std::thread(Subscriber, 43, std::ref(pedal_buffer))),
    };

    for (auto &thread: threads) {
        thread.join();
    }

    return 0;
}