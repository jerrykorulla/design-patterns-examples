# Design Patterns Examples

Small, focused C++ examples of classic design patterns. Each pattern has
its own folder with a `0-before` example showing the problem and a
`1-after` example showing the pattern solving it, plus a `README.md`
walking through both.

## Patterns

### Creational

- [Singleton](Creational/Singleton) — a shared application logger, instead
  of every service creating and configuring its own.
- [Prototype](Creational/Prototype) — spawning configured game enemies by
  cloning a prototype instead of re-typing every constructor argument.

### Structural

- [Adapter](Structural/Adapter) — a common `AudioPlayer` interface over
  incompatible MP3/WAV libraries.
- [Flyweight](Structural/Flyweight) — sharing identical tree mesh/texture
  data across a forest instead of duplicating it per instance.

### Behavioral

- [State](Behavioral/State) — a game character's behavior as state objects
  instead of a mode flag checked in every method.
- [Visitor](Behavioral/Visitor) — file-system operations (size, report) as
  visitor classes instead of methods piling up on `File`/`Directory`.

## Running an example

Each `0-before` and `1-after` folder is a single self-contained `main.cpp`.
Compile and run from inside that folder, e.g.:

```powershell
g++ -std=c++17 main.cpp -o example.exe
.\example.exe
```

(MSVC's `cl` works too: `cl /EHsc /std:c++17 main.cpp`.)

## License

[MIT](LICENSE)
