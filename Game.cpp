//
// Created by JanWi on 06.05.2025.
//

#include "Game.h"

#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "Cofig.h"
#include "fmt/core.h"
#include <random>
#include <SFML/Graphics/Rect.hpp>



Game::Game( Cofig &cofig)
    :config_(cofig),
    font_(cofig.get_game_font().fonts1().at(cofig.get_game_font().keys1().at(config_.get_font_number()))),
    currentText_(font_, "", 70),
    vindow(sf::VideoMode(sf::Vector2u(1400, 800)), sf::String("Monkey Typer")),
    pointSystem_(),
    hp(font_, "3", 40),
    points(font_, "0", 40)


    {

    time_since_last_word_ = 0.0f;
    num_spawn_positions_ = 6;
    start_pos_y_ = 50.0f;
    word_speed_ = cofig.getCofigTextSpeed();
    line_ = sf::RectangleShape(sf::Vector2f(1400.0f, 3.0f));
    line_.setFillColor(sf::Color::White);
    line_.setPosition(sf::Vector2f(0.0f, 600.0f));
    rng = std::mt19937(std::random_device{}());
    wordIndexDist = std::uniform_int_distribution<size_t>(0, config_.get_game_world().getwordsLoaded().size() - 1);
    currentText_.setPosition(sf::Vector2f(vindow.getSize().x/2, vindow.getSize().y- 100));
    non_random_iterator_ = 0;
    startGame();
    }
void Game::startGame() {
   pregameSH();
    while (vindow.isOpen()) {
        delta_time_ = clock_.restart();
        dt_seconds_ = delta_time_.asSeconds();
        time_since_last_word_ += dt_seconds_;

        manageEvents();

        UIreadding();

        manageWords();

        drawAllthat();



    }




}

void Game::manageEvents() {

    while (const std::optional event = vindow.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
        vindow.close();
    }
        if (auto const e = event->getIf<sf::Event::KeyPressed>())
        {
          if (!currentInput.empty() && e->code == sf::Keyboard::Key::Backspace) {
              currentInput.pop_back();
          }

        }
        if (auto const textEnteredEvent = event->getIf<sf::Event::TextEntered>()) {

            unsigned char unicodeChar = textEnteredEvent->unicode;
            if (std::isalpha(unicodeChar)){ currentInput.push_back(unicodeChar);}
            currentText_.setString(currentInput);
        }

    }

}



void Game::manageWords() {
    if (time_since_last_word_ > ((config_.linearFrequency()))) {
        if (!config_.get_game_world().getwordsLoaded().empty()) {
            if (config_.getSpecificOrderNeeded()){NonRadomText();}
            else{random_word_add();}
        }
    }
    if (!wordsLIst.empty()) {
        for (auto &word: wordsLIst) {
            sf::Vector2f offset(0.0f, word_speed_ * dt_seconds_);
            word->move(offset);
            if (word->getPosition().y > line_.getPosition().y -  150 ) {
                changeTextOutline(*word, sf::Color::Red);
            }

        }
        if (!wordsLIst.empty()) {
            for (auto it = wordsLIst.begin(); it != wordsLIst.end();) {
                auto &word_ptr = *it;
                float windowHeight = line_.getPosition().y - 50 ;

                if (word_ptr->getPosition().y > windowHeight) {
                    it = wordsLIst.erase(it);
                    pointSystem_.loseHP();

                    if (pointSystem_.getHP() < 0) {
                        vindow.close();
                    }

                } else {
                    ++it;
                }
            }
        }
        if (!wordsLIst.empty()) {
            for (auto it = wordsLIst.begin(); it != wordsLIst.end();) {
                auto &word_ptr = *it;
                if (word_ptr->getString().toAnsiString() == currentInput) {
                    it = wordsLIst.erase(it);
                    pointSystem_.awardPoint();
                    currentInput.clear();
                    currentText_.setString("");
                } else {
                    ++it;
                }
            }
        }

    }
}


void Game::drawAllthat() {
    vindow.clear(sf::Color::Black);
    vindow.draw(currentText_);
    vindow.draw(line_);
    for (const auto &word: wordsLIst) {
        vindow.draw(*word); // Rysuj bieżące słowo
    }
    UIdrawing();
    vindow.display();



}




void  Game::pregameSH() {
        rng = std::mt19937(std::random_device{}());
        positionIndexDist = std::uniform_int_distribution<size_t>(0, num_positions_ > 0 ? num_positions_ - 1 : 0);

    non_random_iterator_ = 0;
    wordsLIst.clear();

        horizontal_step_ = static_cast<float>(vindow.getSize().x) / (1 + num_spawn_positions_);
        for (int i = 0; i < num_spawn_positions_; ++i) {
            spawnCenterPositionsX.push_back(horizontal_step_ * (i + 1));
        }
        num_positions_ = spawnCenterPositionsX.size();
        size_t numPositions = spawnCenterPositionsX.size();
        positionIndexDist = std::uniform_int_distribution<size_t>(0, numPositions > 0 ? numPositions - 1 : 0);

        hp.setPosition(sf::Vector2f(50 , line_.getPosition().y + 100) );
        points.setPosition(sf::Vector2f(vindow.getSize().x -100 , line_.getPosition().y + 100));
        vindow.setFramerateLimit(config_.get_frame_limit());
    }


void Game::changeTextOutline(sf::Text& text,  sf::Color color) {
         {
            text.setOutlineThickness(12);
            text.setOutlineColor(color);
        }

    }

void Game::UIreadding() {
    hp.setString( std::to_string(pointSystem_.getHP()));
    points.setString(std::to_string(pointSystem_.getPointCount()));

}

void Game::UIdrawing() {
    vindow.draw(hp);
    vindow.draw(points);
}

void Game::NonRadomText() {
   std::string NONrandomWord = config_.get_game_world().getwordsLoaded()[(non_random_iterator_ > config_.get_game_world().getwordsLoaded().size() - 1)? 0 : non_random_iterator_++];
    auto newWord = std::make_unique<sf::Text>(font_, NONrandomWord, config_.getTextSize()); // Kolejność: czcionka, tekst, rozmiar

    newWord->setFillColor(sf::Color::White); // Ustaw kolor

    size_t randomCenterIndex = positionIndexDist(rng);
    center_x_ = spawnCenterPositionsX[randomCenterIndex];
    word_width_ = newWord->getGlobalBounds().size.x;
    start_x_ = center_x_ - word_width_ / 2.0f;
    start_pos_ = sf::Vector2f(start_x_, start_pos_y_);
    newWord->setPosition(start_pos_); // setPosition(float, float) jest OK

    wordsLIst.push_back(std::move(newWord));
    time_since_last_word_ = 0.0f;
}


void Game::random_word_add() {
    std::string randomWord = config_.get_game_world().getwordsLoaded()[wordIndexDist(rng)];
    auto newWord = std::make_unique<sf::Text>(font_, randomWord, config_.getTextSize()); // Kolejność: czcionka, tekst, rozmiar

    newWord->setFillColor(sf::Color::White); // Ustaw kolor

    size_t randomCenterIndex = positionIndexDist(rng);
    center_x_ = spawnCenterPositionsX[randomCenterIndex];
    word_width_ = newWord->getGlobalBounds().size.x;
    start_x_ = center_x_ - word_width_ / 2.0f;
    start_pos_ = sf::Vector2f(start_x_, start_pos_y_);
    newWord->setPosition(start_pos_); // setPosition(float, float) jest OK

    wordsLIst.push_back(std::move(newWord));
    time_since_last_word_ = 0.0f;
}


