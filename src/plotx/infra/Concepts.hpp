#pragma once
#include <concepts>


namespace plotx::concepts {


template <typename T>
concept HasXYZ = requires(T const& t) {
    { t.x } -> std::convertible_to<int>;
    { t.y } -> std::convertible_to<int>;
    { t.z } -> std::convertible_to<int>;
};

template <typename T>
concept HasXZ = requires(T const& t) {
    { t.x } -> std::convertible_to<int>;
    { t.z } -> std::convertible_to<int>;
};


} // namespace plotx::concepts