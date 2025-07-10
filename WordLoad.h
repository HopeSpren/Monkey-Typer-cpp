//
// Created by JanWi on 07.05.2025.
//

#ifndef WORDLOAD_H
#define WORDLOAD_H
#include <string>
#include <vector>
#include <filesystem>

class WordLoad {
public:
    WordLoad();
    std::vector<std::string> getwordsLoaded();

    void GiveDirectoryReciveWords(std::filesystem::path asset_source_path);

    void yourFateEasterEgg();

    void giveupEastergg();

private:
    std::vector <std::string> wordsLoaded;

    void loadWordsFromDirectory();


};


#endif




