#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Before Prototype: every enemy is built by re-typing its full configuration.
// There is no way to say "give me another one just like this" without
// repeating (or manually copying) every field.
class Enemy {
public:
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

    void attack() override {
        std::cout << "Orc (" << texture << ", " << weapon << ") attacks for "
                  << damage << " damage\n";
    }
};

int main() {
    // Spawning a wave of "grunt" orcs means repeating the same five
    // arguments every time. Every caller needs to know -- and agree on --
    // the full configuration, and any drift between calls (a mistyped
    // armor value, a forgotten texture) silently produces an inconsistent
    // enemy.
    std::vector<std::unique_ptr<Enemy>> wave;
    wave.push_back(std::make_unique<Orc>(100, 25, 10, "axe", "orc_green.png"));
    wave.push_back(std::make_unique<Orc>(100, 25, 10, "axe", "orc_green.png"));
    wave.push_back(std::make_unique<Orc>(100, 25, 10, "axe", "orc_green.png"));

    for (auto& enemy : wave) {
        enemy->attack();
    }

    std::cout << "Spawned " << wave.size() << " orcs by re-typing their configuration each time\n";
}
