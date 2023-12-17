#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <chrono>

#pragma once
using namespace std;
using namespace chrono;

struct gameBoard{
    int rows;
    int columns;
    int mineCounter;
    map<string, sf::Texture> textureFiles;

    void loadTextureFiles();
    void loadConfigFile();
};

class Tile : public gameBoard{
public:
    Tile();
    Tile(int x, int y, map<string, sf::Texture>& textureFiles);
    bool flagged;
    bool gameTile;
    int xCoordinate;
    int yCoordinate;
    bool mineLocation;
    int numAdjacentMines;
    bool debugged;
    bool gamePaused;
    vector<Tile*> adjacentTile;
    sf::Sprite gameTileSprite;
    sf::Sprite revealedImageSprite;
    sf::Sprite hiddenImageSprite;
    sf::Sprite flagImageSprite;
    sf::Sprite pauseImageSprite;
    sf::Sprite mineImageSprite;
    sf::Sprite numberSprite;
    void setCoordinates(int x, int y);
    bool uncoverTile(int& counter, bool lost);
    void changeDebug(bool debugMode);
    void draw(sf::RenderWindow &window, bool debugMode);
    void tileRestart();


    enum State {
        Hidden,
        Revealed,
        Flagged,
        RevealedDuringPause
    };
    State getState() const;
};

class Leaderboard : public gameBoard{
public:
    Leaderboard();
    void display();
    void updateLeaderboard(const string& playerName, string time);
    Leaderboard(const string& filePath);
    void displayLeaderboard();
    bool updateIfEligible(const string& playerName, int playerTime);
    void openWindow();
    void closeWindow();
    string leaderboardFilePath;
    bool isWindowOpen;
    void readFromFile();
    void writeToFile();
    void insertScore(const string& playerName, string time);
    struct Score {
        string playerName;
        string time;
        bool isNewTopScore;
    };
    vector<Score> playerScores;
    void drawLeaderboard(sf::RenderWindow& window);
};


class Board : public gameBoard{
public:
    Board(string player, int safeX = 0, int safeY = 0);
    bool openLeaderboard;
    sf::Sprite faceButtonSprite;
    sf::Sprite smileFace;
    sf::Sprite debugSprite;
    sf::Sprite playSprite;
    sf::Sprite leaderboardSprite;
    sf::Sprite digitsSprite;
    sf::Sprite pauseSprite;
    sf::Sprite mineImageSprite;
    string playerName;
    int numUncoveredTiles;
    bool gameOver;
    bool gameLost;
    bool gamePaused;
    bool gameWin;
    bool debugMode;
    int remainingFlags;
    bool showLeaderboard;
    bool displayLeaderboardCheck;
    int numWins;
    void initializeTiles();
    vector<vector<Tile>> tileVec;
    map<int, sf::Sprite> digitsMap;
    void draw(sf::RenderWindow &window);
    void randomMines();
    void AdjacentMines();
    void playingBoard(sf::RenderWindow &window , sf::Event gameEventNew);
    bool checkGameWin();
    int game_started;
    chrono::high_resolution_clock::time_point start_time;
    void restartMinesweeper();
    void debugTiles();
    void setGamePaused(bool paused);
    int updateCounter(bool reset);
    int resetCounter();
    void updateTimer();
    void drawCounter(sf::RenderWindow& window);
    friend map<int, sf::Sprite> parseDigits(sf::Sprite digits);
    int getMinutes() const;
    int getSeconds() const;
    int boardMinutes;
    int boardSeconds;
    int flagsPlaced;
    int flagMines;
    int elapsedTime;
    chrono::high_resolution_clock::time_point startTime;
    chrono::high_resolution_clock::time_point pauseStartTime;
    void displayLeaderboard();
    int totalPauseDuration = 0;
    void startPause();
    void endPause();
    int getElapsedTime() const;
    string getTime();
    int getRemainingMines() const;
    Leaderboard topLeaderboard;
};
