/**
 * @file main.cpp
 * @brief напишите программу, которая читает из файла текст состоящий из букв и знаков пунктуации (,.').
 * Необходимый текст находится в файле "input.txt".
 * Нужно для каждого предложения вывести не уникальные слова, это те слова, которые встречаются дважды и более раз в одном предложении.
 * Слова следует учитывать без учёта регистра.
 * Слово не должно содержать знаков пунктуации, но может содержать символ "\'", а концом предложения является только символ ".". Внутри предложения может присутствовать ",".
 * Для каждого такого случая вывести в std::cout номер предложения, а после символа : все неуникальные слова рядом с номером через запятую.
 * В конце списка слов вывести '\n', а не запятую.
 *   подсказка: std::cout << "\b \n"; - код для удаления последнего символа и вместо него вывод перехода на новую строку
 * Если в предложении все слова уникальны, то для этого предложения ничего не нужно выводить
 * пример вывода:
0:the\n
1:a\n
2:one,the\n
3:a,the\n
 *
 */

#include <cstddef>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>


void Print(std::vector<std::string> line, int countLine){
    std::vector<std::string> duplicates;

    std::map<std::string, int> wordCount;

    for (const auto& element : line) {
        if (wordCount.count(element) > 0) {
            if (wordCount[element] == 1) {
                duplicates.push_back(element);
            }
            wordCount[element]++;
        } else {
            wordCount[element] = 1;
        }
    }
    if (duplicates.size() == 0){
        return;
    }
    std::cout << countLine << ":";
    for (int i = 0; i < duplicates.size(); i ++){
        if (duplicates[i] == ""){
            continue;
        }
        if (i == duplicates.size() - 1){
            std::cout << duplicates[i];
            break;
        }
        std::cout << duplicates[i] << ",";
    }
    std::cout << "\\n" << std::endl;
}

std::vector<std::string> Split(const std::string& str, char delimiter) {
    std::vector<std::string> words;
    std::stringstream ss(str);
    std::string word;
    
    while (std::getline(ss, word, delimiter)) {
        // Удалить запятые из слова.
        word.erase(std::remove(word.begin(), word.end(), ','), word.end());
        word.erase(std::remove(word.begin(), word.end(), '\n'), word.end());
        // Преобразовать слово в нижний регистр.
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        
        words.push_back(word);
    }
    
    return words;
}
std::vector<std::string> readSentencesFromFile(const std::string& filename) {
    std::vector<std::string> sentences;
    std::ifstream file(filename);
    
    if (file.is_open()) {
        std::string line;
        
        while (std::getline(file, line, '.')) {

            sentences.push_back(line);
        }
        
        file.close();
    } else {
        std::cout << "Не удалось открыть файл." << std::endl;
    }
    
    return sentences;
}

int main() {
    std::vector<std::string> sentences = readSentencesFromFile("input.txt");
    for (int i = 0; i <= sentences.size(); i++){
        if (sentences[i].compare("\n") == 0){
            continue;
        }
        Print(Split(sentences[i], ' '), i);
    }
    return 0;
}