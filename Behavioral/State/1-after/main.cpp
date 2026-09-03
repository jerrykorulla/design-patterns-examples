#include <iostream>
#include <memory>

// After State: each mode is its own class implementing a common interface.
// Character no longer knows what modes exist or how they behave -- it just
// delegates every call to whichever state object is current, and swaps
// that object out on the two actions that change mode.
class CharacterState {
public:
    virtual void move() = 0;
    virtual void attack() = 0;
    virtual void enterVehicle() = 0;
    virtual void exitVehicle() = 0;

    virtual ~CharacterState() = default;
};

class WalkingState : public CharacterState {
public:
    void move() override {
        std::cout << "Character is walking\n";
    }

    void attack() override {
        std::cout << "Character attacks with weapon\n";
    }

    void enterVehicle() override {
        std::cout << "Character enters vehicle\n";
    }

    void exitVehicle() override {
        std::cout << "Character is not in a vehicle\n";
    }
};

class DrivingState : public CharacterState {
public:
    void move() override {
        std::cout << "Vehicle is moving\n";
    }

    void attack() override {
        std::cout << "Cannot attack while driving\n";
    }

    void enterVehicle() override {
        std::cout << "Already driving\n";
    }

    void exitVehicle() override {
        std::cout << "Character exits vehicle\n";
    }
};

// The Character delegates its behavior to its current state.
class Character {
public:
    Character() : state_(std::make_unique<WalkingState>()) {}

    void move() { state_->move(); }
    void attack() { state_->attack(); }

    void enterVehicle() {
        state_->enterVehicle();
        // Only a walking character actually gets in -- a driving character
        // that tries again just hears "Already driving" and stays put.
        if (dynamic_cast<WalkingState*>(state_.get())) {
            state_ = std::make_unique<DrivingState>();
        }
    }

    void exitVehicle() {
        state_->exitVehicle();
        if (dynamic_cast<DrivingState*>(state_.get())) {
            state_ = std::make_unique<WalkingState>();
        }
    }

private:
    std::unique_ptr<CharacterState> state_;
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
