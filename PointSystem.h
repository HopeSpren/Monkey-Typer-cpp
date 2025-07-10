//
// Created by JanWi on 13.05.2025.
//

#ifndef POINTSYSTEM_H
#define POINTSYSTEM_H



class PointSystem {
    int pointCount;
    int HP;

    public:
    PointSystem();

    void awardPoint();
    void loseHP();

    int getHP();
    int getPointCount();


};



#endif //POINTSYSTEM_H
