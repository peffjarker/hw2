#include <iostream>
#include <omp.h>
using namespace std;

int main() {
  int a[1000] = {0};
  for (int i = 0; i < 1000; ++i) {
    a[i] = i;
  }
  int sum = 0;
#pragma omp parallel for
  for (int i = 0; i < 1000; ++i) {
    if (a[i] < 10) {
      sum++;
    }
  }

  cout << sum;
  return 0;
}
