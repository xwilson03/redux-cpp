module;
#include <variant>
export module example_store;
import redux;
namespace Example {


export using State = int;

export struct Increment { int amount; };
export struct Decrement { int amount; };
export struct Negate    {};

using Action = std::variant<
    Increment,
    Decrement,
    Negate
>;

// std::visit syntax helper
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

void Reducer(
    State& state,
    const Action& action
) {
    std::visit(overloaded {
        [&](Increment args) { state += args.amount; },
        [&](Decrement args) { state -= args.amount; },
        [&](Negate    args) { state *= -1;          }
    }, action);
}

export class Store : public redux::Store<State, Action> {
public:
    Store(const State& state)
    : redux::Store<State, Action>(state, Reducer) {}
};


} // namespace Example
