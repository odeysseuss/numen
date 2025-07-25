### Available Macros;

- ***Core Macros***

| Macro | Description |
|-------|-------------|
| `TEST(suite, name)` | Defines a test case |
| `ASSERT_TRUE(cond)` | Fails if condition is false |
| `ASSERT_FALSE(cond)` | Fails if condition is true |
| `ASSERT_EQ(a, b)` | Fails if a ≠ b (int/pointer) |
| `ASSERT_NE(a, b)` | Fails if a = b |
| `ASSERT_FLOAT_EQ(a, b)` | Fails if floats not equal (with epsilon tolerance) |
| `ASSERT_NEAR(a, b, tol)` | Fails if a not within tolerance of b |
| `ASSERT_NULL(ptr)` | Fails if pointer is not NULL |
| `ASSERT_NOT_NULL(ptr)` | Fails if pointer is NULL |

- ***Benchmark Macros***

| Macro | Description |
|-------|-------------|
| `BENCHMARK_START()` | Starts timer (place at start of benchmark) |
| `BENCHMARK_END(name)` | Stops timer and prints duration |

- ***Special Functions***

| Function | Description |
|----------|-------------|
| `RUN_ALL_TESTS()` | Runs all registered tests (returns 0 if all pass) |
| `SKIP_TEST()` | Immediately skips current test |

