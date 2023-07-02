#include "city.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "individual.hpp"
#include "genetic_algorithm.hpp"
#include <fstream>

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

  GeneticAlgoritm ga(cities);
  
  int results_size = 4;
  Result results[results_size] = {
    ga.run(100, 50, 0.05, 5, 10),
    ga.run(100, 100, 0.05, 5, 10),
    ga.run(100, 150, 0.05, 5, 10),
    ga.run(100, 200, 0.05, 5, 10)
  };

  if (argc > 1) { // write results to csv
    std::ofstream file(argv[1]);
    if (file.is_open()) {
      file << "populationSize;generations;mutationRate;tournamentSize;crosoverPerGeneration;best";
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
        file << results[i].populationSize << ";" << results[i].generations << ";" << results[i].mutationRate << ";" << results[i].tournamentSize << ";" << results[i].crosoverPerGeneration << ";" << results[i].best;
        for (int j=0; j < results[i].generations; j++) {
          file << ";" << results[i].results[j];
        }
        file << std::endl;
      }
    }
    file.close();
  }
}