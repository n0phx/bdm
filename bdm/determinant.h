#pragma once

#include "seq.h"
#include "types.h"

namespace bdm
{

namespace impl
{

// Naive integer-exponentiation that can be compile-time evaluated and
// eliminated
template <typename T>
constexpr T pow(T base, T exp)
{
    T result{1};
    while (exp > 0)
    {
        result *= base;
        --exp;
    }
    return result;
}

// Naive factorial calculation that can be compile-time evaluated and eliminated
template <typename T>
constexpr T fact(T n)
{
    T result{1};
    while (n > 0)
    {
        result *= n--;
    }
    return result;
}

// Return the number of k-combinations on n elements
constexpr dim_t nck(dim_t n, dim_t k)
{
    return fact(n) / (fact(k) * fact(n - k));
}

constexpr dim_t sum(dim_t A, dim_t B)
{
    return A + B;
}

constexpr dim_t rank_element(dim_t start, dim_t end, dim_t n, dim_t k)
{
    dim_t pos{};
    for (dim_t j = start; j != end; ++j)
    {
        pos += nck(n - j, k - 1);
    }
    return pos;
}

template <dim_t... Is>
constexpr dim_t k_subset_lex_rank(dim_t n, [[maybe_unused]] dim_seq<Is...> indexes)
{
    const dim_t k = indexes.size;
    dim_t index{};
    dim_t i{};
    dim_t j{1u};
    (((index += rank_element(j, Is + 1, n, k - i++)), (j = Is + 2)), ...);
    return index;
}

template <dim_t R, dim_t N, dim_t K, dim_t X, dim_t C = nck(N - X, K), bool Loop = (C <= R)>
struct unrank_element
{
    using next_iter = unrank_element<R - C, N, K, X + 1>;
    static constexpr auto rank = next_iter::rank;
    static constexpr auto value = next_iter::value;
};

template <dim_t R, dim_t N, dim_t K, dim_t X, dim_t C>
struct unrank_element<R, N, K, X, C, false>
{
    static constexpr auto rank = R;
    static constexpr auto value = X;
};

template <dim_t R, dim_t N, dim_t K, dim_t X = 1>
struct k_subset_lex_unrank_impl
{
    using unranked = unrank_element<R, N, K - 1, X>;
    using next_iter = k_subset_lex_unrank_impl<unranked::rank, N, K - 1, unranked::value + 1>;
    using type = seq::prepend<unranked::value - 1, typename next_iter::type>;
};

template <dim_t R, dim_t N, dim_t X>
struct k_subset_lex_unrank_impl<R, N, 0, X>
{
    using type = dim_seq<>;
};

template <dim_t R, dim_t N, dim_t K>
using k_subset_lex_unrank = typename k_subset_lex_unrank_impl<R, N, K>::type;

template <dim_t dimension, dim_t max_rank>
constexpr dim_t row_combinations_for_rank(dim_t rank)
{
    return nck(dimension - (max_rank - rank), rank);
}

template <dim_t dimension>
constexpr dim_t col_combinations_for_rank(dim_t rank)
{
    return nck(dimension, rank);
}

template <dim_t normalizer_value>
constexpr dim_t norm_index(dim_t value)
{
    return value - normalizer_value;
}

template <dim_t normalizer_value>
constexpr dim_t denorm_index(dim_t value)
{
    return value + normalizer_value;
}

template <dim_t R, dim_t C, typename T, dim_t MR = R>
class compute_determinant
{
private:
    // The matrix type over which the determinant is to be computed
    using mat_type = mat<R, C, T>;
    // The chosen rows and columns to be used for precomputing the
    // determinants of the submatrices.
    using mat_rows = make_dim_seq<R>;
    using mat_cols = make_dim_seq<C>;
    // The minimum and maximum rank of the submatrices which determinants are
    // being computed
    static constexpr dim_t min_rank = 2;
    static constexpr dim_t max_rank = MR;
    // Sequence of ranks (2, 3, ..., max_rank)
    using ranks = make_dim_seq<max_rank - 1, min_rank>;
    // Specialized functions for calculating the number of combinations per rank
    static constexpr auto row_combinations_for = row_combinations_for_rank<R, max_rank>;
    static constexpr auto col_combinations_for = col_combinations_for_rank<C>;
    // Sequence of the calculated combinations per rank
    using row_combinations_per_rank = seq::map<row_combinations_for, ranks>;
    using col_combinations_per_rank = seq::map<col_combinations_for, ranks>;
    // The sums of the earlier sequences
    static constexpr auto row_combinations = seq::reduce<sum, row_combinations_per_rank>;
    static constexpr auto col_combinations = seq::reduce<sum, col_combinations_per_rank>;

    const mat_type& m;

    T values[row_combinations][col_combinations];

public:
    constexpr explicit compute_determinant(const mat_type& mref) : m{mref}
    {
        precompute(ranks{});
    }

private:
    template <dim_t... Rs>
    inline void precompute([[maybe_unused]] dim_seq<Rs...>)
    {
        (precompute<
             Rs>(make_dim_seq<seq::at<Rs - min_rank, row_combinations_per_rank>>{},
                 make_dim_seq<seq::at<Rs - min_rank, col_combinations_per_rank>>{}),
         ...);
    }

    template <dim_t Rank, dim_t... RI, dim_t... CI>
    inline void precompute([[maybe_unused]] dim_seq<RI...> rows, dim_seq<CI...> cols)
    {
        (precompute<Rank, RI>(cols), ...);
    }

    template <dim_t Rank, dim_t RI, dim_t... CI>
    inline void precompute([[maybe_unused]] dim_seq<CI...>)
    {
        (precompute<Rank, RI, CI>(), ...);
    }

    template <dim_t Rank, dim_t RI, dim_t CI>
    inline void precompute()
    {
        using normalized_rows = k_subset_lex_unrank<RI, mat_rows::size - (max_rank - Rank), Rank>;
        using normalized_cols = k_subset_lex_unrank<CI, mat_cols::size, Rank>;

        static constexpr auto denorm_row = denorm_index<seq::at<max_rank - Rank, mat_rows>>;
        static constexpr auto denorm_col = denorm_index<seq::first<mat_cols>>;

        using row_pack = seq::map<denorm_row, normalized_rows>;
        using col_pack = seq::map<denorm_col, normalized_cols>;

        constexpr auto ri_offset = seq::reduce<sum, seq::take<Rank - min_rank, row_combinations_per_rank>>;
        constexpr auto ci_offset = seq::reduce<sum, seq::take<Rank - min_rank, col_combinations_per_rank>>;

        values[ri_offset + RI][ci_offset + CI] = determinant<Rank>(row_pack{},
                                                                   col_pack{});
    }

    template <dim_t Rank, dim_t R1, dim_t R2, dim_t C1, dim_t C2>
    inline T determinant([[maybe_unused]] dim_seq<R1, R2>,
                         [[maybe_unused]] dim_seq<C1, C2>)
    {
        return (m[R1][C1] * m[R2][C2] - m[R2][C1] * m[R1][C2]);
    }

    template <dim_t Rank, dim_t... RI, dim_t... CI>
    inline T determinant(dim_seq<RI...> rows, dim_seq<CI...> cols)
    {
        constexpr dim_t RBI = seq::first<decltype(rows)>;
        return ((pow(-1, static_cast<int>(seq::index_of<CI, decltype(cols)>)) *
                 m(RBI, CI) *
                 cached<Rank - 1>(seq::remove<RBI, decltype(rows)>{},
                                  seq::remove<CI, decltype(cols)>{})) +
                ...);
    }

    template <dim_t Rank, dim_t... RI, dim_t... CI>
    inline T cached(dim_seq<RI...> rows, dim_seq<CI...> cols) const
    {
        static constexpr auto norm_row = norm_index<seq::at<max_rank - Rank, mat_rows>>;
        static constexpr auto norm_col = norm_index<seq::first<mat_cols>>;

        using normalized_rows = seq::map<norm_row, decltype(rows)>;
        using normalized_cols = seq::map<norm_col, decltype(cols)>;

        constexpr auto ridx = k_subset_lex_rank(mat_rows::size - (max_rank - Rank),
                                                normalized_rows{});
        constexpr auto cidx = k_subset_lex_rank(mat_cols::size, normalized_cols{});

        constexpr auto ri_offset = seq::reduce<sum, seq::take<Rank - min_rank, row_combinations_per_rank>>;
        constexpr auto ci_offset = seq::reduce<sum, seq::take<Rank - min_rank, col_combinations_per_rank>>;

        return values[ri_offset + ridx][ci_offset + cidx];
    }

public:
    template <dim_t... RI, dim_t... CI>
    inline T operator()(dim_seq<RI...> rows, dim_seq<CI...> cols) const
    {
        return cached<max_rank>(rows, cols);
    }

    inline T operator()() const
    {
        return operator()(make_dim_seq<R>{}, make_dim_seq<C>{});
    }
};

}  // namespace impl

}  // namespace bdm
