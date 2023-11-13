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
class KeyValueDB {
    protected : std::string key;
    protected : std::string value;
    public : KeyValueDB(std::string key_, std::string value_){
        key = key_;
        value = value_;
    }
};

class KeyValueManager : public KeyValueDB {
    public : KeyValueManager(std::string key_, std::string value_) : KeyValueDB(key_, value_) {} ;

};
class FileReader {
    public : std::vector<KeyValueManager> GetFileReader(std::string fileName){
        std::vector<KeyValueManager> vectordb;
        std::string line;
 
        std::ifstream in(fileName); // окрываем файл для чтения
        if (in.is_open())
        {
            while (std::getline(in, line))
            {
                std::vector splitLine = Split(line, ' ');
                std::cout << splitLine[1] << " " << splitLine[1] << std::endl;
                vectordb.push_back(KeyValueManager(splitLine[0], splitLine[1]));
            }
        }
        in.close();     // закрываем файл
        return vectordb;
    }
};
class FileWriter {

};

class ArgumentsParser {

};

int main(int argc, char** argv)
{
    FileReader().GetFileReader("db.txt");
    // auto db = KeyValueManager("db.txt");
    // auto ap = ArgumentsParser(argc, argv);
    
    // // return false if no more commands
    // while(ap.ProcessNextCommand(db)) {}

    return 0;
}