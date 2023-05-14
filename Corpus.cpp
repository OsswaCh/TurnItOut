#include "Corpus.h"
#include <iostream>
#include <fstream>

void Corpus::addDocument(const std::string& filename)
{
    filenames.push_back(filename);
    std::string content = readFile(filename);
    m_corpus.push_back(content);
}

void Corpus::deleteDocument(const std::string& filename)
{
    if (std::remove(filename.c_str()) != 0) {
        std::cout << "Error: could not delete file " << filename << "." << std::endl;
    }
    else {
        std::cout << "File " << filename << " deleted successfully." << std::endl;
    }
}

std::vector<std::string> Corpus::getDocuments() const
{
    return m_corpus;
}

std::vector<std::string> Corpus::getAllFilenameS() const {
    return filenames;
}


std::string Corpus::getDocument(int x) const {
    return m_corpus[x];
}

std::string Corpus::getFileName(int x) const {
    return filenames[x];
}

int Corpus::getCorpSize() const {
    return m_corpus.size();
}

std::string Corpus::readFile(const std::string& filename)
{
    std::string content;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            content += line + "\n";
        }
        file.close();
    }
    return content;
}

void Corpus::writeFile(const std::string& filename, const std::string& content)
{
    std::ofstream file(filename);
    if (file.is_open()) {
        file << content;
        file.close();
    }
}




std::vector<std::string> Corpus::splitSentence(const std::string& sentence) {
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

int Corpus::lookForDocIndex(std::string name) {
    for (int i = 0; i < getCorpSize(); i++) {
        if (name == filenames[i])
            return i;
    }
}