#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <set>
#include <climits>

using namespace std;

class Request {
public:
    // THIS IS FOR THE REQUEST DATA STRUCTURETO STORE MAINTENANCE REQUEST DETAILS
    Request(int id, const string& description, const string& location, const string& status)
        : id(id), description(description), location(location), status(status) {}

    int getId() const { return id; }
    string getDescription() const { return description; }
    string getLocation() const { return location; }
    string getStatus() const { return status; }
    void setStatus(const string& status) { this->status = status; }

private:
    int id;
    string description;
    string location;
    string status;
};

class MaintenanceSystem {
public:
    MaintenanceSystem() : lastStartRoom("") {
        // THIS IS DATA STRUCTURE FOR: MAP BUILDING, FLOOR AND ROOM ORGANIZATION
        buildings["ENGINEERING BUILDING"] = {
            {"Floor 1", {
                "1 | EN 101 (10-15 mins.)", "2 | EN 102 (10-15 mins.)", "3 | EN 103 (10-15 mins.)", "4 | EN 111B (10-15 mins.)", "5 | EN 112 (10-15 mins.)", "6 | EN 113 (10-15 mins.)", "7 | EN 117 (10-15 mins.)", "8 | EN 118 (10-15 mins.)",
                "9 | CAS FACULTY ROOM (20 mins.)", "10 | ME FACULTY ROOM (10 mins.)", "11 | EE FACULTY ROOM (10 mins.)", "12 | ECE FACULTY ROOM (10 mins.)",
                "13 | CPE FACULTY ROOM (10 mins.)", "14 | CE FACULTY ROOM (10 mins.)", "15 | COLLEGE OF ENGINEERING DEPARTMENT (20 mins.)",
                "16 | FACULTY BRIEFING AND TRAINING ROOM (10-15 mins.)", "17 | ACCREDITATION ROOM (10-15 mins.)", "18 | CE TOOL ROOM (10-15 mins.)",
                "19 | MEC LABORATORY (10-15 mins.)", "20 | STRUCTURAL, MATERIAL AND TESTING LABORATORY (10-15 mins.)",
                "21 | FLUID MECHANICS AND HYDRAULICS LABORATORY (10-15 mins.)", "22 | MECHANICAL ENGINEERING LABORATORY (10-15 mins.)",
                "23 | MACHINE FABRICATION SHOP (30 mins.)", "24 | EN FRONT SIDE WOMEN'S COMFORT ROOM (15-20 mins.)",
                "25 | EN FRONT SIDE MEN'S COMFORT ROOM (15-20 mins.)", "26 | EN BACK SIDE WOMENS'S COMFORT ROOM (15-20 mins.)",
                "27 | EN BACK SIDE MEN'S COMFORT ROOM (15-20 mins.)"
            }},
            {"Floor 2", {
                "28 | EN 201 (10-15 mins.)", "29 | EN 205 (10-15 mins.)", "30 | EN 206 (10-15 mins.)", "31 | EN 215 (10-15 mins.)", "32 | EN 217 (10-15 mins.)", "33 | EN 219 (10-15 mins.)",
                "34 | COMPUTER STUDIES AND SYSTEMS FACULTY ROOM (20 mins.)", "35 | SATELITE REPAIR CENTER (10-15 mins.)",
                "36 | ELECTRICAL ENGINEERING SHOP (30 mins.)", "37 | EE TOOL ROOM (10-15 mins.)", "38 | ECE/COE TOOL ROOM (10-15 mins.)",
                "39 | PHYSICS LABORATORY STOCK ROOM (15-20 mins.)", "40 | CHEMISTRY LABORATORY STOCK ROOM (15-20 mins.)",
                "41 | BIO LABORATORY STOCK ROOM (15-20 mins.)", "42 | OPEN LABORATORY ROOM (10-15 mins.)", "43 | NET LABORATORY (10-15 mins.)",
                "44 | ECE LABORATORY ROOM I (10-15 mins.)", "45 | ECE LABORATORY ROOM II (10-15 mins.)", "46 | ECE LABORATORY ROOM III (10-15 mins.)",
                "47 | ECE LABORATORY ROOM IV (10-15 mins.)", "48 | ELECTRICAL POWER ENGINEERING LABORATORY ROOM I (10-15 mins.)",
                "49 | ELECTRICAL POWER ENGINEERING LABORATORY ROOM II (10-15 mins.)",
                "50 | ELECTRICAL POWER ENGINEERINGCOMPUTER LABORATORY ROOM III (10-15 mins.)",
                "51 | ELECTRICAL POWER ENGINEERING LABORATORY ROOM IV (10-15 mins.)", "52 | COMPUTER LABORATORY ROOM II (10-15 mins.)",
                "53 | COMPUTER LABORATORY ROOM III (10-15 mins.)", "54 | COMPUTER LABORATORY ROOM IV (10-15 mins.)",
                "55 | COMPUTER LABORATORY ROOM V (10-15 mins.)", "56 | COMPUTER LABORATORY ROOM VI (10-15 mins.)",
                "57 | COMPUTER LABORATORY ROOM VII (10-15 mins.)", "58 | COMPUTER LABORATORY ROOM VIII (10-15 mins.)",
                "59 | EN FRONT SIDE WOMEN'S COMFORT ROOM (15-20 mins.)", "60 | EN FRONT SIDE MEN'S COMFORT ROOM (15-20 mins.)",
                "61 | EN BACK SIDE WOMEN'S COMFORT ROOM (15-20 mins.)", "62 | EN BACK SIDE MEN'S COMFORT ROOM (15-20 mins.)"
            }},
            {"Floor 3", {
                "63 | EN 301 (10-15 mins.)", "64 | EN 302 (10-15 mins.)", "65 | EN 303 (10-15 mins.)", "66 | EN 304 (10-15 mins.)", "67 | EN 305 (10-15 mins.)", "68 | EN 306 (10-15 mins.)", "69 | EN 307 (10-15 mins.)", "70 | EN 308 (10-15 mins.)",
                "71 | EN 309 (10-15 mins.)", "72 | EN 310 (10-15 mins.)", "73 | EN 311 (10-15 mins.)", "74 | EN 312 (10-15 mins.)", "75 | EN 313 (10-15 mins.)", "76 | EN 317 (10-15 mins.)", "77 | EN 318 (10-15 mins.)", "78 | EN 319 (10-15 mins.)",
                "79 | EN LIBRARY (30 mins.)", "80 | IECEP OFFICE (10-15 mins.)", "81 | DAWN KALOOKAN BUREAU (10-15 mins.)", "82 | MPH I (30 mins.)", "83 | MPH II (30 mins.)",
                "84 | ENTREPRENEUR LABORATORY ROOM III (15-20 mins.)", "85 | EN FRONT SIDE WOMEN'S COMFORT ROOM (15-20 mins.)",
                "86 | EN FRONT SIDE MEN'S COMFORT ROOM (15-20 mins.)", "87 | EN BACK SIDE WOMEN'S COMFORT ROOM (15-20 mins.)",
                "88 | EN BACK SIDE MEN'S COMFORT ROOM (15-20 mins.)"
            }},
            {"Floor 4", {
                "89 | EN 401 (10-15 mins.)", "90 | EN 402 (10-15 mins.)", "91 | EN 403 (10-15 mins.)", "92 | EN 404 (10-15 mins.)", "93 | EN 405 (10-15 mins.)", "94 | EN 406 (10-15 mins.)", "95 | EN 407 (10-15 mins.)", "96 | EN 408 (10-15 mins.)",
                "97 | EN 409 (10-15 mins.)", "98 | EN 410 (10-15 mins.)", "99 | EN 411 (10-15 mins.)", "100 | EN 412 (10-15 mins.)", "101 | EN 413 (10-15 mins.)", "102 | EN 414 (10-15 mins.)", "103 | EN 415 (10-15 mins.)", "104 | EN 416 (10-15 mins.)",
                "105 | EN 417 (10-15 mins.)", "106 | EN 418 (10-15 mins.)", "107 | EN 418 (10-15 mins.)", "108 | EN 419 (10-15 mins.)", "109 | EN 420 (10-15 mins.)", "110 | EN 421 (10-15 mins.)", "111 | EN 422 (10-15 mins.)", "112 | EN 423 (10-15 mins.)",
                "113 | EN 424 (10-15 mins.)", "114 | EN 425 (10-15 mins.)", "115 | EN 426 (10-15 mins.)", "116 | EN 427 (10-15 mins.)", "117 | EN 428 (10-15 mins.)", "118 | EN 429 (10-15 mins.)", "119 | EN 430 (10-15 mins.)", "120 | EN 431 (10-15 mins.)",
                "121 | EN 432 (10-15 mins.)", "122 | EN 433 (10-15 mins.)", "123 | EN 434 (10-15 mins.)", "124 | EN D1 (10-15 mins.)", "125 | EN D2 (10-15 mins.)", "126 | EN D3 (10-15 mins.)", "127 | EN D4 (10-15 mins.)", "128 | EN D5 (10-15 mins.)", "129 | EN D6 (10-15 mins.)",
                "130 | ASSOCIATION OF ELECTRICAL ENGINEERING STUDENTS ROOM (10-15 mins.)", "131 | STOCK ROOM (15-20 mins.)",
                "132 | EN BACK SIDE WOMEN'S COMFORT ROOM (15-20 mins.)", "133 | EN BACK SIDE MEN'S COMFORT ROOM (15-20 mins.)"
            }}
        };
    }

    // THIS LINE IS TO NORMALIZE THE FLOOR STRING INPUT
    string normalizeFloor(const string& input) const {
        string trimmed = input;
        trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r\f\v"));
        trimmed.erase(trimmed.find_last_not_of(" \t\n\r\f\v") + 1);

        string lower = trimmed;
        transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

        if (lower.find("floor") == 0) {
            size_t pos = lower.find_first_of("0123456789");
            if (pos != string::npos) {
                string num = trimmed.substr(pos);
                return "Floor " + num;
            }
        } else if (!lower.empty() && isdigit(lower[0])) {
            return "Floor " + trimmed;
        }
        return trimmed;
    }

    // THIS LINE IS TO DISPLAY ALL BUILDINGS
    void displayBuildings() const {
        cout << "=================================================" << endl;
        cout << " Building: " << endl;
        cout << "=================================================" << endl;
        for (const auto& building : buildings) {
            cout << building.first << endl;
        }
        cout << "=================================================" << endl;
    }

    // THIS LINE IS TO DISPLAY ALL FLOORS IN A BUILDING
    void displayFloors(const string& building) const {
        if (buildings.find(building) != buildings.end()) {
            cout << "=================================================" << endl;
            cout << " Floors in " << building << ":" << endl;
            cout << "=================================================" << endl;
            for (const auto& floor : buildings.at(building)) {
                cout << floor.first << endl;
            }
            cout << "=================================================" << endl;
        } else {
            cout << "Building not found. Please check the building name and try again." << endl;
        }
    }

    // THIS LINE IS TO DISPLAY ALL ROOMS IN A FLOOR
    void displayRooms(const string& building, const string& floor) const {
        if (buildings.find(building) != buildings.end()) {
            const auto& floors = buildings.at(building);
            auto it = find_if(floors.begin(), floors.end(), [&floor](const pair<string, vector<string>>& f) {
                return f.first == floor;
            });

            if (it != floors.end()) {
                cout << "=================================================" << endl;
                cout << " Rooms in " << building << ", " << floor << ":" << endl;
                cout << "=================================================" << endl;
                for (const auto& room : it->second) {
                    cout << room << endl;
                }
                cout << "=================================================" << endl;
            } else {
                cout << "Floor not found. Please check the floor name and try again." << endl;
            }
        } else {
            cout << "Building not found. Please check the building name and try again." << endl;
        }
    }

    bool isRequestIdUnique(int id) const {
        for (const auto& request : requests) {
            if (request.getId() == id) {
                return false;
            }
        }
        return true;
    }

    // THIS LINE IS TO ADD A NEW MAINTENANCE REQUEST
    void addRequest(int id, const string& description, const string& building, const string& floor, const string& room) {
        if (!isRequestIdUnique(id)) {
            cout << "Request ID already exists. Please use a unique ID." << endl;
            return;
        }
        string fullRoomName = getFullRoomName(building, floor, room);
        string location = building + " " + floor + " Room " + fullRoomName;
        Request request(id, description, location, "Pending");
        requests.push_back(request);
    }

    // THIS LINE IS TO VIEW ALL REQUESTS (PENDING OR COMPLETED)
    void viewRequests() const {
        cout << "=================================================" << endl;
        cout << " Pending Requests: " << endl;
        cout << "=================================================" << endl;
        int count = 1;
        for (const auto& request : requests) {
            if (request.getStatus() == "Pending") {
                cout << count << ". ";
                printRequest(request);
                count++;
            }
        }
        cout << endl;

        cout << "\n=================================================" << endl;
        cout << " Completed Requests: " << endl;
        cout << "=================================================" << endl;
        count = 1;
        for (const auto& request : requests) {
            if (request.getStatus() == "Completed") {
                cout << count << ". ";
                printRequest(request);
                count++;
            }
        }
        cout << endl;
    }

    // THIS LINE IS TO MARK A REQUEST AS COMPLETED
    void markRequestAsCompleted(int id) {
        for (auto& request : requests) {
            if (request.getId() == id) {
                request.setStatus("Completed");
                break;
            }
        }
    }

    // THIS LINE IS TO VIEW REQUESTS BY LOCATION (BUILDING)
    void viewRequestsByLocation(const string& building) const {
        bool found = false;
        cout << "=================================================" << endl;
        cout << " Requests in " << building << ":" << endl;
        cout << "=================================================" << endl;
        for (const auto& request : requests) {
            if (request.getLocation().find(building) == 0) {
                printRequest(request);
                found = true;
            }
        }
        if (!found) {
            cout << "No requests found for " << building << "." << endl;
        }
        cout << "=================================================" << endl;
    }

    // THIS LINE IS TO CHECK IF A FLOOR EXISTS IN A BUILDING
    //THIS LINE IS SEARCHING ALGORITHM
    bool isValidFloor(const string& building, const string& floor) const {
        if (buildings.find(building) != buildings.end()) {
            const auto& floors = buildings.at(building);
            return find_if(floors.begin(), floors.end(), [&floor](const pair<string, vector<string>>& f) {
                return f.first == floor;
            }) != floors.end();
        }
        return false;
    }

    // THIS LINE IS TO CHECK IF A ROOM EXISTS IN A FLOOR
    // THIS LINE IS SEARCHING ALGORITHM
    bool isValidRoom(const string& building, const string& floor, const string& room) const {
        if (buildings.find(building) != buildings.end()) {
            const auto& floors = buildings.at(building);
            auto it = find_if(floors.begin(), floors.end(), [&floor](const pair<string, vector<string>>& f) {
                return f.first == floor;
            });

            if (it != floors.end()) {
                const auto& rooms = it->second;
                for (const auto& r : rooms) {
                    size_t spacePos = r.find(' ');
                    if (spacePos != string::npos) {
                        string roomNumber = r.substr(0, spacePos);
                        if (roomNumber == room) {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    // THIS LINE IS TO EXTRACT THE FULL ROOM NAME FROM A LOCATION
    struct RoomInfo {
        string fullRoom;
        int floorNum;
        int roomNum;
    };

    // THIS LINE IS TO REPRESENT A ROOM NODE IN THE GRAPH FOR DIJKSTRA'S ALGORITHM
    struct RoomNode {
        string name;
        vector<pair<string, int>> neighbors;
    };

    // THIS LINE IS TO BUILD A GRAPH FROM ROOM INFORMATION
    unordered_map<string, RoomNode> buildGraph(const vector<RoomInfo>& rooms) {
        unordered_map<string, RoomNode> graph;
        // THIS LINE IS TO INITIALIZE OR TO ADD A GRAPH NODES
        for (const auto& r : rooms) {
            graph[r.fullRoom] = RoomNode{r.fullRoom, {}};
        }
        // THIS LINE IS TO CONNECT ROOMS IN THE GRAPH BASED ON FLOOR AND ROOM NUMBERS
        for (const auto& a : rooms) {
            for (const auto& b : rooms) {
                if (a.fullRoom == b.fullRoom) continue;
                // THIS LINE IS TO CONNECT ROOMS IN THE GRAPH BASED ON FLOOR AND ROOM NUMBERS
                if (a.floorNum == b.floorNum) {
                    graph[a.fullRoom].neighbors.push_back({b.fullRoom, 1}); // THIS LINE IS TO CONNECT ROOMS IN THE GRAPH BASED ON FLOOR AND ROOM NUMBERS
                }
                 // THIS LINE IS TO CONNECT ROOMS ON ADJACENT FLOORS WITH THE SAME ROOM NUMBER
                else if (abs(a.floorNum - b.floorNum) == 1 && a.roomNum == b.roomNum) {
                    graph[a.fullRoom].neighbors.push_back({b.fullRoom, 2}); // THIS LINE IS TO SET A DIFFERENT WEIGHT FOR ADJACENT FLOORS
                }
            }
        }
        return graph;
    }

    // THIS LINE IS TO FIND THE SHORTEST PATH USING DIJKSTRA'S ALGORITHM
    vector<string> dijkstraShortestPath(const unordered_map<string, RoomNode>& graph, const string& start) {
        unordered_map<string, int> distances;
        unordered_map<string, string> previous;
        set<string> visited;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

        // THIS LINE IS TO FIND THE SHORTEST PATH USING DIJKSTRA'S ALGORITHM
        for (const auto& node : graph) {
            distances[node.first] = INT_MAX;
        }
        distances[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            string current = pq.top().second;
            pq.pop();

            if (visited.find(current) != visited.end()) continue;
            visited.insert(current);

            for (const auto& neighbor : graph.at(current).neighbors) {
                string next = neighbor.first;
                int weight = neighbor.second;

                if (visited.find(next) != visited.end()) continue;

                int newDist = distances[current] + weight;
                if (newDist < distances[next]) {
                    distances[next] = newDist;
                    previous[next] = current;
                    pq.push({newDist, next});
                }
            }
        }

        // THIS LINE IS TO RECONSTRUCT THE SHORTEST PATH
        vector<string> path;
        string current = start;
        while (previous.find(current) != previous.end()) {
            path.push_back(current);
            current = previous[current];
        }
        path.push_back(current);
        reverse(path.begin(), path.end());
        return path;
    }

    // THIS LINE IS TO VIEW THE SHORTEST PATH FOR PENDING REQUESTS USING GREEDY NEAREST NEIGHBOR ALGORITHM
    // THIS LINE IS SORTING ALGORITHM AND IMPLEMENTING A GREEDY APPROACH
    void viewShortestPath() {
        // THIS LINE IS TO CHECK IF THERE ARE PENDING REQUESTS
        vector<RoomInfo> pendingRooms;
        for (const auto& request : requests) {
            if (request.getStatus() == "Pending") {
                string fullRoom = getFullRoomFromLocation(request.getLocation());
                string floorStr = extractFloor(request.getLocation());
                int floorNum = 0;
                try { floorNum = stoi(floorStr); } catch (...) { floorNum = 0; }
                int roomNum = 0;
                // THIS LINE IS TO CHECK IF THERE ARE PENDING REQUESTS
                size_t firstNumPos = fullRoom.find_first_of("0123456789");
                if (firstNumPos != string::npos) {
                    size_t endNumPos = fullRoom.find_first_not_of("0123456789", firstNumPos);
                    string numStr = fullRoom.substr(firstNumPos, endNumPos - firstNumPos);
                    try { roomNum = stoi(numStr); } catch (...) { roomNum = 0; }
                }
                pendingRooms.push_back({fullRoom, floorNum, roomNum});
            }
        }

        if (pendingRooms.empty()) {
            cout << "No pending requests found." << endl;
            return;
        }

        // THIS LINE IS TO DISPLAY PENDING ROOMS
        string startRoom;
        if (!lastStartRoom.empty()) {
            cout << "Enter starting room (full name, code, or room ID) [Last: " << lastStartRoom << "]: ";
        } else {
            cout << "Enter starting room (full name, code, or room ID): ";
        }
        cin.ignore();
        getline(cin, startRoom);
        if (startRoom.empty() && !lastStartRoom.empty()) {
            startRoom = lastStartRoom;
        }

        // THIS LINE IS TO DISPLAY PENDING ROOMS
        auto matchesRoom = [](const string& input, const RoomInfo& info) {
            if (input == info.fullRoom) return true;
            size_t firstNumPos = info.fullRoom.find_first_of("0123456789");
            if (firstNumPos != string::npos) {
                size_t endNumPos = info.fullRoom.find_first_not_of("0123456789", firstNumPos);
                string numStr = info.fullRoom.substr(firstNumPos, endNumPos - firstNumPos);
                if (input == numStr) return true;
            }
            size_t spacePos = info.fullRoom.find(' ');
            if (spacePos != string::npos) {
                string code = info.fullRoom.substr(spacePos + 1);
                if (input == code) return true;
            }
            return false;
        };
        auto startIt = find_if(pendingRooms.begin(), pendingRooms.end(), [&](const RoomInfo& info) {
            return matchesRoom(startRoom, info);
        });
        if (startIt == pendingRooms.end()) {
            cout << "Starting room not found in pending requests." << endl;
            return;
        }
        lastStartRoom = startIt->fullRoom;

        // THIS LINE IS TO BUILD THE GRAPH FROM PENDING ROOMS
        vector<RoomInfo> roomsToVisit;
        for (const auto& room : pendingRooms) {
            if (room.fullRoom != startIt->fullRoom) {
                roomsToVisit.push_back(room);
            }
        }

        // THIS LINE IS TO BUILD THE GRAPH USING GREEDY NEAREST NEIGHBOR ALGORITHM
        auto calculateDistance = [](const RoomInfo& a, const RoomInfo& b) {
            int floorDiff = abs(a.floorNum - b.floorNum);
            int roomDiff = abs(a.roomNum - b.roomNum);
            return floorDiff * 10 + roomDiff;
        };
        vector<string> path;
        path.push_back(startIt->fullRoom);
        RoomInfo current = *startIt;
        while (!roomsToVisit.empty()) {
            int minDist = INT_MAX;
            auto nearestIt = roomsToVisit.begin();
            for (auto it = roomsToVisit.begin(); it != roomsToVisit.end(); ++it) {
                int dist = calculateDistance(current, *it);
                if (dist < minDist) {
                    minDist = dist;
                    nearestIt = it;
                }
            }
            path.push_back(nearestIt->fullRoom);
            current = *nearestIt;
            roomsToVisit.erase(nearestIt);
        }
        // THIS LINE IS TO ADD THE STARTING ROOM AT THE END OF THE PATH TO INTIALIZE THE SHORTEST PATH
        cout << "\n=================================================" << endl;
        cout << "Optimized Maintenance Path:" << endl;
        for (size_t i = 0; i < path.size(); i++) {
            cout << i+1 << ". " << path[i] << endl;
            if (i < path.size() - 1) {
                cout << "           ↓" << endl;
            }
        }
    }

private:
    vector<Request> requests; // THIS DATA STRUCTURE LINE IS TO STORE ALL REQUESTS
    map<string, vector<pair<string, vector<string>>>> buildings; // THIS DATA STRUCTURE LINE IS TO STORE ALL REQUESTS
    string lastStartRoom;

    // THIS DATA STRUCTURE LINE IS TO STORE ALL REQUESTS
    void printRequest(const Request& request) const {
        string fullRoom = getFullRoomFromLocation(request.getLocation());
        string roomID = "";
        size_t spacePos = fullRoom.find(' ');
        if (spacePos != string::npos) {
            roomID = fullRoom.substr(0, spacePos);
        } else {
            roomID = fullRoom;
        }

        cout << "ID: " << request.getId()
             << ", Location: " << extractBuilding(request.getLocation())
             << ", Floor: " << extractFloor(request.getLocation())
             << ", Room ID: " << roomID
             << ", Room: " << extractMainRoomID(request.getLocation())
             << ", Description: " << request.getDescription()
             << ", Status: " << request.getStatus() << endl;
    }

    // THIS DATA STRUCTURE LINE IS TO STORE ALL REQUESTS
    string getFullRoomFromLocation(const string& location) const {
        size_t roomPos = location.find(" Room ");
        if (roomPos != string::npos) {
            return location.substr(roomPos + 6);
        }
        return "";
    }

    // THIS DATA STRUCTURE LINE IS TO STORE ALL REQUESTS
    string extractBuilding(const string& location) const {
        size_t floorPos = location.find(" Floor ");
        if (floorPos != string::npos) {
            return location.substr(0, floorPos);
        }
        return location;
    }

    // THIS DATA STRUCTURE LINE IS TO STORE ALL REQUESTS
    string extractFloor(const string& location) const {
        size_t floorPos = location.find(" Floor ");
        if (floorPos != string::npos) {
            size_t start = floorPos + 7;
            size_t end = location.find(' ', start);
            return (end != string::npos) ? location.substr(start, end - start) : location.substr(start);
        }
        return "";
    }

    // THIS LINE IS TO EXTRACT MAIN ROOM ID FROM LOCATION
    string extractMainRoomID(const string& location) const {
        size_t roomPos = location.find(" Room ");
        if (roomPos != string::npos) {
            string room = location.substr(roomPos + 6);
            size_t spacePos = room.find(' ');
            if (spacePos != string::npos) {
                return room.substr(spacePos + 1);
            }
            return room;
        }
        return "";
    }

    // THIS LINE IS TO GET THE FULL ROOM NAME BASED ON BUILDING, FLOOR, AND ROOM
    string getFullRoomName(const string& building, const string& floor, const string& room) const {
        if (buildings.find(building) != buildings.end()) {
            const auto& floors = buildings.at(building);
            auto it = find_if(floors.begin(), floors.end(), [&floor](const pair<string, vector<string>>& f) {
                return f.first == floor;
            });

            if (it != floors.end()) {
                const auto& rooms = it->second;
                for (const auto& r : rooms) {
                    size_t spacePos = r.find(' ');
                    if (spacePos != string::npos) {
                        string roomNumber = r.substr(0, spacePos);
                        if (roomNumber == room) {
                            return r;
                        }
                    }
                }
            }
        }
        return "";
    }

    // THIS LINE IS TO GET THE ROOM INDEX FROM A ROOM NAME
    int getRoomIndex(const string& room) const {
        size_t spacePos = room.find(' ');
        if (spacePos != string::npos) {
            string roomNumberStr = room.substr(spacePos + 1);
            try {
                return stoi(roomNumberStr);
            } catch (const std::invalid_argument& e) {
                return INT_MAX;
            }
        }
        return INT_MAX;
    }
};

int main() {
    int mainChoice;
    do {
        cout << R"(
                                    |=====================================================================================================================|
                                    |                                                                                                                     |
                                    | ███████╗██╗  ██╗███████╗████████╗███████╗███╗   ███╗   ██████╗  ███████╗ ██████╗ ██╗   ██╗███████╗███████╗████████╗ |
                                    | ██╔════╝╚██╗ ██╔╝██╔════╝╚══██╔══╝██╔════╝████╗ ████║   ██╔══██╗██╔════╝██╔═══██╗██║   ██║██╔════╝██╔════╝╚══██╔══╝ |
                                    | ███████╗ ╚████╔╝ ███████╗   ██║   █████╗  ██╔████╔██║   ██████╔╝█████╗  ██║   ██║██║   ██║█████╗  ███████╗   ██║    |
                                    | ╚════██║  ╚██╔╝  ╚════██║   ██║   ██╔══╝  ██║╚██╔╝██║   ██╔══██╗██╔══╝  ██║▄▄ ██║██║   ██║██╔══╝  ╚════██║   ██║    |
                                    | ███████║   ██║   ███████║   ██║   ███████╗██║ ╚═╝ ██║   ██║  ██║███████╗╚██████╔╝╚██████╔╝███████╗███████║   ██║    |
                                    | ╚══════╝   ╚═╝   ╚══════╝   ╚═╝   ╚══════╝╚═╝     ╚═╝   ╚═╝  ╚═╝╚══════╝ ╚═════╝  ╚═════╝ ╚══════╝╚══════╝   ╚═╝    |
                                    |                                                                                                                     |
                                    |=====================================================================================================================|
                                    |                                                 ENTER [1] TO START                                                  |
                                    |                                                 ENTER [2] TO EXIT                                                   |
                                    |=====================================================================================================================|
)" << endl;
        cout << "                                                                      |=================================================|" << endl;
        cout << "                                                                                      CHOOSE YOUR OPTION: ";
        cin >> mainChoice;
        if (mainChoice == 2) {
            cout << "Exiting..." << endl;
            return 0;
        } else if (mainChoice != 1) {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (mainChoice != 1);

    system("clear");

    MaintenanceSystem system;
    int choice;
    int id;
    string description;
    string location;
    string building = "ENGINEERING BUILDING";
    string floor;
    string room;

    do {
        cout << "=================================================" << endl;
        cout << " School Facilities and Maintenance Request System " << endl;
        cout << "1. Add Request" << endl;
        cout << "2. View All Requests" << endl;
        cout << "3. Mark Request as Completed" << endl;
        cout << "4. View Shortest Path" << endl;
        cout << "5. Exit" << endl;
        cout << "=================================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        ::system("clear");

        switch (choice) {
            case 1: {
                system.displayBuildings();
                system.displayFloors(building);

                cout << "Enter Floor Level: ";
                cin.ignore();
                while (true) {
                    getline(cin, floor);
                    floor = system.normalizeFloor(floor);
                    if (system.isValidFloor(building, floor)) break;
                    cout << "Invalid floor level. Please try again: ";
                }
                ::system("clear");

                system.displayRooms(building, floor);
                cout << "Enter Room ID: ";
                while (true) {
                    getline(cin, room);
                    if (system.isValidRoom(building, floor, room)) break;
                    cout << "Invalid room ID. Please try again: ";
                }

                cout << "Enter Request Description: ";
                getline(cin, description);

                cout << "Enter Request ID: ";
                while (true) {
                    cin >> id;
                    if (system.isRequestIdUnique(id)) break;
                    cout << "Request ID already exists. Please use a unique ID: ";
                }
                ::system("clear");

                system.addRequest(id, description, building, floor, room);
                break;
            }
            case 2:
                system.viewRequests();
                break;
            case 3:
                cout << "Enter Request ID to mark as completed: ";
                cin >> id;
                system.markRequestAsCompleted(id);
                break;
            case 4:
                system.viewShortestPath();
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
