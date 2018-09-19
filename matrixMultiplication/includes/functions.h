#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

template<typename T> 
void printMatrixToSerial(T& matrix) {
  auto contentPointer = &matrix.content[0][0];

  Serial.println("Matrix = ");
  for (size_t i = 0; i < matrix.size; i++) {
    if (i % matrix.cols == 0) {
      Serial.print("\t[");
    }

    Serial.print(*(contentPointer + i));

    if (i % matrix.cols == matrix.cols - 1) {
      Serial.println("],");
    } else {
      Serial.print(",\t");
    }
  }
}

template<typename T, typename U, typename V>
inline void multiplyProgMem(T& A, U& B, V& C) {
  // Make sure result array is empty
  for (size_t i = 0; i < A.rows; i++) {
    for (size_t j = 0; j < B.cols; j++) {
      C.content[i][j] = 0;
      for(size_t r = 0; r < B.rows; r++) {
        // Calculate matrix elements
        // For more info, check section definition (last accessed 22-9-2018): https://en.wikipedia.org/wiki/Matrix_multiplication
        C.content[i][j] += pgm_read_byte(&A.content[i][r]) * pgm_read_byte(&B.content[r][j]);
      }
      C.content[i][j] += (pgm_read_byte(&A.content[i][j]) << 1);
    }
  }
}

// Multiply with transposed B
template<typename T, typename U, typename V>
inline void multiplyWithTranposeProgMem(T& A, U& B, V& C) {
  // Ensure result array is empty
  for (size_t i = 0; i < A.rows; i++) {
    for (size_t j = 0; j < B.cols; j++) {
      // Clear element
      C.content[i][j] = 0;
      for(size_t r = 0; r < B.rows; r++) {
        // Calculate matrix elements
        // For more info, check section definition (last accessed 22-9-2018): https://en.wikipedia.org/wiki/Matrix_multiplication
        C.content[i][j] += pgm_read_byte(&A.content[i][r]) * pgm_read_byte(&B.content[j][r]);
      }
      C.content[i][j] += (pgm_read_byte(&A.content[i][j]) << 1);
    }
  }
}

#endif	/* FUNCTIONS_H */
