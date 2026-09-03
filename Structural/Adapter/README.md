# Before Adapter: incompatible audio libraries

This example models an audio player that needs to support multiple
third-party libraries. `MP3Player::playMP3()` and `WAVPlayer::playWAV()` are
both audio libraries, but they expose different, incompatible method names.

Without an adapter, the application has no single `play(file)` call it can
make -- it needs a separate function for each library, and every caller has
to know which concrete player type (and method name) to use. Adding a third
format (FLAC, OGG, ...) means writing yet another one-off function.

Compile and run from the `0-before` folder:

```powershell
g++ -std=c++17 main.cpp -o before-adapter.exe
.\before-adapter.exe
```

The follow-up Adapter version gives every library a common interface.

# After Adapter: a common AudioPlayer interface

`AudioPlayer` defines the single interface the application expects:
`play(file)`. `MP3Adapter` and `WAVAdapter` each wrap one incompatible
library and translate `play()` into that library's real method
(`playMP3()`, `playWAV()`). The application only ever talks to
`AudioPlayer`, so it can hold a mix of adapters and play any of them the
same way.

```
                         Application
                              │
                              │ play(file)
                              ▼
                      ┌───────────────┐
                      │  AudioPlayer  │
                      │   interface   │
                      └───────┬───────┘
                              │
                 ┌────────────┴────────────┐
                 ▼                         ▼
          ┌─────────────┐           ┌─────────────┐
          │ MP3 Adapter │           │ WAV Adapter │
          └──────┬──────┘           └──────┬──────┘
                 │                         │
                 ▼                         ▼
          MP3 Library                WAV Library
          playMP3()                  playWAV()
```

Adding FLAC, OGG, or AAC support later only means adding another adapter --
the `AudioPlayer` interface, and every existing caller, stays unchanged.

Compile and run from the `1-after` folder:

```powershell
g++ -std=c++17 main.cpp -o after-adapter.exe
.\after-adapter.exe
```
