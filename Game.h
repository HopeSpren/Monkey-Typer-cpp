//
// Created by JanWi on 06.05.2025.
//

#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <random>


#include "Cofig.h"
#include "PointSystem.h"


class Game {
    Cofig& config_;
    sf::Font font_;

    std::mt19937 rng;
    std::vector<float> spawnCenterPositionsX;
    float start_pos_y_;

    std::list<std::unique_ptr<sf::Text>> wordsLIst;

    sf::Clock clock_;
    float time_since_last_word_;
    sf::Time delta_time_;

    float word_speed_;


    int num_spawn_positions_;
    float horizontal_step_;
    sf::RectangleShape line_;

    std::string currentInput;
    sf::Text currentText_;



    sf::RenderWindow vindow;
    std::uniform_int_distribution<size_t> positionIndexDist;
    unsigned long long num_positions_;
    std::uniform_int_distribution<size_t> wordIndexDist;

    float dt_seconds_;
    float center_x_;
    float word_width_;
    float start_x_;
    sf::Vector2<float> start_pos_;

    sf::Text hp;
    sf::Text points;

    PointSystem pointSystem_;
    int non_random_iterator_;

    /// =================================================================================
    void changeTextOutline(sf::Text &text, sf::Color color);

    void  startGame();
    void manageEvents();

    void random_word_add();

    void manageWords();

    void pregameSH();

    void drawAllthat();

    void typeWordHandling();

    void UIreadding();
    void UIdrawing();

    void NonRadomText();

public:
    void openGame(const Cofig &cofig);

    Game( Cofig &cofig);


};



#endif //GAME_H
