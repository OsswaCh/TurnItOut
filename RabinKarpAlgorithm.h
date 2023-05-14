//#pragma once
//#ifndef RABINKARPALGORITHM_H
//#define RABINKARPALGORITHM_H
//
//#include <string>
//#include <iostream>
//
//using namespace std;
//
//class RabinKarpAlgorithm
//{
//public:
//    int const q = 101; //The prime number used through the whole algorithm   
//#define d 10
//
//    void RabinKarp(string pattern, string text) {
//        int m = pattern.length();  //Pattern length
//        int n = text.length();    //Text length
//        int i, j;                //Declaring two counters that are used in the for loops
//        int PatternHash = 0;    //The has value of the pattern
//        int TextHash = 0;      //The has value of the text 
//        int h = 1;
//
//        // Precomputing the hash value of the pattern
//        for (i = 0; i < m - 1; i++)
//            h = (h * d) % q;
//
//        // Calculate hash value for pattern and text
//        for (i = 0; i < m; i++) {
//            PatternHash = (d * PatternHash + pattern[i]) % q;
//            TextHash = (d * TextHash + text[i]) % q;
//        }
//
//        // Find the match
//        for (i = 0; i <= n - m; i++) //Iterats over all the possible postions of finding a character
//        {
//            if (PatternHash == TextHash) //Checks if there is a match
//            {
//                for (j = 0; j < m; j++)
//                {
//                    if (text[i + j] != pattern[j]) //if there is a mismatch , we move to the next window
//                    {
//                        break;
//                    }
//
//                }
//                if (j == m) //if we reached end of the string , cout the indexes of the pattern
//                    cout << "Pattern is found at position: " << i + 1 << endl;
//            }
//
//            if (i < n - m) { //As long it is not the end of the string 
//                //The new hashvalue is calculated using the hashvalue of the previous window + the value if the new character to avoid recalculating the whole window 
//                TextHash = (d * (TextHash - text[i] * h) + text[i + m]) % q;
//
//                if (TextHash < 0) //ensure that the hashvalue is always less than q
//                    TextHash = (TextHash + q);
//            }
//        }
//    }
//};
//
//#endif // RABINKARPALGORITHM_H

#include <string>
#include <vector>
#include <iostream>

class RabinKarpAlgorithm {
public:
    std::vector<int> match(const std::string& text, const std::string& pattern, const int& maxDistance) {
        std::vector<int> matches;
        int m = pattern.length();
        int n = text.length();
        int i, j;
        int patternHash = 0;
        int textHash = 0;
        int h = 1;

        // Precompute the hash value of the pattern
        for (i = 0; i < m - 1; i++) {
            h = (h * d) % q;
        }
        for (i = 0; i < m; i++) {
            patternHash = (d * patternHash + pattern[i]) % q;
            textHash = (d * textHash + text[i]) % q;
        }

        // Find the match
        for (i = 0; i <= n - m; i++) {
            if (patternHash == textHash) {
                for (j = 0; j < m; j++) {
                    if (text[i + j] != pattern[j]) {
                        break;
                    }
                }
                if (j == m) {
                    int wordCount = 1;
                    for (int k = 0; k < i; k++) {
                        if (std::isspace(text[k]) || std::ispunct(text[k])) {
                            wordCount++;
                        }
                    }
                    matches.push_back(wordCount);
                }
            }
            if (i < n - m) {
                textHash = (d * (textHash - text[i] * h) + text[i + m]) % q;
                if (textHash < 0) {
                    textHash += q;
                }
            }
        }
        return matches;
    }

private:
    static const int q = 101;
    static const int d = 10;
};
