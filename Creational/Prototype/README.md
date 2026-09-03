# Before Prototype: game enemy spawning

This example models spawning a wave of `Orc` enemies. Each `Orc` carries a
handful of configuration -- health, damage, armor, weapon, texture -- and in
a real game that list would grow further (AI configuration, animations,
sounds, and more).

Without a prototype, every spawn point re-types the full constructor
argument list. Callers must know every field and repeat it exactly; any
drift between calls (a mistyped value, a forgotten field) produces an
inconsistent enemy with no compiler warning.

Compile and run from the `0-before` folder:

```powershell
g++ -std=c++17 main.cpp -o before-prototype.exe
.\before-prototype.exe
```

The follow-up Prototype version configures one enemy and clones it instead.

# After Prototype: cloning a configured enemy

`Enemy::clone()` lets a fully-configured `Orc` produce copies of itself. A
single prototype is built once with all of its configuration, and every
subsequent enemy is created with `prototype.clone()` instead of repeating
the constructor call. Each clone starts identical to the prototype and can
still be customized afterward without affecting the prototype or any other
clone.

Compile and run from the `1-after` folder:

```powershell
g++ -std=c++17 main.cpp -o after-prototype.exe
.\after-prototype.exe
```
