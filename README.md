# HawtLA
A Linear Algebra Library written in C++.

Create matrices and vectors and perform arithmetic on them. It can also be used to calculate various matrix functions such as the Determinant, Norm, Transpose, Inverse, etc.

## Sample

### Sample Code

```c++
#include "Matrix.h"
#include "Common.h"

int main() 
{
  // Create Matrices
  HLA::Matrix m2({ 1, 2, 3, 4, 5, 6 }, { 3,2 });
  HLA::Matrix m3 = HLA::Zero(3, 3);
  m3(0, 0) = 1;
  m3(1, 1) = 2;
  m3(2, 2) = 1;
  
  std::cout << m3.PrintFormat() << std::endl; // Prints the matrix on screen
  
  m1.IsVector() // Checks if m1 is a vector
  HLA::IsSquare(m1) // Checks if given matrix is a square
  m1.Determinant() // Calculates the determinant
  
  // Create Vectors
  HLA::Matrix vec0{ { -3, 2, 1, }, { 3, 1 } };
  HLA::Matrix vec1{ { -3, 3, 5, }, { 3, 1 } };
  
  // Get the angle between two vectors in Radians
  HLA::TwoVectorAngle(std::vector<double>(vec0), std::vector<double>(vec1)); 
}

```
### Sample App (HLA_Demo)

![HLA used in a demo app](/Resources/sampleGif.gif)

## Build
In a terminal enter the following command: ```git clone https://github.com/HawtStrokes/HawtLA.git ```

Open the sln file in the root folder and build, and then link the .lib file to your project


## **Dependencies**

There are no dependencies for the library, all external code included are for the Demo App.

- https://github.com/glfw/glfw
- https://github.com/ocornut/imgui
