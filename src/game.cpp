#include <fstream>
#include "game.h"

int Game::instance_ = 0;

Game::Game(int w, int h) : window(sf::VideoMode(w, h), "LLP3"), loaded(false)
{
    if (instance_)
        throw std::logic_error("Only one instance of the class Game allowed");
    ++instance_;
    window.setVerticalSyncEnabled(true);

}

void Game::menu()
{
    Unit::loadTextures();
    if (!font.loadFromFile("ttf/ComicSans.ttf"))
        throw Game::fileNotFoundException();
    sf::Texture texture;
    if (!texture.loadFromFile("gfx/menu.jpg"))
        throw Game::fileNotFoundException();
    sf::Sprite background(texture);
    sf::Music music;
    if (!music.openFromFile("sfx/menu.flac"))
        throw Game::fileNotFoundException();

    music.play();
    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
            {
                sf::Vector2i m = sf::Mouse::getPosition(window);
                if (m.x > 300 && m.y > 400 && m.x < 500 && m.y < 480) {
                    window.close();
                }
                if (m.x > 270 && m.y > 280 && m.x < 530 && m.y < 360) {
                    music.stop();
                    try {
                        load();
                    }
                    catch (Game::fileNotFoundException& e) {
                        sf::Text error("Couldn't load save, starting new game", font);
                        error.setPosition(150, 270);
                        error.setFillColor(sf::Color(255, 0, 0, 255));
                        window.clear();
                        window.draw(error);
                        window.display();
                        sf::sleep(sf::milliseconds(1000));
                    }
                    catch (Game::invalidSaveFile& e) {
                        sf::Text error("Corrupt save file, starting new game", font);
                        error.setPosition(150, 270);
                        error.setFillColor(sf::Color(255, 0, 0, 255));
                        window.clear();
                        window.draw(error);
                        window.display();
                        sf::sleep(sf::milliseconds(1000));
                    }
                    return;
                }
                if (m.x > 250 && m.y > 160 && m.x < 550 && m.y < 240) {
                    music.stop();
                    return;
                }
                break;
            }

            default:
                break;
            }
        }
        window.clear();
        window.draw(background);
        window.display();
    }
}

void Game::load()
{
    std::ifstream f("save1.txt");
    if (!f.is_open())
        throw Game::fileNotFoundException();
    f >> N;
    if (f.fail())
        throw Game::invalidSaveFile();
    f >> player;
    if (f.fail())
        throw Game::invalidSaveFile();
    selected = 0;
    grid = new Unit**[N];
    for (int i = 0; i < N; ++i)
        grid[i] = new Unit*[N];
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < N; ++x) {
            Unit *t;
            std::string type;
            f >> type;
            if (f.fail())
                throw Game::invalidSaveFile();
            int hp;
            f >> hp;
            if (f.fail())
                throw Game::invalidSaveFile();
            int team;
            f >> team;
            if (f.fail())
                throw Game::invalidSaveFile();
            if (type == "Archer") {
                t = new Archer(hp, team);
            } else if (type == "Warrior") {
                t = new Warrior(hp, team);
            } else if (type == "Knight") {
                t = new Knight(hp, team);
            } else if (type == "Wizard") {
                t = new Wizard(hp, team);
            } else if (type == "Cavalier") {
                t = new Cavalier(hp, team);
            } else if (type == "None") {
                t = nullptr;
            } else
                throw Game::invalidSaveFile();

            grid[y][x] = t;

        }

    }

    f.close();
    loaded = true;
}

void Game::save()
{
    std::ofstream f("save1.txt");
    if (!f.is_open())
        throw Game::cannotSave();
    f << N;
    if (f.fail())
        throw Game::cannotSave();
    f << "\n";
    f << player;
    if (f.fail())
        throw Game::cannotSave();
    f << "\n";
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < N; ++x) {
            if (grid[y][x] == nullptr) {
                f << "None\n0\n0\n";
                continue;
            }
            else if (dynamic_cast<Archer*>(grid[y][x]) != nullptr)
                f << "Archer\n";
            else if (dynamic_cast<Warrior*>(grid[y][x]) != nullptr)
                f << "Warrior\n";
            else if (dynamic_cast<Knight*>(grid[y][x]) != nullptr)
                f << "Knight\n";
            else if (dynamic_cast<Wizard*>(grid[y][x]) != nullptr)
                f << "Wizard\n";
            else if (dynamic_cast<Cavalier*>(grid[y][x]) != nullptr)
                f << "Cavalier\n";
            if (f.fail())
                throw Game::cannotSave();
            f << grid[y][x]->hp;
            if (f.fail())
                throw Game::cannotSave();
            f << "\n";
            f << grid[y][x]->team;
            if (f.fail())
                throw Game::cannotSave();
            f << "\n";
        }
    }

    f.close();
}

void Game::mainGame()
{
    if (!loaded)
    {
        N = 8;
        player = 0;
        selected = 0;
        grid = new Unit**[N];
        for (int i = 0; i < N; ++i)
            grid[i] = new Unit*[N];
        for (int y = 0; y < N; ++y) {
            grid[y][0] = new Archer(20, 0);
            grid[y][7] = new Archer(20, 1);
            grid[y][2] = grid[y][3] = grid[y][4] = grid[y][5] = nullptr;
        }
        grid[0][1] = new Warrior(40, 0);
        grid[0][6] = new Warrior(40, 1);
        grid[7][1] = nullptr; grid[7][2] = new Warrior(80, 0);
        grid[7][6] = nullptr; grid[7][5] = new Warrior(80, 1);
        grid[1][1] = new Knight(80, 0);
        grid[1][6] = new Knight(80, 1);
        grid[6][1] = new Knight(80, 0);
        grid[6][6] = new Knight(80, 1);
        grid[2][1] = new Wizard(10, 0);
        grid[2][6] = new Wizard(10, 1);
        grid[5][1] = new Wizard(10, 0);
        grid[5][6] = new Wizard(10, 1);
        grid[3][1] = new Cavalier(60, 0);
        grid[3][6] = new Cavalier(60, 1);
        grid[4][1] = new Cavalier(60, 0);
        grid[4][6] = new Cavalier(60, 1);
    }

    sf::Music music;
    if (!music.openFromFile("sfx/maingame.flac"))
        throw Game::fileNotFoundException();
    music.play();
    window.clear();
    window.display();
    int x1, y1;
    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
            {
                sf::Vector2i m = sf::Mouse::getPosition(window);
                int xx = -1, yy = -1, t = player;
                if (selected)
                    t = !t;
                for (int y = N - 1; y >= 0; --y) {
                    for (int x = N - 1; x >= 0; --x) {
                        if (grid[y][x] == nullptr)
                            continue;
                        if (grid[y][x]->team != t)
                            continue;
                        if (grid[y][x]->getSprite().getGlobalBounds().contains(sf::Vector2f(m.x, m.y))) {
                            xx = x;
                            yy = y;
                        }
                        if (xx != -1)
                            break;
                    }
                    if (xx != -1)
                        break;
                }
                if (xx != -1) {
                    if (!selected) {
                        x1 = xx;
                        y1 = yy;
                        selected = true;
                    } else {
                        grid[y1][x1]->attack(grid, N, x1, y1, xx, yy);
                        player = !player;
                        selected = false;
                        if (grid[y1][x1] != nullptr) {
                            if (grid[y1][x1]->team)
                                grid[y1][x1]->getSprite().setColor(sf::Color(255, 190, 190, 255));
                            else
                                grid[y1][x1]->getSprite().setColor(sf::Color(190, 190, 255, 255));
                        }
                    }
                }
                break;
            }

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::S) {
                    try {
                        save();
                    } catch (std::exception& e) {
                        handleException(e);
                    }
                }

                break;
            default:
                break;
            }
        }

        if (player == 0)
            window.clear(sf::Color(0, 0, 128, 255));
        else
            window.clear(sf::Color(128, 0, 0, 255));
        for (int y = 0; y < N; ++y)
            for (int x = 0; x < N; ++x) {
                if (grid[y][x] == nullptr)
                    continue;
                if (grid[y][x]->hp <= 0) {
                    delete grid[y][x];
                    grid[y][x] = nullptr;
                    continue;
                }
                grid[y][x]->getSprite().setPosition(x * (800.0 / N), y * (600.0 / N) - 50);
                if (x1 == x && y1 == y && selected)
                    grid[y][x]->getSprite().setColor(sf::Color(255, 255, 255, 255));
                window.draw(grid[y][x]->getSprite());
            }
        int sum0 = 0;
        for (int y = 0; y < N; ++y)
            for (int x = 0; x < N; ++x)
                if (grid[y][x] != nullptr && grid[y][x]->team == 0)
                    ++sum0;
        int sum1 = 0;
        for (int y = 0; y < N; ++y)
            for (int x = 0; x < N; ++x)
                if (grid[y][x] != nullptr && grid[y][x]->team == 1)
                    ++sum1;

        if (sum1 == 0) {
            music.stop();
            window.clear(sf::Color(0, 0, 128, 255));
            window.display();
            sf::Music winner;
            winner.openFromFile("sfx/winner.flac");
            winner.play();
            sf::sleep(sf::milliseconds(4000));
            window.close();
            break;
        }
        if (sum0 == 0) {
            music.stop();
            window.clear(sf::Color(128, 0, 0, 255));
            window.display();
            sf::Music winner;
            winner.openFromFile("sfx/lost.flac");
            winner.play();
            sf::sleep(sf::milliseconds(4000));
            window.close();
        }

        window.display();
    }
}

Game::~Game()
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            delete grid[i][j];
        delete [] grid[i];
    }
    delete [] grid;
}


void Game::handleException(std::exception& e)
{
    e.what();
    sf::Music ex;
    if (!ex.openFromFile("sfx/exception.flac"))
        return;
    ex.play();
    sf::sleep(sf::milliseconds(2500));
}
