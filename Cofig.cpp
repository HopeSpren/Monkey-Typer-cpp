//
// Created by JanWi on 06.05.2025.
//

#include "Cofig.h"

#include <iostream>


#include "fmt/format.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"



Cofig::Cofig()
    : gameFont(),
      gameWord(),
    uperFonttext(gameFont.fonts1().at(gameFont.keys1().at(0)), "", 20),
    choiceFonttext(gameFont.fonts1().at(gameFont.keys1().at(0)), gameFont.keys1().at(0), 20),
    downFonttext(gameFont.fonts1().at(gameFont.keys1().at(0)), "", 20),
    curentDifuclty(gameFont.fonts1().at(gameFont.keys1().at(0)), "", 30),
    oneText(gameFont.fonts1().at(gameFont.keys1().at(0)), " This is how your \n text will look like!", 40)
{
    this->dificutly = 1;
    this->frameLimit = 60;
    printf("Welcome to Malpo pisacz\n");
    this->fontNumber = 0;

    uperFonttext.setPosition(sf::Vector2f(600, 400));
    choiceFonttext.setPosition(sf::Vector2f(600, 450));
    downFonttext.setPosition(sf::Vector2f(600, 500));
    textSize = 40;

    this -> cofigTextSpeed =  20.0f *dificutly;
    oneText.setPosition(sf::Vector2f(100, 200));
    curentDifuclty.setPosition(sf::Vector2f(50, 550));

    curentDifuclty.setOutlineColor(sf::Color::Red);
    curentDifuclty.setOutlineThickness(5);

    currentInputCOFIG = "";
}


void Cofig::TimerStuff() {
    Cofig_delta_time_ = Cofig_clock_.restart();
    Cofig_dt_seconds_ = Cofig_delta_time_.asSeconds();
    Cofig_time_since_last_word_ += Cofig_dt_seconds_;
}

int Cofig::configureateGame() {
    return_code_ = 0;
    window_ = sf::RenderWindow(
        sf::VideoMode({800, 600}), "Test",
        sf::Style::Default, sf::State::Windowed,
        sf::ContextSettings{.antiAliasingLevel = 8});

    specificOrderNeeded =false;

    currentInputCOFIG.clear();
    while (window_.isOpen()) {
        TimerStuff();

        cofigEvents();

        cofigPrepere();

        draw();

        }



    return return_code_;
}

void Cofig::cofigEvents() {
    while (const std::optional event = window_.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            return_code_ = 1;
            window_.close();
        }
        if (auto const e = event->getIf<sf::Event::KeyPressed>())
        {
            if ( e->code == sf::Keyboard::Key::Down) {
                slideDonwn();
            }
            if (e->code == sf::Keyboard::Key::Up) {
                slideUp();
            }
            if (e->code == sf::Keyboard::Key::Enter) {

                window_.close();
            }
            if (e->code == sf::Keyboard::Key::Right) {
                slideDifucltyright();
            }
            if (e->code == sf::Keyboard::Key::Left) {
                slideDifucltyleft();
            }

        }
        if (auto const c = event->getIf<sf::Event::MouseWheelScrolled>() ) {

            textSize += static_cast<int>(c->delta);
            if (textSize <= 0) {
                textSize = 1;
            }
            printf(std::to_string(textSize).c_str());
            printf(" \n");

        }
        if (auto const textEnteredEvent = event->getIf<sf::Event::TextEntered>()) {

            unsigned char unicodeChar = textEnteredEvent->unicode;
            if (std::isalpha(unicodeChar)) {
                currentInputCOFIG.push_back(unicodeChar);

                handleEasterEggs(currentInputCOFIG);

            }


        }
        }

}

void Cofig::cofigPrepere() {
    cofigTextSpeed =  20.0f *dificutly;
    oneText.setCharacterSize(textSize);

    oneText.setFont(gameFont.fonts1().at(gameFont.keys1().at(fontNumber)));
    sf::Vector2f offset(0.0f, cofigTextSpeed * Cofig_dt_seconds_);
    oneText.move(offset);
    oneText.setCharacterSize(textSize);
    if (oneText.getPosition().y >= window_.getSize().y-300) {
        oneText.setPosition(sf::Vector2f(100, 00));
    }

    curentDifuclty.setString(fmt::to_string(dificutly).c_str());

}

void Cofig::draw() {
    window_.clear(sf::Color::Black);

    window_.draw(uperFonttext);
    window_.draw(choiceFonttext);
    window_.draw(downFonttext);
    window_.draw(oneText);

    window_.draw(curentDifuclty);

    window_.display();
}

void Cofig::slideUp() {
    if (gameFont.keys1().empty()) return;

    int numFonts = gameFont.keys1().size();

    fontNumber = (fontNumber + 1) % numFonts;

    int uperIndex = (fontNumber - 1 + numFonts) % numFonts;
    int choiceIndex = fontNumber;
    int downIndex = (fontNumber + 1) % numFonts;

    uperFonttext.setString(gameFont.keys1().at(uperIndex));
    uperFonttext.setFont(gameFont.fonts1().at(gameFont.keys1().at(uperIndex)));

    choiceFonttext.setString(gameFont.keys1().at(choiceIndex));
    choiceFonttext.setFont(gameFont.fonts1().at(gameFont.keys1().at(choiceIndex)));

    downFonttext.setString(gameFont.keys1().at(downIndex));
    downFonttext.setFont(gameFont.fonts1().at(gameFont.keys1().at(downIndex)));
}



void Cofig::slideDonwn() {
    int numFonts = gameFont.keys1().size();

    fontNumber = (fontNumber - 1 + numFonts) % numFonts;

    int uperIndex = (fontNumber - 1 + numFonts) % numFonts;
    int choiceIndex = fontNumber;
    int downIndex = (fontNumber + 1) % numFonts;

    uperFonttext.setString(gameFont.keys1().at(uperIndex));
    uperFonttext.setFont(gameFont.fonts1().at(gameFont.keys1().at(uperIndex)));

    choiceFonttext.setString(gameFont.keys1().at(choiceIndex));
    choiceFonttext.setFont(gameFont.fonts1().at(gameFont.keys1().at(choiceIndex)));

    downFonttext.setString(gameFont.keys1().at(downIndex));
    downFonttext.setFont(gameFont.fonts1().at(gameFont.keys1().at(downIndex)));
}

float Cofig::linearFrequency() {
    float freqMIN = 0.5f;
    float freqMAX = 1.0f;

    float normalized_difficulty = (dificutly - 1.0f) / 9.0f;


    float current_frequency = freqMIN + (freqMAX - freqMIN) * normalized_difficulty;


    return  1.0f / current_frequency;

}








void Cofig::slideDifucltyright() {
    dificutly = (dificutly % 10) + 1;
    curentDifuclty.setPosition(sf::Vector2f(30*dificutly +40, 550.0f));
}

void Cofig::slideDifucltyleft() {
    dificutly--;
    if (dificutly < 1) {
        dificutly = 10;
    }
    curentDifuclty.setPosition(sf::Vector2f(30*dificutly +40, 550.0f));

}

void Cofig::handleEasterEggs(std::string imput) {
    if (imput.find("myfate") != std::string::npos) {
        gameWord.yourFateEasterEgg();
        window_.close();
    }
    if (imput.find("giveup") != std::string::npos) {
        gameWord.giveupEastergg();
        specificOrderNeeded = true;
        window_.close();
    }



}


void Cofig::prrepareOneWord() {

}

int Cofig::getTextSize() {
    return textSize;
}

bool Cofig::getSpecificOrderNeeded() {
    return specificOrderNeeded;
}

float Cofig::getCofigTextSpeed() {
    return cofigTextSpeed;
}


FontLoad Cofig::get_game_font() const {
    return gameFont;
}

void Cofig::set_game_font(const FontLoad &game_font) {
    gameFont = game_font;
}

WordLoad Cofig::get_game_world() const {
    return gameWord;
}

int Cofig::get_font_number() const {
    return fontNumber;
}

void Cofig::set_game_word(const WordLoad &game_world) {
    gameWord = game_world;
}

int Cofig::get_frame_limit() const {
    return frameLimit;
}

void Cofig::set_frame_limit(int frame_limit) {
    frameLimit = frame_limit;
}

short Cofig::get_dificutly() const {
    return dificutly;
}

void Cofig::set_dificutly(short dificutly) {
    this->dificutly = dificutly;
}
