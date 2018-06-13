#pragma once
#include <exception>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "unit.h"

class Game
{
private:
    static int instance_;
    sf::RenderWindow window;
    sf::Font font;
    Unit*** grid;
    int N;
    bool loaded;
    bool player;
    bool selected;
public:
    Game(int = 800, int = 600);
    ~Game();
    void load();
    void save();
    void menu();
    void mainGame();
    void handleException(std::exception& e);
    struct fileNotFoundException;
    struct invalidSaveFile;
    struct cannotSave;
    friend class Unit;
};

struct Game::fileNotFoundException : std::exception
{
    const char* what() const noexcept
    {
        return "File not found\n";
    }
};

struct Game::invalidSaveFile : std::exception
{
    const char* what() const noexcept
    {
        return "Corrupt save file\n";
    }
};

struct Game::cannotSave : std::exception
{
    const char* what() const noexcept
    {
        return "Error writing to a save file\n";
    }
};
