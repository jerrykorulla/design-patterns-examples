#include <iostream>
#include <memory>
#include <string>
#include <vector>

// After Prototype: configure one enemy fully, then clone it. Every clone
// starts identical to the prototype, and callers no longer need to know (or
// repeat) the full constructor argument list.
class Enemy {
public:
    virtual std::unique_ptr<Enemy> clone() const = 0;
    virtual void attack() = 0;
    virtual ~Enemy() = default;
};

class Orc : public Enemy {
public:
    int health;
    int damage;
    int armor;
    std::string weapon;
    std::string texture;

    Orc(int health, int damage, int armor, std::string weapon, std::string texture)
        : health(health), damage(damage), armor(armor),
          weapon(std::move(weapon)), texture(std::move(texture)) {}

    std::unique_ptr<Enemy> clone() const override {
        return std::make_unique<Orc>(*this);
    }

    void attack() override {
        std::cout << "Orc (" << texture << ", " << weapon << ") attacks for "
                  << damage << " damage\n";
    }
};

int main() {
    // Configure the prototype once, with every field it needs.
    Orc prototype(100, 25, 10, "axe", "orc_green.png");

    // Spawning a wave is now just cloning the prototype -- no argument list
    // to repeat, and no risk of the clones drifting from one another.
    std::vector<std::unique_ptr<Enemy>> wave;
    wave.push_back(prototype.clone());
    wave.push_back(prototype.clone());
    wave.push_back(prototype.clone());

    for (auto& enemy : wave) {
        enemy->attack();
    }

    // Individual clones can still be customized after the fact, without
    // touching the prototype or any other clone.
    auto& orc1 = static_cast<Orc&>(*wave[0]);
    orc1.health = 150;

    auto& orc2 = static_cast<Orc&>(*wave[1]);
    orc2.damage = 40;

    std::cout << "Customized orc1 health=" << orc1.health
              << ", orc2 damage=" << orc2.damage << '\n';
    std::cout << "Spawned " << wave.size() << " orcs by cloning a single prototype\n";
}
