export module example_store;
import redux;


export using ExampleState = int;

export enum class ExampleAction {
    Increment,
    Decrement,
};

void TestReducer (
    ExampleState& state,
    const ExampleAction& action
) {
    if      (action == ExampleAction::Increment) state += 1;
    else if (action == ExampleAction::Decrement) state -= 1;
}

export class ExampleStore : public redux::Store<ExampleState, ExampleAction> {
public:
    ExampleStore(const ExampleState& state)
    : redux::Store<ExampleState, ExampleAction>(state, TestReducer) {}
};
