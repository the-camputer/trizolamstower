# Trizolam's Tower

Trizolam's Tower is a text-based fantasy adventure game centered around exploring the mysterious disappearance of the members of the town of Bridgerton.


## Building

### Dependencies

Dependencies are managed by Conan.

The following are required to begin development:

* g++-10
* Python3
* Pip
* Conan (installed via pip)

In addition, Conan profile will need the following profile attributes updated:
```
compiler=gcc
compiler.version=10
compiler.libcxx=libstdc++11
```

The following libraries are required to build Trizolam's Tower, as managed by Conan

* Catch2 v2 (Tests only)
* Boost
* spdlog

### Build Process

From empty directory:

```sh
git clone https://github.com/the-camputer/trizolamstower.git
cd trizolamstower
mkdir build
cd build
conan install ..
cmake ..
cmake --build .
```
