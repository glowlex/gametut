#include <ctime>
#include <cstdlib>
#include <cmath>
#include <cstdio>

int main() {
  srand(static_cast<unsigned int>(time(0)));
  for(size_t i = 0; i < 26; ++i) {
    for (size_t j = 0; j < 8; ++j) {
      int rnd = rand() % 65;
      printf("%02d ", rnd);
	}
	printf("\n");
  }
  system("pause");
}
