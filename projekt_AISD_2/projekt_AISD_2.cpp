#include <iostream>
#include "Functions.h"

int main()
{
    int WIDTH, HEIGHT;
    int cities_am = 0, flights = 0, commands = 0;
    std::cin >> WIDTH;
    std::cin >> HEIGHT;
    getchar();
    char** board = new char*[HEIGHT];
    for (int i = 0; i < HEIGHT; i++)
        board[i] = new char[WIDTH];
    readBoard(board, WIDTH, HEIGHT, cities_am);
    City* cities = new City[cities_am];
    addNameToCity(board, cities, WIDTH, HEIGHT);
    City** hash_cities = new City*[HEIGHT * WIDTH];
    List<City*>* hash_name_cities = new List<City*>[HEIGHT * WIDTH / 13 + 1];
    for (int i = 0; i < HEIGHT * WIDTH; i++) {
        hash_cities[i] = nullptr;
    }
    for (int i = 0; i < cities_am; i++) {
        hash_cities[cities[i].y * WIDTH + cities[i].x] = &cities[i];
        hash_name_cities[hashName(cities[i].name, WIDTH, HEIGHT)].push_back(&cities[i]);
        if (hash_name_cities[hashName(cities[i].name, WIDTH, HEIGHT)].empty()) std::cout << 2;
    }
    createGraph(board, cities, cities_am, hash_cities, WIDTH, HEIGHT);
    std::cin >> flights;
    City** pr_city = new City * [HEIGHT * WIDTH];
    for (int i = 0; i < HEIGHT * WIDTH; i++)
        pr_city[i] = nullptr;
    readFlights(flights, cities, hash_name_cities, WIDTH, HEIGHT);
    std::cin >> commands;
    readCommands(commands, cities, hash_name_cities, hash_cities, pr_city, cities_am, WIDTH, HEIGHT);
    delete[]pr_city;
    delete[]hash_name_cities;
    delete[]hash_cities;
    delete[]cities;
    for (int i = 0; i < HEIGHT; i++)
        delete[]board[i];
    delete[]board;
    return 0;
}