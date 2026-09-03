# Before State: a mode flag checked everywhere

This example models a game `Character` that behaves differently depending
on whether it's walking or driving a vehicle. Without the State pattern,
that difference is a `Mode` enum checked with `if`/`else if` inside every
single method -- `move()`, `attack()`, `enterVehicle()`, and `exitVehicle()`
all have to know about every mode that exists.

That works for two modes, but it doesn't scale: adding a third mode (say,
`Swimming`) means finding and editing all four methods, and it's easy to
update three of them and forget the fourth.

Compile and run from the `0-before` folder:

```powershell
g++ -std=c++17 main.cpp -o before-state.exe
.\before-state.exe
```

The follow-up State version moves each mode's behavior into its own class.

# After State: behavior delegated to a state object

`CharacterState` defines the interface every mode must implement.
`WalkingState` and `DrivingState` each implement it once, with no
conditionals -- a `DrivingState` simply *is* the "cannot attack, vehicle is
moving" behavior. `Character` no longer knows what modes exist; it just
forwards every call to whatever `CharacterState` is current, and swaps that
object out on the two actions that actually change mode.

```
                     Character (context)
                            │
                            │ delegates to
                            ▼
                    CharacterState
                      (interface)
                            │
                 ┌──────────┴──────────┐
                 ▼                     ▼
          WalkingState           DrivingState
                 │                     │
                 │   enterVehicle()    │
                 ├────────────────────►│
                 │                     │
                 │    exitVehicle()    │
                 │◄────────────────────┤
```

Adding a `Swimming` mode later means adding one new `CharacterState`
subclass -- `Character`, and every method already written against
`CharacterState`, stays unchanged.

Compile and run from the `1-after` folder:

```powershell
g++ -std=c++17 main.cpp -o after-state.exe
.\after-state.exe
```
