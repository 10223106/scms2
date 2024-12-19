#ifndef CIRCUITSIMULATOR_H
#define CIRCUITSIMULATOR_H

#include "olcPixelGameEngine.h"
#include "Menu.h"
#include "CircuitGui.h"
#include "Colors.h"
#include <vector>
#include <string>

class CircuitSimulator : public olc::PixelGameEngine {
public:
    CircuitSimulator();
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

private:
    enum class AppState {
        MENU,
        SIMULATION,
        VOLTAGE_DIVIDER,
        SERIES_PARALLEL_RESISTOR
    };

    AppState currentState;
    Menu menu;  // Using the Menu class for handling menu
    CircuitGui circuitGui;

    // Menu-related methods
    void InitializeMenu();
    void DrawMenuUI();
    void DrawMenu();
    void HandleMenuInput();

    // Simulation-related methods
    bool SimulationOnUserCreate();
    bool SimulationOnUserUpdate(float fElapsedTime);
    void HandleSimulationInput();
    void DrawSimulationUI();

    // Drawing methods for other modes
    void DrawVoltageDividerUI();
    void DrawSeriesParallelResistorUI();

    // Helper method to draw a box with a border and a filled area
    void DrawBox(int x, int y, int w, int h, olc::Pixel color); 
};

#endif // CIRCUITSIMULATOR_H
