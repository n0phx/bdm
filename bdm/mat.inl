namespace bdm
{

template <dim_t R, dim_t C, typename T>
template <typename U, dim_t... RI>
constexpr mat<R, C, T>::mat(U val, dim_seq<RI...> /*unused*/)
    : values{row_type{(static_cast<void>(RI), val)}...}
{
}

template <dim_t R, dim_t C, typename T>
template <typename U>
constexpr mat<R, C, T>::mat(U val) : mat{val, make_dim_seq<R>{}}
{
}

template <dim_t R, dim_t C, typename T>
template <typename... Us, dim_t... I>
constexpr mat<R, C, T>::mat(const std::tuple<Us...>& vals, dim_seq<I...> /*unused*/)
{
    ((data()[I] = std::get<I>(vals)), ...);
}

template <dim_t R, dim_t C, typename T>
template <typename... Us, std::enable_if_t<sizeof...(Us) == R * C>*>
constexpr mat<R, C, T>::mat(Us... vals)
    : mat{std::forward_as_tuple(vals...), make_dim_seq<R * C>{}}
{
}

template <dim_t R, dim_t C, typename T>
template <typename U, dim_t... RI>
constexpr mat<R, C, T>::mat(const mat<R, C, U>& m, dim_seq<RI...> /*unused*/)
    : values{row_type{m[RI]}...}
{
}

template <dim_t R, dim_t C, typename T>
template <typename U>
constexpr mat<R, C, T>::mat(const mat<R, C, U>& m) : mat{m, make_dim_seq<R>{}}
{
}

template <dim_t R, dim_t C, typename T>
template <typename... Us, std::enable_if_t<sizeof...(Us) == R>*>
constexpr mat<R, C, T>::mat(const vec<C, Us>&... vs) : values{row_type{vs}...}
{
}

template <dim_t R, dim_t C, typename T>
template <typename... Us, std::enable_if_t<sizeof...(Us) == R>*>
constexpr mat<R, C, T> mat<R, C, T>::from_rows(const vec<C, Us>&... vs)
{
    return mat<R, C, T>{vs...};
}

template <dim_t R, dim_t C, typename T>
template <typename... Vs, dim_t... CI>
constexpr typename mat<R, C, T>::row_type mat<R, C, T>::from_cols(
    const std::tuple<Vs...>& vs,
    dim_seq<CI...> /*unused*/,
    dim_t element_index)
{
    return row_type{std::get<CI>(vs)[element_index]...};
}

template <dim_t R, dim_t C, typename T>
template <typename... Vs, dim_t... RI>
constexpr mat<R, C, T> mat<R, C, T>::from_cols(const std::tuple<Vs...>& vs,
                                               dim_seq<RI...> /*unused*/)
{
    return mat<R, C, T>{
        mat<R, C, T>::from_cols(vs, make_dim_seq<sizeof...(Vs)>{}, RI)...};
}

template <dim_t R, dim_t C, typename T>
template <typename... Us, std::enable_if_t<sizeof...(Us) == C>*>
constexpr mat<R, C, T> mat<R, C, T>::from_cols(const vec<R, Us>&... vs)
{
    return mat<R, C, T>::from_cols(std::forward_as_tuple(vs...), make_dim_seq<R>{});
}

template <dim_t R, dim_t C, typename T>
template <typename U, dim_t... I>
constexpr mat<R, C, T> mat<R, C, T>::diagonal(U val, dim_seq<I...> /*unused*/)
{
    mat<R, C, T> ret{};
    ((ret(I, I) = val), ...);
    return ret;
}

template <dim_t R, dim_t C, typename T>
template <typename U, typename..., dim_t Y, dim_t X>
constexpr std::enable_if_t<Y == X, mat<R, C, T>> mat<R, C, T>::diagonal(U val)
{
    return diagonal(val, make_dim_seq<R>{});
}

template <dim_t R, dim_t C, typename T>
template <typename U, dim_t... I>
constexpr mat<R, C, T> mat<R, C, T>::diagonal(const vec<C, U>& vals,
                                              dim_seq<I...> /*unused*/)
{
    mat<R, C, T> ret{};
    ((ret(I, I) = vals[I]), ...);
    return ret;
}

template <dim_t R, dim_t C, typename T>
template <typename U, typename..., dim_t Y, dim_t X>
constexpr std::enable_if_t<Y == X, mat<R, C, T>> mat<R, C, T>::diagonal(
    const vec<X, U>& vals)
{
    return diagonal(vals, make_dim_seq<R>{});
}

template <dim_t R, dim_t C, typename T>
template <typename... Us, std::enable_if_t<sizeof...(Us) == R>*>
constexpr mat<R, C, T> mat<R, C, T>::diagonal(Us... vals)
{
    return diagonal(vec<R, T>{vals...});
}

template <dim_t R, dim_t C, typename T>
template <typename..., dim_t Y, dim_t X>
constexpr std::enable_if_t<Y == X, mat<R, C, T>> mat<R, C, T>::identity()
{
    return diagonal(static_cast<T>(1));
}

template <dim_t R, dim_t C, typename T>
template <typename U>
constexpr mat<R, C, T>& mat<R, C, T>::operator=(const mat<R, C, U>& rhs)
{
    return operator=(mat<R, C, T>{rhs});
}

template <dim_t R, dim_t C, typename T>
inline T* mat<R, C, T>::data()
{
    return &(values[0][0]);
}

template <dim_t R, dim_t C, typename T>
inline const T* mat<R, C, T>::data() const
{
    return &(values[0][0]);
}

template <dim_t R, dim_t C, typename T>
inline typename mat<R, C, T>::row_type& mat<R, C, T>::operator[](dim_t row_index)
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
    assert(0 <= row_index && row_index < rows);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
    return values[row_index];
}

template <dim_t R, dim_t C, typename T>
inline const typename mat<R, C, T>::row_type& mat<R, C, T>::operator[](dim_t row_index) const
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay,hicpp-no-array-decay)
    assert(0 <= row_index && row_index < rows);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
    return values[row_index];
}

template <dim_t R, dim_t C, typename T>
inline T& mat<R, C, T>::operator()(dim_t row_index, dim_t col_index)
{
    return operator[](row_index)[col_index];
}

template <dim_t R, dim_t C, typename T>
inline const T& mat<R, C, T>::operator()(dim_t row_index, dim_t col_index) const
{
    return operator[](row_index)[col_index];
}

template <dim_t R, dim_t C, typename T>
inline typename mat<R, C, T>::row_type mat<R, C, T>::row(dim_t row_index) const
{
    return operator[](row_index);
}

template <dim_t R, dim_t C, typename T>
template <dim_t... RI>
inline typename mat<R, C, T>::col_type mat<R, C, T>::column(dim_t col_index,
                                                            dim_seq<RI...> /*unused*/) const
{
    return col_type{operator[](RI)[col_index]...};
}

template <dim_t R, dim_t C, typename T>
inline typename mat<R, C, T>::col_type mat<R, C, T>::col(dim_t col_index) const
{
    return column(col_index, make_dim_seq<R>{});
}

template <dim_t R, dim_t C, typename T>
template <dim_t H, dim_t W, dim_t... CI>
inline typename mat<H, W, T>::row_type mat<R, C, T>::submat(dim_t y,
                                                            dim_t x,
                                                            dim_t RI,
                                                            dim_seq<CI...> /*unused*/) const
{
    using submat_row_type = typename mat<H, W, T>::row_type;
    return submat_row_type{operator()(y + RI, x + CI)...};
}

template <dim_t R, dim_t C, typename T>
template <dim_t H, dim_t W, dim_t... RI>
inline mat<H, W, T> mat<R, C, T>::submat(dim_t y,
                                         dim_t x,
                                         dim_seq<RI...> /*unused*/) const
{
    return mat<H, W, T>{submat<H, W>(y, x, RI, make_dim_seq<W>{})...};
}

template <dim_t R, dim_t C, typename T>
template <dim_t H, dim_t W>
inline std::enable_if_t<(H > 1 && W > 1), mat<H, W, T>> mat<R, C, T>::submat(
    dim_t y,
    dim_t x) const
{
    return submat<H, W>(y, x, make_dim_seq<H>{});
}

template <dim_t R, dim_t C, typename T>
template <dim_t... CI, dim_t CI_s>
inline vec<CI_s, T> mat<R, C, T>::submat(dim_t RI, dim_seq<CI...> /*unused*/) const
{
    return vec<CI_s, T>{operator()(RI, CI)...};
}

template <dim_t R, dim_t C, typename T>
template <dim_t... RI, dim_t... CI, dim_t RI_s, dim_t CI_s>
inline std::enable_if_t<(RI_s > 1 && CI_s > 1), mat<RI_s, CI_s, T>> mat<R, C, T>::submat(
    [[maybe_unused]] dim_seq<RI...> row_indexes,
    dim_seq<CI...> col_indexes) const
{
    return mat<RI_s, CI_s, T>{submat(RI, col_indexes)...};
}

template <dim_t R, dim_t C, typename T>
template <typename F, dim_t H>
inline std::enable_if_t<(H < 4), mat<R, C, T>&> mat<R, C, T>::apply(F func)
{
    impl::unrolled_invoke_n<R>([this, &func](dim_t n) { func(operator[](n)); });
    return *this;
}

template <dim_t R, dim_t C, typename T>
template <typename F, dim_t H>
inline std::enable_if_t<(H >= 4), mat<R, C, T>&> mat<R, C, T>::apply(F func)
{
    for (dim_t di = 0; di != rows; ++di)
    {
        func(operator[](di));
    }
    return *this;
}

template <dim_t R, dim_t C, typename T>
template <typename F, typename U, dim_t H>
inline std::enable_if_t<(H < 4), mat<R, C, T>&> mat<R, C, T>::apply(
    F func,
    const mat<R, C, U>& rhs)
{
    impl::unrolled_invoke_n<R>(
        [this, &func, &rhs](dim_t n) { func(operator[](n), rhs[n]); });
    return *this;
}

template <dim_t R, dim_t C, typename T>
template <typename F, typename U, dim_t H>
inline std::enable_if_t<(H >= 4), mat<R, C, T>&> mat<R, C, T>::apply(
    F func,
    const mat<R, C, U>& rhs)
{
    for (dim_t di = 0; di != rows; ++di)
    {
        func(operator[](di), rhs[di]);
    }
    return *this;
}

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T>& mat<R, C, T>::operator++()
{
    return apply([](row_type& r) { ++r; });
}

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T>& mat<R, C, T>::operator--()
{
    return apply([](row_type& r) { --r; });
}

template <dim_t R, dim_t C, typename T>
template <typename U>
inline mat<R, C, T>& mat<R, C, T>::operator+=(U rhs)
{
    return apply([rhs](row_type& r) { r += rhs; });
}

template <dim_t R, dim_t C, typename T>
template <typename U>
inline mat<R, C, T>& mat<R, C, T>::operator+=(const mat<R, C, U>& rhs)
{
    using rhs_row_type = typename mat<R, C, U>::row_type;
    return apply([](row_type& r1, const rhs_row_type& r2) { r1 += r2; }, rhs);
}

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T>& mat<R, C, T>::operator+=(const mat<R, C, T>& rhs)
{
    return operator+=<T>(rhs);
}

template <dim_t R, dim_t C, typename T>
template <typename U>
inline mat<R, C, T>& mat<R, C, T>::operator-=(U rhs)
{
    return apply([rhs](row_type& r) { r -= rhs; });
}

template <dim_t R, dim_t C, typename T>
template <typename U>
inline mat<R, C, T>& mat<R, C, T>::operator-=(const mat<R, C, U>& rhs)
{
    using rhs_row_type = typename mat<R, C, U>::row_type;
    return apply([](row_type& r1, const rhs_row_type& r2) { r1 -= r2; }, rhs);
}

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T>& mat<R, C, T>::operator-=(const mat& rhs)
{
    return operator-=<T>(rhs);
}

template <dim_t R, dim_t C, typename T>
template <typename U>
inline mat<R, C, T>& mat<R, C, T>::operator*=(U rhs)
{
    return apply([rhs](row_type& r) { r *= rhs; });
}

template <dim_t R, dim_t C, typename T>
template <typename U>
inline mat<R, C, T>& mat<R, C, T>::operator*=(const mat<R, C, U>& rhs)
{
    return (*this = *this * rhs);
}

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T>& mat<R, C, T>::operator*=(const mat& rhs)
{
    return operator*=<T>(rhs);
}

template <dim_t R, dim_t C, typename T>
template <typename U>
inline mat<R, C, T>& mat<R, C, T>::operator/=(U rhs)
{
    return apply([rhs](row_type& r) { r /= rhs; });
}

template <dim_t R, dim_t C, typename T>
template <typename U>
inline mat<R, C, T>& mat<R, C, T>::operator/=(const mat<R, C, U>& rhs)
{
    return operator*=(bdm::inverse(rhs));
}

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T>& mat<R, C, T>::operator/=(const mat& rhs)
{
    return operator/=<T>(rhs);
}

template <dim_t R, dim_t C, typename T>
template <typename..., dim_t Y, dim_t X>
inline std::enable_if_t<Y == X, mat<R, C, T>&> mat<R, C, T>::transpose()
{
    return (*this = bdm::transpose(*this));
}

template <dim_t R, dim_t C, typename T>
inline bool operator==(const mat<R, C, T>& lhs, const mat<R, C, T>& rhs)
{
    bool retval = true;
    impl::unrolled_invoke_n<R>([&lhs, &rhs, &retval](dim_t n) {
        retval = retval && (lhs[n] == rhs[n]);
    });
    return retval;
}

template <dim_t R, dim_t C, typename T>
inline bool operator!=(const mat<R, C, T>& lhs, const mat<R, C, T>& rhs)
{
    return !(lhs == rhs);
}

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator+(const mat<R, C, T>& m)
{
    return m;
}

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator-(const mat<R, C, T>& m)
{
    return negate(m);
}

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator+(const mat<R, C, T>& lhs, const mat<R, C, T>& rhs)
{
    return mat<R, C, T>(lhs) += rhs;
}

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator+(const mat<R, C, T>& lhs, T rhs)
{
    return mat<R, C, T>(lhs) += rhs;
}

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator+(T lhs, const mat<R, C, T>& rhs)
{
    return mat<R, C, T>(lhs) += rhs;
}

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator-(const mat<R, C, T>& lhs, const mat<R, C, T>& rhs)
{
    return mat<R, C, T>(lhs) -= rhs;
}

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator-(const mat<R, C, T>& lhs, T rhs)
{
    return mat<R, C, T>(lhs) -= rhs;
}

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator-(T lhs, const mat<R, C, T>& rhs)
{
    return mat<R, C, T>(lhs) -= rhs;
}

namespace impl
{

template <dim_t R, dim_t S, dim_t C, typename T, dim_t... CI>
inline typename mat<R, C, T>::row_type multiply(const mat<R, S, T>& lhs,
                                                const mat<S, C, T>& rhs,
                                                dim_t RI,
                                                dim_seq<CI...> /*unused*/)
{
    using row_type = typename mat<R, C, T>::row_type;
    return row_type{dot(lhs.row(RI), rhs.col(CI))...};
}

template <dim_t R, dim_t S, dim_t C, typename T, dim_t... RI>
inline mat<R, C, T> multiply(const mat<R, S, T>& lhs,
                             const mat<S, C, T>& rhs,
                             dim_seq<RI...> /*unused*/)
{
    return mat<R, C, T>{multiply(lhs, rhs, RI, make_dim_seq<C>{})...};
}

template <dim_t R, dim_t S, dim_t C, typename T>
inline mat<R, C, T> multiply(const mat<R, S, T>& lhs, const mat<S, C, T>& rhs)
{
    return multiply(lhs, rhs, make_dim_seq<R>{});
}

}  // namespace impl

template <dim_t R, dim_t S, dim_t C, typename T>
inline mat<R, C, T> operator*(const mat<R, S, T>& lhs, const mat<S, C, T>& rhs)
{
    return impl::multiply(lhs, rhs);
}

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator*(const mat<R, C, T>& lhs, T rhs)
{
    return mat<R, C, T>(lhs) *= rhs;
}

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator*(T lhs, const mat<R, C, T>& rhs)
{
    return mat<R, C, T>(rhs) *= lhs;
}

namespace impl
{

template <dim_t R, dim_t C, typename T, dim_t... CI>
inline typename mat<R, C, T>::col_type mul_vec_mat(typename mat<R, C, T>::row_type& lhs,
                                                   const mat<R, C, T>& rhs,
                                                   dim_seq<CI...> /*unused*/)
{
    return typename mat<R, C, T>::col_type{dot(lhs, rhs.col(CI))...};
}

template <dim_t R, dim_t C, typename T, dim_t... RI>
inline typename mat<R, C, T>::row_type mul_mat_vec(const mat<R, C, T>& lhs,
                                                   typename mat<R, C, T>::col_type& rhs,
                                                   dim_seq<RI...> /*unused*/)
{
    return typename mat<R, C, T>::row_type{dot(lhs[RI], rhs)...};
}

}  // namespace impl

template <dim_t R, dim_t C, typename T>
inline typename mat<R, C, T>::col_type operator*(typename mat<R, C, T>::row_type& lhs,
                                                 const mat<R, C, T>& rhs)
{
    return impl::mul_vec_mat(lhs, rhs, make_dim_seq<C>{});
}

template <dim_t R, dim_t C, typename T>
inline typename mat<R, C, T>::row_type operator*(const mat<R, C, T>& lhs,
                                                 typename mat<R, C, T>::col_type& rhs)
{
    return impl::mul_mat_vec(lhs, rhs, make_dim_seq<R>{});
}

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator/(const mat<R, C, T>& lhs, const mat<R, C, T>& rhs)
{
    return mat<R, C, T>(lhs) /= rhs;
}

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator/(const mat<R, C, T>& lhs, T rhs)
{
    return mat<R, C, T>(lhs) /= rhs;
}

template <dim_t R, dim_t C, typename T>
inline mat<R, C, T> operator/(T lhs, const mat<R, C, T>& rhs)
{
    using row_type = typename mat<R, C, T>::row_type;
    mat<R, C, T> tmp{rhs};
    tmp.apply([lhs](row_type& r) { r = lhs / r; });
    return tmp;
}

template <dim_t R, dim_t C, typename T>
inline typename mat<R, C, T>::col_type operator/(typename mat<R, C, T>::row_type& lhs,
                                                 const mat<R, C, T>& rhs)
{
    return impl::mul_vec_mat(lhs, bdm::inverse(rhs), make_dim_seq<C>{});
}

template <dim_t R, dim_t C, typename T>
inline typename mat<R, C, T>::row_type operator/(const mat<R, C, T>& lhs,
                                                 typename mat<R, C, T>::col_type& rhs)
{
    return impl::mul_mat_vec(bdm::inverse(lhs), rhs, make_dim_seq<R>{});
}

}  // namespace bdm
