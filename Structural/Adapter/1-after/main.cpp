#include <iostream>
#include <memory>
#include <string>
#include <vector>

// After Adapter: the application only ever calls play(file) through the
// AudioPlayer interface. Each incompatible library gets its own adapter
// that translates play() into that library's real method name.
class AudioPlayer {
public:
    virtual void play(const std::string& file) = 0;
    virtual ~AudioPlayer() = default;
};

// These are the same third-party libraries as before -- their APIs are not
// something we can change.
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

class MP3Adapter : public AudioPlayer {
private:
    MP3Player mp3Player;

public:
    void play(const std::string& file) override {
        mp3Player.playMP3(file);
    }
};

class WAVAdapter : public AudioPlayer {
private:
    WAVPlayer wavPlayer;

public:
    void play(const std::string& file) override {
        wavPlayer.playWAV(file);
    }
};

int main() {
    // The application deals only with AudioPlayer -- it never sees playMP3
    // or playWAV directly.
    std::vector<std::unique_ptr<AudioPlayer>> playlist;
    playlist.push_back(std::make_unique<MP3Adapter>());
    playlist.push_back(std::make_unique<WAVAdapter>());

    playlist[0]->play("song.mp3");
    playlist[1]->play("sound.wav");

    // Adding FLAC support later means adding a FLACAdapter -- the
    // AudioPlayer interface, and every existing caller, stays unchanged.
}
