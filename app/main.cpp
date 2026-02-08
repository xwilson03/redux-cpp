#include <iostream>

import redux;

int main() {
    redux::Store<float> store;

    {
        auto reader = store.reader();
        std::cout << "1: " << std::to_string(reader.data) << std::endl;
    }

    {
        auto writer = store.writer();
        writer.data = 1.0;
    }

    {
        auto reader = store.reader();
        std::cout << "2: " << std::to_string(reader.data) << std::endl;
    }

}
