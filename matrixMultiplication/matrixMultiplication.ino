template <typename type, uint8_t R, uint8_t C>
struct Matrix {
  type content[R][C]; // Two dimensional array containing matrix data
  const uint8_t rows = R; // Number of rows
  const uint8_t cols = C; // Number of columns
  const uint16_t size = R * C; // Total matrix size
};

// Define the 13x13 square matrix type
typedef struct Matrix<uint8_t, 13, 13> Matrix13;

const Matrix13 A = {
  .content = {
    {29,1,5,82,117,113,115,67,91,107,75,73,39},
    {84,90,82,59,125,102,122,72,35,59,2,75,22},
    {109,44,125,33,46,125,125,67,16,11,13,124,78},
    {82,30,48,3,3,69,0,24,123,108,92,127,16},
    {117,77,26,77,30,74,71,63,68,12,66,126,84},
    {39,86,124,25,99,101,26,9,8,91,97,101,104},
    {7,67,121,95,84,109,92,14,88,105,120,119,84},
    {90,18,94,29,126,84,82,28,103,23,101,108,122},
    {56,11,39,107,15,59,104,120,106,83,102,38,103},
    {14,81,100,76,42,3,5,5,31,22,29,77,15},
    {118,59,124,89,85,3,58,74,22,49,78,51,28},
    {118,123,87,64,93,32,91,20,85,102,65,119,16},
    {33,81,8,114,69,77,63,114,42,34,62,34,103}
  },
};

const Matrix13 B = {
  .content = {
    {103,30,41,69,98,13,72,23,82,72,108,96,25},
    {121,16,54,73,66,58,111,1,110,100,126,50,79},
    {77,70,73,41,92,62,62,100,115,87,18,125,91},
    {98,81,65,5,81,6,42,115,122,14,60,121,112},
    {63,86,4,16,38,53,110,11,73,49,107,7,114},
    {29,71,100,72,25,11,112,4,120,94,111,16,2},
    {105,62,120,39,114,38,105,56,125,11,30,17,37},
    {86,46,16,93,26,100,63,116,93,64,108,44,21},
    {61,108,126,110,8,85,67,36,25,52,43,26,78},
    {52,21,13,31,58,10,60,6,13,82,84,81,88},
    {10,102,16,59,117,0,1,76,84,72,13,95,120},
    {120,81,69,74,64,55,70,61,43,42,17,90,59},
    {101,103,39,106,115,15,88,75,24,118,41,75,104}
  },
};

// Create an empty result matrix (all 0 initialized) of 13 by 13 with 16 bit unsigned integers
const Matrix13 transposed = {
  .content = {
    {103,121,77,98,63,29,105,86,61,52,10,120,101},
    {30,16,70,81,86,71,62,46,108,21,102,81,103},
    {41,54,73,65,4,100,120,16,126,13,16,69,39},
    {69,73,41,5,16,72,39,93,110,31,59,74,106},
    {98,66,92,81,38,25,114,26,8,58,117,64,115},
    {13,58,62,6,53,11,38,100,85,10,0,55,15},
    {72,111,62,42,110,112,105,63,67,60,1,70,88},
    {23,1,100,115,11,4,56,116,36,6,76,61,75},
    {82,110,115,122,73,120,125,93,25,13,84,43,24},
    {72,100,87,14,49,94,11,64,52,82,72,42,118},
    {108,126,18,60,107,111,30,108,43,84,13,17,41},
    {96,50,125,121,7,16,17,44,26,81,95,90,75},
    {25,79,91,112,114,2,37,21,78,88,120,59,104},
  },
};
Matrix<uint32_t, 13, 13> result = {};

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
inline void multiply(T& A, U& B, V& C) {
  // Make sure result array is empty

  // Don't use memset, terribly slow
  //memset(C.content, 0, C.size * sizeof(C.content[0][0]));
  for (size_t i = 0; i < A.rows; i++) {
    for (size_t j = 0; j < B.cols; j++) {
      C.content[i][j] = 0;
      for(size_t r = 0; r < B.rows; r++) {
        // Calculate matrix elements
        // For more info, check section definition (last accessed 22-9-2018): https://en.wikipedia.org/wiki/Matrix_multiplication
        C.content[i][j] += A.content[i][r] * B.content[r][j];
      }
      C.content[i][j] += (A.content[i][j] << 1);
    }
  }
}

// Multiply with transposed B
template<typename T, typename U, typename V>
inline void multiplyWithTranpose(T& A, U& B, V& C) {
  // Ensure result array is empty
  //memset(C.content, 0, C.size * sizeof(C.content[0][0]));
  for (size_t i = 0; i < A.rows; i++) {
    for (size_t j = 0; j < B.cols; j++) {
      // Clear element
      C.content[i][j] = 0;
      for(size_t r = 0; r < B.rows; r++) {
        // Calculate matrix elements
        // For more info, check section definition (last accessed 22-9-2018): https://en.wikipedia.org/wiki/Matrix_multiplication
        C.content[i][j] += A.content[i][r] * B.content[j][r];
      }
      C.content[i][j] += (A.content[i][j] << 1);
    }
  }
}

template<typename T, typename U>
inline void transpose(T& org, U& tr) {
  for (size_t i = 0; i < A.rows; i++) {
    for (size_t j = 0; j < B.cols; j++) {
        tr.content[i][j] = org.content[j][i];
    }
  }
}

void setup() {
  // Begin serial communication at 115.200 baud/s
  Serial.begin(115200);
}

void loop() {
  // Initialize timing variable
  unsigned long timeVariable = 0;
  
  // Start counter
  timeVariable = micros();

  // Calculate the multiplication 1000 times
  for (size_t i = 0; i < 1000; i++) {
    multiply< >(A, B, result);
  }
  timeVariable = micros() - timeVariable;

  Serial.print("Multiply Time: ");
  Serial.println(timeVariable);
  printMatrixToSerial< >(result);

  // Start counter
  //transpose< >(B, transposed);
  timeVariable = micros();
  // Calculate the multiplication 1000 times
  for (size_t i = 0; i < 1000; i++) {
    multiplyWithTranpose< >(A, transposed, result);
  }
  timeVariable = micros() - timeVariable;
  Serial.print("MultiplyWithTranspose Time: ");
  Serial.println(timeVariable);
  printMatrixToSerial< >(result);
  
}
