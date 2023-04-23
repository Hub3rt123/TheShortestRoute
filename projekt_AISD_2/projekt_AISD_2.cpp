#include <iostream>
#include <stack>
#include "PriorityQueue.h"

int WIDTH, HEIGHT;


void addCitiesName(char** board, Cities* cities, int cities_am);
bool addCitiesCoords(char** board, Cities& cities, int i, int j);
void createGraph(char** board, Cities* cities, int cities_am);
void findTheShortestWay(String& start, String& target, int type, Cities* cities, int cities_am);
void setFlights(String& start, String& target, int distance, Cities* cities);

int main()
{
    int cities_am = 0, flights = 0, commands = 0;
    char x;
    std::cin >> WIDTH;
    std::cin >> HEIGHT;
    x = getchar();
    char** board = new char*[HEIGHT];
    for (int i = 0; i < HEIGHT; i++)
        board[i] = new char[WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = getchar();
            if (board[i][j] == '*')
                cities_am++;
        }   
        x = getchar();
    }
    Cities* cities = new Cities[cities_am];
    addCitiesName(board, cities, cities_am);
    createGraph(board, cities, cities_am);
    std::cin >> flights;
    for (int i = 0; i < flights; i++) {
        x = getchar();
        String start;
        String target;
        int distance;
        while ((x = getchar()) != ' ')
            start += x;
        while ((x = getchar()) != ' ')
            target += x;
        std::cin >> distance;
        setFlights(start, target, distance, cities);
    }
    x = getchar();
    std::cin >> commands;
    for (int i = 0; i < commands; i++) {
        x = getchar();
        String start;
        String target;
        int type;
        while ((x = getchar()) != ' ')
            start += x;
        while ((x = getchar()) != ' ')
            target += x;
        std::cin >> type;
        findTheShortestWay(start, target, type, cities, cities_am);
    }
    return 0;
}

void addCitiesName(char** board, Cities* cities, int cities_am) {
    int x = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j] != '*' && board[i][j] != '#' && board[i][j] != '.') {
                cities[x].name += board[i][j];
                bool coords = addCitiesCoords(board, cities[x], i, j);
                j++;
                while (j < WIDTH && board[i][j] != '*' && board[i][j] != '#' && board[i][j] != '.') {
                    cities[x].name += board[i][j];
                    j++;
                }
                if (coords == false)
                    addCitiesCoords(board, cities[x], i, j - 1);
                x++;
            }
        }
    }
}

bool addCitiesCoords(char** board, Cities& cities, int i, int j) {
    for (int col = -1; col < 2; col++) {
        for (int row = -1; row < 2; row++)
            if (i + col < HEIGHT && i + col >= 0 && j + row < WIDTH && j + row >= 0 && board[i + col][j + row] == '*') {
                cities.x = j + row;
                cities.y = i + col;
                return true;
            }
    }
    return false;
}

void checkPath(int x, int y, char** board, int **int_board, int distance) {
    if (x + 1 < WIDTH && (board[y][x + 1] == '*' || board[y][x + 1] == '#') && int_board[y][x + 1] > distance + 1) {
        int_board[y][x + 1] = distance + 1;
        if (board[y][x + 1] == '#')
            checkPath(x + 1, y, board, int_board, distance + 1);
    }
    if (x - 1 >= 0 && (board[y][x - 1] == '*' || board[y][x - 1] == '#') && int_board[y][x - 1] > distance + 1) {
        int_board[y][x - 1] = distance + 1;
        if (board[y][x - 1] == '#')
            checkPath(x - 1, y, board, int_board, distance + 1);
    }
    if (y + 1 < HEIGHT && (board[y + 1][x] == '*' || board[y + 1][x] == '#') && int_board[y + 1][x] > distance + 1) {
        int_board[y + 1][x] = distance + 1;
        if (board[y + 1][x] == '#')
            checkPath(x, y + 1, board, int_board, distance + 1);
    }
    if (y - 1 >= 0 && (board[y - 1][x] == '*' || board[y - 1][x] == '#') && int_board[y - 1][x] > distance + 1) {
        int_board[y - 1][x] = distance + 1;
        if (board[y - 1][x] == '#')
            checkPath(x, y - 1, board, int_board, distance + 1);
    }
}

void findWay(char** board, Cities* cities, int x_start, int y_start, int cities_am, int city_nr) {
    int** int_board = new int* [HEIGHT];
    for (int i = 0; i < HEIGHT; i++)
        int_board[i] = new int[WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int_board[i][j] = HEIGHT * WIDTH;
        }
    }
    int_board[y_start][x_start] = 0;
    checkPath(x_start, y_start, board, int_board, 0);
    for (int i = 0; i < cities_am; i++) {
        if (int_board[cities[i].y][cities[i].x] < HEIGHT * WIDTH && int_board[cities[i].y][cities[i].x] > 0) {
            CityNeighbours city_neighbours;
            city_neighbours.city = &cities[i];
            city_neighbours.distance = int_board[cities[i].y][cities[i].x];
            cities[city_nr].neighbours.push_back(city_neighbours);
        }
    }
    for (int i = 0; i < HEIGHT; i++)
        delete [] int_board[i];
    delete[] int_board;
}

void createGraph(char** board, Cities* cities, int cities_am) {
    for (int i = 0; i < cities_am; i++) {
        findWay(board, cities, cities[i].x, cities[i].y, cities_am, i);
    }
}

void findTheShortestWay(String& start, String& target, int type, Cities* cities, int cities_am) {
    int* shortest_ways = new int[cities_am];
    Cities** pr_city = new Cities*[cities_am];
    for (int i = 0; i < cities_am; i++) {
        if (cities[i].name == start)
            shortest_ways[i] = 0;
        else
            shortest_ways[i] = HEIGHT * WIDTH;
    }
    PriorityQueue queue(cities, shortest_ways, cities_am);
    while (!queue.isEmpty()) {
        Cities* temp = queue.getMinCity();
        int temp_distance = queue.getMinDistance();
        for (std::list<CityNeighbours>::iterator it = temp->neighbours.begin(); it != temp->neighbours.end(); it++) {
            if (queue.isCity((*it).city)) {
                int* distance = queue.getDistance((*it).city);
                if (*distance > temp_distance + (*it).distance) {
                    *distance = temp_distance + (*it).distance;
                    for (int i = 0; i < cities_am; i++) {
                        if ((*it).city->name == cities[i].name)
                            pr_city[i] = temp;
                    }
                }
            }
        }
        queue.removeMin();
    }
    for (int i = 0; i < cities_am; i++) {
        if (cities[i].name == target)
            std::cout << shortest_ways[i];
    }
    if (type == 1) {
        Cities* pr_temp = pr_city[0];
        std::stack<String*> city_name;
        for (int i = 0; i < cities_am; i++) {
            if (cities[i].name == target) {
                pr_temp = pr_city[i];
                break;
            }
        }
        while (pr_temp->name != start) {
            city_name.push(&pr_temp->name);
            for (int i = 0; i < cities_am; i++) {
                if (cities[i].name == pr_temp->name) {
                    pr_temp = pr_city[i];
                    break;
                }
            }
        }
        while (!city_name.empty()) {
            std::cout << " " << *city_name.top();
            city_name.pop();
        }
    }
    std::cout << std::endl;
    delete[]pr_city;
    delete[]shortest_ways;
}

void setFlights(String& start, String& target, int distance, Cities* cities) {
    int i = 0;
    while (cities[i].name != start) {
        i++;
    }
    bool is_road = false;
    for (std::list<CityNeighbours>::iterator it = cities[i].neighbours.begin(); it != cities[i].neighbours.end(); it++) {
        if ((*it).city->name == target) {
            if ((*it).distance > distance)
                (*it).distance = distance;
            is_road = true;
            break;
        }
    }
    if (is_road == false) {
        int j = 0;
        while (cities[j].name != target) {
            j++;
        }
        CityNeighbours city_neighbours;
        city_neighbours.city = &cities[j];
        city_neighbours.distance = distance;
        cities[i].neighbours.push_back(city_neighbours);
    }
}


/*
20 20
.........GDANSK.....
........*...........
........#...........
........#...........
*##################.
#SZCZECIN.........#.
#.................#.
##................#.
.############*#####.
.#...WARSZAWA.......
.#..................
.#############......
.#...........#......
.#..WROCLAW.##......
.#..*.......*.......
.####.......#KIELCE.
......*##.#########.
.OPOLE..#.*.......#.
........#.KRAKOW..#.
........###########.
3
GDANSK SZCZECIN 5
SZCZECIN WARSZAWA 20
OPOLE GDANSK 10
*/

/*
    for (int i = 0; i < cities_am; i++) {
        for (std::list<CityNeighbours>::iterator it = cities[i].neighbours.begin(); it != cities[i].neighbours.end(); it++)
            std::cout << (*it).city->name << " " << (*it).distance << " ";
        std::cout << std::endl;
    }
*/

/*
20 20
.........GDANSK.....
........*...........
........#...........
........#...........
*##################.
#SZCZECIN.........#.
#.................#.
##................#.
.############*#####.
.#...WARSZAWA.......
.#..................
.#############......
.#...........#......
.#..WROCLAW.##......
.#..*.......*.......
.####.......#KIELCE.
......*##.#########.
.OPOLE..#.*.......#.
........#.KRAKOW..#.
........###########.
0
3
KIELCE KRAKOW 0
KRAKOW GDANSK 0
KRAKOW GDANSK 1
*/