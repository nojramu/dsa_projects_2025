#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>   // For file operations
#include <iomanip>   // For formatting
#include <sstream>   // For stringstream
#include <ctime>     // For getting current date
using namespace std;

// Event structure to hold event details
struct Event {
    string name;
    string description;
    int date;      // Format: YYYYMMDD

    Event() : name(""), description(""), date(0) {} // Default constructor
    Event(string n, string d, int dt) : name(n), description(d), date(dt) {}
};

// Helper to format date as YYYY/MM/DD
string formatDate(int date) {
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;

    ostringstream oss;
    oss << setw(4) << setfill('0') << year << "/"
        << setw(2) << setfill('0') << month << "/"
        << setw(2) << setfill('0') << day;
    return oss.str();
}

// Save all events to a file
void saveEventsToFile(const vector<Event>& events) {
    ofstream file("events.txt");
    for (const auto& event : events) {
        file << event.name << "|" << event.description << "|" << event.date << "\n";
    }
    file.close();
}

// Segment Tree for efficient date range queries
class SegmentTree {
    vector<vector<Event>> tree;
    int size;

    // Recursively build the segment tree
    void buildTree(vector<Event>& events, int node, int start, int end) {
        if (start == end) {
            tree[node] = {events[start]};
        } else {
            int mid = (start + end) / 2;
            buildTree(events, 2 * node + 1, start, mid);
            buildTree(events, 2 * node + 2, mid + 1, end);
            merge(tree[2 * node + 1].begin(), tree[2 * node + 1].end(),
                  tree[2 * node + 2].begin(), tree[2 * node + 2].end(),
                  back_inserter(tree[node]),
                  [](Event a, Event b) { return a.date < b.date; });
        }
    }

public:
    // Constructor builds the tree from the events vector
    SegmentTree(vector<Event>& events) {
        size = events.size();
        tree.resize(4 * size);
        buildTree(events, 0, 0, size - 1);
    }

    // Query for events in a date index range
    vector<Event> query(int node, int start, int end, int l, int r) {
        if (r < start || l > end) return {};
        if (l <= start && r >= end) return tree[node];
        int mid = (start + end) / 2;
        auto left = query(2 * node + 1, start, mid, l, r);
        auto right = query(2 * node + 2, mid + 1, end, l, r);
        vector<Event> result;
        merge(left.begin(), left.end(), right.begin(), right.end(), back_inserter(result),
              [](Event a, Event b) { return a.date < b.date; });
        return result;
    }

    // Public query interface
    vector<Event> query(int l, int r) {
        return query(0, 0, size - 1, l, r);
    }
};

// Binary search for event by date (requires sorted events)
Event* binarySearch(vector<Event>& events, int date) {
    int low = 0, high = events.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (events[mid].date == date) return &events[mid];
        else if (events[mid].date < date) low = mid + 1;
        else high = mid - 1;
    }
    return nullptr;
}

// Linear search for events by keyword in name or description
vector<Event> linearSearch(vector<Event>& events, const string& keyword) {
    vector<Event> result;
    for (auto& event : events) {
        if (event.name.find(keyword) != string::npos || event.description.find(keyword) != string::npos) {
            result.push_back(event);
        }
    }
    return result;
}

// Helper to get today's date as YYYYMMDD
int getTodayDate() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    int year = now->tm_year + 1900;
    int month = now->tm_mon + 1;
    int day = now->tm_mday;
    return year * 10000 + month * 100 + day;
}

// Sort events by the date nearest to today (ascending by absolute difference)
void sortByNearestDate(vector<Event>& events) {
    int today = getTodayDate();
    sort(events.begin(), events.end(), [today](const Event& a, const Event& b) {
        int diffA = abs(a.date - today);
        int diffB = abs(b.date - today);
        // If two events are equally near, show the earlier one first
        if (diffA == diffB) return a.date < b.date;
        return diffA < diffB;
    });
}

// Display the main menu
void displayMenu() {
    cout << "\n🏫 School Event Calendar Organizer\n";
    cout << "1️⃣  ➕ Add Event\n";
    cout << "2️⃣  👀 View Events\n";
    cout << "3️⃣  📜 View Past Events\n";
    cout << "4️⃣  🔎 Search Event by Date\n";
    cout << "5️⃣  🔎 Search Event by Keyword\n";
    cout << "6️⃣  🔎 Search Events by Month Name\n";
    cout << "7️⃣  📆 Search Events in Date Range\n";
    cout << "8️⃣  ❌ Remove Event\n";
    cout << "9️⃣  🚪 Exit\n";
    cout << "Enter your choice: ";
}

// Helper to check if a date is valid
bool isValidDate(int date) {
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;

    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    // Leap year check for February
    if (month == 2) {
        bool leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (leap && day == 29) return true;
    }
    if (day < 1 || day > daysInMonth[month - 1]) return false;
    return true;
}

// Add this function before main()
int monthNameToNumber(const string& monthName) {
    static const vector<string> months = {
        "january", "february", "march", "april", "may", "june",
        "july", "august", "september", "october", "november", "december"
    };
    string lowerMonth = monthName;
    transform(lowerMonth.begin(), lowerMonth.end(), lowerMonth.begin(), ::tolower);
    for (size_t i = 0; i < months.size(); ++i) {
        if (lowerMonth == months[i]) return i + 1;
    }
    return 0; // Invalid month
}

int main() {
    vector<Event> events;           // All events in memory
    SegmentTree* segmentTree = nullptr; // Pointer to segment tree

    // Load events from file if exists
    ifstream infile("events.txt");
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string name, description, dateStr;
        getline(ss, name, '|');
        getline(ss, description, '|');
        getline(ss, dateStr, '|');
        if (!name.empty() && !dateStr.empty()) {
            events.emplace_back(name, description, stoi(dateStr));
        }
    }
    infile.close();

    // Always keep events sorted by nearest date
    sortByNearestDate(events);

    if (!events.empty()) {
        segmentTree = new SegmentTree(events); // Build segment tree if events exist
    }

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;

        if (choice == 1) {
            // Add Event
            string name, description;
            int date;
            cout << "📝 Enter event name (or type 'cancel' to abort): ";
            cin.ignore();
            getline(cin, name);
            if (name == "cancel") {
                cout << "❌ Add event cancelled.\n";
                continue;
            }
            cout << "📝 Enter event description (or type 'cancel' to abort): ";
            getline(cin, description);
            if (description == "cancel") {
                cout << "❌ Add event cancelled.\n";
                continue;
            }
            cout << "📅 Enter event date (YYYYMMDD) (or 0 to cancel): ";
            cin >> date;
            if (date == 0) {
                cout << "❌ Add event cancelled.\n";
                continue;
            }
            if (!isValidDate(date)) {
                cout << "❌ Invalid date. Please enter a real date.\n";
                continue;
            }

            events.emplace_back(name, description, date);

            // Always keep events sorted by nearest date after adding
            sortByNearestDate(events);

            cout << "✅ Event added successfully!\n";

            // Save to file and rebuild segment tree
            saveEventsToFile(events);
            delete segmentTree;
            segmentTree = new SegmentTree(events);
        }
        else if (choice == 2) {
            // View Events (only today or future)
            int today = getTodayDate();
            vector<Event> upcomingEvents;
            for (const auto& event : events) {
                if (event.date >= today) {
                    upcomingEvents.push_back(event);
                }
            }
            if (upcomingEvents.empty()) {
                cout << "⚠️ No upcoming events to display.\n";
            } else {
                sortByNearestDate(upcomingEvents);
                cout << "\n📋 Events List (Nearest Date First):\n";
                for (const auto& event : upcomingEvents) {
                    cout << "📌 Name: " << event.name
                         << ", 📅 Date: " << formatDate(event.date)
                         << ", 📝 Description: " << event.description << "\n";
                }
            }
        }
        else if (choice == 3) {
            // View Past Events (only before today)
            int today = getTodayDate();
            vector<Event> pastEvents;
            for (const auto& event : events) {
                if (event.date < today) {
                    pastEvents.push_back(event);
                }
            }
            if (pastEvents.empty()) {
                cout << "⚠️ No past events to display.\n";
            } else {
                sort(pastEvents.begin(), pastEvents.end(), [](const Event& a, const Event& b) {
                    return a.date < b.date;
                });
                cout << "\n📜 Past Events:\n";
                for (const auto& event : pastEvents) {
                    cout << "📌 Name: " << event.name
                         << ", 📅 Date: " << formatDate(event.date)
                         << ", 📝 Description: " << event.description << "\n";
                }
            }
        }
        else if (choice == 4) {
            // Search Event by Date
            int date;
            cout << "📅 Enter date (YYYYMMDD) (or 0 to cancel): ";
            cin >> date;
            if (date == 0) {
                cout << "❌ Search cancelled.\n";
                continue;
            }
            if (!isValidDate(date)) {
                cout << "❌ Invalid date. Please enter a real date.\n";
                continue;
            }
            // Already sorted, so just search
            Event* event = binarySearch(events, date);
            if (event) {
                cout << "📌 Name: " << event->name
                     << ", 📝 Description: " << event->description
                     << ", 📅 Date: " << formatDate(event->date) << "\n";
            } else {
                cout << "❌ No event found on this date.\n";
            }
        }
        else if (choice == 5) {
            // Search Event by Keyword
            string keyword;
            cout << "🔎 Enter keyword (or type 'cancel' to abort): ";
            cin.ignore();
            getline(cin, keyword);
            if (keyword == "cancel") {
                cout << "❌ Search cancelled.\n";
                continue;
            }
            auto results = linearSearch(events, keyword);
            if (results.empty()) {
                cout << "❌ No matching events found.\n";
            } else {
                // Sort results by nearest date before displaying
                sortByNearestDate(results);
                for (const auto& event : results) {
                    cout << "📌 Name: " << event.name
                         << ", 📅 Date: " << formatDate(event.date)
                         << ", 📝 Description: " << event.description << "\n";
                }
            }
        }
        else if (choice == 6) {
            // Search Events by Month Name
            string monthText;
            cout << "📅 Enter month name (e.g., January) (or type 'cancel' to abort): ";
            cin.ignore();
            getline(cin, monthText);
            if (monthText == "cancel") {
                cout << "❌ Search cancelled.\n";
                continue;
            }
            int monthNum = monthNameToNumber(monthText);
            if (monthNum == 0) {
                cout << "❌ Invalid month name.\n";
                continue;
            }
            string yearInput;
            cout << "📅 Enter year (YYYY) (or type 'all' to show all years): ";
            getline(cin, yearInput);
            int yearNum = 0;
            bool filterByYear = false;
            if (yearInput != "all") {
                try {
                    yearNum = stoi(yearInput);
                    filterByYear = true;
                } catch (...) {
                    cout << "❌ Invalid year input.\n";
                    continue;
                }
            }
            vector<Event> monthEvents;
            for (const auto& event : events) {
                int eventMonth = (event.date / 100) % 100;
                int eventYear = event.date / 10000;
                if (eventMonth == monthNum && (!filterByYear || eventYear == yearNum)) {
                    monthEvents.push_back(event);
                }
            }
            if (monthEvents.empty()) {
                if (filterByYear)
                    cout << "❌ No events found in " << monthText << " " << yearNum << ".\n";
                else
                    cout << "❌ No events found in " << monthText << ".\n";
            } else {
                if (filterByYear)
                    cout << "\n📋 Events in " << monthText << " " << yearNum << ":\n";
                else
                    cout << "\n📋 Events in " << monthText << " (all years):\n";
                sortByNearestDate(monthEvents);
                for (const auto& event : monthEvents) {
                    cout << "📌 Name: " << event.name
                         << ", 📅 Date: " << formatDate(event.date)
                         << ", 📝 Description: " << event.description << "\n";
                }
            }
        }
        else if (choice == 7) {
            // Search Events in Date Range
            if (!segmentTree) {
                cout << "⚠️ No events available to search.\n";
                continue;
            }

            int startDate, endDate;
            cout << "📅 Enter start date (YYYYMMDD) (or 0 to cancel): ";
            cin >> startDate;
            if (startDate == 0) {
                cout << "❌ Search cancelled.\n";
                continue;
            }
            if (!isValidDate(startDate)) {
                cout << "❌ Invalid start date. Please enter a real date.\n";
                continue;
            }
            cout << "📅 Enter end date (YYYYMMDD) (or 0 to cancel): ";
            cin >> endDate;
            if (endDate == 0) {
                cout << "❌ Search cancelled.\n";
                continue;
            }
            if (!isValidDate(endDate)) {
                cout << "❌ Invalid end date. Please enter a real date.\n";
                continue;
            }

            // Query the segment tree for all events
            auto results = segmentTree->query(0, 0, events.size() - 1, 0, events.size() - 1);

            // Filter by date range since tree stores sorted ranges, not actual indexes by date
            vector<Event> filtered;
            for (const auto& event : results) {
                if (event.date >= startDate && event.date <= endDate) {
                    filtered.push_back(event);
                }
            }

            if (filtered.empty()) {
                cout << "❌ No events found in this date range.\n";
            } else {
                // Already sorted, just display
                cout << "\n📋 Events from " << formatDate(startDate)
                     << " to " << formatDate(endDate) << " (Nearest Date First):\n";
                for (const auto& event : filtered) {
                    cout << "📌 Name: " << event.name
                         << ", 📅 Date: " << formatDate(event.date)
                         << ", 📝 Description: " << event.description << "\n";
                }
            }
        }
        else if (choice == 8) {
            // Remove Event
            if (events.empty()) {
                cout << "⚠️ No events to remove.\n";
                continue;
            }
            int date;
            cout << "📅 Enter the date (YYYYMMDD) of the event to remove (or 0 to cancel): ";
            cin >> date;
            if (date == 0) {
                cout << "❌ Remove cancelled.\n";
                continue;
            }
            if (!isValidDate(date)) {
                cout << "❌ Invalid date. Please enter a real date.\n";
                continue;
            }
            // List all events on that date
            vector<int> idxs;
            for (size_t i = 0; i < events.size(); ++i) {
                if (events[i].date == date) {
                    idxs.push_back(i);
                }
            }
            if (idxs.empty()) {
                cout << "❌ No event found on this date.\n";
                continue;
            }
            cout << "Events on " << formatDate(date) << ":\n";
            for (size_t i = 0; i < idxs.size(); ++i) {
                const auto& e = events[idxs[i]];
                cout << i+1 << ". 📌 Name: " << e.name
                     << ", 📝 Description: " << e.description << "\n";
            }
            cout << "Enter the number of the event to remove (or 0 to cancel): ";
            int sel;
            cin >> sel;
            if (sel == 0) {
                cout << "❌ Remove cancelled.\n";
                continue;
            }
            if (sel < 1 || sel > (int)idxs.size()) {
                cout << "❌ Cancelled or invalid selection.\n";
                continue;
            }
            cout << "Are you sure you want to delete this event? (y/n): ";
            char confirm;
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') {
                events.erase(events.begin() + idxs[sel-1]);
                // Always keep events sorted by nearest date after removal
                sortByNearestDate(events);
                cout << "✅ Event removed.\n";
                saveEventsToFile(events);
                delete segmentTree;
                segmentTree = events.empty() ? nullptr : new SegmentTree(events);
            } else {
                cout << "❌ Deletion cancelled.\n";
            }
        }
        else if (choice == 9) {
            // Exit
            cout << "👋 Goodbye!\n";
            break;
        }
        else {
            cout << "❌ Invalid choice. Try again.\n";
        }
    } 

    delete segmentTree;
    return 0;
}