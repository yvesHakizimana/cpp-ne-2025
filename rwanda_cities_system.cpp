#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cctype>

using namespace std;

class RwandaCitiesSystem {
private:
    map<int, string> cities;
    vector<vector<int>> roadMatrix;
    vector<vector<double>> budgetMatrix;
    int nextId;
    
    // Valid Rwandan districts (including Kigali for the scenario
    set<string> validRwandanDistricts = {
        "Kigali", "Huye", "Muhanga", "Musanze", "Nyagatare", "Rubavu", "Rusizi",
        "Bugesera", "Burera", "Gakenke", "Gasabo", "Gatsibo", "Gicumbi", "Gisagara",
        "Gisozi", "Kamonyi", "Karongi", "Kayonza", "Kicukiro", "Kirehe", "Ngoma",
        "Ngororero", "Nyabihu", "Nyamagabe", "Nyamasheke", "Nyanza", "Nyarugenge",
        "Nyaruguru", "Ruhango", "Rulindo", "Rwamagana", "Rutsiro"
    };

public:
    RwandaCitiesSystem() : nextId(1) {
        initializeDefaultCities();
    }

    void initializeDefaultCities() {
        // Initialize with default cities from scenario
        cities[1] = "Kigali";
        cities[2] = "Huye";
        cities[3] = "Muhanga";
        cities[4] = "Musanze";
        cities[5] = "Nyagatare";
        cities[6] = "Rubavu";
        cities[7] = "Rusizi";
        nextId = 8;
        
        updateMatrices();
        saveCitiesToFile();
    }

    void updateMatrices() {
        int size = cities.size();
        roadMatrix.assign(size, vector<int>(size, 0));
        budgetMatrix.assign(size, vector<double>(size, 0.0));
    }

    bool isValidRwandanDistrict(const string& cityName) {
        string normalizedName = cityName;
        // Capitalize first letter and make rest lowercase
        if (!normalizedName.empty()) {
            normalizedName[0] = toupper(normalizedName[0]);
            for (size_t i = 1; i < normalizedName.length(); i++) {
                normalizedName[i] = tolower(normalizedName[i]);
            }
        }
        return validRwandanDistricts.find(normalizedName) != validRwandanDistricts.end();
    }

    bool isCityUnique(const string& cityName) {
        for (const auto& pair : cities) {
            if (pair.second == cityName) {
                return false;
            }
        }
        return true;
    }

    string validateAndNormalizeCityName(const string& input) {
        if (input.empty() || input.length() > 25 ) {
            throw invalid_argument("City name must be between 1 and 25 characters");
        }
        
        string normalized = input;
        // Remove leading/trailing spaces
        normalized.erase(0, normalized.find_first_not_of(" \t"));
        normalized.erase(normalized.find_last_not_of(" \t") + 1);
        
        if (normalized.empty()) {
            throw invalid_argument("City name cannot be empty or just spaces");
        }
        
        // Capitalize first letter and make rest lowercase
        normalized[0] = toupper(normalized[0]);
        for (size_t i = 1; i < normalized.length(); i++) {
            normalized[i] = tolower(normalized[i]);
        }
        
        if (!isValidRwandanDistrict(normalized)) {
            throw invalid_argument("Invalid Rwandan district name");
        }
        
        if (!isCityUnique(normalized)) {
            throw invalid_argument("City already exists");
        }
        
        return normalized;
    }

    void addNewCities() {
        cout << "\n=== Add New City(ies) ===" << endl;
        int numCities;
        
        while (true) {
            cout << "Enter number of cities to add (1-10): ";
            if (cin >> numCities && numCities >= 1 && numCities <= 10) {
                cin.ignore(); // Clear the newline
                break;
            } else {
                cout << "Error: Please enter a valid number between 1 and 10." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        
        for (int i = 1; i <= numCities; i++) {
            while (true) {
                try {
                    cout << "Enter the name of city " << i << ": ";
                    string cityName;
                    getline(cin, cityName);
                    
                    string validatedName = validateAndNormalizeCityName(cityName);
                    cities[nextId] = validatedName;
                    cout << "City '" << validatedName << "' added with ID " << nextId << endl;
                    nextId++;
                    break;
                } catch (const invalid_argument& e) {
                    cout << "Error: " << e.what() << ". Please try again." << endl;
                }
            }
        }
        
        updateMatrices();
        saveCitiesToFile();
        cout << "Cities added successfully!" << endl;
    }

    int findCityIdByName(const string& cityName) {
        for (const auto& pair : cities) {
            if (pair.second == cityName) {
                return pair.first;
            }
        }
        return -1;
    }

    void addRoadsBetweenCities() {
        cout << "\n=== Add Roads Between Cities ===" << endl;
        
        string firstCity, secondCity;
        cout << "Enter the name of the first city: ";
        getline(cin, firstCity);
        cout << "Enter the name of the second city: ";
        getline(cin, secondCity);
        
        int id1 = findCityIdByName(firstCity);
        int id2 = findCityIdByName(secondCity);
        
        if (id1 == -1 || id2 == -1) {
            cout << "Error: One or both cities not found." << endl;
            return;
        }
        
        if (id1 == id2) {
            cout << "Error: Cannot add road from a city to itself." << endl;
            return;
        }
        
        // Convert to 0-based index for matrix
        int index1 = 0, index2 = 0;
        int counter = 0;
        for (const auto& pair : cities) {
            if (pair.first == id1) index1 = counter;
            if (pair.first == id2) index2 = counter;
            counter++;
        }
        
        if (roadMatrix[index1][index2] == 1) {
            cout << "Road already exists between " << firstCity << " and " << secondCity << "." << endl;
            return;
        }
        
        roadMatrix[index1][index2] = 1;
        roadMatrix[index2][index1] = 1; // Undirected graph
        
        saveRoadsToFile();
        cout << "Road added between " << firstCity << " and " << secondCity << "." << endl;
    }

    void addBudgetForRoads() {
        cout << "\n=== Add Budget for Roads ===" << endl;
        
        string firstCity, secondCity;
        cout << "Enter the name of the first city: ";
        getline(cin, firstCity);
        cout << "Enter the name of the second city: ";
        getline(cin, secondCity);
        
        int id1 = findCityIdByName(firstCity);
        int id2 = findCityIdByName(secondCity);
        
        if (id1 == -1 || id2 == -1) {
            cout << "Error: One or both cities not found." << endl;
            return;
        }
        
        // Convert to 0-based index for matrix
        int index1 = 0, index2 = 0;
        int counter = 0;
        for (const auto& pair : cities) {
            if (pair.first == id1) index1 = counter;
            if (pair.first == id2) index2 = counter;
            counter++;
        }
        
        if (roadMatrix[index1][index2] == 0) {
            cout << "Error: No road exists between " << firstCity << " and " << secondCity << ". Add road first." << endl;
            return;
        }
        
        double budget;
        while (true) {
            cout << "Enter the budget for the road (in billion RWF): ";
            if (cin >> budget && budget > 0) {
                cin.ignore();
                break;
            } else {
                cout << "Error: Please enter a valid positive budget amount." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        
        budgetMatrix[index1][index2] = budget;
        budgetMatrix[index2][index1] = budget; // Undirected graph
        
        saveRoadsToFile();
        cout << "Budget added for the road between " << firstCity << " and " << secondCity << "." << endl;
    }

    void editCity() {
        cout << "\n=== Edit City ===" << endl;
        
        int cityIndex;
        while (true) {
            cout << "Enter the index of the city to edit: ";
            if (cin >> cityIndex && cities.find(cityIndex) != cities.end()) {
                cin.ignore();
                break;
            } else {
                cout << "Error: City with index " << cityIndex << " not found." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        
        cout << "Current name: " << cities[cityIndex] << endl;
        
        while (true) {
            try {
                cout << "Enter the new name for city: ";
                string newName;
                getline(cin, newName);
                
                // Temporarily remove the current city for uniqueness check
                string oldName = cities[cityIndex];
                cities.erase(cityIndex);
                
                string validatedName = validateAndNormalizeCityName(newName);
                cities[cityIndex] = validatedName;
                
                saveCitiesToFile();
                cout << "City updated successfully." << endl;
                break;
            } catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << ". Please try again." << endl;
                // Restore the old name if validation failed
                if (cities.find(cityIndex) == cities.end()) {
                    cities[cityIndex] = cities[cityIndex]; // This should restore it
                }
            }
        }
    }

    void searchCityByIndex() {
        cout << "\n=== Search for City ===" << endl;
        
        int cityIndex;
        cout << "Enter the index of the city to search: ";
        if (cin >> cityIndex && cities.find(cityIndex) != cities.end()) {
            cout << "City found: " << cityIndex << ". " << cities[cityIndex] << endl;
        } else {
            cout << "City with index " << cityIndex << " not found." << endl;
        }
        cin.ignore();
    }

    void displayCities() {
        cout << "\n=== Cities ===" << endl;
        if (cities.empty()) {
            cout << "No cities recorded." << endl;
            return;
        }
        
        for (const auto& pair : cities) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }

    void displayRoads() {
        cout << "\n=== Display Roads ===" << endl;
        displayCities();
        cout << "\nRoad adjacency matrix:" << endl;
        
        if (cities.empty()) {
            cout << "No cities to display roads for." << endl;
            return;
        }
        
        for (const auto& row : roadMatrix) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
    }

    void displayRecordedData() {
        cout << "\n=== Display Recorded Data ===" << endl;
        displayCities();
        
        cout << "\nRoad adjacency matrix:" << endl;
        for (const auto& row : roadMatrix) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
        
        cout << "\nBudget adjacency matrix (billion RWF):" << endl;
        
        // Print column headers (city names)
        cout << setw(16) << " ";
        vector<string> cityNames;
        for (const auto& pair : cities) {
            cityNames.push_back(pair.second);
            cout << setw(16) << left << pair.second.substr(0, 16);
        }
        cout << endl;
        
        // Print separator line
        cout << string(16 + 15 * cities.size(), '-') << endl;
        
        // Print each row with city name as label
        int rowIndex = 0;
        for (const auto& row : budgetMatrix) {
            cout << setw(16) << left << cityNames[rowIndex++].substr(0, 16);
            for (double val : row) {
                if (val == 0.0) {
                    cout << setw(16) << left << "-";
                } else {
                    cout << setw(16) << left << fixed << setprecision(2) << val;
                }
            }
            cout << endl;
        }
    }

    void saveCitiesToFile() {
        ofstream file("cities.txt");
        if (file.is_open()) {
            file << "Index City_name" << endl;
            for (const auto& pair : cities) {
                file << pair.first << "     " << pair.second << endl;
            }
            file.close();
        }
    }

    void saveRoadsToFile() {
        ofstream file("roads.txt");
        if (file.is_open()) {
            // Header with proper column formatting
            file << left << setw(5) << "Nbr" 
                 << setw(25) << "Road" 
                 << setw(15) << "Budget(Billion RWF)" << endl;
            file << string(45, '-') << endl; // Separator line
            
            vector<int> cityIds;
            for (const auto& pair : cities) {
                cityIds.push_back(pair.first);
            }

            int currentIndex = 1;
            
            for (size_t i = 0; i < cityIds.size(); i++) {
                for (size_t j = i + 1; j < cityIds.size(); j++) {
                    if (roadMatrix[i][j] == 1) {
                        string roadName = cities[cityIds[i]] + "-" + cities[cityIds[j]];
                        file << left << setw(5) << currentIndex++ 
                             << setw(25) << roadName
                             << setw(15) << fixed << setprecision(2) << budgetMatrix[i][j] << endl;
                    }
                }
            }
            file.close();
        }
    }

    void displayMenu() {
        cout << "\n=====================================" << endl;
        cout << "Rwanda Cities and Roads Management" << endl;
        cout << "=====================================" << endl;
        cout << "1. Add new city(ies)" << endl;
        cout << "2. Add roads between cities." << endl;
        cout << "3. Add the budget for roads." << endl;
        cout << "4. Edit city" << endl;
        cout << "5. Search for city using its index" << endl;
        cout << "6. Display cities." << endl;
        cout << "7. Display roads." << endl;
        cout << "8. Display recorded data on console." << endl;
        cout << "9. Exit" << endl;
        cout << "=====================================" << endl;
    }

    void run() {
        int choice;
        
        while (true) {
            displayMenu();
            cout << "Enter your choice: ";
            
            if (!(cin >> choice)) {
                cout << "Error: Invalid input. Please enter a number between 1 and 9." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            
            cin.ignore(); // Clear the newline character
            
            switch (choice) {
                case 1:
                    addNewCities();
                    break;
                case 2:
                    addRoadsBetweenCities();
                    break;
                case 3:
                    addBudgetForRoads();
                    break;
                case 4:
                    editCity();
                    break;
                case 5:
                    searchCityByIndex();
                    break;
                case 6:
                    displayCities();
                    break;
                case 7:
                    displayRoads();
                    break;
                case 8:
                    displayRecordedData();
                    break;
                case 9:
                    cout << "Exiting system. Goodbye!" << endl;
                    return;
                default:
                    cout << "Error: Invalid choice. Please enter a number between 1 and 9." << endl;
                    break;
            }
            
            cout << "\nPress Enter to continue...";
            cin.get();
        }
    }
};

int main() {
    try {
        RwandaCitiesSystem system;
        system.run();
    } catch (const exception& e) {
        cout << "Fatal error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}