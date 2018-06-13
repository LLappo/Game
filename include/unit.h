#pragma once
#include <SFML/Graphics.hpp>

class Unit
{
protected:
    sf::Sprite sprite;
public:
    Unit(int h, int t) : hp(h), team(t) {
        if (t) {
            sprite.setColor(sf::Color(255, 190, 190, 255));
        } else
            sprite.setColor(sf::Color(190, 190, 255, 255));
    }
    virtual ~Unit() {}
    virtual void attack(Unit ***grid, int N, int xx, int yy, int x, int y);
    sf::Sprite& getSprite() {return sprite;}
    static sf::Texture ar, wa, kn, wi, ca, ar2, wa2, kn2, wi2, ca2;
    static void loadTextures() {
        Unit::ar.loadFromFile("gfx/archer.png");
        Unit::wa.loadFromFile("gfx/warrior.png");
        Unit::kn.loadFromFile("gfx/knight.png");
        Unit::wi.loadFromFile("gfx/wizard.png");
        Unit::ca.loadFromFile("gfx/cavalier.png");
        Unit::ar2.loadFromFile("gfx/archer2.png");
        Unit::wa2.loadFromFile("gfx/warrior2.png");
        Unit::kn2.loadFromFile("gfx/knight2.png");
        Unit::wi2.loadFromFile("gfx/wizard2.png");
        Unit::ca2.loadFromFile("gfx/cavalier2.png");
    }
    int hp;
    int team;
};

class Archer: public Unit
{
public:
    Archer(int h, int t) : Unit(h, t) {sprite.setTexture(t?ar2:ar);}
    ~Archer() {};
    void attack(Unit ***grid, int N, int xx, int yy, int x, int y);
};

class Warrior: public Unit
{

public:
    Warrior(int h, int t) : Unit(h, t) {sprite.setTexture(t?wa2:wa);}
    ~Warrior() {};
    void attack(Unit ***grid, int N, int xx, int yy, int x, int y);
};

class Knight: public Unit
{

public:
    Knight(int h, int t) : Unit(h, t) {sprite.setTexture(t?kn2:kn);}
    ~Knight() {};
    void attack(Unit ***grid, int N, int xx, int yy, int x, int y);
};

class Wizard: public Unit
{

public:
    Wizard(int h, int t) : Unit(h, t) {sprite.setTexture(t?wi2:wi);}
    ~Wizard() {};
    void attack(Unit ***grid, int N, int xx, int yy, int x, int y);
};

class Cavalier: public Unit
{

public:
    Cavalier(int h, int t) : Unit(h, t) {sprite.setTexture(t?ca2:ca);}
    ~Cavalier() {};
    void attack(Unit ***grid, int N, int xx, int yy, int x, int y);
};
