#include <iostream>
#include <memory>
#include <string>
#include <vector>

// After Visitor: File and Directory stay focused on what they are. Each
// operation (size, report, ...) lives in its own visitor class instead of
// being another method every element has to implement.
class File;
class Directory;

class FileSystemVisitor {
public:
    virtual void visit(File& file) = 0;
    virtual void visit(Directory& directory) = 0;
    virtual ~FileSystemVisitor() = default;
};

class FileSystemElement {
public:
    virtual void accept(FileSystemVisitor& visitor) = 0;
    virtual ~FileSystemElement() = default;
};

class File : public FileSystemElement {
public:
    File(std::string name, std::size_t sizeInBytes)
        : name_(std::move(name)), sizeInBytes_(sizeInBytes) {}

    void accept(FileSystemVisitor& visitor) override {
        // The concrete type of *this is known here at compile time, so this
        // resolves to the visitor's File overload -- this is what gives
        // Visitor its double dispatch.
        visitor.visit(*this);
    }

    const std::string& name() const { return name_; }
    std::size_t sizeInBytes() const { return sizeInBytes_; }

private:
    std::string name_;
    std::size_t sizeInBytes_;
};

class Directory : public FileSystemElement {
public:
    explicit Directory(std::string name) : name_(std::move(name)) {}

    void add(std::unique_ptr<FileSystemElement> child) { children_.push_back(std::move(child)); }

    void accept(FileSystemVisitor& visitor) override {
        visitor.visit(*this);
        for (auto& child : children_) {
            child->accept(visitor);
        }
    }

    const std::string& name() const { return name_; }

private:
    std::string name_;
    std::vector<std::unique_ptr<FileSystemElement>> children_;
};

// --------------------------------------------------
// Visitors: one class per operation
// --------------------------------------------------
class SizeVisitor : public FileSystemVisitor {
public:
    void visit(File& file) override { totalBytes_ += file.sizeInBytes(); }
    void visit(Directory&) override { /* a directory itself has no size; its files do */ }

    std::size_t totalBytes() const { return totalBytes_; }

private:
    std::size_t totalBytes_ = 0;
};

class ReportVisitor : public FileSystemVisitor {
public:
    void visit(File& file) override {
        std::cout << "  - " << file.name() << " (" << file.sizeInBytes() << " bytes)\n";
    }

    void visit(Directory& directory) override {
        std::cout << directory.name() << "/\n";
    }
};

int main() {
    Directory root("project");
    root.add(std::make_unique<File>("main.cpp", 2048));
    root.add(std::make_unique<File>("README.md", 512));

    auto src = std::make_unique<Directory>("src");
    src->add(std::make_unique<File>("utils.cpp", 4096));
    root.add(std::move(src));

    // Adding an operation means adding a visitor -- File and Directory
    // above are untouched by either of these.
    SizeVisitor sizeVisitor;
    root.accept(sizeVisitor);
    std::cout << "Total size: " << sizeVisitor.totalBytes() << " bytes\n\n";

    ReportVisitor reportVisitor;
    root.accept(reportVisitor);
}
