#pragma once

#include <coroutine>

namespace co {
    template<typename T>
    concept Numerical = std::is_arithmetic_v<T>;

    template<Numerical T>
    struct generator {
        struct promise_type;
        using handle_type = std::coroutine_handle<promise_type>;

        struct promise_type {
            T value;
            std::exception_ptr exception;

            generator get_return_object() {
                return generator(handle_type::from_promise(*this));
            }
            std::suspend_always initial_suspend() { return {}; }
            std::suspend_always final_suspend() noexcept { return {}; }
            void unhandled_exception() { exception = std::current_exception(); }
            template<typename U>
            std::suspend_always yield_value(U &&value) {
                this->value = std::forward<U>(value);
                return {};
            }
            void return_void() {}
        };

        handle_type coro;

        generator(handle_type h) : coro(h) {}
        ~generator() { if (coro) coro.destroy(); }

        T operator()() {
            coro.resume();
            if (coro.done()) {
                if (coro.promise().exception)
                    std::rethrow_exception(coro.promise().exception);
            }
            return coro.promise().value;
        }
    };
}