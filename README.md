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

| Original Image | Cutoff Frequency = 10 | Cutoff Frequency = 200 | 
| <img src="https://github.com/bixiphel/dftFilter/blob/440b9afd7f5d63ab6b47a0006dced248edb8114d/examples/Knee.png" /> | <img src="https://github.com/bixiphel/dftFilter/blob/742f0a6f55ce9ead7dfa666c62ca4f321dcbc971/examples/output10.png" /> | <img src="https://github.com/bixiphel/dftFilter/blob/742f0a6f55ce9ead7dfa666c62ca4f321dcbc971/examples/output200.png" /> |

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
