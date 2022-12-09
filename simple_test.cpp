#include <thread>
#include "actors.h"

int main() {

    std::thread threads[] = {
            std::move(std::thread(Producer, 11, 1, std::ref(wheel_buffer))),
            std::move(std::thread(Subscriber, 13, std::ref(wheel_buffer))),
    };

    for (auto &thread: threads) {
        thread.join();
    }

    return 0;
}