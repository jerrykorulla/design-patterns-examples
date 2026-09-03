#include <iostream>
#include <string>

// Before Adapter: the audio libraries below are third-party and each
// exposes its own incompatible method name. Without a common interface,
// the application has to know which concrete library it is calling and
// call the right method for each -- there is no single `play(file)` call
// it can make against every format.
class MP3Player {
public:
    void playMP3(const std::string& file) {
        std::cout << "Playing MP3: " << file << '\n';
    }
};

class WAVPlayer {
public:
    void playWAV(const std::string& file) {
        std::cout << "Playing WAV: " << file << '\n';
    }
};

void playSong(const std::string& file) {
    // The application is hard-wired to MP3Player's specific method name.
    // Playing a WAV file means writing a second function with a different
    // method call, and every caller has to pick the right one.
    MP3Player mp3Player;
    mp3Player.playMP3(file);
}

void playSound(const std::string& file) {
    WAVPlayer wavPlayer;
    wavPlayer.playWAV(file);
}

int main() {
    // Every new format (FLAC, OGG, AAC, ...) means another one-off function
    // and another method name the application must learn.
    playSong("song.mp3");
    playSound("sound.wav");
}
