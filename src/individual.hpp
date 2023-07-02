#include <iostream>
#include "city.hpp"
#include <vector>

#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

class Individual {
  friend std::ostream& operator<<(std::ostream& os, Individual& individual);
  private:
    std::vector<City> cities;
  
  public:

    Individual() {};

    Individual(std::vector<City> cities) {
      this->cities = cities;
    };

    Individual(const Individual& individual) {
      this->cities = individual.cities;
    };

    double fitness() {
      double fitness = 0;
      for (int i = 0; i < cities.size() - 1; i++) {
        fitness += cities[i].distanceTo(cities[i + 1]);
      }
      fitness += cities[cities.size() - 1].distanceTo(cities[0]);
      return fitness;
    };

    std::pair<Individual, Individual> crossover(Individual parent2, double mutationRate) { // Two Point Crossover
      int p1 = rand() % cities.size();
      int p2 = rand() % cities.size();

      if (p1 > p2) {
        int aux = p1;
        p1 = p2;
        p2 = aux;
      }

      std::vector<City> parent1Fragment;
      std::vector<City> parent2Fragment;

      for (int i = p1; i <= p2; i++) {
        parent1Fragment.push_back(cities[i]);
        parent2Fragment.push_back(parent2.cities[i]);
      }

      Individual child1 = *this;
      Individual child2 = parent2;

      for (int i = 0; i < parent1Fragment.size(); i++) {
        child1.remove(parent2Fragment[i]);
        child2.remove(parent1Fragment[i]);
      }

      for (int i = 0; i < parent1Fragment.size(); i++) {
        child1.insertOn(p1 + i, parent2Fragment[i]);
        child2.insertOn(p1 + i, parent1Fragment[i]);
      }

      if (mutationRate > (double)rand() / (double)RAND_MAX) {
        child1.swapMutation();
      }

      if (mutationRate > (double)rand() / (double)RAND_MAX) {
        child2.swapMutation();
      }

      return std::pair<Individual, Individual>(child1, child2);
    };

    void swapMutation() {
      int p1 = rand() % cities.size();
      int p2 = rand() % cities.size();

      City aux = cities[p1];
      cities[p1] = cities[p2];
      cities[p2] = aux;
    };

    void insertOn(int pos, City city) {
      cities.insert(cities.begin() + pos, city);
    };

    void remove(City city) {
      for (int i = 0; i < cities.size(); i++) {
        if (cities[i] == city) {
          cities.erase(cities.begin() + i);
          return;
        }
      }
    }

    bool operator<(Individual& individual) {
      return fitness() < individual.fitness();
    };

    bool operator==(Individual& individual) {
      return fitness() == individual.fitness();
    };

    bool operator!=(Individual& individual) {
      return fitness() != individual.fitness();
    };

    bool operator>(Individual& individual) {
      return fitness() > individual.fitness();
    };
};

std::ostream& operator<<(std::ostream& os, Individual& individual) {
  os << "Individual: ";
      for (int i = 0; i < individual.cities.size(); i++) {
        os << individual.cities[i];
        if (i < individual.cities.size() - 1) {
          os << "->";
        }
      }
      os << " Fitness: " << individual.fitness();
      return os;
}

#endif