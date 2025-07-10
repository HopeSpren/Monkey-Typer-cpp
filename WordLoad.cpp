//
// Created by JanWi on 07.05.2025.
//

#include "WordLoad.h"

#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

WordLoad::WordLoad() {
    printf("attempting to load words... \n");
    loadWordsFromDirectory();
}

void WordLoad::loadWordsFromDirectory() {

    std::filesystem::path asset_source_path = "Assets/words";
    GiveDirectoryReciveWords(asset_source_path);


}

std::vector<std::string> WordLoad::getwordsLoaded() {
    return wordsLoaded;
}

void WordLoad::GiveDirectoryReciveWords(std::filesystem::path asset_source_path) {
    int n = 0;
    for (const auto& entry : std::filesystem::directory_iterator(asset_source_path)) {
        std::ifstream inputFile(entry.path());

        std::string word;
        while (std::getline(inputFile, word)) {
            wordsLoaded.push_back(word);
            n++;
        }
        std::cout << n << " words loaded "<< std::endl;;
    }
}

void WordLoad::yourFateEasterEgg() {

    wordsLoaded.clear();

        std::filesystem::path asset_source_path = "Assets/easter eggs/Your fate";
        GiveDirectoryReciveWords(asset_source_path);
}
void WordLoad::giveupEastergg() {
    wordsLoaded.clear();

    std::filesystem::path asset_source_path = "Assets/easter eggs/rick";
    GiveDirectoryReciveWords(asset_source_path);
}

