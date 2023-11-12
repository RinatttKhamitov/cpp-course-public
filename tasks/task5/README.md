
# Задача 5

Даты сдачи - в таблице

Для сдачи клонируете репозиторий, создаёте ветку для задания 5.
После того, как решили, весь код пушим в ветку в своём форке (клонировали в форк).
Далее делаем Pull request в основной репозиторий в ветку master.

В папке содержаться файлы, который можно менять:
    * main.cpp
    * file_reader_raii.h
    * rectangle.h

Тестирование будет через утилиту valgrind, которая проверяет утечки памяти

Требования к реализации:

* Основная задача - поменять код таким образом, чтобы избежать утечек памяти
* В данном задание полная свобода действий:
    * Можно поправить только через операции удаления вручную
    * Эталонная реализация должна предусматривать использование умных указателей
    * Использовать материал лекции и свои знания с прошлых лекций
* Проверка тестов Valgrind обязательна для сдачи, но может быть неполной(вы можете убрать не все утечки памяти, это нормально, но балл будет ниже)
* После проверки Valgrind будет ручная проверка написанного кода, насколько точно он соответсвует рекомендациям по написанию корректного когда
    * Проверяется не читаемость, а соответствие правилам `хорошего кода` (почти весь код из лекций соответствует этим правилам)
---
* Рядом со всеми местами в коде написаны комментарии - что и как нужно делать.
* Все вопросы можно задавать в любой форме. Открыто в беседу или в личные сообщения. Можно отправить код на ревью и подписать, чтобы была проверка кода без тестов.

### Примечание:

> запустить тесты можно через Makefile: `make test`
    (может быть проблема с запуском, т.к. нужна утилита valgrind `sudo apt install valgrind`)
