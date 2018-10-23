#pragma once

#define ASSERT_VEC_NEAR(v1, v2, threshold)                                     \
    ASSERT_EQ(v1.dimension, v2.dimension);                                     \
    for (bdm::dim_t ri = 0u; ri < v1.dimension; ++ri)                          \
    {                                                                          \
        ASSERT_NEAR(v1[ri], v2[ri], threshold);                                \
    }

#define ASSERT_MAT_NEAR(m1, m2, threshold)                                     \
    ASSERT_EQ(m1.rows, m2.rows);                                               \
    ASSERT_EQ(m1.cols, m2.cols);                                               \
    for (bdm::dim_t ri = 0u; ri < m1.rows; ++ri)                               \
    {                                                                          \
        for (bdm::dim_t ci = 0u; ci < m1.rows; ++ci)                           \
        {                                                                      \
            ASSERT_NEAR(m1[ri][ci], m2[ri][ci], threshold);                    \
        }                                                                      \
    }
