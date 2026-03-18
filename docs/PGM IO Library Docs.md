# 1.1 - Functions

| Function   | Parameter(s)                        | Return Type | Description                                               |
| ---------- | ----------------------------------- | ----------- | --------------------------------------------------------- |
| `readPGM`  | - `String` filename<br>- `FILE*` fp | `void`      | Reads in a PGM file and stores information in a buffer    |
| `writePGM` | - `String` filename<br>- `FILE*` fp | `void`      | Writes to a PGM file using information stored in a buffer |
|            |                                     |             |                                                           |
# 1.2 - Structs

| Name       | Data Fields                                                                | Description of Each Field                                                                                                                                                                            |
| ---------- | -------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `PGMimage` | - `int` width<br>- `int` height<br>- `int` max<br>- `unsigned char` \*data | - `width`: The width of the image<br>- `height`: The height of the image<br>- `max`: The max intensity of the image (typically a power of 2)<br>- `*data`: A pointer to an array of `char` in memory |

