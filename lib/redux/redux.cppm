module;
#include <mutex>
#include <shared_mutex>
export module redux;
namespace redux {


export
template <typename StateT>
class Store {

    using Mutex = std::shared_mutex;
    using ReadLock = std::shared_lock<Mutex>;
    using WriteLock = std::unique_lock<Mutex>;

    private:
        Mutex mutex_;
        StateT state_;

    public:

        class Reader {
            ReadLock lock_;
        public:
            Reader(Mutex &m, const StateT &s) : lock_(m), data(s) {};
            const StateT& data;
        };

        class Writer {
            WriteLock lock_;
        public:
            Writer(Mutex &m, StateT &s) : lock_(m), data(s) {};
            StateT& data;
        };

        Reader reader() { return Store::Reader(mutex_, state_); }
        Writer writer() { return Store::Writer(mutex_, state_); }

}; // class Store



} // namespace redux
