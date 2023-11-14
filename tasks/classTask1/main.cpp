/**
 * @file main.cpp
 * @brief задача написать программу, которая будет обслуживать текстовую key-value базу данных в файле db.txt
 * 
 * Должен компилироваться бинарник db, и откликаться на команды (команды подаются как аргументы при запуске приложения *argv)
 * `INSERT KEY=VALUE` - операция вставки пары в базу данных (если добавляется ключ который уже есть в файле, то он обновляется)
 * `DELETE KEY` - удалить пару из базы данных
 * `FIND KEY` - вывести значение по ключу в базе данных (возврашает сообщение с элементов в консоль `FOUND: VALUE`, или выдаёт на вывод `NOT FOUND`, если элемента нет в базе данных)
 * `PRINT KEYS/VALUES` - вывести значение всех ключей/значений в базе данных
 * `DROPALL` - удалить всю базу данных (все значения из базы)   
 * Любая команда должна заканчиваться на '?' , можно обрабатывать сразу несколько команд
 * 
 * KEY и VALUE - гарантированно не пустые строки (используют символы букв и цифр, не используют знаки)
 * Как вы будете хранить в файле данные - на ваше усмотрение. Главное - чтобы пользовательское API не нарушалось.
 * Главное - база данных храниться в файле, но не в памяти и программу запускаем по необходимости.
 * Программа может быть неоптимальна с точки зрения вычислений, главное чтобы правильно выполнялась основная логика команд.
 */

#include <deque>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <map>
#include <cstring>

class FileReader;
namespace {
    constexpr char end_command_delimiter{'?'};
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
class FileWriter {
    public: 
    void AddNewString(std::string fileName, std::string string){
        std::fstream file("db.txt", std::ios::app);

        if (file.is_open()) {
            file << string << std::endl;
        } 

    file.close();
    }
    bool removeLineFromFile(const std::string& filename, const std::string& lineToRemove) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cout << "Ошибка открытия файла." << std::endl;
        return false;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(inputFile, line)) {
        if (line != lineToRemove) {
            lines.push_back(line);
        }
    }

    inputFile.close();

    std::ofstream outputFile(filename);
    if (!outputFile) {
        std::cout << "Ошибка открытия файла для записи." << std::endl;
        return false;
    }

    for (const auto& line : lines) {
        outputFile << line << std::endl;
    }
    outputFile.close();
    return true;
}
};
class FileReader {
    public : FileReader(){

    }
    public : std::map<std::string, std::string> GetFileReader(std::string fileName){
        std::map<std::string, std::string> mapDb;
        std::string line;
 
        std::ifstream in(fileName); // окрываем файл для чтения
        if (in.is_open())
        {
            while (std::getline(in, line))
            {
                std::vector splitLine = Split(line, ' ');
                mapDb[splitLine[0]] = splitLine[1];
            }
        }
        in.close();     // закрываем файл
        return mapDb;
    }
};
class KeyValueDB {
    protected : std::map<std::string, std::string> keyValue;
};
class KeyValueManager : public KeyValueDB {
    std::string fileName;
    
    public : KeyValueManager(std::string fileName_){
        fileName = fileName_;
        keyValue = FileReader().GetFileReader(fileName_);
    }
    void InsertKeyValue(std::string key_, std::string value_){
        if (keyValue.count(key_)){
            return;
        }
        keyValue[key_] = value_;
        FileWriter().AddNewString(fileName, key_ + " " + value_);
    }
    void DeleteKey(std::string key_){
        if (keyValue.count(key_))
        {
            FileWriter().removeLineFromFile(fileName, key_ + " " + keyValue[key_]);
            keyValue.erase(key_);
        }
    }
    void FindKey(std::string key_){
        if (keyValue.count(key_))
        {
            std::cout << "FOUND: " << keyValue[key_] << std::endl;
        }
        else
        {
            std::cout << "NOT FOUND" << std::endl;
        }
    }
    void PrintKeyValue(std::string option){
        if (option == "KEYS"){
        for (const auto& [key, value] : keyValue)
            std::cout << key << std::endl;
        }
        
        if (option == "VALUES"){
        for (const auto& [key, value] : keyValue)
            std::cout << value << std::endl;
        }
        
    }
    void DropAll(){
        keyValue.clear();
        std::ofstream file(fileName, std::ofstream::trunc);
        file.close();
    }
};

class ArgumentsParser {
    int argc;
    char** argv;
    int lastArg;
    public : ArgumentsParser(int argc_, char** argv_){
        argc = argc_;
        argv = argv_;
        lastArg = 1;
    }
    bool ProcessNextCommand(KeyValueManager& db){
        if (lastArg >= argc){
            return false;
        }

        if (strcmp(argv[lastArg], "INSERT") == 0){
            std::string command = argv[lastArg + 1];
            command.pop_back();
            std::vector<std::string> keyAndValue = Split(command, '=');
            db.InsertKeyValue(keyAndValue[0], keyAndValue[1]);
            lastArg+= 2;
            return true;
        }
        if (strcmp(argv[lastArg],"DELETE") == 0){
            std::string command = argv[lastArg + 1];
            command.pop_back();
            db.DeleteKey(command);
            lastArg+= 2;
            return true;
        }
        if (strcmp(argv[lastArg],"FIND") == 0){
            std::string command = argv[lastArg + 1];
            command.pop_back();
            db.FindKey(command);
            lastArg+= 2;
            return true;
        }
        if (strcmp(argv[lastArg], "PRINT") == 0){
            
            std::string command = argv[lastArg + 1];
            command.pop_back();
            
            db.PrintKeyValue(command);
            lastArg+=2;
            return true;
        }
        if (strcmp(argv[lastArg], "DROPALL?") == 0){
            db.DropAll();
            lastArg++;
            return true;
        }
        exit(0);
        return true;
    }

};

int main(int argc, char** argv) // INSERT newkey=newvalue? DELETE 1? 
{
    auto db = KeyValueManager("db.txt");
    auto ap = ArgumentsParser(argc, argv);
    
    // // return false if no more commands
    while(ap.ProcessNextCommand(db)) {
    }

    return 0;
}