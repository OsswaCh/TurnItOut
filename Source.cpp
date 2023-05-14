#include <iostream>
#include <fstream>
#include "BruteForce.h"
#include "RabinKarpAlgorithm.h"
#include "Corpus.h"
using namespace std;



struct sentences {
    int senPos;
    std::string where;
    int PlaPercentage;

};


struct plagia {
    string word;
    vector<int> found;
    string filename;
    int senNum ;
        };

plagia findMatchInOneSentence(const std::string& , const std::string& , const std::string&, int );
plagia findMatchInOneSentenceRK(const std::string&, const std::string&, const std::string&, int);
std::vector<std::string> splitIntoSentences(std::string);
std::vector <plagia> getMatchFromTextBF(std::vector<std::string>, Corpus);
std::vector<plagia> getMatchFromTextRK(std::vector<std::string>, Corpus);
std::vector<sentences> ParaphrasingPercentage(std:: string, std::string, vector <plagia>, Corpus);
void Printmatches(std::vector <plagia>, int);
int countWordsInSentence(const std::string&);

string warning(int);


int main() {

    
    cout << "\t" << "\t" << "\t" << "\t" << "WELCOME TO TURNITOUT" << endl << endl << endl;

        Corpus corpus;

        // Add the existing documents to the corpus vector
        corpus.addDocument("document1.txt");
        corpus.addDocument("document2.txt");
        corpus.addDocument("document3.txt");
        corpus.addDocument("document4.txt");
        corpus.addDocument("document5.txt");

        // Get user input and split it into words
        std::string content;
        std::cout << "Enter the content that you want to write: " << std::endl;
        std::getline(std::cin, content);
        std::vector<std::string> userContent = corpus.splitSentence(content);

        
        cout << "\t" << "\t" << "the Rabin karp example" << endl;
        cout << "how it works from the inside: mathces word by word" << endl;
        vector<plagia> matches = getMatchFromTextRK(userContent, corpus);
        for (const auto& match : matches) {
            cout << match.filename << " sentence" << match.senNum +1<< ' ' << match.word;
            for (const auto& f : match.found) {
                cout << f-1 << " ";
            }
            cout << endl;
        }
        std::vector<sentences> result;
        for (const auto& match : matches) {
            int index = corpus.lookForDocIndex(match.filename);
            std::string text = corpus.getDocument(index);
            result = ParaphrasingPercentage(content, text , matches, corpus);

        }
        
        cout << "the final result of the code" << endl<<endl;
        cout << "similarities found at: " << endl;
        for (const auto& match : result) {
            cout <<  "doc num" << match.where;
            cout << " at sentence num " << match.senPos+1;
            cout << " you copied this percentage of it: " << match.PlaPercentage << "% " ;
            cout<<warning(match.PlaPercentage)<<endl;

        }

        cout << endl<<endl<<"\t" << "\t" << "the Brute Force example" << endl;
        cout << "how it works from the inside: mathces word by word" << endl << endl;
        vector<plagia> matches2 = getMatchFromTextBF(userContent, corpus);
        for (const auto& match : matches2) {
            cout << match.filename << " sentence" << match.senNum + 1 << ' ' << match.word;
            for (const auto& f : match.found) {
                cout << f - 1 << " ";
            }
            cout << endl;
        }
        std::vector<sentences> result2;
        for (const auto& match : matches2) {
            int index = corpus.lookForDocIndex(match.filename);
            std::string text = corpus.getDocument(index);
            result2 = ParaphrasingPercentage(content, text, matches, corpus);

        }

        cout << "the final result of the code" << endl;
        cout << "similarities found at: " << endl;
        for (const auto& match : result2) {
            cout << "doc num" << match.where;
            cout << " at sentence num " << match.senPos + 1;
            cout << " you copied this percentage of it: " << match.PlaPercentage << "% ";
            cout << warning(match.PlaPercentage) << endl;

        }

   



	return 0;
}



//this is a primary implementation of rabin karb algorthim, it looks fo rthe matches of each word in the pattern in one sentence
//and puts the found result in a struct holdig all the infomation about the found macthes
plagia findMatchInOneSentenceRK(const std::string& match, const std::string& document, const std::string& filename, int counter) {
    RabinKarpAlgorithm titou;
    plagia p;
    p.found = titou.match(document,match,1);
    p.word = match;
    p.filename = filename;
    p.senNum = counter;
    return p;
}


//this is a primary implementation of Brute force matches, it looks for the matches of each word in the pattern in one sentence
//and puts the found result in a struct holdig all the infomation about the found macthes
plagia findMatchInOneSentence(const std::string& match, const std::string& document, const std::string& filename, int counter) {
    BruteForce titou(match, 1);
    plagia p;
    p.found = titou.match(document);
    p.word = match;
    p.filename = filename;
    p.senNum = counter;
    return p;
}

//this prints the infomartion about the found matches 
void Printmatches(std::vector <plagia> matches, Corpus corpus, std::string filename, int senNum) {
    std::cout << "\t" << filename << std::endl;
    std::cout << filename << std::endl;
    for (const auto& match : matches) {
        if (match.filename == filename && match.senNum == senNum) {
            std::cout << match.word << ": ";
            for (const auto& found : match.found) {
                std::cout << "Sentence " << match.senNum + 1 << ": " << match.word << ": ";
                std::cout << found << " ";
            }
            std::cout << std::endl;
        }
    }
}

//this finds the matches for each word in the pattern 
//then puts the vector containing the matches in a vector inside a struct
//we obtain a struct containing
std::vector<plagia> getMatchFromTextBF(std::vector<std::string> userContent, Corpus corpus) {
    std::vector<plagia> matches;
    for (int filenum = 0; filenum < corpus.getAllFilenameS().size(); filenum++) {
        const std::string& document = corpus.getDocument(filenum);
        const std::string& filename = corpus.getFileName(filenum);
        std::vector<std::string> splitsen = splitIntoSentences(document);

        for (int senNum = 0; senNum < splitsen.size(); senNum++) {
            const std::string& sentence = splitsen[senNum];
            bool sentenceMatched = false;

            for (const auto& match : userContent) {
                plagia p = findMatchInOneSentence(match, sentence, filename, senNum);
                if (!p.found.empty()) {
                    matches.push_back(p);
                    sentenceMatched = true;
                }
            }
        }
    }

    return matches;
}

//same principle of the BF but using rabin carp
std::vector<plagia> getMatchFromTextRK(std::vector<std::string> userContent, Corpus corpus) {
    std::vector<plagia> matches;
    for (int filenum = 0; filenum < corpus.getAllFilenameS().size(); filenum++) {
        const std::string& document = corpus.getDocument(filenum);
        const std::string& filename = corpus.getFileName(filenum);
        std::vector<std::string> splitsen = splitIntoSentences(document);

        for (int senNum = 0; senNum < splitsen.size(); senNum++) {
            const std::string& sentence = splitsen[senNum];
            bool sentenceMatched = false;

            for (const auto& match : userContent) {
                plagia p = findMatchInOneSentenceRK(match, sentence, filename, senNum);
                if (!p.found.empty()) {
                    matches.push_back(p);
                    sentenceMatched = true;
                }
            }
        }
    }

    return matches;
}



//calculates the percentage of the copied data from a source sentance at a time
std::vector<sentences> ParaphrasingPercentage(std::string pattern, std::string text, vector <plagia> p, Corpus corpus) {
    int value = 0;
    int counter = 0;
    std::vector<sentences> Sentence;
    sentences sentence;

    while (counter < p.size()) {
        value += p[counter].found.size();
        if ((counter + 1 == p.size()) || p[counter].filename != p[counter + 1].filename) {
            sentence.senPos = p[counter].senNum;
            sentence.where = p[counter].filename;
            sentence.PlaPercentage = (value * 100) / countWordsInSentence(text);
            if (sentence.PlaPercentage > 100) {
                sentence.PlaPercentage = 100;
            }
            Sentence.push_back(sentence);
            value = 0;
        }
        counter++;
    }

    
    return Sentence;
}


//splits a text into sentances based on punctuation
std::vector<std::string> splitIntoSentences(std::string text) {
    std::vector<std::string> sentences;
    int start = 0;
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!') {
            std::string sentence = text.substr(start, i - start + 1);
            sentences.push_back(sentence);
            start = i + 1;
        }
    }
    return sentences;
}


//counts the number of words in a given string
int countWordsInSentence(const std::string& sentence) {
    int count = 0;
    std::istringstream iss(sentence);
    std::string word;
    while (iss >> word) {
        count++;
    }
    return count;
}

//return the type of warning depending on the amount of plagarism
std::string warning(int perc) {
    
    string word;
    if ( perc < 30) {
        word = " you took insperation ";
        return word;
    }
    if ( perc < 50) {
        word =  " you took a bit more than just insperation" ;
        return word;
    }
    if (perc < 70) {
        word = " Be careful you are becoming sus";
        return word;
    }
    else {
        word = "PLAGIARIZED";
        return word;

    }
}