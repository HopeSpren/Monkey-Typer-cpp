//
// Created by JanWi on 06.05.2025.
//

#ifndef COFIG_H
#define COFIG_H
#include "FontLoad.h"

#include "WordLoad.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"


class Cofig {
    FontLoad gameFont;
    WordLoad gameWord;
    int frameLimit;
    short dificutly;

    sf::Text uperFonttext;
    sf::Text choiceFonttext;
    sf::Text downFonttext;

    int fontNumber;
    sf::RenderWindow window_;
    int return_code_;

    void slideDonwn();
    void slideUp();

    void slideDifucltyright();
    void slideDifucltyleft();

    int textSize;
    float cofigTextSpeed;
    sf::Text oneText;
    sf::Text curentDifuclty;

    sf::Clock Cofig_clock_;
    float Cofig_time_since_last_word_;
    sf::Time Cofig_delta_time_;
    float Cofig_dt_seconds_;


    std::string currentInputCOFIG;

    void handleEasterEggs(std::string input);

    bool specificOrderNeeded;


public:
    Cofig();

    void TimerStuff();

    float linearFrequency();
    FontLoad get_game_font() const;


    void set_game_font(const FontLoad &game_font);


    WordLoad get_game_world() const;

    int get_font_number() const;

    void set_game_word(const WordLoad &game_world);

    int get_frame_limit() const;

    void set_frame_limit(int frame_limit);

    short get_dificutly() const;

    void set_dificutly(short dificutly);

    int configureateGame();

    void cofigEvents();
    void cofigPrepere();
    void draw();
    int getTextSize();
    bool getSpecificOrderNeeded();
    void prrepareOneWord();

    float getCofigTextSpeed();
};




#endif //COFIG_H
