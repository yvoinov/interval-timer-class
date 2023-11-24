# Interval timer class
[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://github.com/yvoinov/interval-timer-class/blob/master/LICENSE)

Easy to use, Boost-free templated interval timer class for periodic tasks that need to be performed constantly.

To use just include this header to your project and instantiate class as ahown:

```cpp
// Instantiation
Timer<std::size_t, std::function<void()>> timer(/* Here must be timer interval */, []() { /* Executable statements */ });
```
