module;
#include <mutex>
#include <shared_mutex>
export module redux:store;
namespace redux {


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

    StateT& data() & { return data_; };
    StateT& data() && = delete;

}; // class StateWriter


export
template <typename StateT>
class Store {

public:
    StateReader<StateT> reader() { return StateReader(mutex_, state_); }
    StateWriter<StateT> writer() { return StateWriter(mutex_, state_); }

private:
    std::shared_mutex mutex_;
    StateT state_;

}; // class Store


} // namespace redux
