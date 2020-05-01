#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int width = 800;
const int length = 600;
const int archer_damage = 10, archer_radius = 50;
const int gun_damage = 15, gun_radius = 30;
const int wave1_count_goblin = 3, wave1_count_ogre = 4;
const int wave2_count_goblin = 5, wave2_count_ogre = 5;
const int begin_x = 0, begin_y = 0;
const int health_goblin = 20, speed_goblin = 20;
const int health_ogre = 30, speed_ogre = 15;
const vector<vector<int>> road = { {76,  80},
                                   {138, 56},
                                   {193, 80},
                                   {683, 79},
                                   {756, 152},
                                   {716, 241},
                                   {505, 265},
                                   {452, 309},
                                   {450, 555},
                                   {450, 600} };
const vector<vector<int>> tree = { {5,  30},
                                   {130, 560},
                                   {193, 8},
                                   {798, 54} };
const vector<vector<int>> grass = { {57,  84},
                                    {147, 534},
                                    {193, 187},
                                    {798, 540} };

class InterfaceObjects;
class Button;
class GunButton;
class ArcherButton;
class Enemy;
class Ogre;
class Goblin;
class Road;

class InterfaceObjects {
public:
    void draw() {

    }
};

class InterfaceWave :public InterfaceObjects {
public:
    virtual void run(vector<Road*> road) = 0;
    virtual void draw() = 0;
};

class Objects :public InterfaceObjects {
protected:
    int x, y;
public:
    virtual void draw() = 0;
};

class Grass :public Objects {
public:
    Grass(int x, int y) {
        this->x = x;
        this->y = y;
    }
    void draw() {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < length; ++j) {
                if (i == x && j == y) {
                    cout << "H";
                }
                else {
                    cout << " ";
                }
            }
        }
    }
};

class Road :public Objects {
public:
    Road(int x, int y) {
        this->x = x;
        this->y = y;
    }
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    void draw() {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < length; ++j) {
                if (i == x && j == y) {
                    cout << "O";
                }
                else {
                    cout << " ";
                }
            }
        }
    }
};

class Tree :public Objects {
public:
    Tree(int x, int y) {
        this->x = x;
        this->y = y;
    }
    void draw() {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < length; ++j) {
                if (i == x && j == y) {
                    cout << "Y";
                }
                else {
                    cout << " ";
                }
            }
        }
    }
};

class Enemy :public InterfaceWave {
public:
    virtual void get_damage(int damage) = 0;
    virtual void run(vector<Road*> road) = 0;
    virtual void draw() = 0;
};

class Goblin :public Enemy {
private:
    int x, y;
    int health;
    int speed;
    int position;
public:
    Goblin() {
        x = begin_x, y = begin_y;
        health = health_goblin;
        speed = speed_goblin;
        position = 0;
    }
    void get_damage(int damage) override {
        health -= damage;
    }
    void run(vector<Road*> road) override {
        if (position == road.size() - 1) {
            return;
        }
        int next_x = road[position + 1]->getX();
        int next_y = road[position + 1]->getY();
        if (next_x == x && next_y == y) {
            position++;
            int next_x = road[position + 1]->getX();
            int next_y = road[position + 1]->getY();
        }
        x += int(speed * ((next_x - x) / sqrt(pow((next_x - x), 2)) + pow((next_y - y), 2)));
        y += int(speed * ((next_y - y) / sqrt(pow((next_x - x), 2)) + pow((next_y - y), 2)));
    }
    void draw() override {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < length; ++j) {
                if (i == x && j == y) {
                    cout << "H";
                }
                else {
                    cout << " ";
                }
            }
        }
    }
};

class Ogre :public Enemy {
private:
    int x, y;
    int health;
    int speed;
    int position;
public:
    Ogre() {
        x = begin_x, y = begin_y;
        health = health_ogre;
        speed = speed_ogre;
        position = 0;
    }
    void get_damage(int damage) override {
        health -= damage;
    }
    void run(vector<Road*> road) override {
        if (position == road.size() - 1) {
            return;
        }
        int next_x = road[position + 1]->getX();
        int next_y = road[position + 1]->getY();
        if (next_x == x && next_y == y) {
            position++;
            int next_x = road[position + 1]->getX();
            int next_y = road[position + 1]->getY();
        }
        x += int(speed * ((next_x - x) / sqrt(pow((next_x - x), 2)) + pow((next_y - y), 2)));
        y += int(speed * ((next_y - y) / sqrt(pow((next_x - x), 2)) + pow((next_y - y), 2)));
    }
    void draw() override {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < length; ++j) {
                if (i == x && j == y) {
                    cout << "0";
                }
                else {
                    cout << " ";
                }
            }
        }
    }
};

class Wave :public InterfaceWave {
private:
    vector<Enemy*> wave;
public:
    Wave() = default;
    void addGoblin(Goblin& goblin) {
        wave.push_back(&goblin);
    }
    void addOgre(Ogre& ogre) {
        wave.push_back(&ogre);
    }
    void run(vector<Road*> road) {
        for (int i = 0; i < wave.size(); ++i) {
            wave[i]->run(road);
        }
    }
    void draw() {
        for (int i = 0; i < wave.size(); ++i) {
            wave[i]->draw();
        }
    }
};

class WaveBuilder {
public:
    virtual void reset() = 0;
    virtual void addGoblin() = 0;
    virtual void addOgre() = 0;
    virtual Wave& getResult() = 0;
};

class Wave1Builder : public WaveBuilder {
private:
    Wave result;
public:
    void reset() {
        Wave* temp = new Wave();
        result = *temp;
    }
    void addGoblin() override {
        for (int i = 0; i < wave1_count_goblin; ++i) {
            Goblin* temp = new Goblin();
            result.addGoblin(*temp);
        }
    }
    void addOgre() override {
        for (int i = 0; i < wave1_count_ogre; ++i) {
            Ogre* temp = new Ogre();
            result.addOgre(*temp);
        }
    }
    Wave& getResult() {
        return result;
    }
};

class Wave2Builder : public WaveBuilder {
private:
    Wave result;
public:
    void reset() {
        Wave* temp = new Wave();
        result = *temp;
    }
    void addGoblin() override {
        for (int i = 0; i < wave2_count_goblin; ++i) {
            Goblin* temp = new Goblin();
            result.addGoblin(*temp);
        }
    }
    void addOgre() override {
        for (int i = 0; i < wave2_count_ogre; ++i) {
            Ogre* temp = new Ogre();
            result.addOgre(*temp);
        }
    }
    Wave& getResult() {
        return result;
    }
};


class InterfaceTower : public InterfaceObjects {
public:
    virtual void attack(Enemy& enemy) = 0;
    virtual void draw() = 0;
};

class Tower :public InterfaceTower {
protected:
    int x, y;
    int damage;
    int radius;
public:
    virtual void attack(Enemy& enemy) = 0;
    virtual void draw() = 0;
};

class Archer :public Tower {
public:
    Archer(int x, int y) {
        this->x = x;
        this->y = y;
        this->damage = archer_damage;
        this->radius = archer_radius;
    }
    void attack(Enemy& enemy) override {
        enemy.get_damage(damage);
    }
    void draw() override {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < length; ++j) {
                if (i == x && j == y) {
                    cout << "A";
                }
                else {
                    cout << " ";
                }
            }
        }
    }
};

class Gun :public Tower {
public:
    Gun(int x, int y) {
        this->x = x;
        this->y = y;
        this->damage = gun_damage;
        this->radius = gun_radius;
    }
    void attack(Enemy& enemy) override {
        enemy.get_damage(damage);
    }
    void draw() override {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < length; ++j) {
                if (i == x && j == y) {
                    cout << "G";
                }
                else {
                    cout << " ";
                }
            }
        }
    }
};

class Button {
public:
    void click() {
        return;
    }
};

class TowersButton :public Button {
public:
    virtual Tower& click(int x, int y) = 0;
};

class ArcherButton :public TowersButton {
public:
    Tower& click(int x, int y) override {
        Tower* temp = new Archer(x, y);
        return *temp;
    }
};

class GunButton :public TowersButton {
public:
    Tower& click(int x, int y) override {
        Tower* temp = new Gun(x, y);
        return *temp;
    }
};

class SettingButton :public Button {
public:
    virtual void click() = 0;
};

class PauseButton :public SettingButton {
public:
    void click() override {
        //
        //
        return;
    }
};

class SoundButton :public SettingButton {
public:
    void click() override {
        //
        //
        return;
    }
};

class Menu {
private:
    vector<Button*> buttons;
public:
    void clickButton(Button& button) {
        button.click();
    }

};

class World :public InterfaceObjects {
private:
    vector<InterfaceObjects> objects;
public:
    World(vector<InterfaceObjects>& objects) {
        this->objects = objects;
    }
    void draw() {
        for (int i = 0; i < objects.size(); ++i) {
            objects[i].draw();
        }
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < length; ++j) {
                if (i == 0 || i == width - 1) {
                    cout << "#";
                }
                if (j == 0 || j == length - 1) {
                    cout << "#";
                }
            }
        }
    }
};

class Fabric {
public:
    virtual InterfaceObjects* createObj(int x, int y) = 0;
};

class RoadFabric :public Fabric {
public:
    InterfaceObjects* createObj(int x, int y)  override {
        return new Road(x, y);
    }
};

class GrassFabric :public Fabric {
public:
    InterfaceObjects* createObj(int x, int y) override {
        return new Grass(x, y);
    }
};

class TreesFabric :public Fabric {
public:
    InterfaceObjects* createObj(int x, int y) override {
        return new Tree(x, y);
    }
};

class Game {
private:
    vector<InterfaceObjects*> objects;
    Wave wave;
public:
    void startGame() {
        Fabric* fabric = new RoadFabric();
        for (int i = 0; i < road.size(); ++i) {
            objects.push_back(fabric->createObj(road[i][0], road[i][1]));
        }
        fabric = new TreesFabric();
        for (int i = 0; i < tree.size(); ++i) {
            objects.push_back(fabric->createObj(tree[i][0], tree[i][1]));
        }
        fabric = new GrassFabric();
        for (int i = 0; i < grass.size(); ++i) {
            objects.push_back(fabric->createObj(grass[i][0], grass[i][1]));
        }
        WaveBuilder* builder = new Wave1Builder();
        builder->addGoblin();
        builder->addOgre();
    }
    void draw() {
        for (int i = 0; i < objects.size(); ++i) {
            objects[i]->draw();
        }
    }
};

int main() {
    Game game;
    game.startGame();
    game.draw();
    return 0;
}