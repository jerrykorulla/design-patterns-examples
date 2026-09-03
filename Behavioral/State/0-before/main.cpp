#include <iostream>

// Before State: Character behavior branches on an internal mode flag inside
// every single method. Each of move(), attack(), enterVehicle(), and
// exitVehicle() has to know about every possible mode, and adding a new
// mode (e.g. Swimming) means finding and editing all four methods.
class Character {
public:
    enum class Mode { Walking, Driving };

    void move() {
        if (mode == Mode::Walking) {
            std::cout << "Character is walking\n";
        } else if (mode == Mode::Driving) {
            std::cout << "Vehicle is moving\n";
        }
    }

    void attack() {
        if (mode == Mode::Walking) {
            std::cout << "Character attacks with weapon\n";
        } else if (mode == Mode::Driving) {
            std::cout << "Cannot attack while driving\n";
        }
    }

    void enterVehicle() {
        if (mode == Mode::Walking) {
            std::cout << "Character enters vehicle\n";
            mode = Mode::Driving;
        } else if (mode == Mode::Driving) {
            std::cout << "Already driving\n";
        }
    }

    void exitVehicle() {
        if (mode == Mode::Walking) {
            std::cout << "Character is not in a vehicle\n";
        } else if (mode == Mode::Driving) {
            std::cout << "Character exits vehicle\n";
            mode = Mode::Walking;
        }
    }

private:
    Mode mode = Mode::Walking;
};

int main() {
    Character character;

    character.move();
    character.attack();

    character.enterVehicle();
    character.move();
    character.attack();

    character.exitVehicle();
    character.move();
}
