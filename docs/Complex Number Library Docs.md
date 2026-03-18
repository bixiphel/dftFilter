# 1.1 - Functions

| Function Group | Function Name | Parameter(s)                                                         | Return Type                                             | Description                                                         |
| -------------- | ------------- | -------------------------------------------------------------------- | ------------------------------------------------------- | ------------------------------------------------------------------- |
| Mathematic     | `c_add`       | - [[#1.2 - Structs\|Complex]] z1<br>- [[#1.2 - Structs\|Complex]] z2 | [[#1.2 - Structs\|Complex]] [[#1.2 - Structs\|Complex]] | Adds two complex values z1 and z2                                   |
| Mathetmatic    | `c_sub`       | - [[#1.2 - Structs\|Complex]] z1<br>- [[#1.2 - Structs\|Complex]] z2 | [[#1.2 - Structs\|Complex]]                             | Subtracts two complex values z1 and z2                              |
| Mathematic     | `c_mul`       | - [[#1.2 - Structs\|Complex]] z1<br>- [[#1.2 - Structs\|Complex]] z2 | [[#1.2 - Structs\|Complex]]                             | Multiplies two complex values z1 and z2                             |
| Mathematic     | `c_exp`       | - [[#1.2 - Structs\|Complex]] $z$                                    | [[#1.2 - Structs\|Complex]]                             | Performs $e^{z}$, uses Euler's formula: $e^{ix} = \cos(x)+i\sin(x)$ |
| Utility        | `c_print`     | - [[#1.2 - Structs\|Complex]] $z$                                    | `void`                                                  | Prints out a complex number                                         |
| Utility        | `c_rep`       | - `double` x                                                         | [[#1.2 - Structs\|Complex]]                             | Returns the complex representation of a value $x$                   |
| Utility        | `c_real`      | - Complex $z$                                                        | `double`                                                | Returns the real component of a complex number                      |
| Utility        | `c_imag`      | - Complex $z$                                                        | `double`                                                | Returns the imaginary component of a complex number                 |
| Utility        | `c_mag`       | - Complex $z$                                                        | `double`                                                | Returns the magnitude of a complex number                           |

# 1.2 - Structs

| Name    | Data Fields                        | Description              |
| ------- | ---------------------------------- | ------------------------ |
| Complex | - `double` real<br>- `double` imag | Defines a complex number |
