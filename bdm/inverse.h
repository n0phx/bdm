#pragma once

#include "determinant.h"
#include "seq.h"
#include "types.h"

namespace bdm
{

namespace impl
{

template <dim_t R, dim_t C, typename T>
class compute_inverse
{
private:
    // The matrix type over which the determinant is to be computed
    using mat_type = mat<R, C, T>;
    using row_type = typename mat_type::row_type;

    using rows = make_dim_seq<R>;
    using cols = make_dim_seq<C>;

    impl::compute_determinant<R, C, T, R - 1> determinant;
    // Matrix to be inverted
    const mat_type& m;

public:
    constexpr explicit compute_inverse(const mat_type& mref) : determinant{mref}, m{mref}
    {
    }

private:
    template <dim_t RI, dim_t... CI>
    inline row_type cofactors_for_row(T multiplier,
                                      dim_seq<RI> /*unused*/,
                                      dim_seq<CI...> /*unused*/)
    {
        return row_type{
            pow(-1, static_cast<int>(RI + CI)) * multiplier *
            determinant(seq::remove<RI, rows>{}, seq::remove<CI, cols>{})...};
    }

    template <dim_t... RI, dim_t... CI>
    inline mat_type transposed_cofactors(const row_type& row0_cofactors,
                                         T one_over_det,
                                         [[maybe_unused]] dim_seq<RI...> cofactor_rows,
                                         dim_seq<CI...> cofactor_cols)
    {
        return mat_type::from_cols(row0_cofactors * one_over_det,
                                   cofactors_for_row(one_over_det,
                                                     dim_seq<RI>{},
                                                     cofactor_cols)...);
    }

public:
    inline mat_type operator()()
    {
        const auto row0_cofactors = cofactors_for_row(static_cast<T>(1),
                                                      dim_seq<0>{},
                                                      cols{});
        T one_over_det = static_cast<T>(1) / dot(m[0], row0_cofactors);
        return transposed_cofactors(row0_cofactors,
                                    one_over_det,
                                    seq::remove<0, rows>{},
                                    cols{});
    }
};

}  // namespace impl

}  // namespace bdm
