#pragma once
#include <mc/deps/core/string/HashedString.h>

#include <compare>
#include <string_view>

namespace plotx {

class HashedStringView {
    uint64_t         hash_;
    std::string_view str_;

public:
    constexpr HashedStringView() noexcept : hash_(0), str_("") {}
    consteval HashedStringView(const char* str) noexcept : hash_(HashedString::computeHash(str)), str_(str) {}
    consteval HashedStringView(std::string_view str) noexcept : hash_(HashedString::computeHash(str)), str_(str) {}

    [[nodiscard]] constexpr uint64_t         getHash() const noexcept { return hash_; }
    [[nodiscard]] constexpr std::string_view getString() const noexcept { return str_; }

    [[nodiscard]] constexpr bool operator==(HashedStringView const& rhs) const noexcept { return hash_ == rhs.hash_; }

    [[nodiscard]] constexpr std::strong_ordering operator<=>(HashedStringView const& rhs) const noexcept {
        return hash_ <=> rhs.hash_;
    }
};

consteval HashedStringView operator""_hsv(const char* str, std::size_t len) {
    return HashedStringView(std::string_view(str, len));
}

struct HashedStringHasher {
    using is_transparent = void;

    std::size_t operator()(HashedStringView const& v) const noexcept { return v.getHash(); }

    std::size_t operator()(HashedString const& v) const noexcept { return v.getHash(); }

    std::size_t operator()(std::string_view v) const noexcept { return HashedString::computeHash(v); }
};

struct HashedStringEqual {
    using is_transparent = void;

    bool operator()(HashedStringView const& lhs, HashedString const& rhs) const noexcept {
        return lhs.getHash() == rhs.getHash();
    }
    bool operator()(HashedString const& lhs, HashedStringView const& rhs) const noexcept {
        return lhs.getHash() == rhs.getHash();
    }
    bool operator()(HashedString const& lhs, HashedString const& rhs) const noexcept {
        return lhs.getHash() == rhs.getHash();
    }
    bool operator()(HashedStringView const& lhs, HashedStringView const& rhs) const noexcept {
        return lhs.getHash() == rhs.getHash();
    }
};

} // namespace plotx

template <>
struct std::hash<plotx::HashedStringView> {
    std::size_t operator()(plotx::HashedStringView const& v) const noexcept { return v.getHash(); }
};