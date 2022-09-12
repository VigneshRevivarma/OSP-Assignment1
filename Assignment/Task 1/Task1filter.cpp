#include "Task1filter.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>


void TaskFilter(std::string inputFile, std::string outputFile){
    std::ifstream dirty;
    dirty.open(inputFile);
    std::string word;
    std::ofstream clean;
    clean.open(outputFile);
    std::vector<std::string> wordlist;
    while(std::getline(dirty,word))
    {
        std::regex r("[^0-9a-zA-Z]+");
        std::string cleanedWord = std::regex_replace(word, r,"");
        if(cleanedWord!="") 
        {
            wordlist.push_back(cleanedWord);
        }
    }
    std::sort(wordlist.begin(),wordlist.end());
    for(auto x : wordlist)
    {
        clean<< x << "\n";
    }
    clean.close();
    dirty.close();


}

int main(int argc, char** argv){
    TaskFilter(argv[1],argv[2]);
    exit(0);
}

