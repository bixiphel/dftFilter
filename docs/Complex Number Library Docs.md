# 1.1 - Functions

| Function Group | Function Name | Parameter(s)                                                         | Return Type                                             | Description                                                         |
| -------------- | ------------- | -------------------------------------------------------------------- | ------------------------------------------------------- | ------------------------------------------------------------------- |
| Mathematic     | `c_add`       | - `Complex` $z1$<br>- `Complex` $z2$ | `Complex` `Complex` | Adds two complex values $z1$ and $z2$                                   |
| Mathetmatic    | `c_sub`       | - `Complex` $z1$<br>- `Complex` $z2$ | `Complex`                             | Subtracts two complex values $z1$ and $z2$                              |
| Mathematic     | `c_mul`       | - `Complex` $z1$<br>- `Complex` $z2$ | `Complex`                             | Multiplies two complex values $z1$ and $z2$                             |
| Mathematic     | `c_exp`       | - `Complex` $z$                                    | `Complex`                             | Performs $e^{z}$, uses Euler's formula: $e^{ix} = \cos(x)+i\sin(x)$ |
| Utility        | `c_print`     | - `Complex` $z$                                    | `void`                                                  | Prints out a complex number                                         |
| Utility        | `c_rep`       | - `double` $x$                                                         | `Complex`                             | Returns the complex representation of a value $x$                   |
| Utility        | `c_real`      | - Complex $z$                                                        | `double`                                                | Returns the real component of a complex number                      |
| Utility        | `c_imag`      | - Complex $z$                                                        | `double`                                                | Returns the imaginary component of a complex number                 |
| Utility        | `c_mag`       | - Complex $z$                                                        | `double`                                                | Returns the magnitude of a complex number                           |

# 1.2 - Structs

| Name    | Data Fields                        | Description              |
| ------- | ---------------------------------- | ------------------------ |
| Complex | - `double` real<br>- `double` imag | Defines a complex number |
