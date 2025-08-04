### Matrix Types

- ***2x2 matrices***
```c
typedef union {
    nml_t Elements[4];
    Vec2 Columns[2];
} Mat2;
```

- ***3x3 matrices***
```c
typedef union {
    nml_t Elements[9];
    Vec3 Columns[3];
} Mat3;
```

- ***4x4 matrices***
```c
typedef union {
    nml_t Elements[16];
    Vec4 Columns[4];
} Mat4;
```
