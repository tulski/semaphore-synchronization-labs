#ifndef KSO_LAB_3_ACTORS_H
#define KSO_LAB_3_ACTORS_H

#include <thread>
#include "buffer.h"
#include "repository.h"

void Producer(int id, int insertCount, Buffer &buffer) {
    while (true) {
        // Random delay
        std::this_thread::sleep_for(std::chrono::milliseconds(id * 200));

        log_debug(Color::WHITE, buffer.get_name() + " producer " + std::to_string(id) + " wants to insert an element");

        std::vector<int> payload(insertCount, id);
        buffer.insert(payload);

        log_debug(Color::GREEN,
                  buffer.get_name() + " producer " + std::to_string(id) + " inserted " +
                  std::to_string(payload.size()) +
                  " element");
    }
}

void Subscriber(int id, Buffer &buffer) {
    while (true) {
        // Random delay
        std::this_thread::sleep_for(std::chrono::milliseconds(id * 200));

        log_debug(Color::WHITE,
                  buffer.get_name() + " subscriber " + std::to_string(id) + " wants to retrieve elements");

        auto elements = buffer.retrieve();

        log_debug(Color::RED, buffer.get_name() + " subscriber " + std::to_string(id) + " retrieved " +
                              std::to_string(elements.size()) + " elements");
    }
}

#endif //KSO_LAB_3_ACTORS_H
