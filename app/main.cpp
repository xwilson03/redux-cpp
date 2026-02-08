#include <iostream>
import redux;


using TestStateT = int;

enum class TestActionT {
    Increment,
    Decrement,
};

void TestReducer (
    TestStateT& state,
    const TestActionT& action
) {
    if      (action == TestActionT::Increment) state += 1;
    else if (action == TestActionT::Decrement) state -= 1;
}


int main() {

    TestStateT initialState = 0;
    redux::Store<TestStateT,TestActionT> store (initialState, TestReducer);

    int i = 1;
    store.subscribe([&](const TestStateT& state){
        std::cout << std::to_string(i++) << ": " << std::to_string(state) << std::endl;
    });

    for (int i = 0; i < 5; i++) {
        store.dispatch(TestActionT::Increment);
    }

    for (int i = 0; i < 5; i++) {
        store.dispatch(TestActionT::Decrement);
    }

    /*
     *  This fails because it uses a temporary accessor which violates data safety constraints.
     *
     * {
     *     auto data = store.reader().data();
     *     std::cout << "3: " << std::to_string(data) << std::endl;
     * }
     */


}
