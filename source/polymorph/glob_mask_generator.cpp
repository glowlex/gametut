#include <ctime>
#include <cmath>
#include <cstdlib>
#include <cstdio>

int main() {
  srand(static_cast<unsigned int>(time(0)));
  for(size_t i = 0; i < 26; ++i) {
    for(size_t j = 0; j < 10; ++j) {
      int rnd = rand() % 321;
      printf("%03d ", rnd);
	}
	printf("\n");
  }
  system("pause");
}
