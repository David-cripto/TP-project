#include <iostream>
#include <vector>
#include <cmath>

using std::vector;

const int X = 0, Y = 0;
const vector <vector<int>> PATH = {{76,  80},
                                   {138, 56},
                                   {193, 80},
                                   {683, 79},
                                   {756, 152},
                                   {716, 241},
                                   {505, 265},
                                   {452, 309},
                                   {450, 555},
                                   {450, 600}};

const int troll_vel = 5, troll_health = 100;
const int ogre_vel = 2, ogre_health = 200;
const int goblin_vel = 8, goblin_health = 50;
const int wave1_count_goblins = 10, wave1_count_ogres = 5, wave1_count_trolls = 8, wave2_count_goblins = 15, wave2_count_ogres = 12, wave2_count_trolls = 18;
const int price_archer = 200, sell_price_archer = 150, damage_archer = 50, radius_archer = 10;
const int price_gun = 300, sell_price_gun = 200, damage_gun = 150, radius_gun = 8;
const int archer_button_x = 100, archer_button_y = 100;
const int gun_button_x = 100, gun_button_y = 150;

class Enemy {
protected:
    int health;
    int vel;
    int x;
    int y;
    bool live;
    vector <vector<int>> path;
    int path_pos;
public:

    virtual void move() = 0;

    virtual void get_damage(int damage) = 0;
};

class Troll : public Enemy {
public:
    Troll() {
        x = X;
        y = Y;
        live = true;
        vel = troll_vel;
        health = troll_health;
        path_pos = 0;
        path = PATH;
    }

    void move() override {
        if (this->x == this->path[this->path_pos][0] && this->y == this->path[this->path_pos][1]) {
            this->path_pos++;
        }
        //speed projection on the X axis
        this->x += (this->path[this->path_pos][0] - this->x) /
                   sqrt(pow((this->path[this->path_pos][0] - this->x), 2) +
                        pow((this->path[this->path_pos][1] - this->y), 2));
        //speed projection on the Y axis
        this->y += (this->path[this->path_pos][1] - this->y) /
                   sqrt(pow((this->path[this->path_pos][0] - this->x), 2) +
                        pow((this->path[this->path_pos][1] - this->y), 2));
    }

    void get_damage(int damage) override {
        this->health -= damage;
        if (this->health <= 0) {
            this->live = false;
        }
    }

};

class Ogre : public Enemy {
public:
    Ogre() {
        x = X;
        y = Y;
        live = true;
        vel = ogre_vel;
        health = ogre_health;
        path_pos = 0;
        path = PATH;
    }

    void move() override {
        if (this->x == this->path[this->path_pos][0] && this->y == this->path[this->path_pos][1]) {
            this->path_pos++;
        }
        //speed projection on the X axis
        this->x += (this->path[this->path_pos][0] - this->x) /
                   sqrt(pow((this->path[this->path_pos][0] - this->x), 2) +
                        pow((this->path[this->path_pos][1] - this->y), 2));
        //speed projection on the Y axis
        this->y += (this->path[this->path_pos][1] - this->y) /
                   sqrt(pow((this->path[this->path_pos][0] - this->x), 2) +
                        pow((this->path[this->path_pos][1] - this->y), 2));
    }

    void get_damage(int damage) override {
        this->health -= damage;
        if (this->health <= 0) {
            this->live = false;
        }
    }

};

class Goblin : public Enemy {
public:
    Goblin() {
        x = X;
        y = Y;
        live = true;
        vel = goblin_vel;
        health = goblin_health;
        path_pos = 0;
        path = PATH;
    }

    void move() override {
        if (this->x == this->path[this->path_pos][0] && this->y == this->path[this->path_pos][1]) {
            this->path_pos++;
        }
        //speed projection on the X axis
        this->x += (this->path[this->path_pos][0] - this->x) /
                   sqrt(pow((this->path[this->path_pos][0] - this->x), 2) +
                        pow((this->path[this->path_pos][1] - this->y), 2));
        //speed projection on the Y axis
        this->y += (this->path[this->path_pos][1] - this->y) /
                   sqrt(pow((this->path[this->path_pos][0] - this->x), 2) +
                        pow((this->path[this->path_pos][1] - this->y), 2));
    }

    void get_damage(int damage) override {
        this->health -= damage;
        if (this->health <= 0) {
            this->live = false;
        }
    }

};

class Wave {
private:
    vector<Troll *> trolls;
    vector<Ogre *> ogres;
    vector<Goblin *> goblins;
public:
    void add_trolls(vector<Troll *> temp) {
        for (auto tr : temp) {
            trolls.push_back(tr);
        }
    }

    void add_ogres(vector<Ogre *> temp) {
        for (auto og : temp) {
            ogres.push_back(og);
        }
    }

    void add_goblins(vector<Goblin *> temp) {
        for (auto go : temp) {
            goblins.push_back(go);
        }
    }
};

class WaveFactory {
public:
    virtual vector<Troll *> create_trolls() = 0;

    virtual vector<Ogre *> create_ogres() = 0;

    virtual vector<Goblin *> create_goblins() = 0;
};

class Wave1Factory : public WaveFactory {
public:
    vector<Troll *> create_trolls() override {
        vector < Troll * > temp;
        for (int i = 0; i < wave1_count_trolls; ++i) {
            temp.push_back(new Troll());
        }
        return temp;
    }

    vector<Ogre *> create_ogres() override {
        vector < Ogre * > temp;
        for (int i = 0; i < wave1_count_ogres; ++i) {
            temp.push_back(new Ogre());
        }
        return temp;
    }

    vector<Goblin *> create_goblins() override {
        vector < Goblin * > temp;
        for (int i = 0; i < wave1_count_goblins; ++i) {
            temp.push_back(new Goblin());
        }
        return temp;
    }
};

class Wave2Factory : public WaveFactory {
public:
    vector<Troll *> create_trolls() override {
        vector < Troll * > temp;
        for (int i = 0; i < wave2_count_trolls; ++i) {
            temp.push_back(new Troll());
        }
        return temp;
    }

    vector<Ogre *> create_ogres() override {
        vector < Ogre * > temp;
        for (int i = 0; i < wave2_count_ogres; ++i) {
            temp.push_back(new Ogre());
        }
        return temp;
    }

    vector<Goblin *> create_goblins() override {
        vector < Goblin * > temp;
        for (int i = 0; i < wave2_count_goblins; ++i) {
            temp.push_back(new Goblin());
        }
        return temp;
    }
};

class Tower {
protected:
    int x;
    int y;
    int price;
    int sell_price;
    int damage;
    int radius_damage;
    bool fire;
public:
    virtual int sell_tower() = 0;

    virtual void attack(Enemy *temp) = 0;
};

class ArcherTower : public Tower {
public:
    ArcherTower(int x, int y) {
        this->x = x;
        this->y = y;
        this->fire = false;
        this->damage = damage_archer;
        this->price = price_archer;
        this->sell_price = sell_price_archer;
        this->radius_damage = radius_archer;
    }

    int sell_tower() override {
        return sell_price;
    }

    void attack(Enemy *temp) override {}
};

class Gun : public Tower {
public:
    Gun(int x, int y) {
        this->x = x;
        this->y = y;
        this->fire = false;
        this->damage = damage_gun;
        this->price = price_gun;
        this->sell_price = sell_price_gun;
        this->radius_damage = radius_gun;
    }

    int sell_tower() override {
        return sell_price;
    }

    void attack(Enemy *temp) override {}
};

class Button {
protected:
    int x;
    int y;
    bool clicked;
public:
    virtual void click(int mouse_x, int mouse_y) = 0;
};

class ArcherButton : public Button {
public:
    ArcherButton() {
        this->x = archer_button_x;
        this->y = archer_button_y;
        this->clicked = false;
    }

    void click(int mouse_x, int mouse_y) override {
        if (mouse_x == this->x && mouse_y == this->y) {
            this->clicked = true;
        }
    }
};

class GunButton : public Button {
public:
    GunButton() {
        this->x = gun_button_x;
        this->y = gun_button_y;
        this->clicked = false;
    }

    void click(int mouse_x, int mouse_y) override {
        if (mouse_x == this->x && mouse_y == this->y) {
            this->clicked = true;
        }
    }
};

class AbstractTowersFactory {
public:
    virtual Button *createButton() = 0;

    virtual Tower *createTower(int x, int y) = 0;
};

class ArcherFactory : public AbstractTowersFactory {
public:
    Button *createButton() override {
        return new ArcherButton();
    }

    Tower *createTower(int x, int y) override {
        return new ArcherTower(x, y);
    }
};

class GunFactory : public AbstractTowersFactory {
public:
    Button *createButton() override {
        return new GunButton();
    }

    Tower *createTower(int x, int y) override {
        return new Gun(x, y);
    }
};

class Towers {
private:
    vector<Tower *> towers;
    vector<Button *> buttons;
public:
    void add_tower(Tower *tower) {
        towers.push_back(tower);
    }

    void add_button(Button *button) {
        buttons.push_back(button);
    }
};


class Game {
public:
    Wave *create_wave(WaveFactory &factory) {
        Wave *new_wave = new Wave();
        new_wave->add_goblins(factory.create_goblins());
        new_wave->add_ogres(factory.create_ogres());
        new_wave->add_trolls(factory.create_trolls());
        return new_wave;
    }

    Towers *create_tower(AbstractTowersFactory &factory, int x = -1, int y = -1) {
        Towers *new_towers = new Towers();
        if (x == -1 && y == -1) {
            new_towers->add_button(factory.createButton());
        } else {
            new_towers->add_tower(factory.createTower(x, y));
        }
        return new_towers;
    }

};

int main() {
    Game game;
    Wave1Factory wave1_factory;
    game.create_wave(wave1_factory);
    ArcherFactory archer_factory;
    game.create_tower(archer_factory);
    GunFactory gun_factory;
    game.create_tower(gun_factory);
    Wave2Factory wave2_factory;
    game.create_wave(wave2_factory);
    std::cout << "Done!";
    return 0;
}