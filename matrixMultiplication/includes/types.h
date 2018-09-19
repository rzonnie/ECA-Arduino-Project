#ifndef TYPES_H
#define	TYPES_H

template <typename type, uint8_t R, uint8_t C>
struct Matrix {
  type content[R][C]; // Two dimensional array containing matrix data
  const uint8_t rows = R; // Number of rows
  const uint8_t cols = C; // Number of columns
  const uint16_t size = R * C; // Total matrix size
};

// Define the 13x13 square matrix type
typedef struct Matrix<uint8_t, 13, 13> Matrix13;

#endif	/* TYPES_H */
