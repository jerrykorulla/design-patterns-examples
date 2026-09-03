# Before Flyweight: a forest of duplicated trees

This example models a forest of `Tree` objects. Every "Pine" tree needs the
same mesh (`Pine.obj`) and texture (`Pine.png`), but only its position and
scale actually differ from tree to tree.

Without a flyweight, each `Tree` stores its own copy of the mesh and texture
strings and "loads" them in its constructor. Six trees means six redundant
loads of identical data -- in a real forest of thousands of trees, that is
thousands of redundant mesh and texture copies for data that never changes
between them.

Compile and run from the `0-before` folder:

```powershell
g++ -std=c++17 main.cpp -o before-flyweight.exe
.\before-flyweight.exe
```

The follow-up Flyweight version loads the shared data once and reuses it.

# After Flyweight: shared tree data

The data every "Pine" tree has in common (the mesh and texture) is its
**intrinsic state** -- it's pulled out into `TreeType` and loaded exactly
once by `TreeFactory`, no matter how many trees ask for it. Each tree's
position and scale is its **extrinsic state** -- genuinely unique per
instance, so it stays on the lightweight `Tree` struct alongside a pointer
to the shared `TreeType`.

```
                 TreeType
              ┌─────────────┐
              │ Pine.obj    │  ← Shared
              │ Pine.png    │  ← Shared
              └──────┬──────┘
                     │
          ┌──────────┼──────────┐
          ↓          ↓          ↓
       Tree #1    Tree #2     Tree #6
       x,y,z      x,y,z       x,y,z
       scale      scale       scale
```

Instead of N copies of the mesh, texture, and material, there is one of
each, plus N lightweight `{ pointer, position, scale }` records. Requesting
"Pine" from `TreeFactory::getTreeType()` any number of times returns the
same `TreeType` instance rather than creating a new one -- only a single
`Loading: Pine.obj + Pine.png` line prints, however many trees are created.

Flyweight = share what is common; keep what is unique outside the shared
object.

For a real game, this pattern is often combined with GPU instancing, where
the many position/scale values are sent to the GPU and the shared mesh is
rendered in very few draw calls.

Compile and run from the `1-after` folder:

```powershell
g++ -std=c++17 main.cpp -o after-flyweight.exe
.\after-flyweight.exe
```
