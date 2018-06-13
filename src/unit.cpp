#include <cstdlib>
#include "unit.h"

sf::Texture Unit::ar;
sf::Texture Unit::wa;
sf::Texture Unit::kn;
sf::Texture Unit::wi;
sf::Texture Unit::ca;
sf::Texture Unit::ar2;
sf::Texture Unit::wa2;
sf::Texture Unit::kn2;
sf::Texture Unit::wi2;
sf::Texture Unit::ca2;

void Unit::attack(Unit ***grid, int N, int xx, int yy, int x, int y)
{
    grid = grid;
    N = x = y = xx = yy;
}

void Archer::attack(Unit ***grid, int N, int xx, int yy, int x, int y)
{
    if (abs(x - xx) + abs(y - yy) > 10)
        return;
    if (grid[y][x] == nullptr)
        return;
    if (dynamic_cast<Warrior*>(grid[y][x]) != nullptr && (rand() % 10000 > 1000))
        grid[y][x]->hp -= (rand() % 20) + 40;
    if (dynamic_cast<Archer*>(grid[y][x]) != nullptr)
        grid[y][x]->hp -= (rand() % 20) + 10;
    if (dynamic_cast<Knight*>(grid[y][x]) != nullptr)
        grid[y][x]->hp -= (rand() % 20) + 40;
    if (dynamic_cast<Wizard*>(grid[y][x]) != nullptr)
        grid[y][x]->hp -= (rand() % 20) + 10;
    if (dynamic_cast<Cavalier*>(grid[y][x]) != nullptr)
        grid[y][x]->hp -= (rand() % 20) + 20;

}

void Warrior::attack(Unit ***grid, int N, int xx, int yy, int x, int y)
{
    if (grid[y][x] == nullptr)
        return;
    if (y != yy)
        return ;
    int dif = x > xx ? 1 : -1;
    int t = 0;
    for (int i = xx + dif; abs(i - x) > 0; i += dif, t++) {
        if (grid[y][i] != nullptr || t >= 1) {
            std::swap(grid[y][i - dif], grid[y][xx]);
            xx = i - dif;
            break;
        }
        if (abs(i - x) == 1) {
            std::swap(grid[y][i], grid[y][xx]);
            xx = i;
            break;
        }

    }
    if (grid[y][xx + dif] == nullptr)
        return ;
    if (grid[y][xx + dif]->team == !grid[y][xx]->team) {
        if (dynamic_cast<Warrior*>(grid[y][x]) != nullptr && (rand() % 10000 > 1000))
            grid[y][x]->hp -= (rand() % 60) + 40;
        if (dynamic_cast<Archer*>(grid[y][x]) != nullptr)
            grid[y][x]->hp -= (rand() % 60) + 10;
        if (dynamic_cast<Knight*>(grid[y][x]) != nullptr)
            grid[y][x]->hp -= (rand() % 60) + 40;
        if (dynamic_cast<Wizard*>(grid[y][x]) != nullptr)
            grid[y][x]->hp -= (rand() % 60) + 10;
        if (dynamic_cast<Cavalier*>(grid[y][x]) != nullptr)
            grid[y][x]->hp -= (rand() % 60) + 20;
    }
}

void Knight::attack(Unit ***grid, int N, int xx, int yy, int x, int y)
{
    if (grid[y][x] == nullptr)
        return;
    if (y != yy)
        return ;
    int dif = x > xx ? 1 : -1;
    int t = 0;
    for (int i = xx + dif; abs(i - x) > 0; i += dif, t++) {
        if (grid[y][i] != nullptr || t >= 1) {
            std::swap(grid[y][i - dif], grid[y][xx]);
            xx = i - dif;
            break;
        }
        if (abs(i - x) == 1) {
            std::swap(grid[y][i], grid[y][xx]);
            xx = i;
            break;
        }

    }
    if (grid[y][xx + dif] == nullptr)
        return ;
    x=xx+dif;
    if (grid[y][xx + dif]->team == !grid[y][xx]->team) {
        if (dynamic_cast<Warrior*>(grid[y][x]) != nullptr && (rand() % 10000 > 1000))
            grid[y][x]->hp -= (rand() % 90) + 40;
        if (dynamic_cast<Archer*>(grid[y][x]) != nullptr)
            grid[y][x]->hp -= (rand() % 90) + 10;
        if (dynamic_cast<Knight*>(grid[y][x]) != nullptr)
            grid[y][x]->hp -= (rand() % 90) + 40;
        if (dynamic_cast<Wizard*>(grid[y][x]) != nullptr)
            grid[y][x]->hp -= (rand() % 90) + 10;
        if (dynamic_cast<Cavalier*>(grid[y][x]) != nullptr)
            grid[y][x]->hp -= (rand() % 90) + 20;
    }

}

void Wizard::attack(Unit ***grid, int N, int xx, int yy, int x, int y)
{
    if (abs(x - xx) + abs(y - yy) > 10)
        return;
    if (grid[y][x] == nullptr)
        return;

    if (grid[y][x]!=nullptr){
        if (dynamic_cast<Warrior*>(grid[y][x]) != nullptr && (rand() % 10000 > 1000))
            grid[y][x]->hp -= (rand() % 80) + 40;
        if (dynamic_cast<Archer*>(grid[y][x]) != nullptr)
            grid[y][x]->hp -= (rand() % 80) + 10;
        if (dynamic_cast<Knight*>(grid[y][x]) != nullptr)
            grid[y][x]->hp -= (rand() % 80) + 40;
        if (dynamic_cast<Wizard*>(grid[y][x]) != nullptr)
            grid[y][x]->hp -= (rand() % 10) + 10;
        if (dynamic_cast<Cavalier*>(grid[y][x]) != nullptr)
            grid[y][x]->hp -= (rand() % 80) + 20;
    }
    if (y+1 < N && grid[y+1][x] != nullptr && grid[y+1][x]->team == !grid[yy][xx]->team) {
        if (dynamic_cast<Warrior*>(grid[y+1][x]) != nullptr && (rand() % 10000 > 1000))
            grid[y+1][x]->hp -= (rand() % 40) + 20;
        if (dynamic_cast<Archer*>(grid[y+1][x]) != nullptr)
            grid[y+1][x]->hp -= (rand() % 40) + 5;
        if (dynamic_cast<Knight*>(grid[y+1][x]) != nullptr)
            grid[y+1][x]->hp -= (rand() % 40) + 20;
        if (dynamic_cast<Wizard*>(grid[y+1][x]) != nullptr)
            grid[y+1][x]->hp -= (rand() % 5) + 5;
        if (dynamic_cast<Cavalier*>(grid[y+1][x]) != nullptr)
            grid[y+1][x]->hp -= (rand() % 40) + 10;

    }
    if (x+1 < N && grid[y][x+1] != nullptr && grid[y][x+1]->team == !grid[yy][xx]->team) {
        if (dynamic_cast<Warrior*>(grid[y][x+1]) != nullptr && (rand() % 10000 > 1000))
            grid[y][x+1]->hp -= (rand() % 40) + 20;
        if (dynamic_cast<Archer*>(grid[y][x+1]) != nullptr)
            grid[y][x+1]->hp -= (rand() % 40) + 5;
        if (dynamic_cast<Knight*>(grid[y][x+1]) != nullptr)
            grid[y][x+1]->hp -= (rand() % 40) + 20;
        if (dynamic_cast<Wizard*>(grid[y][x+1]) != nullptr)
            grid[y][x+1]->hp -= (rand() % 5) + 5;
        if (dynamic_cast<Cavalier*>(grid[y][x+1]) != nullptr)
            grid[y][x+1]->hp -= (rand() % 40) + 10;

    }
    if (y-1 > 0 && grid[y-1][x] != nullptr && grid[y-1][x]->team == !grid[yy][xx]->team) {
        if (dynamic_cast<Warrior*>(grid[y-1][x]) != nullptr && (rand() % 10000 > 1000))
            grid[y-1][x]->hp -= (rand() % 40) + 20;
        if (dynamic_cast<Archer*>(grid[y-1][x]) != nullptr)
            grid[y-1][x]->hp -= (rand() % 40) + 5;
        if (dynamic_cast<Knight*>(grid[y-1][x]) != nullptr)
            grid[y-1][x]->hp -= (rand() % 40) + 20;
        if (dynamic_cast<Wizard*>(grid[y-1][x]) != nullptr)
            grid[y-1][x]->hp -= (rand() % 5) + 5;
        if (dynamic_cast<Cavalier*>(grid[y-1][x]) != nullptr)
            grid[y-1][x]->hp -= (rand() % 40) + 10;
    }
    if (x-1 > 0 && grid[y][x-1] != nullptr && grid[y][x-1]->team == !grid[yy][xx]->team) {
        if (dynamic_cast<Warrior*>(grid[y][x-1]) != nullptr && (rand() % 10000 > 1000))
            grid[y][x-1]->hp -= (rand() % 40) + 20;
        if (dynamic_cast<Archer*>(grid[y][x-1]) != nullptr)
            grid[y][x-1]->hp -= (rand() % 40) + 5;
        if (dynamic_cast<Knight*>(grid[y][x-1]) != nullptr)
            grid[y][x-1]->hp -= (rand() % 40) + 20;
        if (dynamic_cast<Wizard*>(grid[y][x-1]) != nullptr)
            grid[y][x-1]->hp -= (rand() % 5) + 5;
        if (dynamic_cast<Cavalier*>(grid[y][x-1]) != nullptr)
            grid[y][x-1]->hp -= (rand() % 40) + 10;
    }

}

void Cavalier::attack(Unit ***grid, int N, int xx, int yy, int x, int y)
{
    if (grid[y][x] == nullptr)
        return;
    if (y != yy)
        return ;
    int dif = x > xx ? 1 : -1;
    int t = 1;
    for (int i = xx + dif; abs(i - x) > 0; i += dif, t++) {
        if (grid[y][i] != nullptr) {
            std::swap(grid[y][i - dif], grid[y][xx]);
            xx = i - dif;
            break;
        }
        if (abs(i - x) == 1) {
            std::swap(grid[y][i], grid[y][xx]);
            xx = i;
            break;
        }
    }
    if (grid[y][xx + dif] == nullptr)
        return ;
    x=xx+dif;
    if (grid[y][xx + dif]->team == !grid[y][xx]->team) {
        if (dynamic_cast<Warrior*>(grid[y][x]) != nullptr && (rand() % 10000 > 1000))
            grid[y][x]->hp -= (rand() % 30*t) + 40;
        if (dynamic_cast<Archer*>(grid[y][x]) != nullptr)
            grid[y][x]->hp -= (rand() % 30*t) + 10;
        if (dynamic_cast<Knight*>(grid[y][x]) != nullptr)
            grid[y][x]->hp -= (rand() % 30*t) + 40;
        if (dynamic_cast<Wizard*>(grid[y][x]) != nullptr)
            grid[y][x]->hp -= (rand() % 30*t) + 10;
        if (dynamic_cast<Cavalier*>(grid[y][x]) != nullptr)
            grid[y][x]->hp -= (rand() % 30*t) + 20;
    }

}
