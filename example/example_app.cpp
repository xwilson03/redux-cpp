#include <iostream>
import example_store;


int main() {

    Example::Store store;

    store.subscribe([](const Example::State& state){
        std::cout << std::to_string(state) << std::endl;
    });

    for (int i = 0; i < 5; i++) store.dispatch(Example::Increment {2} );
    for (int i = 0; i < 5; i++) store.dispatch(Example::Decrement {1} );
    store.dispatch(Example::Negate {} );
}
