#include "BruteForce.h"

int BruteForce::computedistance(const std::string& str1, const std::string& str2) {
	
	if (str1.length() != str2.length())
		return -1;
    int distance = 0;
    for (size_t i = 0; i < str1.length(); ++i) {
        if (str1[i] != str2[i]) {
            ++distance;
        }
    }
    return distance;

}
int BruteForce::computedistance(const std::string& str1, const std::string& str2, int threashold) {

    if (str1.length() != str2.length())
        return -1;
    int distance = 0;
    for (size_t i = 0; i < str1.length(); ++i) {
        if (str1[i] != str2[i]) {
            ++distance;
            
            if (distance == threashold) {
                return -1;
            }
        }
    }
    return distance;

}

std::vector<std::string> BruteForce::splitSentence(const std::string& sentence) {
    std::vector<std::string> words;
    std::string currentWord;
    for (const char& c : sentence) {
        if (std::isspace(c) || std::ispunct(c)) {
            if (!currentWord.empty()) {
                words.push_back(currentWord);
                currentWord.clear();
            }
        }
        else {
            currentWord += c;
        }
    }
    if (!currentWord.empty()) {
        words.push_back(currentWord);
    }
    return words;
}
