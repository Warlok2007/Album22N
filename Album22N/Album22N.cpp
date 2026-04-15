
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int SIZE = 20;

struct album {
    char name[25];
    char band[25];
    int genre;
    int year;
    int time;
    int price;
};

// Инициализация массива альбомов (жанр цифрой)
album* init() {
    album* albums = new album[SIZE];

    albums[0] = { "Ride the Lighting", "Metallica", 0, 1978, 40, 10 };
    albums[1] = { "Master of Puppets", "Eetallica", 3, 1981, 70, 10 };
    albums[2] = { "Elvis Vol1", "Elvis", 2, 1963, 120, 30 };
    albums[3] = { "Caphead OST", "Caphead", 1, 2017, 50, 15 };
    albums[4] = { "Alan Wake 2 OST", "Asgard", 2, 2023, 60, 15 };
    albums[5] = { "Kill em all", "Retallica", 0, 1976, 50, 10 };
    albums[6] = { "Frahk Sinatra the Best", "Frank", 3, 1963, 90, 20 };
    albums[7] = { "The Silver Beatls", "Beatles", 2, 1961, 40, 10 };
    albums[8] = { "Load", "Netallica", 3, 1979, 45, 15 };
    albums[9] = { "jazz vol1", "Igor", 1, 2017, 55, 15 };
    albums[10] = { "blues vol1", "Anton", 2, 2021, 62, 40 };
    albums[11] = { "Raining blood", "Slayer", 0, 1975, 50, 100 };
    albums[12] = { "ReLoad", "Atallica", 0, 2001, 80, 10 };
    albums[13] = { "Frahk Sinatra the Best2", "Srank", 1, 1965, 90, 30 };
    albums[14] = { "Elvis Vol2", "Elvis", 2, 1966, 127, 30 };
    albums[15] = { "The Big Silver Beatls", "Bitles", 2, 1962, 110, 2 };
    albums[16] = { "Pice sels", "Megadeth", 3, 1973, 100, 15 };
    albums[17] = { "Master of Puppets", "a", 3, 1981, 70, 10 };
    albums[18] = { "Frahk Sinatra the Best3", "Jank", 1, 1961, 100, 210 };
    albums[19] = { "Elvis Vol3", "ZElvis", 2, 1951, 150, 150 };

    return albums;
}

// ЗАДАНИЕ 1: чтение из текстового файла и обновление цены
void readFromTxtFile(album* albums, const char* filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "ОШИБКА: файл " << filename << " не найден!\n";
        return;
    }

    char line[100];
    while (fin.getline(line, 100)) {
        char* lastSpace = strrchr(line, ' ');
        if (lastSpace == nullptr) continue;

        *lastSpace = '\0';
        char* name = line;
        int newPrice = atoi(lastSpace + 1);

        for (int i = 0; i < SIZE; i++) {
            if (strcmp(albums[i].name, name) == 0) {
                albums[i].price = newPrice;
                cout << "Обновили: " << name << " " << newPrice << "$\n";
            }
        }
    }
    fin.close();
}

// ЗАДАНИЕ 2: запись массива структур в бинарный файл
void writeToBinaryFile(const char* filename, album* albums) {
    ofstream fout(filename, ios::binary);
    fout.write((char*)albums, sizeof(album) * SIZE);
    fout.close();
    cout << "Записано в " << filename << endl;
}

// ЗАДАНИЕ 2: чтение массива структур из бинарного файла
void readFromBinaryFile(const char* filename, album* albums) {
    ifstream fin(filename, ios::binary);
    fin.read((char*)albums, sizeof(album) * SIZE);
    fin.close();
    cout << "Прочитано из " << filename << endl;
}

// Оберточная функция для вывода альбомов
void printAlbums(album* albums, int n) {
    for (int i = 0; i < n; i++) {
        cout << albums[i].name << " " << albums[i].price << "$\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    album* albums = init();           // Создаем массив альбомов

    // Задание 1
    cout << "Задание 1 \n";
    readFromTxtFile(albums, "prices.txt");

    // Задание 2
    cout << "\nЗадание 2 \n";
    writeToBinaryFile("albums.bin", albums);      // Запись в бинарный файл

    album* loaded = new album[SIZE];              // Массив для загрузки
    readFromBinaryFile("albums.bin", loaded);     // Чтение из бинарного файла

    cout << "\nПроверяем \n";
    printAlbums(loaded, 5);                       // Вывод первых 5 альбомов для проверки
    // Это надо для того чтобы программа каждый раз работала
    delete[] albums; 
    delete[] loaded;
    return 0;
}