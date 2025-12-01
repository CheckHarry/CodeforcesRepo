#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <array>

// =====================================================
// FAST I/O AND PARSING LIBRARY
// =====================================================

namespace IO {
    // 1. Fast I/O Setup
    void setup() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);
    }

    // 2. Generic Input for Fundamental Types
    template <typename T>
    void read(T& x) {
        std::cin >> x;
    }

    // 3. Input for std::pair
    template <typename T1, typename T2>
    void read(std::pair<T1, T2>& p) {
        read(p.first);
        read(p.second);
    }

    // 4. Input for std::vector
    template <typename T>
    void read(std::vector<T>& v) {
        for (auto& x : v) {
            read(x);
        }
    }

    // 5. Input for std::array
    template <typename T, std::size_t N>
    void read(std::array<T, N>& a) {
        for (auto& x : a) {
            read(x);
        }
    }

    // 6. Input for C-style array (requires size to be known or passed differently, 
    //    but usually handled via loops in main. Here is a wrapper if size is known at compile time)
    template <typename T, size_t N>
    void read(T (&a)[N]) {
        for (size_t i = 0; i < N; ++i) {
            read(a[i]);
        }
    }

    // 7. Variadic Template to read multiple arguments
    template <typename T, typename... Args>
    void read(T& head, Args&... tail) {
        read(head);
        read(tail...);
    }
}