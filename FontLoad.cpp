//
// Created by JanWi on 06.05.2025.
//

#include "FontLoad.h"
#include "SFML/Graphics/Font.hpp"
#include <filesystem>
#include <cstdio>
#include <string>
#include <map>



FontLoad::FontLoad() {
    printf("Atempting to load font...\n");
    loadFontsFromDirectory();
}


void FontLoad::loadFontsFromDirectory() {


    std::filesystem::path font_path = "Assets/fonts";
    if (!std::filesystem::exists(font_path)) {
        printf("Error: Directory %s does not exist or path is incorrect.\n", font_path.string().c_str());
    }
    for (const auto& entry : std::filesystem::directory_iterator(font_path)) {
        sf::Font fontA;
        printf("Found entry: %s\n", entry.path().string().c_str());


        if (fontA.openFromFile(entry.path().string())) {
            fonts[entry.path().filename().string()] = fontA;
            keys.push_back(entry.path().filename().string());
            printf("Fonts loaded:  \n");
        }

    }
    for (const auto& entry : keys) {

    printf(entry.c_str());}
    printf("\n");
}


const std::map<std::string, sf::Font>& FontLoad::fonts1() const {
    return fonts;
}

