#include "city.hpp"
#include "individual.hpp"
#include <algorithm>

#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

struct Result {
  double* results;
  double best;
  int populationSize;
  int generations;
  double mutationRate;
  int tournamentSize;
  int crosoverPerGeneration;
};

class GeneticAlgotihm {
  private:
    std::vector<City> cities;
    std::vector<Individual> population;
    Individual bestIndividual;

    void initializePopulation(int populationSize) {
      for (int i = 0; i < populationSize; i++) {
        std::random_shuffle(cities.begin(), cities.end());
        population.push_back(Individual(cities));
      }
    };

  public:
    GeneticAlgotihm(std::vector<City> cities) {
      this->cities = cities;
    };

    Result run(int populationSize, int generations, double mutationRate, int tournamentSize, int crosoverPerGeneration) {
      initializePopulation(populationSize);
      Result result;
      result.populationSize = populationSize;
      result.generations = generations;
      result.mutationRate = mutationRate;
      result.tournamentSize = tournamentSize;
      result.crosoverPerGeneration = crosoverPerGeneration;
      result.results = new double[generations];


      for (int i = 0; i < generations; i++) {
        std::sort(population.begin(), population.end(), [](Individual a, Individual b) {
          return a.fitness() < b.fitness();
        });

        if (i == 0 || population[0].fitness() < bestIndividual.fitness()) {
          bestIndividual = population[0];
        }
        result.results[i] = population[0].fitness();

        evolve(mutationRate, crosoverPerGeneration, tournamentSize);
      }

      std::cout << "Best Individual: " << bestIndividual.fitness() << std::endl;
      result.results[generations] = bestIndividual.fitness();
      population.clear();

      result.best = bestIndividual.fitness();
      return result;
    };

    void evolve(double mutationRate, int crosoverPerGeneration, int tournamentSize) {
      int* winners = tournamentSelection(tournamentSize, crosoverPerGeneration * 2);
      for (int i = 0; i < crosoverPerGeneration; i++) {
        std::pair<Individual, Individual> children = population[winners[i]].crossover(population[winners[i + 1]], mutationRate);
        population.erase(population.begin()+i);
        population.erase(population.begin()+i+1);
        population.push_back(children.first);
        population.push_back(children.second);
      }
      
      delete[] winners;
    };

    int* tournamentSelection(int tournamentSize, int winners) {
      int* winnerGroup = new int[winners];

      for (int i = 0; i < winners; i++) {
        int winner = rand() % population.size();
        for (int j = 0; j < tournamentSize; j++) {

          int random = rand() % population.size();
          while (std::find(winnerGroup, winnerGroup + winners, random) != winnerGroup + winners) { // repaeat if winner is already in the group
            random = rand() % population.size();
          }

          if (population[random].fitness() < population[winner].fitness()) {
            winner = random;
          }
        }
        winnerGroup[i] = winner;
      }
      return winnerGroup;
    }

};

#endif