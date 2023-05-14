#ifndef CORPUS_H
#define CORPUS_H

#include <vector>
#include <string>

class Corpus {
public:

    //getters
    std::vector<std::string> getDocuments() const;
    std::vector<std::string> getAllFilenameS() const;
    std::string getDocument(int) const;
    std::string getFileName(int) const;

    int lookForDocIndex(std::string);
    int getCorpSize() const;
    std::string readFile(const std::string& filename);



    //setters
    void addDocument(const std::string& filename);
    void deleteDocument(const std::string& filename);
    void writeFile(const std::string& filename, const std::string& content);
    
    
    //useful functions
    std::vector<std::string> splitSentence(const std::string& );


private:
    std::vector<std::string> m_corpus;
    std::vector<std::string> filenames;
};

#endif // CORPUS_H
