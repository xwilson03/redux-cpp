#include <iostream>
import example_store;


int main() {

    ExampleStore store(0);

    store.subscribe([](const ExampleState& state){
        std::cout << std::to_string(state) << std::endl;
    });

    for (int i = 0; i < 5; i++) store.dispatch(ExampleAction::Increment);
    for (int i = 0; i < 5; i++) store.dispatch(ExampleAction::Decrement);
}
