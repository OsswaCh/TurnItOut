#pragma once
#include <algorithm>
#include<iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Corpus.h"
class BruteForce
{
private: 
	
	std::string m_pattern;
	int m_threshold;
	int computedistance(const std::string&, const std::string&);
	int computedistance(const std::string&, const std::string&, int);
public:

    /*struct matchy {
        size_t index;
        size_t length;
        int frequency = 0;
    };*/
	
    BruteForce(const std::string& pattern, int threshold) : m_pattern(pattern), m_threshold(threshold){}

	
    std::vector<std::string> splitSentence(const std::string& );
    

    //this works for one word
    //using match function; this looks into the file, we put each word in a vector and then find where one word of pattern and text intersect
// it retrun the position of the **words** (not characters) where one word of the pattern is present
    std::vector<int> match(const std::string& text) {
        
            Corpus corpus;
            std::vector<int> matches;
            const size_t patternLength = m_pattern.length();
            const size_t textLength = text.length();

            std::vector <std::string> newsen = corpus.splitSentence(text);
            for (size_t i = 0; i < newsen.size(); ++i) {
                    int distance = computedistance(newsen[i], m_pattern);
                    if (distance <= m_threshold && distance!=-1) {
                        matches.push_back(i);
                    }
               
            }
            
            return matches;
        

    }

};

