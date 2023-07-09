#include "city.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "individual.hpp"
#include "genetic_algorithm.hpp"
#include <fstream>

void write_to_csv(char* filename, Result* results, int results_size) {
  std::ofstream file(filename);
  if (file.is_open()) {
    file << ";best;";
    int biggest_gen = results[0].generations;
    for (int i=1; i < results_size; i++) {
      if (results[i].generations > biggest_gen) {
        biggest_gen = results[i].generations;
      }
    }
    for (int i=1; i <= biggest_gen; i++) {
      file << ";g" << i;
    }
    file << std::endl;
    for (int i=0; i < results_size; i++) {
      file << ";" << results[i].best << ";";
      for (int j=0; j < results[i].generations; j++) {
        file << ";" << results[i].results[j];
      }
      file << std::endl;
    }
  }
  file.close();
}

int main(int argc, char** argv) {
  srand((unsigned int)time(NULL));
  int n;
  std::cin >> n;
  std::vector<City> cities;;

  for (int i = 0; i < n; i++) {
    City c;
    std::cin >> c;
    cities.push_back(c);
  }

  GeneticAlgotihm ga(cities);
  
  int results_size = 4;
  Result results[results_size] = {
    ga.run(100, 100, 0.05, 5, 10),
    ga.run(100, 100, 0.05, 5, 10),
    ga.run(100, 100, 0.05, 5, 10),
    ga.run(100, 100, 0.05, 5, 10)
  };

  if (argc > 1) {
    write_to_csv(argv[1], results, results_size);
  }
}