#include "Functions.h"

void readBoard(char** board, int WIDTH, int HEIGHT, int& cities_am) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = getchar();
            if (board[i][j] == '*')
                cities_am++;
        }
        getchar();
    }
}

void readFlights(int flights, City* cities, List<City*>* hash_name_cities, int WIDTH, int HEIGHT) {
    getchar();
    for (int i = 0; i < flights; i++) {
        char buffer[MAX_BUFFER_SIZE];
        String start;
        String target;
        String distance;
        int distance_int;
        fgets(buffer, MAX_BUFFER_SIZE, stdin);
        int j;
        for (j = 0; j < MAX_BUFFER_SIZE; j++) {
            if (buffer[j] == ' ') {
                buffer[j] = '\0';
                start = buffer;
                break;
            }
        }
        int k;
        for (k = ++j; k < MAX_BUFFER_SIZE; k++) {
            if (buffer[k] == ' ') {
                buffer[k] = '\0';
                target = &buffer[j];
                break;
            }
        }
        for (int l = ++k; l < MAX_BUFFER_SIZE; l++) {
            if (buffer[l] == '\n') {
                buffer[l] = '\0';
                distance = &buffer[k];
                break;
            }
        }
        distance_int = distance.string_to_int();
        setFlights(start, target, distance_int, cities, hash_name_cities, WIDTH, HEIGHT);
    }
}

void readCommands(int commands, City* cities, List<City*>* hash_name_cities, City** hash_cities, City** pr_city, int cities_am, int WIDTH, int HEIGHT) {
    getchar();
    for (int i = 0; i < commands; i++) {
        char buffer[MAX_BUFFER_SIZE];
        String start;
        String target;
        char type;
        fgets(buffer, MAX_BUFFER_SIZE, stdin);
        int j;
        for (j = 0; j < 30; j++) {
            if (buffer[j] == ' ') {
                buffer[j] = '\0';
                start = buffer;
                break;
            }
        }
        int k;
        for (k = ++j; k < MAX_BUFFER_SIZE; k++) {
            if (buffer[k] == ' ') {
                buffer[k] = '\0';
                target = &buffer[j];
                break;
            }
        }
        type = buffer[++k];
        findTheShortestWay(start, target, type, cities, cities_am, hash_cities, hash_name_cities, pr_city, WIDTH, HEIGHT);
    }
}

void addNameToCity(char** board, City* cities, int WIDTH, int HEIGHT) {
    int x = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j] != '*' && board[i][j] != '#' && board[i][j] != '.') {
                cities[x].name += board[i][j];
                bool coords = addCoordsToCity(board, cities[x], i, j, WIDTH, HEIGHT);
                j++;
                while (j < WIDTH && board[i][j] != '*' && board[i][j] != '#' && board[i][j] != '.') {
                    cities[x].name += board[i][j];
                    j++;
                }
                if (coords == false)
                    addCoordsToCity(board, cities[x], i, j - 1, WIDTH, HEIGHT);
                x++;
            }
        }
    }
}

bool addCoordsToCity(char** board, City& cities, int i, int j, int WIDTH, int HEIGHT) {
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

void checkPath(int x, int y, char** board, int** int_board, int distance, City** hash_cities, int city_nr, City* city, int WIDTH, int HEIGHT) {
    struct DistanceToCoords {
        int x;
        int y;
        int distance;
    };
    DistanceToCoords coord;
    coord.x = x;
    coord.y = y;
    coord.distance = distance;
    Queue<DistanceToCoords> coords_queue;
    Queue<DistanceToCoords> is_city;
    Queue<DistanceToCoords> visited;
    coords_queue.push(coord);
    while (!coords_queue.empty())
    {
        DistanceToCoords current_coord = coords_queue.front();
        coords_queue.pop();
        if (current_coord.x + 1 < WIDTH && (board[current_coord.y][current_coord.x + 1] == '*' || board[current_coord.y][current_coord.x + 1] == '#')
            && int_board[current_coord.y][current_coord.x + 1] > current_coord.distance + 1) {
            int_board[current_coord.y][current_coord.x + 1] = current_coord.distance + 1;
            coord.x = current_coord.x + 1;
            coord.y = current_coord.y;
            coord.distance = current_coord.distance + 1;
            if (board[current_coord.y][current_coord.x + 1] == '#') {
                coords_queue.push(coord);
            }
            else if (board[current_coord.y][current_coord.x + 1] == '*') {
                is_city.push(coord);
            }
        }
        if (current_coord.x - 1 >= 0 && (board[current_coord.y][current_coord.x - 1] == '*' || board[current_coord.y][current_coord.x - 1] == '#')
            && int_board[current_coord.y][current_coord.x - 1] > current_coord.distance + 1) {
            int_board[current_coord.y][current_coord.x - 1] = current_coord.distance + 1;
            coord.x = current_coord.x - 1;
            coord.y = current_coord.y;
            coord.distance = current_coord.distance + 1;
            if (board[current_coord.y][current_coord.x - 1] == '#') {
                coords_queue.push(coord);
            }
            else if (board[current_coord.y][current_coord.x - 1] == '*') {
                is_city.push(coord);
            }
        }
        if (current_coord.y + 1 < HEIGHT && (board[current_coord.y + 1][current_coord.x] == '*' || board[current_coord.y + 1][current_coord.x] == '#')
            && int_board[current_coord.y + 1][current_coord.x] > current_coord.distance + 1) {
            int_board[current_coord.y + 1][current_coord.x] = current_coord.distance + 1;
            coord.x = current_coord.x;
            coord.y = current_coord.y + 1;
            coord.distance = current_coord.distance + 1;
            if (board[current_coord.y + 1][current_coord.x] == '#') {
                coords_queue.push(coord);
            }
            else if (board[current_coord.y + 1][current_coord.x] == '*') {
                is_city.push(coord);
            }
        }
        if (current_coord.y - 1 >= 0 && (board[current_coord.y - 1][current_coord.x] == '*' || board[current_coord.y - 1][current_coord.x] == '#')
            && int_board[current_coord.y - 1][current_coord.x] > current_coord.distance + 1) {
            int_board[current_coord.y - 1][current_coord.x] = current_coord.distance + 1;
            coord.x = current_coord.x;
            coord.y = current_coord.y - 1;
            coord.distance = current_coord.distance + 1;
            if (board[current_coord.y - 1][current_coord.x] == '#') {
                coords_queue.push(coord);
            }
            else if (board[current_coord.y - 1][current_coord.x] == '*') {
                is_city.push(coord);
            }
        }
        visited.push(current_coord);
    }
    while (!is_city.empty()) {
        coord = is_city.front();
        int_board[coord.y][coord.x] = HEIGHT * WIDTH;
        is_city.pop();
        CityNeighbours city_neighbours;
        city_neighbours.city = hash_cities[coord.y * WIDTH + coord.x];
        city_neighbours.distance = coord.distance;
        city[city_nr].neighbours.push_back(city_neighbours);
    }
    while (!visited.empty()) {
        coord = visited.front();
        int_board[coord.y][coord.x] = HEIGHT * WIDTH;
        visited.pop();
    }
}

void createGraph(char** board, City* cities, int cities_am, City** hash_cities, int WIDTH, int HEIGHT) {
    int** int_board = new int* [HEIGHT];
    for (int i = 0; i < HEIGHT; i++)
        int_board[i] = new int[WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++)
            int_board[i][j] = HEIGHT * WIDTH;
    }
    for (int i = 0; i < cities_am; i++) {
        int_board[cities[i].y][cities[i].x] = 0;
        checkPath(cities[i].x, cities[i].y, board, int_board, 0, hash_cities, i, cities, WIDTH, HEIGHT);
    }
    for (int i = 0; i < HEIGHT; i++)
        delete[] int_board[i];
    delete[] int_board;
}

void findTheShortestWay(String& start, String& target, char type, City* cities, int cities_am, City** hash_cities,
    List<City*>* hash_name_cities, City** pr_city, int WIDTH, int HEIGHT) {
    Queue<Coords> using_coords;
    int* shortest_ways = new int[HEIGHT * WIDTH];
    for (int i = 0; i < HEIGHT * WIDTH; i++) {
        if (hash_cities[i] != nullptr && hash_cities[i]->name == start)
            shortest_ways[i] = 0;
        else
            shortest_ways[i] = HEIGHT * WIDTH;
    }
    PriorityQueue queue(hash_cities, shortest_ways, HEIGHT * WIDTH, WIDTH);
    while (!queue.isEmpty()) {
        City* temp = queue.getMinCity();
        int temp_distance = queue.getMinDistance();
        if (temp != nullptr) {
            CityNeighbours* city_neighbours;
            while ((city_neighbours = temp->neighbours.getItem()) != nullptr) {
                if (queue.changeDistance(city_neighbours->city, temp_distance, city_neighbours->distance)) {
                    pr_city[city_neighbours->city->y * WIDTH + city_neighbours->city->x] = temp;
                    Coords coords;
                    coords.x = city_neighbours->city->x;
                    coords.y = city_neighbours->city->y;
                    using_coords.push(coords);
                }
            }
        }
        queue.removeMin();
    }
    int way = 0;
    City* city_temp = (&hash_name_cities[hashName(target, WIDTH, HEIGHT)])->find(target);
    std::cout << shortest_ways[city_temp->y * WIDTH + city_temp->x];
    way = shortest_ways[city_temp->y * WIDTH + city_temp->x];
    if (type == '1' && way != 0) {
        City* pr_temp = pr_city[city_temp->y * WIDTH + city_temp->x];
        Stack<String*> city_name;
        while (pr_temp != nullptr && pr_temp->name != start) {
            city_name.push(&pr_temp->name);
            pr_temp = pr_city[pr_temp->y * WIDTH + pr_temp->x];
        }
        while (!city_name.empty()) {
            std::cout << " " << *city_name.top();
            city_name.pop();
        }
    }
    std::cout << std::endl;
    delete[]shortest_ways;
}

void setFlights(String& start, String& target, int& distance, City* cities, List<City*>* hash_name_cities, int WIDTH, int HEIGHT) {
    City* city = (&hash_name_cities[hashName(start, WIDTH, HEIGHT)])->find(start);;
    City* city_target = (&hash_name_cities[hashName(target, WIDTH, HEIGHT)])->find(target);
    CityNeighbours city_neighbours;
    city_neighbours.city = city_target;
    city_neighbours.distance = distance;
    city->neighbours.push_back(city_neighbours);
}

int hashName(String& name, int WIDTH, int HEIGHT) {
    int sum = 0;
    for (int i = 0; i < name.getSize(); i++) {
        sum += 97 * (i + 1) * name[i];
    }
    return sum % (HEIGHT * WIDTH / 13 + 1);
}