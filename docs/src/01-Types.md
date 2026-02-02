### Matrix Types

- ***2x2 matrices***
```c
typedef union {
    nml_t elems[4];
    Vec2 cols[2];
} Mat2;
```

- ***3x3 matrices***
```c
typedef union {
    nml_t elems[9];
    Vec3 cols[3];
} Mat3;
```

- ***4x4 matrices***
```c
typedef union {
    nml_t elems[16];
    Vec4 cols[4];
} Mat4;
```
