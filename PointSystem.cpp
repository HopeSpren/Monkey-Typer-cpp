//
// Created by JanWi on 13.05.2025.
//

#include "PointSystem.h"

PointSystem::PointSystem() {
  this ->  pointCount = 0;
  this -> HP = 3;
}

void PointSystem::awardPoint() {
  pointCount++;
}

void PointSystem::loseHP() {
  HP--;
}
int PointSystem::getHP() {
  return HP;

}

int PointSystem::getPointCount() {

  return pointCount;
}
