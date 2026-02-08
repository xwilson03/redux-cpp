module;
#include <functional>
#include <mutex>
#include <shared_mutex>
#include <vector>
export module redux;
namespace redux {

/*
 * StateReader is publicly accessible from the store and used to access the internal state.
 */
template <typename StateT>
class StateReader {

private:
    const std::shared_lock<std::shared_mutex> lock_;
    const StateT& data_;

public:
    StateReader(
        std::shared_mutex& m,
        const StateT& s
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
    const std::unique_lock<std::shared_mutex> lock_;
    StateT& data_;

public:
    StateWriter(
        std::shared_mutex& m,
        StateT& s
    ) : lock_(m), data_(s) {};

    StateT& data() const & { return data_; };
    StateT& data() const && = delete;

}; // class StateWriter


/*
 * Store wraps the active state with concurrent read/write access control.
 * It uses an injected reducer function to modify the state and invokes listener
 * callbacks afterwards.
 */
export
template <typename StateT, typename ActionT>
class Store {

    using ReducerFn = std::function<void(StateT&, const ActionT&)>;
    using ListenerFn = std::function<void(const StateT&)>;

private:

    std::shared_mutex mutex_;
    StateT state_;
    const ReducerFn reducer_;
    std::vector<ListenerFn> listeners_;

    const StateWriter<StateT> writer() { return StateWriter(mutex_, state_); }

public:

    Store(
        const StateT& state,
        const ReducerFn& reducer
    ) : state_(state), reducer_(reducer) {};

    const StateReader<StateT> reader() { return StateReader(mutex_, state_); }

    void dispatch(const ActionT& action) {
        {
            const auto writer = this->writer();
            reducer_(writer.data(), action);
        }
        const auto reader = this->reader();
        for (const auto& listener : listeners_) listener(reader.data());
    }

    void subscribe(const ListenerFn& listener) {
        listeners_.push_back(listener);
    }

}; // class Store


} // namespace redux
