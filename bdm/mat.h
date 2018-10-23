#pragma once

#include "computations.h"
#include "types.h"

namespace bdm
{

template <dim_t R, dim_t C, typename T>
struct mat
{
    using row_type = vec<C, T>;
    using col_type = vec<R, T>;
    using value_type = T;

    enum
    {
        rows = R,
        cols = C
    };

private:
    row_type values[rows];

private:
    template <typename U, dim_t... RI>
    constexpr mat(U val, dim_seq<RI...> /*unused*/);

    template <typename... Us, dim_t... I>
    constexpr mat(const std::tuple<Us...>& vals, dim_seq<I...> /*unused*/);

    template <typename U, dim_t... RI>
    constexpr mat(const mat<R, C, U>& m, dim_seq<RI...> /*unused*/);

    template <typename... Vs, dim_t... CI>
    static constexpr row_type from_cols(const std::tuple<Vs...>& vs,
                                        dim_seq<CI...> /*unused*/,
                                        dim_t element_index);

    template <typename... Vs, dim_t... RI>
    static constexpr mat from_cols(const std::tuple<Vs...>& vs,
                                   dim_seq<RI...> /*unused*/);

    template <typename U, dim_t... I>
    static constexpr mat diagonal(U val, dim_seq<I...> /*unused*/);

    template <typename U, dim_t... I>
    static constexpr mat diagonal(const vec<C, U>& vals, dim_seq<I...> /*unused*/);

public:
    template <typename U>
    constexpr explicit mat(U val);

    template <typename... Us, std::enable_if_t<sizeof...(Us) == R * C>* = nullptr>
    constexpr explicit mat(Us... vals);

    template <typename U>
    constexpr explicit mat(const mat<R, C, U>& m);

    template <typename... Us, std::enable_if_t<sizeof...(Us) == R>* = nullptr>
    constexpr mat(const vec<C, Us>&... vs);

    template <typename... Us, std::enable_if_t<sizeof...(Us) == R>* = nullptr>
    static constexpr mat from_rows(const vec<C, Us>&... vs);

    template <typename... Us, std::enable_if_t<sizeof...(Us) == C>* = nullptr>
    static constexpr mat from_cols(const vec<R, Us>&... vs);

    template <typename U, typename..., dim_t Y = R, dim_t X = C>
    static constexpr std::enable_if_t<Y == X, mat> diagonal(U val);

    template <typename U, typename..., dim_t Y = R, dim_t X = C>
    static constexpr std::enable_if_t<Y == X, mat> diagonal(const vec<X, U>& vals);

    template <typename... Us, std::enable_if_t<sizeof...(Us) == R>* = nullptr>
    static constexpr mat diagonal(Us... vals);

    template <typename..., dim_t Y = R, dim_t X = C>
    static constexpr std::enable_if_t<Y == X, mat> identity();

    constexpr mat() = default;
    ~mat() = default;

    mat(const mat&) = default;
    mat& operator=(const mat&) = default;

    mat(mat&&) noexcept = default;
    mat& operator=(mat&&) noexcept = default;

    template <typename U>
    constexpr mat& operator=(const mat<R, C, U>& rhs);

    row_type& operator[](dim_t row_index);
    const row_type& operator[](dim_t row_index) const;

    T& operator()(dim_t row_index, dim_t col_index);
    const T& operator()(dim_t row_index, dim_t col_index) const;

    row_type row(dim_t row_index) const;
    col_type col(dim_t col_index) const;

    template <dim_t H, dim_t W>
    std::enable_if_t<(H > 1 && W > 1), mat<H, W, T>> submat(dim_t y, dim_t x) const;

    template <dim_t... RI, dim_t... CI, dim_t RI_s = sizeof...(RI), dim_t CI_s = sizeof...(CI)>
    std::enable_if_t<(RI_s > 1 && CI_s > 1), mat<RI_s, CI_s, T>> submat(
        dim_seq<RI...> /*unused*/,
        dim_seq<CI...> /*unused*/) const;

    template <typename F, dim_t H = R>
    std::enable_if_t<(H < 4), mat&> apply(F func);
    template <typename F, dim_t H = R>
    std::enable_if_t<(H >= 4), mat&> apply(F func);

    template <typename F, typename U, dim_t H = R>
    std::enable_if_t<(H < 4), mat&> apply(F func, const mat<R, C, U>& rhs);
    template <typename F, typename U, dim_t H = R>
    std::enable_if_t<(H >= 4), mat&> apply(F func, const mat<R, C, U>& rhs);

    mat& operator++();
    mat& operator--();

    template <typename U>
    mat& operator+=(U rhs);
    template <typename U>
    mat& operator+=(const mat<R, C, U>& rhs);
    mat& operator+=(const mat& rhs);

    template <typename U>
    mat& operator-=(U rhs);
    template <typename U>
    mat& operator-=(const mat<R, C, U>& rhs);
    mat& operator-=(const mat& rhs);

    template <typename U>
    mat& operator*=(U rhs);
    template <typename U>
    mat& operator*=(const mat<R, C, U>& rhs);
    mat& operator*=(const mat& rhs);

    template <typename U>
    mat& operator/=(U rhs);
    template <typename U>
    mat& operator/=(const mat<R, C, U>& rhs);
    mat& operator/=(const mat& rhs);

    template <typename..., dim_t Y = R, dim_t X = C>
    std::enable_if_t<Y == X, mat&> transpose();

    value_type* data();
    const value_type* data() const;

private:
    template <dim_t... I>
    col_type column(dim_t col_index, dim_seq<I...> /*unused*/) const;

    template <dim_t H, dim_t W, dim_t... CI>
    typename mat<H, W, T>::row_type submat(dim_t y,
                                           dim_t x,
                                           dim_t RI,
                                           dim_seq<CI...> /*unused*/) const;

    template <dim_t H, dim_t W, dim_t... RI>
    mat<H, W, T> submat(dim_t y, dim_t x, dim_seq<RI...> /*unused*/) const;

    template <dim_t... CI, dim_t CI_s = sizeof...(CI)>
    vec<CI_s, T> submat(dim_t RI, dim_seq<CI...> /*unused*/) const;
};

template <dim_t R, dim_t C, typename T>
inline bool operator==(const mat<R, C, T>& lhs, const mat<R, C, T>& rhs);
template <dim_t R, dim_t C, typename T>
inline bool operator!=(const mat<R, C, T>& lhs, const mat<R, C, T>& rhs);

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator+(const mat<R, C, T>& m);
template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator-(const mat<R, C, T>& m);

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator+(const mat<R, C, T>& lhs, const mat<R, C, T>& rhs);
template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator+(const mat<R, C, T>& lhs, T rhs);
template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator+(T lhs, const mat<R, C, T>& rhs);

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator-(const mat<R, C, T>& lhs, const mat<R, C, T>& rhs);
template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator-(const mat<R, C, T>& lhs, T rhs);
template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator-(T lhs, const mat<R, C, T>& rhs);

template <dim_t R, dim_t S, dim_t C, typename T>
inline mat<R, C, T> operator*(const mat<R, S, T>& lhs, const mat<S, C, T>& rhs);
template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator*(const mat<R, C, T>& lhs, T rhs);
template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator*(T lhs, const mat<R, C, T>& rhs);
template <dim_t R, dim_t C, typename T>
inline typename mat<R, C, T>::col_type operator*(typename mat<R, C, T>::row_type& lhs,
                                                 const mat<R, C, T>& rhs);
template <dim_t R, dim_t C, typename T>
inline typename mat<R, C, T>::row_type operator*(const mat<R, C, T>& lhs,
                                                 typename mat<R, C, T>::col_type& rhs);

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator/(const mat<R, C, T>& lhs, const mat<R, C, T>& rhs);
template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator/(const mat<R, C, T>& lhs, T rhs);
template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator/(T lhs, const mat<R, C, T>& rhs);
template <dim_t R, dim_t C, typename T>
inline typename mat<R, C, T>::col_type operator/(typename mat<R, C, T>::row_type& lhs,
                                                 const mat<R, C, T>& rhs);
template <dim_t R, dim_t C, typename T>
inline typename mat<R, C, T>::row_type operator/(const mat<R, C, T>& lhs,
                                                 typename mat<R, C, T>::col_type& rhs);

}  // namespace bdm

#include "mat.inl"
