# Before Visitor: operations pile up on every element

This example models a small file system: `File` and `Directory`. Each of
them needs to support several operations -- calculate size, generate a
report, and (in a real file system) compress, scan for viruses, and more.

Without Visitor, every new operation becomes another method on `File` *and*
`Directory`, with `Directory` also having to know how to combine that
operation's results across its children. The classes keep growing, and any
future element type (a `SymbolicLink`, say) has to implement every one of
those methods too.

Compile and run from the `0-before` folder:

```powershell
g++ -std=c++17 main.cpp -o before-visitor.exe
.\before-visitor.exe
```

The follow-up Visitor version moves each operation into its own class.

# After Visitor: operations pulled out into visitors

`File` and `Directory` go back to knowing only what they are -- each just
implements `accept(FileSystemVisitor&)`. Every operation becomes a separate
`FileSystemVisitor` implementation instead of a method on the elements:

```
                File System Elements
                       │
          ┌────────────┴────────────┐
          ▼                         ▼
        File                   Directory
          │                         │
          └────────────┬────────────┘
                       ▼
                    Visitor
                       │
              ┌────────┴─────────┐
              ▼                  ▼
           Size              Report
          Visitor            Visitor
```

`accept()` calls `visitor.visit(*this)` where the concrete type of `*this`
(`File` or `Directory`) is known at compile time, so the call resolves to
the matching `visit()` overload -- that's the "double dispatch" that makes
Visitor work: which element responds is decided by `accept()`, and which
operation runs is decided by which `FileSystemVisitor` was passed in.

```
file.accept(sizeVisitor);
directory.accept(reportVisitor);
```

Adding a new operation (compress, virus scan, ...) means adding one new
`FileSystemVisitor` subclass -- `File` and `Directory` stay unchanged.
Adding a new element type (`SymbolicLink`) means adding one `visit()`
overload to every existing visitor, which the compiler will enforce since
`FileSystemVisitor::visit()` is pure virtual.

Compile and run from the `1-after` folder:

```powershell
g++ -std=c++17 main.cpp -o after-visitor.exe
.\after-visitor.exe
```
