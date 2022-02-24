#include <iostream>
#include <limits.h>
#include <string.h>
#include <string>
unsigned int *sieve(unsigned int count) {
  bool *numbers = NULL;
  if (count > 0)
    numbers = new bool[count];
  if (!numbers) {
    printf("error: Could not allocate memmory!");
    return nullptr;
  }
  // initalize array of numbers to sieve
  for (int i = 0; i < count; i++) {
    numbers[i] = true;
  }
  // sieve numbers
  for (int i = 2; i < count; i++) {
    if (numbers[i]) {
      unsigned int factor = i;
      for (int j = factor * 2; j < count; j += factor) {
        numbers[j] = false;
      }
    }
  }
  // count found primes
  unsigned int prime_count = 0;
  for (int i = 0; i < count; i++) {
    if (numbers[i]) {
      prime_count++;
    }
  }
  // add found primes to new array of found primes
  unsigned int *found_primes = new unsigned int[prime_count + 1];
  unsigned int position = 0;
  for (int i = 0; i < count; i++) {
    if (numbers[i]) {
      found_primes[position] = i;
      position++;
    }
  }
  found_primes[prime_count + 1] = 0;
  delete[] numbers;
  return found_primes;
}
uint64_t hash(const char *s, unsigned int *primes, uint64_t maximum_index) {
  uint64_t hash = 1;
  for (int i = 0; i < strlen(s); i++) {
    unsigned int prime_index = s[i] % maximum_index;
    hash *= primes[prime_index];
    hash *= hash;
  }
  return hash % primes[maximum_index - 1];
}
int main() {
  unsigned int *primes = sieve(16000);
  if (primes == nullptr) {
    std::cout << "could not generate primes\n";
    return -1;
  }

  unsigned int maximum_index = 1;
  while (primes[maximum_index] != 0) {
    maximum_index++;
  }
  unsigned int valid_hashes_count = 8 * 8 * 8 * 8;
  unsigned int *hash_hits = new unsigned int[valid_hashes_count];

  std::cout << "maximum index : " << maximum_index << std::endl;
  bool quit = false;
 while(!quit) {
	std::string in = "";
	std::cin >> in;
	std::cout << hash(in.c_str(), primes, maximum_index);
       }
  delete[] primes;
  delete[] hash_hits;
  return 0;
}
