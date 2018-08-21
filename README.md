# BDM

BDM stands for Barely Dimensional Mathematics. It's a futile attempt at creating another 3d-math library for graphics programming, utilizing cutting-edge C++ features, and leaning heavily on performing as much computation as possible during compile time.

The library's design-goal is to strive towards fully generic abstractions, and as such there is only a single vector, matrix, etc. template. Likewise, all the algorithms that are being implemented are expected to work on abstractions of all sizes and dimensions (provided they have a meaningful mathematical definition of course).

A clear inspiration is the already industry-standard GLM library, which is even used in the benchmarks for a side-by-side comparison.

At the moment SIMD support is not implemented at all whatsoever, but it's on the to-do list, right after achieving initial feature-completeness.

No 3rd-party dependencies are used (except for running the tests and benchmarks), but another in-house developed library _is_ included actually in the source tree (https://github.com/integricho/seq), although at the moment it's just directly copied into the tree.

## Versioning

This project uses [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/integricho/bdm/tags).

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
