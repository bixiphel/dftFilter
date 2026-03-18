# 2D DFT Image Processing in C
This project implements a **2D Discrete Fourier Transform (DFT)** and its inverse (**IDFT**) from scratch in C, using custom complex number operations and PGM image I/O, to perform an **Ideal Low Pass Filter** in the frequency domain.

## Features
- Forward 2D DFT and Inverse 2D DFT
- Frequency-domain filtering (using ideal low-pass)
- User-specified input, output, and cutoff frequency parameters
- Custom implementations of:
  - Complex arithmetic
  - PGM image read/write
 
## General Notes
- Input/output image file type **only supports PGM files**
- Time complexity is on the order of $O(n^3)$, hence long execution time
- Only non-built in libraries that are used are `stdlib.h`, `stdio.h`, and `math.h` for utility and trignometric functions

## Usage
1. Place a `.pgm` image in the project directory (e.g., `Knee.pgm`)
2. Compile (using GCC):
   ```bash
   gcc 2ddft.c complex.c pgm.c -lm -o dft
   ```
3. Execute (using Bash):
   ```bash
   ./dft <input_pgm> <output_pgm> <cutoff_frequency>
   ```
