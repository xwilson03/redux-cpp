module;
#include <variant>
export module example_store;
import redux;


export using ExampleState = int;

export struct Increment { int amount; };
export struct Decrement { int amount; };
export struct Negate    {};

export using ExampleAction = std::variant<
    Increment,
    Decrement,
    Negate
>;

// std::visit syntax helper
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

void ExampleReducer(
    ExampleState& state,
    const ExampleAction& action
) {
    std::visit(overloaded {
        [&](Increment args) { state += args.amount; },
        [&](Decrement args) { state -= args.amount; },
        [&](Negate    args) { state *= -1;          }
    }, action);
}

export class ExampleStore : public redux::Store<ExampleState, ExampleAction> {
public:
    ExampleStore(const ExampleState& state)
    : redux::Store<ExampleState, ExampleAction>(state, ExampleReducer) {}
};
