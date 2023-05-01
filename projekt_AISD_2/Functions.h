#pragma once
#include "Stack.h"
#include "PriorityQueue.h"
#include "Queue.h"

const int MAX_BUFFER_SIZE = 30;

struct Coords {
    int x;
    int y;
};

void addNameToCity(char** board, City* cities, int WIDTH, int HEIGHT);
bool addCoordsToCity(char** board, City& cities, int i, int j, int WIDTH, int HEIGHT);
void createGraph(char** board, City* cities, int cities_am, City** hash_cities, int WIDTH, int HEIGHT);
void checkPath(int x, int y, char** board, int** int_board, int distance, City** hash_cities, int city_nr, City* city, int WIDTH, int HEIGHT);
void findTheShortestWay(String& start, String& target, char type, City* cities, int cities_am, City** hash_cities,
    List<City*>* hash_name_cities, City** pr_city, int WIDTH, int HEIGHT);
void setFlights(String& start, String& target, int& distance, City* cities, List<City*>* hash_name_cities, int WIDTH, int HEIGHT);
int hashName(String& str, int WIDTH, int HEIGHT);
void readBoard(char** board, int WIDTH, int HEIGHT, int& cities_am);
void readFlights(int flights, City* cities, List<City*>* hash_name_cities, int WIDTH, int HEIGHT);
void readCommands(int commands, City* cities, List<City*>* hash_name_cities, City** hash_cities, City** pr_city, int cities_am, int WIDTH, int HEIGHT);