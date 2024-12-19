#include "CircuitSimulator.h"
#include "Colors.h"

CircuitSimulator::CircuitSimulator() {
    sAppName = "SCMS - G27";
    currentState = AppState::MENU;
}

bool CircuitSimulator::OnUserCreate() {
    Clear(Colors::_darkBlue);

    if (currentState == AppState::MENU) {
        InitializeMenu();
    }
    else if (currentState == AppState::SIMULATION) {
        SimulationOnUserCreate();
    }
    else if (currentState == AppState::VOLTAGE_DIVIDER) {
        DrawVoltageDividerUI();
    }
    else if (currentState == AppState::SERIES_PARALLEL_RESISTOR) {
        DrawSeriesParallelResistorUI();
    }

    return true;
}

bool CircuitSimulator::OnUserUpdate(float fElapsedTime) {
    Clear(Colors::_darkBlue);

    // Switch on the currentState
    switch (currentState) {
    case AppState::MENU:
        // Draw menu UI and handle menu input
        DrawMenuUI();            // Draws the UI (background, header, etc.) for the menu
        menu.HandleInput(this);  // Handling menu input through Menu class
        menu.Draw(this);         // Drawing the menu using Menu class
         // Test key press directly in the menu
        if (GetKey(olc::Key::ENTER).bPressed) {
            std::cout << "ENTER key pressed in menu!" << std::endl;
        } 
        break;

    case AppState::SIMULATION:
        // Handle simulation state
        if (IsFocused()) {
            SimulationOnUserUpdate(fElapsedTime);  // Update simulation logic
        }

        // Check for ESC key to return to the menu
        if (GetKey(olc::Key::ESCAPE).bPressed) {
            currentState = AppState::MENU;
            OnUserCreate();  // Reset/initialize user settings
        }
        break;

    case AppState::VOLTAGE_DIVIDER:
        // Handle voltage divider UI and logic
        DrawVoltageDividerUI();  // Draw voltage divider UI
        if (GetKey(olc::Key::ESCAPE).bPressed) {
            currentState = AppState::MENU;
            OnUserCreate();  // Reset/initialize user settings
        }
        break;

    case AppState::SERIES_PARALLEL_RESISTOR:
        // Handle series-parallel resistor UI and logic
        DrawSeriesParallelResistorUI();  // Draw series-parallel resistor UI
        if (GetKey(olc::Key::ESCAPE).bPressed) {
            currentState = AppState::MENU;
            OnUserCreate();  // Reset/initialize user settings
        }
        break;

        // Default case can handle unexpected state values (optional)
    default:
        std::cerr << "Unknown state!" << std::endl;
        break;
    }

    return true;
}

void CircuitSimulator::InitializeMenu() {
    menu.AddOption("Start Simulation", { 30, 90 }, Colors::_pink);
    menu.AddOption("Voltage Divider", { 30, 130 }, Colors::_pink);
    menu.AddOption("Series/Parallel Resistor", { 30, 170 }, Colors::_pink);
    menu.AddOption("Exit", { 30, 210 }, Colors::_pink);
}
void CircuitSimulator::DrawBox(int x, int y, int w, int h, olc::Pixel color) {
    DrawRect(x, y, w, h, color); // DrawRect is a function from olc::PixelGameEngine to draw rectangles
}
void CircuitSimulator::DrawMenuUI() {
    // Drawing the header and the background for the menu
    DrawBox(10, 10, 780, 50, Colors::_neonBlue); // Header
    DrawString(20, 20, "SCMS Menu", Colors::_orange);

    DrawBox(10, 70, 780, 520, Colors::_brown); // Background for menu
}

void CircuitSimulator::DrawMenu() {
    menu.Draw(this);  // Drawing menu using Menu class (handles highlight and colors)
}

void CircuitSimulator::HandleMenuInput() {
    int selectedOption = menu.GetSelectedOption();  // Get selected menu option

    // Handle ENTER key press to select the menu option
    if (GetKey(olc::Key::ENTER).bPressed) {
        switch (selectedOption) {
        case 0:
            currentState = AppState::SIMULATION;
            break;
        case 1:
            currentState = AppState::VOLTAGE_DIVIDER;
            break;
        case 2:
            currentState = AppState::SERIES_PARALLEL_RESISTOR;
            break;
        case 3:
            exit(0); // Exit the application
            break;
        }
        OnUserCreate();  // Recreate the user interface after selection
    }
}

// Implement the simulation scene setup
bool CircuitSimulator::SimulationOnUserCreate() {
    circuitGui.drawTitleBar();        // Drawing the title bar of the simulation UI
    circuitGui.drawToolBar();         // Drawing the toolbar of the simulation UI
    circuitGui.drawBorders();         // Drawing the borders of the simulation area
    circuitGui.drawField();           // Drawing the main simulation field (e.g., where the circuit is drawn)

    DrawSimulationUI();               // Draw simulation-specific UI on top of CircuitGui components
    return true;
}

// Handle simulation-specific updates
bool CircuitSimulator::SimulationOnUserUpdate(float fElapsedTime) {
    HandleSimulationInput();

    if (GetKey(olc::Key::ESCAPE).bPressed) {
        currentState = AppState::MENU;
        OnUserCreate();
    }

    return true;
}

// Handle simulation-specific key input
void CircuitSimulator::HandleSimulationInput() {
    if (GetKey(olc::Key::UP).bPressed) {
        // Example: Navigate up in the simulation (if applicable)
    }

    if (GetKey(olc::Key::DOWN).bPressed) {
        // Example: Navigate down in the simulation (if applicable)
    }

    if (GetKey(olc::Key::ENTER).bPressed) {
        // Example: Enter/execute a specific simulation action
    }
}

// Drawing the simulation UI components
void CircuitSimulator::DrawSimulationUI() {
    // Calling CircuitGui's methods to draw the UI elements
    DrawBox(10, 10, 780, 50, Colors::_purple);  // Header for simulation
    DrawString(20, 20, "Simulation Running", Colors::_orange);

    DrawBox(10, 70, 780, 520, Colors::_darkBlue); // Main area for simulation
    DrawString(30, 90, "1. Add Resistor", Colors::_softGreen);
    DrawString(30, 110, "2. Add Voltage Source", Colors::_softOrange);
    DrawString(30, 130, "3. Simulate Circuit", Colors::_softGreen);

    // Additional UI elements specific to simulation can be drawn here.
}

// Drawing UI for Voltage Divider
void CircuitSimulator::DrawVoltageDividerUI() {
    DrawBox(10, 10, 780, 50, Colors::_neonBlue);
    DrawString(20, 20, "Voltage Divider", Colors::_orange);

    DrawBox(10, 70, 780, 520, Colors::_darkBlue);
    DrawString(30, 90, "Adjust voltage and resistors to calculate output", Colors::_softOrange);
}

// Drawing UI for Series/Parallel Resistor
void CircuitSimulator::DrawSeriesParallelResistorUI() {
    DrawBox(10, 10, 780, 50, Colors::_neonBlue);
    DrawString(20, 20, "Series/Parallel Resistor", Colors::_orange);

    DrawBox(10, 70, 780, 520, Colors::_darkBlue);
    DrawString(30, 90, "Select resistor configuration and enter values", Colors::_softOrange);
}