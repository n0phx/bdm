#pragma once

#include "computations.h"
#include "config.h"
#include "types.h"

namespace bdm
{

template <typename T>
inline mat4<T> look_at(const vec3<T> from,
                       const vec3<T> at,
                       const vec3<T> up,
                       handedness h = handedness::right)
{
    const auto z_axis = normalize(from - at) * static_cast<T>(h);
    const auto x_axis = normalize(cross(up, z_axis));
    const auto y_axis = cross(z_axis, x_axis);
    return mat4<T>{vec4<T>{x_axis, T{}},
                   vec4<T>{y_axis, T{}},
                   vec4<T>{z_axis, T{}},
                   vec4<T>{-dot(x_axis, from),
                           -dot(y_axis, from),
                           -dot(z_axis, from),
                           static_cast<T>(1)}};
}

#pragma push_macro("near")
#pragma push_macro("far")
#undef near
#undef far
template <typename T>
inline mat4<T> perspective(T fov,
                           T aspect,
                           T near,
                           T far,
                           handedness h = handedness::right,
                           T clip_space_depth = 2)
{
    mat4<T> ret;
    const T one_over_tan_of_half_fov = static_cast<T>(1) /
                                       std::tan(fov * static_cast<T>(0.5));
    const T sign = static_cast<T>(h) * static_cast<T>(-1);
    ret[0][0] = one_over_tan_of_half_fov / aspect;
    ret[1][1] = one_over_tan_of_half_fov;
    ret[2][2] = sign * (far + near) / (far - near);
    ret[2][3] = sign;
    ret[3][2] = -(clip_space_depth * far * near) / (far - near);
    return ret;
}

template <typename T>
inline mat4<T> ortho(T left,
                     T right,
                     T bottom,
                     T top,
                     T near,
                     T far,
                     handedness h = handedness::right,
                     T clip_space_depth = 2)
{
    mat4<T> ret;
    const T sign = static_cast<T>(h) * static_cast<T>(-1);
    // Multiplying the far parameter with the value will cancel it out when
    // the clip space depth is 1 (DirectX) and will keep it when it's 2 (OpenGL)
    const T cancel_out_far = clip_space_depth - static_cast<T>(1);
    ret[0][0] = static_cast<T>(2) / (right - left);
    ret[1][1] = static_cast<T>(2) / (top - bottom);
    ret[2][2] = sign * clip_space_depth / (far - near);
    ret[3][0] = -(right + left) / (right - left);
    ret[3][1] = -(top + bottom) / (top - bottom);
    ret[3][2] = -(cancel_out_far * far + near) / (far - near);
    ret[3][3] = static_cast<T>(1);
    return ret;
}
#pragma pop_macro("near")
#pragma pop_macro("far")

namespace impl
{

static constexpr const double pi = 3.14159265358979323846;

}  // namespace impl

template <typename T>
std::enable_if_t<std::is_floating_point_v<T>, T> degrees(T radians)
{
    static constexpr const auto c = static_cast<T>(180.0 / impl::pi);
    return c * radians;
}

template <typename T>
std::enable_if_t<std::is_floating_point_v<T>, T> radians(T degrees)
{
    static constexpr const auto c = static_cast<T>(impl::pi / 180.0);
    return c * degrees;
}

namespace affine
{

template <dim_t L, typename T>
inline mat<L, L, T> scale(const vec<L, T>& factors)
{
    return mat<L, L, T>::diagonal(factors);
}

template <dim_t L, typename T>
inline mat<L, L, T> scale(const mat<L, L, T>& m, const vec<L, T>& factors)
{
    return m * scale(factors);
}

template <dim_t L, typename T>
inline mat<L, L, T> scale(T factor)
{
    return scale(vec<L, T>{factor});
}

template <dim_t L, typename T>
inline mat<L, L, T> scale(const mat<L, L, T>& m, T factor)
{
    return scale(m, vec<L, T>{factor});
}

}  // namespace affine

inline namespace projective
{

template <typename T>
inline mat4<T> rotate(const vec3<T>& axis, T radians)
{
    const T c = std::cos(radians);
    const T s = std::sin(radians);
    const T one_minus_c = static_cast<T>(1) - c;
    const vec3<T> n = bdm::normalize(axis);
    return mat4<T>{n.x * n.x * one_minus_c + c,
                   n.x * n.y * one_minus_c + n.z * s,
                   n.x * n.z * one_minus_c - n.y * s,
                   static_cast<T>(0),
                   n.y * n.x * one_minus_c - n.z * s,
                   n.y * n.y * one_minus_c + c,
                   n.y * n.z * one_minus_c + n.x * s,
                   static_cast<T>(0),
                   n.z * n.x * one_minus_c + n.y * s,
                   n.z * n.y * one_minus_c - n.x * s,
                   n.z * n.z * one_minus_c + c,
                   static_cast<T>(0),
                   static_cast<T>(0),
                   static_cast<T>(0),
                   static_cast<T>(0),
                   static_cast<T>(1)};
}

template <typename T>
inline mat4<T> rotate(const mat4<T>& m, const vec3<T>& axis, T radians)
{
    return m * rotate(axis, radians);
}

template <dim_t L, typename T>
inline mat<L + 1, L + 1, T> scale(const vec<L, T>& factors)
{
    return mat<L + 1, L + 1, T>::diagonal(vec<L + 1, T>{factors, static_cast<T>(1)});
}

template <dim_t L, typename T>
inline mat<L + 1, L + 1, T> scale(const mat<L + 1, L + 1, T>& m,
                                  const vec<L, T>& factors)
{
    return m * scale(factors);
}

template <dim_t L, typename T>
inline mat<L + 1, L + 1, T> scale(T factor)
{
    return scale(vec<L, T>{factor});
}

template <dim_t L, typename T>
inline mat<L, L, T> scale(const mat<L, L, T>& m, T factor)
{
    return scale(m, vec<L - 1, T>{factor});
}

template <dim_t L, typename T>
inline mat<L + 1, L + 1, T> translate(const vec<L, T>& position)
{
    auto m = mat<L + 1, L + 1, T>::identity();
    m[L] = vec<L + 1, T>{position, static_cast<T>(1)};
    return m;
}

template <dim_t L, typename T>
inline mat<L + 1, L + 1, T> translate(const mat<L + 1, L + 1, T>& m,
                                      const vec<L, T>& position)
{
    return m * translate(position);
}

}  // namespace projective

}  // namespace bdm
