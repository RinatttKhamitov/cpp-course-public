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
    public : KeyValueManager(std::string fileName){
        keyValue = FileReader().GetFileReader(fileName);
    }
    void InsertKeyValue(std::string key_, std::string value_){
        keyValue[key_] = value_;
    }
    void DeleteKey(std::string key_){
        if (keyValue.count(key_))
        {
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
    void PrintKeyValue(){
        for (const auto& [key, value] : keyValue)
            std::cout << key << "\t" << value << std::endl;
    }
    void DropAll(){
        keyValue.clear();
    }
};
class FileWriter {

};

class ArgumentsParser {

};

int main(int argc, char** argv)
{

    auto db = KeyValueManager("db.txt");
    db.PrintKeyValue();
    db.DropAll();
    // auto ap = ArgumentsParser(argc, argv);
    
    // // return false if no more commands
    // while(ap.ProcessNextCommand(db)) {}

    return 0;
}