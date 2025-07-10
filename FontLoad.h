//
// Created by JanWi on 06.05.2025.
//

#ifndef FONTLOAD_H
#define FONTLOAD_H

#include <SFML/Graphics/Font.hpp>
#include <string>
#include <map>
#include <filesystem>

class FontLoad {
public:
    const std::map<std::string, sf::Font>& fonts1() const;

    void set_fonts(const std::map<std::string, sf::Font> &fonts) {
        this->fonts = fonts;
    }

    std::vector<std::string> keys1() const {
        return keys;
    }

    void set_keys(const std::vector<std::string> &keys) {
        this->keys = keys;
    }

    FontLoad();




private:
    std::map<std::string, sf::Font> fonts;
    std::vector<std::string> keys;

    void loadFontsFromDirectory();
};

#endif