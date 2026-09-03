#include <iostream>
#include <string>
#include <vector>

// Before Flyweight: every tree owns its own copy of the mesh and texture,
// even though every "Pine" tree in the forest is identical apart from its
// position and scale. Loading that data happens once per tree instead of
// once per tree TYPE -- in a real forest of thousands of trees, that is
// thousands of redundant mesh/texture copies.
class Tree {
public:
    Tree(const std::string& type, float x, float y, float z, float scale)
        : mesh(type + ".obj"), texture(type + ".png"), x(x), y(y), z(z), scale(scale) {
        std::cout << "Loading: " << mesh << " + " << texture << '\n';
    }

    void render() const {
        std::cout << "Render tree at (" << x << ", " << y << ", " << z
                  << "), scale = " << scale << '\n';
    }

private:
    // INTRINSIC STATE -- identical for every "Pine" tree, but duplicated
    // here in every single instance.
    std::string mesh;
    std::string texture;

    // Genuinely unique per tree.
    float x, y, z;
    float scale;
};

int main() {
    std::vector<Tree> forest;

    // Every tree reloads (and stores its own copy of) "Pine.obj" and
    // "Pine.png", even though they're identical across the whole forest.
    for (int i = 0; i < 6; ++i) {
        forest.emplace_back("Pine", i * 10.0f, 0.0f, i * 5.0f, 0.8f + (i % 5) * 0.1f);
    }

    for (const auto& tree : forest) {
        tree.render();
    }
}
