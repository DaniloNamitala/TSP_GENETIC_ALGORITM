#include <math.h>
#include <iostream>

#ifndef CITY_HPP
#define CITY_HPP

class City {
  private:
    int x;
    int y;

  public:
    City(int x, int y) {
      this->x = x;
      this->y = y;
    };

    City(const City& city) {
      this->x = city.x;
      this->y = city.y;
    };

    City() {
      this->x = 0;
      this->y = 0;
    };

    int getX() {
      return this->x;
    };

    int getY() {
      return this->y;
    };

    double distanceTo(City city) {
      int xDistance = abs(getX() - city.getX());
      int yDistance = abs(getY() - city.getY());
      double distance = sqrt((xDistance * xDistance) + (yDistance * yDistance));

      return distance;
    };

    bool operator==(const City& city) const {
      return (this->x == city.x && this->y == city.y);
    };
};

std::ostream& operator<<(std::ostream& os, City& city) {
  os << "(" << city.getX() << "," << city.getY() << ")";
  return os;
}

std::istream& operator>>(std::istream& is, City& city) {
  int x, y;
  is >> x >> y;
  city = City(x, y);
  return is;
}

#endif