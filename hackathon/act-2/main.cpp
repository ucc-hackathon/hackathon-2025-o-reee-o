#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <cctype>

using namespace std;

using Move = pair<string, int>;
using RoomMap = map<int, vector<Move>>;
using Element = pair<bool, bool>;          // { isWeapon, isPicked }
using ElementMap = map<int, vector<Element>>;

void printMoves(const RoomMap &map, int currentRoom) {
    RoomMap::const_iterator it = map.find(currentRoom);
    if (it == map.end()) {
        cout << "Habitación " << currentRoom << " no existe.\n";
        return;
    }

    const vector<Move> &moves = it->second;
    if (moves.empty()) {
        cout << "Habitación " << currentRoom << " no tiene movimientos.\n";
        return;
    }

    for (size_t i = 0; i < moves.size(); ++i) {
        const Move &mv = moves[i];
        const string &dirStr = mv.first;
        int toRoom = mv.second;

        char d = dirStr.empty() ? '?' : toupper(static_cast<unsigned char>(dirStr[0]));
        string fullDir;
        switch (d) {
            case 'N': fullDir = "[N] Norte"; break;
            case 'S': fullDir = "[S] Sur";   break;
            case 'E': fullDir = "[E] Este";  break;
            case 'O': fullDir = "[O] Oeste"; break;
            default:  fullDir = dirStr;  break;
        }

        cout << fullDir << " (Hab " << toRoom << ")";

        if (i + 1 < moves.size()) cout << ", ";
    }

    cout << '\n';
}

int getDestination(const RoomMap &map, int from, char dir) {
    RoomMap::const_iterator it = map.find(from);
    if (it == map.end()) return -1;

    const vector<Move> &moves = it->second;
    for (size_t i = 0; i < moves.size(); ++i) {
        const Move &mv = moves[i];
        const string &dirStr = mv.first;
        if (dirStr.empty()) continue;
        char a = toupper(static_cast<unsigned char>(dirStr[0]));
        if (a == dir) return mv.second;
    }
    return -1;
}

void printElements(const ElementMap &em, int currentRoom) {
    ElementMap::const_iterator it = em.find(currentRoom);
    if (it == em.end()) return;
    const vector<Element> &elts = it->second;
    for (size_t i = 0; i < elts.size(); ++i) {
        const Element &e = elts[i];
        bool isWeapon = e.first;
        bool isPicked = e.second;
        if (!isPicked) {
            if (isWeapon) cout << "Recoger arma [g]\n";
            else cout << "Recoger alimento [g]\n";
        }
    }
}

int pickElement(ElementMap &em, int currentRoom) {
    ElementMap::iterator it = em.find(currentRoom);
    if (it == em.end()) return 0;
    vector<Element> &elts = it->second;
    for (size_t i = 0; i < elts.size(); ++i) {
        Element &e = elts[i];
        if (!e.second) {
            e.second = true;
            if (e.first) return 10;
            else return 5;
        }
    }
    return 0;
}

int main() {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(5, 10);

    const int ELEMENT_PROB = 70;
    const int WEAPON_PROB  = 50;

    uniform_int_distribution<int> perc(0, 99);

    RoomMap map {
        {1, { {"S", 3} } },
        {2, { {"S", 4} } },
        {3, { {"N", 1}, {"O", 4} } },
        {4, { {"N", 2}, {"S", 6}, {"E", 3}, {"O", 5} } },
        {5, { {"S", 7}, {"E", 4} } },
        {6, { {"N", 4}, {"O", 7} } },
        {7, { {"N", 5}, {"E", 6} } }
    };

    ElementMap elements;
    for (RoomMap::const_iterator it = map.begin(); it != map.end(); ++it) {
        int room = it->first;
        int p = perc(gen);
        if (p < ELEMENT_PROB) {
            int w = perc(gen);
            bool isWeapon = (w < WEAPON_PROB);
            elements[room].push_back(Element(isWeapon, false));
        }
    }

    int currentRoom = 4;
    bool running = true;
    int points = 0;
    int maxMovements = dist(gen);

    do {
        cout << "Estas en la: \"Habitacion " << currentRoom << "\"\n";
        cout << "> Acciones:\n";
        printElements(elements, currentRoom);
        printMoves(map, currentRoom);

        string cmd;
        if (!(cin >> cmd)) break;
        if (cmd.empty()) continue;

        string cmdLower = cmd;
        for (size_t i = 0; i < cmdLower.size(); ++i)
            cmdLower[i] = static_cast<char>(tolower(static_cast<unsigned char>(cmdLower[i])));

        bool actionPerformed = false;

        if (cmdLower == "g") {
            int gained = pickElement(elements, currentRoom);
            if (gained > 0) {
                points += gained;
                cout << "Agarraste un objeto. +"<< gained << " puntos. Puntos totales: " << points << "\n";
            } else {
                cout << "No hay objetos disponibles para agarrar en esta habitación.\n";
            }
            actionPerformed = true;
        } else {
            char c = toupper(static_cast<unsigned char>(cmd[0]));
            if (c == 'N' || c == 'S' || c == 'E' || c == 'O') {
                int dest = getDestination(map, currentRoom, c);
                if (dest != -1) {
                    currentRoom = dest;
                }
                actionPerformed = true;
            }
        }

        if (actionPerformed) {
            maxMovements -= 1;
            if (maxMovements <= 0) {
                cout << "Te quedaste sin movimientos. Puntos totales: " << points << "\n";
                break;
            }
        }

    } while (running);

    return 0;
}
