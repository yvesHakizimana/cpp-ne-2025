# Flowchart for Rwanda Cities System

```mermaid
flowchart TD
    A[Start] --> B[Initialize RwandaCitiesSystem]
    B --> C[Load Default Cities]
    C --> D[Display Menu]
    D --> E{User Choice}
    
    %% Option 1: Add new city(ies)
    E -->|1| F[Add New Cities]
    F --> F1[Get number of cities to add]
    F1 --> F2[For each city]
    F2 --> F3[Get city name]
    F3 --> F4[Validate city name]
    F4 -->|Valid| F5[Add city to map]
    F4 -->|Invalid| F3
    F5 --> F6[Update matrices]
    F6 --> F7[Save cities to file]
    F7 --> D
    
    %% Option 2: Add roads between cities
    E -->|2| G[Add Roads Between Cities]
    G --> G1[Get first city name]
    G1 --> G2[Get second city name]
    G2 --> G3[Find city IDs]
    G3 -->|Cities found| G4{Road exists?}
    G3 -->|Cities not found| G9[Display error]
    G4 -->|No| G5[Add road to matrix]
    G4 -->|Yes| G8[Display error]
    G5 --> G6[Save roads to file]
    G6 --> G7[Display confirmation]
    G7 --> D
    G8 --> D
    G9 --> D
    
    %% Option 3: Add budget for roads
    E -->|3| H[Add Budget for Roads]
    H --> H1[Get first city name]
    H1 --> H2[Get second city name]
    H2 --> H3[Find city IDs]
    H3 -->|Cities found| H4{Road exists?}
    H3 -->|Cities not found| H9[Display error]
    H4 -->|Yes| H5[Get budget amount]
    H4 -->|No| H8[Display error]
    H5 --> H6[Add budget to matrix]
    H6 --> H7[Save roads to file]
    H7 --> D
    H8 --> D
    H9 --> D
    
    %% Option 4: Edit city
    E -->|4| I[Edit City]
    I --> I1[Get city index]
    I1 -->|Valid index| I2[Display current name]
    I1 -->|Invalid index| I6[Display error]
    I2 --> I3[Get new name]
    I3 --> I4[Validate new name]
    I4 -->|Valid| I5[Update city name]
    I4 -->|Invalid| I3
    I5 --> I7[Save cities to file]
    I6 --> D
    I7 --> D
    
    %% Option 5: Search for city
    E -->|5| J[Search City by Index]
    J --> J1[Get city index]
    J1 -->|Valid index| J2[Display city]
    J1 -->|Invalid index| J3[Display error]
    J2 --> D
    J3 --> D
    
    %% Option 6: Display cities
    E -->|6| K[Display Cities]
    K --> K1{Cities exist?}
    K1 -->|Yes| K2[List all cities]
    K1 -->|No| K3[Display message]
    K2 --> D
    K3 --> D
    
    %% Option 7: Display roads
    E -->|7| L[Display Roads]
    L --> L1[Display cities]
    L1 --> L2{Cities exist?}
    L2 -->|Yes| L3[Display road matrix]
    L2 -->|No| L4[Display message]
    L3 --> D
    L4 --> D
    
    %% Option 8: Display recorded data
    E -->|8| M[Display Recorded Data]
    M --> M1[Display cities]
    M1 --> M2[Display road matrix]
    M2 --> M3[Display budget matrix]
    M3 --> D
    
    %% Option 9: Exit
    E -->|9| N[Exit]
    N --> O[End]
    
    %% Invalid option
    E -->|Other| P[Display error]
    P --> D
```

## Class Structure

```mermaid
classDiagram
    class RwandaCitiesSystem {
        -map~int, string~ cities
        -vector~vector~int~~ roadMatrix
        -vector~vector~double~~ budgetMatrix
        -int nextId
        -set~string~ validRwandanDistricts
        +RwandaCitiesSystem()
        +initializeDefaultCities()
        +updateMatrices()
        +isValidRwandanDistrict(string)
        +isCityUnique(string)
        +validateAndNormalizeCityName(string)
        +addNewCities()
        +findCityIdByName(string)
        +addRoadsBetweenCities()
        +addBudgetForRoads()
        +editCity()
        +searchCityByIndex()
        +displayCities()
        +displayRoads()
        +displayRecordedData()
        +saveCitiesToFile()
        +saveRoadsToFile()
        +displayMenu()
        +run()
    }
```

## Data Flow Diagram

```mermaid
flowchart LR
    User[User Input] --> Menu[Menu System]
    Menu --> AddCity[Add City]
    Menu --> AddRoad[Add Road]
    Menu --> AddBudget[Add Budget]
    Menu --> EditCity[Edit City]
    Menu --> SearchCity[Search City]
    Menu --> DisplayCities[Display Cities]
    Menu --> DisplayRoads[Display Roads]
    Menu --> DisplayData[Display Data]
    
    AddCity --> Validation[Validation]
    Validation --> CityMap[Cities Map]
    
    AddRoad --> RoadMatrix[Road Matrix]
    AddBudget --> BudgetMatrix[Budget Matrix]
    
    CityMap --> CitiesFile[cities.txt]
    RoadMatrix --> RoadsFile[roads.txt]
    BudgetMatrix --> RoadsFile
    
    CityMap --> DisplayCities
    RoadMatrix --> DisplayRoads
    CityMap --> DisplayData
    RoadMatrix --> DisplayData
    BudgetMatrix --> DisplayData
    
    DisplayCities --> User
    DisplayRoads --> User
    DisplayData --> User
    SearchCity --> CityMap
    SearchCity --> User
    EditCity --> CityMap
```

## Key Functions and Their Relationships

```mermaid
flowchart TD
    Main[main()] --> Run[run()]
    Run --> DisplayMenu[displayMenu()]
    
    Run --> AddNewCities[addNewCities()]
    Run --> AddRoadsBetweenCities[addRoadsBetweenCities()]
    Run --> AddBudgetForRoads[addBudgetForRoads()]
    Run --> EditCity[editCity()]
    Run --> SearchCityByIndex[searchCityByIndex()]
    Run --> DisplayCities[displayCities()]
    Run --> DisplayRoads[displayRoads()]
    Run --> DisplayRecordedData[displayRecordedData()]
    
    AddNewCities --> ValidateAndNormalizeCityName[validateAndNormalizeCityName()]
    ValidateAndNormalizeCityName --> IsValidRwandanDistrict[isValidRwandanDistrict()]
    ValidateAndNormalizeCityName --> IsCityUnique[isCityUnique()]
    AddNewCities --> UpdateMatrices[updateMatrices()]
    AddNewCities --> SaveCitiesToFile[saveCitiesToFile()]
    
    AddRoadsBetweenCities --> FindCityIdByName[findCityIdByName()]
    AddRoadsBetweenCities --> SaveRoadsToFile[saveRoadsToFile()]
    
    AddBudgetForRoads --> FindCityIdByName
    AddBudgetForRoads --> SaveRoadsToFile
    
    EditCity --> ValidateAndNormalizeCityName
    EditCity --> SaveCitiesToFile
    
    DisplayRoads --> DisplayCities
    DisplayRecordedData --> DisplayCities
```