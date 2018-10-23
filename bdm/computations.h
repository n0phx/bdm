#pragma once

#include "determinant.h"
#include "inverse.h"
#include "types.h"

#include <cmath>
#include <utility>

namespace bdm
{

namespace impl
{

template <typename F, dim_t... Ds>
constexpr void unrolled_invoke_n(F func, dim_seq<Ds...> /*unused*/)
{
    using expander = int[];
    static_cast<void>(expander{0, (static_cast<void>(func(Ds)), 0)...});
}

template <dim_t N, typename F>
constexpr void unrolled_invoke_n(F func)
{
    unrolled_invoke_n(func, bdm::make_dim_seq<N>{});
}

template <typename T, dim_t... I>
inline T negate(const T& src, dim_seq<I...> /*unused*/)
{
    return T{-src[I]...};
}

}  // namespace impl

template <dim_t L, typename T>
inline vec<L, T> negate(const vec<L, T>& v)
{
    return impl::negate(v, make_dim_seq<L>{});
}

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> negate(const mat<R, C, T>& m)
{
    return impl::negate(m, make_dim_seq<R>{});
}

template <typename T>
vec3<T> cross(const vec3<T>& lhs, const vec3<T>& rhs)
{
    return vec3<T>{lhs.y * rhs.z - lhs.z * rhs.y,
                   lhs.z * rhs.x - lhs.x * rhs.z,
                   lhs.x * rhs.y - lhs.y * rhs.x};
}

template <dim_t L, typename T>
T dot(const vec<L, T>& lhs, const vec<L, T>& rhs)
{
    return (lhs * rhs).sum();
}

template <dim_t L, typename T>
std::enable_if_t<std::is_floating_point_v<T>, T> length(const vec<L, T>& v)
{
    return std::sqrt(dot(v, v));
}

template <dim_t L, typename T>
std::enable_if_t<std::is_floating_point_v<T>, vec<L, T>> normalize(vec<L, T> v)
{
    v.normalize();
    return v;
}

template <dim_t R, dim_t C, typename T>
inline mat<C, R, T> transpose(const mat<R, C, T>& m)
{
    mat<C, R, T> ret;
    impl::unrolled_invoke_n<R>([&](dim_t ri) {
        impl::unrolled_invoke_n<C>([&, ri](dim_t ci) { ret[ci][ri] = m[ri][ci]; });
    });
    return ret;
}

template <dim_t R, dim_t C, typename T>
inline std::enable_if_t<R == C, T> determinant(const mat<R, C, T>& m)
{
    return impl::compute_determinant<R, C, T>{m}();
}

template <dim_t R, dim_t C, typename T>
inline std::enable_if_t<R == C, mat<R, C, T>> inverse(const mat<R, C, T>& m)
{
    return impl::compute_inverse<R, C, T>{m}();
}

}  // namespace bdm
