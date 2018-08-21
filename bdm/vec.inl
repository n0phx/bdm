namespace bdm
{

template <dim_t L, typename T>
template <typename U, dim_t... I>
constexpr vec<L, T>::vec(U v, [[maybe_unused]] dim_seq<I...>)
    : vec_base<L, T>{(static_cast<void>(I), v)...}
{
}

template <dim_t L, typename T>
template <typename U>
constexpr vec<L, T>::vec(U v) : vec{v, make_dim_seq<L>{}}
{
}

template <dim_t L, typename T>
template <typename... Ts, std::enable_if_t<sizeof...(Ts) == L>*>
constexpr vec<L, T>::vec(Ts... vals) : vec_base<L, T>{vals...}
{
}

template <dim_t L, typename T>
template <typename U>
constexpr vec<L, T>::vec(const vec<L, U>& v) : vec_base<L, T>{v}
{
}

template <dim_t L, typename T>
template <typename U>
constexpr vec<L, T>& vec<L, T>::operator=(const vec<L, U>& rhs)
{
    vec_base<L, T>::operator=(rhs);
    return *this;
}

template <dim_t L, typename T>
template <typename..., dim_t S>
inline std::enable_if_t<(S <= 4), T*> vec<L, T>::data()
{
    return &(vec_base<L, T>::x);
}

template <dim_t L, typename T>
template <typename..., dim_t S>
inline std::enable_if_t<(S <= 4), const T*> vec<L, T>::data() const
{
    return &(vec_base<L, T>::x);
}

template <dim_t L, typename T>
template <typename..., dim_t S>
inline std::enable_if_t<(S > 4), T*> vec<L, T>::data()
{
    return vec_base<L, T>::values;
}

template <dim_t L, typename T>
template <typename..., dim_t S>
inline std::enable_if_t<(S > 4), const T*> vec<L, T>::data() const
{
    return vec_base<L, T>::values;
}

template <dim_t L, typename T>
inline T& vec<L, T>::operator[](dim_t index)
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
    assert(0 <= index && index < dimension);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    return data()[index];
}

template <dim_t L, typename T>
inline const T& vec<L, T>::operator[](dim_t index) const
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
    assert(0 <= index && index < dimension);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    return data()[index];
}

template <dim_t L, typename T>
template <typename F, typename..., dim_t S>
inline std::enable_if_t<(S < 4), vec<L, T>&> vec<L, T>::apply(F func)
{
    impl::unrolled_invoke_n<L>([this, &func](dim_t n) { func(operator[](n)); });
    return *this;
}

template <dim_t L, typename T>
template <typename F, typename..., dim_t S>
inline std::enable_if_t<(S >= 4), vec<L, T>&> vec<L, T>::apply(F func)
{
    for (dim_t di = 0u; di != dimension; ++di)
    {
        func(operator[](di));
    }
    return *this;
}

template <dim_t L, typename T>
template <typename F, typename..., dim_t S>
inline std::enable_if_t<(S < 4), const vec<L, T>&> vec<L, T>::apply(F func) const
{
    impl::unrolled_invoke_n<L>([this, &func](dim_t n) { func(operator[](n)); });
    return *this;
}

template <dim_t L, typename T>
template <typename F, typename..., dim_t S>
inline std::enable_if_t<(S >= 4), const vec<L, T>&> vec<L, T>::apply(F func) const
{
    for (dim_t di = 0u; di != dimension; ++di)
    {
        func(operator[](di));
    }
    return *this;
}

template <dim_t L, typename T>
template <typename F, typename U, typename..., dim_t S>
inline std::enable_if_t<(S < 4), vec<L, T>&> vec<L, T>::apply(F func,
                                                              const vec<L, U>& rhs)
{
    impl::unrolled_invoke_n<L>(
        [this, &func, &rhs](dim_t n) { func(operator[](n), rhs[n]); });
    return *this;
}

template <dim_t L, typename T>
template <typename F, typename U, typename..., dim_t S>
inline std::enable_if_t<(S >= 4), vec<L, T>&> vec<L, T>::apply(F func,
                                                               const vec<L, U>& rhs)
{
    for (dim_t di = 0u; di != dimension; ++di)
    {
        func(operator[](di), rhs[di]);
    }
    return *this;
}

template <dim_t L, typename T>
template <typename F, typename U, typename..., dim_t S>
inline std::enable_if_t<(S < 4), const vec<L, T>&> vec<L, T>::apply(
    F func,
    const vec<L, U>& rhs) const
{
    impl::unrolled_invoke_n<L>(
        [this, &func, &rhs](dim_t n) { func(operator[](n), rhs[n]); });
    return *this;
}

template <dim_t L, typename T>
template <typename F, typename U, typename..., dim_t S>
inline std::enable_if_t<(S >= 4), const vec<L, T>&> vec<L, T>::apply(
    F func,
    const vec<L, U>& rhs) const
{
    for (dim_t di = 0u; di != dimension; ++di)
    {
        func(operator[](di), rhs[di]);
    }
    return *this;
}

template <dim_t L, typename T>
inline vec<L, T>& vec<L, T>::operator++()
{
    return apply([](T& v) { ++v; });
}

template <dim_t L, typename T>
inline vec<L, T>& vec<L, T>::operator--()
{
    return apply([](T& v) { --v; });
}

template <dim_t L, typename T>
template <typename U>
inline vec<L, T>& vec<L, T>::operator+=(const vec<L, U>& rhs)
{
    return apply([](T& lv, U rv) { lv += rv; }, rhs);
}

template <dim_t L, typename T>
template <typename U>
inline vec<L, T>& vec<L, T>::operator+=(U rhs)
{
    return apply([rhs](T& lhs) { lhs += rhs; });
}

template <dim_t L, typename T>
inline vec<L, T>& vec<L, T>::operator+=(const vec<L, T>& rhs)
{
    return operator+=<T>(rhs);
}

template <dim_t L, typename T>
template <typename U>
inline vec<L, T>& vec<L, T>::operator-=(const vec<L, U>& rhs)
{
    return apply([](T& lv, U rv) { lv -= rv; }, rhs);
}

template <dim_t L, typename T>
template <typename U>
inline vec<L, T>& vec<L, T>::operator-=(U rhs)
{
    return apply([rhs](T& lhs) { lhs -= rhs; });
}

template <dim_t L, typename T>
inline vec<L, T>& vec<L, T>::operator-=(const vec<L, T>& rhs)
{
    return operator-=<T>(rhs);
}

template <dim_t L, typename T>
template <typename U>
inline vec<L, T>& vec<L, T>::operator*=(const vec<L, U>& rhs)
{
    return apply([](T& lv, U rv) { lv *= rv; }, rhs);
}

template <dim_t L, typename T>
template <typename U>
inline vec<L, T>& vec<L, T>::operator*=(U rhs)
{
    return apply([rhs](T& lhs) { lhs *= rhs; });
}

template <dim_t L, typename T>
inline vec<L, T>& vec<L, T>::operator*=(const vec<L, T>& rhs)
{
    return operator*=<T>(rhs);
}

template <dim_t L, typename T>
template <typename U>
inline vec<L, T>& vec<L, T>::operator/=(const vec<L, U>& rhs)
{
    return apply([](T& lv, U rv) { lv /= rv; }, rhs);
}

template <dim_t L, typename T>
template <typename U>
inline vec<L, T>& vec<L, T>::operator/=(U rhs)
{
    return apply([rhs](T& lhs) { lhs /= rhs; });
}

template <dim_t L, typename T>
inline vec<L, T>& vec<L, T>::operator/=(const vec<L, T>& rhs)
{
    return operator/=<T>(rhs);
}

template <dim_t L, typename T>
template <typename U>
inline vec<L, T>& vec<L, T>::operator%=(const vec<L, U>& rhs)
{
    return apply([](T& lv, U rv) { lv %= rv; }, rhs);
}

template <dim_t L, typename T>
template <typename U>
inline vec<L, T>& vec<L, T>::operator%=(U rhs)
{
    return apply([rhs](T& lhs) { lhs %= rhs; });
}

template <dim_t L, typename T>
inline vec<L, T>& vec<L, T>::operator%=(const vec<L, T>& rhs)
{
    return operator%=<T>(rhs);
}

template <dim_t L, typename T>
template <typename..., typename U>
inline std::enable_if_t<std::is_floating_point_v<U>, U> vec<L, T>::length() const
{
    return bdm::length(*this);
}

template <dim_t L, typename T>
template <typename..., typename U>
inline std::enable_if_t<std::is_floating_point_v<U>, vec<L, T>&> vec<L, T>::normalize()
{
    return operator/=(length());
}

template <dim_t L, typename T>
inline T vec<L, T>::sum() const
{
    T retval{};
    apply([&retval](const T& v) { retval += v; });
    return retval;
}

template <dim_t L, typename T>
inline T vec<L, T>::prod() const
{
    T retval{operator[](0)};
    apply([&retval](const T& v) { retval *= v; });
    return retval;
}

template <dim_t L, typename T>
inline bool operator==(const vec<L, T>& lhs, const vec<L, T>& rhs)
{
    bool equal = true;
    lhs.apply([&equal](const T& lv, const T& rv) { equal = equal && (lv == rv); },
              rhs);
    return equal;
}

template <dim_t L, typename T>
inline bool operator!=(const vec<L, T>& lhs, const vec<L, T>& rhs)
{
    return !(lhs == rhs);
}

template <dim_t L, typename T>
inline vec<L, T> operator+(const vec<L, T>& v)
{
    return v;
}

template <dim_t L, typename T>
inline vec<L, T> operator-(const vec<L, T>& v)
{
    return impl::negate(v, make_dim_seq<L>{});
}

template <dim_t L, typename T>
inline vec<L, T> operator+(const vec<L, T>& lhs, const vec<L, T>& rhs)
{
    return vec<L, T>(lhs) += rhs;
}

template <dim_t L, typename T>
inline vec<L, T> operator+(const vec<L, T>& lhs, T rhs)
{
    return vec<L, T>(lhs) += rhs;
}

template <dim_t L, typename T>
inline vec<L, T> operator+(T lhs, const vec<L, T>& rhs)
{
    return vec<L, T>(lhs) += rhs;
}

template <dim_t L, typename T>
inline vec<L, T> operator-(const vec<L, T>& lhs, const vec<L, T>& rhs)
{
    return vec<L, T>(lhs) -= rhs;
}

template <dim_t L, typename T>
inline vec<L, T> operator-(const vec<L, T>& lhs, T rhs)
{
    return vec<L, T>(lhs) -= rhs;
}

template <dim_t L, typename T>
inline vec<L, T> operator-(T lhs, const vec<L, T>& rhs)
{
    return vec<L, T>(lhs) -= rhs;
}

template <dim_t L, typename T>
inline vec<L, T> operator*(const vec<L, T>& lhs, const vec<L, T>& rhs)
{
    return vec<L, T>(lhs) *= rhs;
}

template <dim_t L, typename T>
inline vec<L, T> operator*(const vec<L, T>& lhs, T rhs)
{
    return vec<L, T>(lhs) *= rhs;
}

template <dim_t L, typename T>
inline vec<L, T> operator*(T lhs, const vec<L, T>& rhs)
{
    return vec<L, T>(lhs) *= rhs;
}

template <dim_t L, typename T>
inline vec<L, T> operator/(const vec<L, T>& lhs, const vec<L, T>& rhs)
{
    return vec<L, T>(lhs) /= rhs;
}

template <dim_t L, typename T>
inline vec<L, T> operator/(const vec<L, T>& lhs, T rhs)
{
    return vec<L, T>(lhs) /= rhs;
}

template <dim_t L, typename T>
inline vec<L, T> operator/(T lhs, const vec<L, T>& rhs)
{
    return vec<L, T>(lhs) /= rhs;
}

template <dim_t L, typename T>
inline vec<L, T> operator%(const vec<L, T>& lhs, const vec<L, T>& rhs)
{
    return vec<L, T>(lhs) %= rhs;
}

template <dim_t L, typename T>
inline vec<L, T> operator%(const vec<L, T>& lhs, T rhs)
{
    return vec<L, T>(lhs) %= rhs;
}

template <dim_t L, typename T>
inline vec<L, T> operator%(T lhs, const vec<L, T>& rhs)
{
    return vec<L, T>(lhs) %= rhs;
}

}  // namespace bdm
