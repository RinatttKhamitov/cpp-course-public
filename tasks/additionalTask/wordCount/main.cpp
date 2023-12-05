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
auto Split(const std::string& str, char delimiter) -> std::vector<std::string> 
{
    std::vector<std::string> result;
    std::string token;
    std::size_t start = 0;
    std::size_t end = str.find(delimiter);

    while (end != std::string::npos) {
        token = str.substr(start, end - start);
        result.push_back(token);
        start = end + 1;
        end = str.find(delimiter, start);
    }

    token = str.substr(start, end);
    result.push_back(token);

    return result;
}

std::vector<std::string> processString(const std::string& str) {
    std::vector<std::string> words;
    std::string word;
    
    for (char c : str) {
        if ((std::isalpha(c) || c == '\\' || c == '\'') && c != '.' && c != ',' && c != '!' && c != '?') {
            word += std::tolower(c);
        }
        if (c == ' ') {
            words.push_back(word);
            word.clear();
        }
    }
    
    if (!word.empty()) {
        words.push_back(word);
    }
    
    return words;
}

int main() {
    std::string line;
    std::string allLine;
    std::ifstream file("input.txt");
    int count = 0;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (line == ""){
                continue;
            }
            if (line[line.length() - 1] != '.'){
                allLine += " " + line;
                continue;
            }
            else{
                if (allLine != ""){
                    allLine +=  " " + line;
                    // ...
                }
                else{
                    allLine = line;
                }
            }
            std::vector<std::string> splitedLine = processString(allLine);
        
            Print(splitedLine, count);
            count += 1;
            allLine = "";
        }
        
        file.close();
    }
    return 0;
}