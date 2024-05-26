﻿#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <mutex>
#include <iostream>
#include <cstdlib>
#include <locale.h>

using namespace std;

#define MAX_FILES 1000
#define MAX_FILE_NAME 32
#define MAX_DATA_SIZE 1024

typedef struct File {
	string name;
	string data;
	int size;
} File;

File files[MAX_FILES] = {};
std::mutex mt;
int place = 0;

void createFile(string name) {
	int flag = 0;
	File currFile;
	if (name.size() < MAX_FILE_NAME)
	{

		for (int i = 0; i < MAX_FILES; i++)
		{
			if (name == files->name)
			{
				cout << "Файл с таким именем уже существует" << endl;
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			currFile.name = name;
			currFile.data.clear();
			currFile.size = 0;
			files[place] = currFile;

			cout << "Файл был успешно создан" << endl;
			place++;
		}
	}
	else
		cout << "Длина имени файла превышает допустимую" << endl;


}

int readFile(string name) {//std::cout
	mt.lock();
	int flag = 0;
	for (int i = 0; i < MAX_FILES; i++)
	{
		if (files[i].name == name)
		{
			if (files[i].data.empty())
			{
				cout << "Файл пуст" << endl;
			}
			else
			{
				cout << "Извлеченные данные: " << files[i].data << endl;
			}
			flag = 1;
			break;
		}
	}
	if (!flag)
	{
		cout << "Файл не был найден" << endl;
	}
	mt.unlock();
	return 0;
}

int writeFile(string name, string text) {
	mt.lock();
	int flag = 0;
	if (text.size() >= MAX_DATA_SIZE)
	{
		cout << "Размер данных превышает размер файла" << endl;
	}
	else
	{
		for (int i = 0; i < MAX_FILES; i++)
		{
			if (files[i].name == name)
			{
				flag = 1;
				files[i].data = text;
				files[i].size = text.size();
				cout << "Данные записаны" << endl;
				break;
			}

		}
		if (!flag)
		{
			cout << "Файл не был найден" << endl;
		}
	}
	mt.unlock();
	return 0;
}

int deleteFile(string name) {
	mt.lock();
	int indexToDelete = 0;
	int flag = 0;
	for (int i = 0; i < MAX_FILES; i++)
	{
		if (files[i].name == name)
		{
			indexToDelete = i;
			flag = 1;
			break;
		}
	}
	for (int i = indexToDelete; i < MAX_FILES; i++)
	{
		files[i] = files[i + 1];
	}
	if (place > 0)
	{
		place--;
	}
	else
		place = 0;
	if (flag)
	{
		cout << "Файл удален" << endl;
	}
	else
		cout << "Файл не был найден" << endl;

	mt.unlock();
	return 0;
}

void fsInfo() {
	int count = 0;
	for (count; count < MAX_FILES; count++) {
		if (files[count].name.empty())
		{
			break;
		}
	}
	cout << "N-множество файлов в системе: " << count << endl;
}

int searchFile(string text)
{
	mt.lock();
	int flag = 0;
	for (int i = 0; i < MAX_FILES; i++)
	{
		if (files[i].name == text)
		{
			cout << "Файл существует" << endl;
			flag = 1;
			break;
		}
		else if (files[i].data == text)
		{
			cout << "Файл с этим текстом существует" << endl;
			flag = 1;
			break;
		}


	}
	if (!flag)
	{
		cout << "Файл не был найден" << endl;
	}

	mt.unlock();
	return 0;
}

void printCommands()
{
	char command;
	string nameFile;
	string textFile;

	while (true) {
		cout << "Набор команд:" << endl;
		cout << "1. Создание файл" << endl;
		cout << "2. Чтение файл" << endl;
		cout << "3. Запись в файл" << endl;
		cout << "4. Удалить файл" << endl;
		cout << "5. Информация о файловой системе" << endl;
		cout << "6. Поиск файла" << endl;
		cout << "7. Выход из программы" << endl;

		cout << "Выберите команду: ";
		cin >> command;

		switch (command) {
		case '1':
			cout << "Введите имя файла: ";
			cin >> nameFile;

			createFile(nameFile);
			break;
		case '2':
			cout << "Введите имя файла: ";
			cin >> nameFile;

			readFile(nameFile);
			break;
		case '3':
			cout << "Введите имя файла: ";
			cin >> nameFile;
			_flushall();

			cout << "Введите необходимые данные: ";
			cin.ignore();
			getline(cin, textFile);


			writeFile(nameFile, textFile);
			break;
		case '4':
			cout << "Введите имя файла: ";
			cin >> nameFile;

			deleteFile(nameFile);
			break;
		case '5':
			cout << "Информация о файловой системе..." << endl;
			fsInfo();
			break;
		case '6':
			cout << "Введите имя или содержимое файла: ";
			cin >> textFile;

			searchFile(textFile);
			break;
		case '7':
			cout << "Выход из программы." << endl;
			break;
		default:
			cout << "Неверная команда! Пожалуйста, попробуйте снова." << endl;
		}
	}

}
int main() {
	setlocale(LC_ALL, "ru");

	printCommands();

}

