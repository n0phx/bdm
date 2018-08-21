#pragma once

#include "computations.h"
#include "types.h"

namespace bdm
{

template <dim_t L, typename T>
struct vec_base
{
    T values[L];

    constexpr vec_base() : values{}
    {
    }

    template <typename... Vs, std::enable_if_t<(sizeof...(Vs) == L)>* = nullptr>
    constexpr vec_base(Vs... vs) : values{vs...}
    {
    }

    template <typename U>
    constexpr explicit vec_base(const vec_base<L, U>& v)
    {
        std::copy(std::begin(v.values), std::end(v.values), std::begin(values));
    }

    template <typename U>
    constexpr vec_base& operator=(const vec_base<L, U>& v)
    {
        std::copy(std::begin(v.values), std::end(v.values), std::begin(values));
        return *this;
    }
};

template <typename T>
struct vec_base<2, T>
{
    T x;
    T y;

    constexpr vec_base() : x{}, y{}
    {
    }

    template <typename U, typename V>
    constexpr vec_base(U xv, V yv) : x{xv}, y{yv}
    {
    }

    template <typename U>
    constexpr explicit vec_base(const vec_base<2, U>& v) : vec_base{v.x, v.y}
    {
    }

    template <typename U>
    constexpr vec_base& operator=(const vec_base<2, U>& v)
    {
        x = v.x;
        y = v.y;
        return *this;
    }
};

template <typename T>
struct vec_base<3, T>
{
    T x;
    T y;
    T z;

    constexpr vec_base() : x{}, y{}, z{}
    {
    }

    template <typename U, typename V, typename X>
    constexpr vec_base(U xv, V yv, X zv) : x{xv}, y{yv}, z{zv}
    {
    }

    template <typename U>
    constexpr explicit vec_base(const vec_base<3, U>& v)
        : vec_base{v.x, v.y, v.z}
    {
    }

    template <typename U>
    constexpr vec_base& operator=(const vec_base<3, U>& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
};

template <typename T>
struct vec_base<4, T>
{
    T x;
    T y;
    T z;
    T w;

    constexpr vec_base() : x{}, y{}, z{}, w{}
    {
    }

    template <typename U, typename V, typename X, typename Y>
    constexpr vec_base(U xv, V yv, X zv, Y wv) : x{xv}, y{yv}, z{zv}, w{wv}
    {
    }

    template <typename U>
    constexpr explicit vec_base(const vec_base<4, U>& v)
        : vec_base{v.x, v.y, v.z, v.w}
    {
    }

    template <typename U>
    constexpr vec_base& operator=(const vec_base<4, U>& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
        return *this;
    }
};

template <dim_t L, typename T>
struct vec : vec_base<L, T>
{
    using value_type = T;

    enum
    {
        dimension = L
    };

    constexpr vec() = default;
    ~vec() = default;

    vec(const vec&) = default;
    vec& operator=(const vec&) = default;

    vec(vec&&) noexcept = default;
    vec& operator=(vec&&) noexcept = default;

private:
    template <typename U, dim_t... I>
    constexpr vec(U v, [[maybe_unused]] dim_seq<I...>);

public:
    template <typename U>
    constexpr explicit vec(U v);

    template <typename... Ts, std::enable_if_t<sizeof...(Ts) == L>* = nullptr>
    constexpr vec(Ts... vals);

    template <typename U>
    constexpr explicit vec(const vec<L, U>& v);

    template <typename U>
    constexpr vec& operator=(const vec<L, U>& rhs);

private:
    template <typename..., dim_t S = L>
    std::enable_if_t<(S <= 4), T*> data();
    template <typename..., dim_t S = L>
    std::enable_if_t<(S <= 4), const T*> data() const;
    template <typename..., dim_t S = L>
    std::enable_if_t<(S > 4), T*> data();
    template <typename..., dim_t S = L>
    std::enable_if_t<(S > 4), const T*> data() const;

public:
    T& operator[](dim_t index);
    const T& operator[](dim_t index) const;

    template <typename F, typename..., dim_t S = L>
    std::enable_if_t<(S < 4), vec&> apply(F func);
    template <typename F, typename..., dim_t S = L>
    std::enable_if_t<(S >= 4), vec&> apply(F func);

    template <typename F, typename..., dim_t S = L>
    std::enable_if_t<(S < 4), const vec&> apply(F func) const;
    template <typename F, typename..., dim_t S = L>
    std::enable_if_t<(S >= 4), const vec&> apply(F func) const;

    template <typename F, typename U, typename..., dim_t S = L>
    std::enable_if_t<(S < 4), vec&> apply(F func, const vec<L, U>& rhs);
    template <typename F, typename U, typename..., dim_t S = L>
    std::enable_if_t<(S >= 4), vec&> apply(F func, const vec<L, U>& rhs);

    template <typename F, typename U, typename..., dim_t S = L>
    std::enable_if_t<(S < 4), const vec&> apply(F func, const vec<L, U>& rhs) const;
    template <typename F, typename U, typename..., dim_t S = L>
    std::enable_if_t<(S >= 4), const vec&> apply(F func, const vec<L, U>& rhs) const;

    vec& operator++();
    vec& operator--();

    template <typename U>
    vec& operator+=(U rhs);
    template <typename U>
    vec& operator+=(const vec<L, U>& rhs);
    vec& operator+=(const vec& rhs);

    template <typename U>
    vec& operator-=(U rhs);
    template <typename U>
    vec& operator-=(const vec<L, U>& rhs);
    vec& operator-=(const vec& rhs);

    template <typename U>
    vec& operator*=(U rhs);
    template <typename U>
    vec& operator*=(const vec<L, U>& rhs);
    vec& operator*=(const vec& rhs);

    template <typename U>
    vec& operator/=(U rhs);
    template <typename U>
    vec& operator/=(const vec<L, U>& rhs);
    vec& operator/=(const vec& rhs);

    template <typename U>
    vec& operator%=(U rhs);
    template <typename U>
    vec& operator%=(const vec<L, U>& rhs);
    vec& operator%=(const vec& rhs);

    template <typename..., typename U = T>
    std::enable_if_t<std::is_floating_point_v<U>, U> length() const;

    template <typename..., typename U = T>
    std::enable_if_t<std::is_floating_point_v<U>, vec&> normalize();

    T sum() const;
    T prod() const;
};

template <dim_t L, typename T>
inline bool operator==(const vec<L, T>& lhs, const vec<L, T>& rhs);
template <dim_t L, typename T>
inline bool operator!=(const vec<L, T>& lhs, const vec<L, T>& rhs);

template <dim_t L, typename T>
inline vec<L, T> operator+(const vec<L, T>& v);
template <dim_t L, typename T>
inline vec<L, T> operator-(const vec<L, T>& v);

template <dim_t L, typename T>
inline vec<L, T> operator+(const vec<L, T>& lhs, const vec<L, T>& rhs);
template <dim_t L, typename T>
inline vec<L, T> operator+(const vec<L, T>& lhs, T rhs);
template <dim_t L, typename T>
inline vec<L, T> operator+(T lhs, const vec<L, T>& rhs);

template <dim_t L, typename T>
inline vec<L, T> operator-(const vec<L, T>& lhs, const vec<L, T>& rhs);
template <dim_t L, typename T>
inline vec<L, T> operator-(const vec<L, T>& lhs, T rhs);
template <dim_t L, typename T>
inline vec<L, T> operator-(T lhs, const vec<L, T>& rhs);

template <dim_t L, typename T>
inline vec<L, T> operator*(const vec<L, T>& lhs, const vec<L, T>& rhs);
template <dim_t L, typename T>
inline vec<L, T> operator*(const vec<L, T>& lhs, T rhs);
template <dim_t L, typename T>
inline vec<L, T> operator*(T lhs, const vec<L, T>& rhs);

template <dim_t L, typename T>
inline vec<L, T> operator/(const vec<L, T>& lhs, const vec<L, T>& rhs);
template <dim_t L, typename T>
inline vec<L, T> operator/(const vec<L, T>& lhs, T rhs);
template <dim_t L, typename T>
inline vec<L, T> operator/(T lhs, const vec<L, T>& rhs);

template <dim_t L, typename T>
inline vec<L, T> operator%(const vec<L, T>& lhs, const vec<L, T>& rhs);
template <dim_t L, typename T>
inline vec<L, T> operator%(const vec<L, T>& lhs, T rhs);
template <dim_t L, typename T>
inline vec<L, T> operator%(T lhs, const vec<L, T>& rhs);

}  // namespace bdm

#include "vec.inl"
