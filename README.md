# Rwanda Cities System Flowcharts

This repository contains flowchart diagrams for the Rwanda Cities System C++ program. The flowcharts are provided in two popular formats:

1. **Mermaid** - A JavaScript-based diagramming and charting tool that renders Markdown-inspired text definitions to create diagrams.
2. **PlantUML** - A tool that allows you to create diagrams from a simple text language.

## Files

- `rwanda_cities_system.cpp` - The main C++ program for managing cities and roads in Rwanda
- `cities.txt` - Contains the list of cities with their indices
- `roads.txt` - Contains information about roads between cities and their budgets
- `rwanda_cities_system_flowchart.md` - Flowcharts in Mermaid format
- `rwanda_cities_system_flowchart_plantuml.txt` - Flowcharts in PlantUML format

## How to View the Flowcharts

### Mermaid Flowcharts

To view the Mermaid flowcharts:

1. Open the `rwanda_cities_system_flowchart.md` file in a Markdown viewer that supports Mermaid (like GitHub, GitLab, or VS Code with the Mermaid extension).
2. Alternatively, you can copy the Mermaid code and paste it into the [Mermaid Live Editor](https://mermaid.live/).

### PlantUML Flowcharts

To view the PlantUML flowcharts:

1. Install PlantUML (see [PlantUML website](https://plantuml.com/starting) for instructions).
2. Use a PlantUML viewer or editor to open the `rwanda_cities_system_flowchart_plantuml.txt` file.
3. Alternatively, you can copy the PlantUML code and paste it into the [PlantUML Web Server](http://www.plantuml.com/plantuml/uml/).

## Flowchart Types

Both the Mermaid and PlantUML files contain the following types of diagrams:

1. **Main Program Flow** - Shows the overall flow of the program, including the menu system and all options.
2. **Class Structure** - Shows the structure of the RwandaCitiesSystem class with its attributes and methods.
3. **Data Flow Diagram** - Shows how data moves through the system.
4. **Function Relationships** - Shows how the different functions in the program interact with each other.

## Program Description

The Rwanda Cities System is a C++ program that allows users to:

- Add new cities (with validation for Rwandan district names)
- Add roads between cities
- Add budget information for roads
- Edit city names
- Search for cities by index
- Display cities, roads, and all recorded data

The program uses maps and matrices to store the data and provides a menu-driven interface for user interaction.