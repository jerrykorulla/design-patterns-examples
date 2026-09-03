#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// After Flyweight: the mesh and texture (intrinsic state -- identical for
// every "Pine" tree) are loaded once and shared. Only the position and
// scale (extrinsic state -- unique per tree) are stored per instance.

// --------------------------------------------------
// Flyweight: shared tree data
// --------------------------------------------------
class TreeType {
public:
    TreeType(const std::string& mesh, const std::string& texture)
        : mesh(mesh), texture(texture) {
        std::cout << "Loading: " << mesh << " + " << texture << '\n';
    }

    void render(float x, float y, float z, float scale) const {
        // In a real game, this would issue the GPU draw call.
        std::cout << "Render tree at (" << x << ", " << y << ", " << z
                   << "), scale = " << scale << '\n';
    }

private:
    // INTRINSIC STATE -- shared by all instances.
    std::string mesh;
    std::string texture;
};

// --------------------------------------------------
// Flyweight Factory
// --------------------------------------------------
class TreeFactory {
public:
    static TreeType& getTreeType(const std::string& type) {
        auto it = treeTypes.find(type);

        if (it == treeTypes.end()) {
            auto treeType = std::make_unique<TreeType>(type + ".obj", type + ".png");
            it = treeTypes.emplace(type, std::move(treeType)).first;
        }

        return *it->second;
    }

private:
    // One TreeType object per tree type, no matter how many trees exist.
    static std::unordered_map<std::string, std::unique_ptr<TreeType>> treeTypes;
};

std::unordered_map<std::string, std::unique_ptr<TreeType>> TreeFactory::treeTypes;

// --------------------------------------------------
// Tree Instance
// --------------------------------------------------
struct Tree {
    TreeType* type;  // Shared flyweight (intrinsic state)
    float x, y, z;   // Extrinsic state -- unique per tree
    float scale;     // Extrinsic state -- unique per tree

    void render() const {
        type->render(x, y, z, scale);
    }
};

// --------------------------------------------------
// Forest
// --------------------------------------------------
int main() {
    std::vector<Tree> forest;

    // Create a forest of pine trees -- in a real game this loop might run
    // for thousands of trees.
    for (int i = 0; i < 6; ++i) {
        Tree tree;

        // Shared flyweight: every tree gets the SAME TreeType instance.
        tree.type = &TreeFactory::getTreeType("Pine");

        // Extrinsic state: unique to this tree.
        tree.x = i * 10.0f;
        tree.y = 0.0f;
        tree.z = i * 5.0f;
        tree.scale = 0.8f + (i % 5) * 0.1f;

        forest.push_back(tree);
    }

    // Only one "Loading: Pine.obj + Pine.png" line prints above, no matter
    // how many trees are in the forest.
    for (const auto& tree : forest) {
        tree.render();
    }
}
