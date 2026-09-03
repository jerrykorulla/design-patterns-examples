#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Before Visitor: every new operation (size, compress, virus scan, report,
// ...) has to become a method on every file-system element. File and
// Directory grow with each new operation, and any future element type
// (a SymbolicLink, say) would need to implement all of them too.
class File {
public:
    File(std::string name, std::size_t sizeInBytes)
        : name(std::move(name)), sizeInBytes(sizeInBytes) {}

    std::size_t size() const { return sizeInBytes; }

    std::string report() const {
        return name + " (" + std::to_string(sizeInBytes) + " bytes)";
    }

    // compress(), scanForVirus(), and every future operation would each
    // need a matching method here...

private:
    std::string name;
    std::size_t sizeInBytes;
};

class Directory {
public:
    explicit Directory(std::string name) : name(std::move(name)) {}

    void add(std::unique_ptr<File> file) { files.push_back(std::move(file)); }
    void add(std::unique_ptr<Directory> directory) { directories.push_back(std::move(directory)); }

    std::size_t size() const {
        std::size_t total = 0;
        for (const auto& file : files) total += file->size();
        for (const auto& directory : directories) total += directory->size();
        return total;
    }

    std::string report() const {
        std::string result = name + "/\n";
        for (const auto& file : files) result += "  - " + file->report() + "\n";
        for (const auto& directory : directories) result += directory->report();
        return result;
    }

    // ...and every operation added to File has to be repeated here too,
    // with its own logic for combining child results.

private:
    std::string name;
    std::vector<std::unique_ptr<File>> files;
    std::vector<std::unique_ptr<Directory>> directories;
};

int main() {
    Directory root("project");
    root.add(std::make_unique<File>("main.cpp", 2048));
    root.add(std::make_unique<File>("README.md", 512));

    auto src = std::make_unique<Directory>("src");
    src->add(std::make_unique<File>("utils.cpp", 4096));
    root.add(std::move(src));

    std::cout << "Total size: " << root.size() << " bytes\n\n";
    std::cout << root.report();
}
