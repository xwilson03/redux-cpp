module;
#include <functional>
#include <mutex>
#include <shared_mutex>
export module redux;
namespace redux {

/*
 * StateReader is publicly accessible from the store and used to access the internal state.
 */
template <typename StateT>
class StateReader {

private:
    std::shared_lock<std::shared_mutex> lock_;
    const StateT& data_;

public:
    StateReader(
        std::shared_mutex &m,
        const StateT &s
    ) : lock_(m), data_(s) {};

    const StateT& data() const & { return data_; };
    const StateT& data() const && = delete;

}; // class StateReader


/*
 * StateWriter is privated and only used by the Store internally for dispatching actions.
 */
template <typename StateT>
class StateWriter {

private:
    std::unique_lock<std::shared_mutex> lock_;
    StateT& data_;

public:
    StateWriter(
        std::shared_mutex &m,
        StateT &s
    ) : lock_(m), data_(s) {};

    StateT& data() const & { return data_; };
    StateT& data() const && = delete;

}; // class StateWriter


/*
 * Store wraps the active state with concurrent read/write access control.
 * It uses an injected reducer function to modify the state.
 */
export
template <typename StateT, typename ActionT>
class Store {

    using ReducerFn = std::function<void(StateT&, const ActionT&)>;

private:

    std::shared_mutex mutex_;
    StateT state_;
    const ReducerFn& reducer_;

    StateWriter<StateT> writer() { return StateWriter(mutex_, state_); }

public:

    Store(
        StateT state,
        const ReducerFn& reducer
    ) : state_(state), reducer_(reducer) {};

    StateReader<StateT> reader() { return StateReader(mutex_, state_); }

    void dispatch(ActionT action) {
        const auto writer = this->writer();
        reducer_(writer.data(), action);
    }

}; // class Store


} // namespace redux
