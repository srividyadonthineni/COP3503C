#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
#include "main.h"
#include <chrono>
#include <sstream>
#include <algorithm>
#pragma once
using namespace std;

void nameValidation(string& playerName){
    if(!playerName.empty()){
        playerName[0] = toupper(playerName[0]);
    }
    for(unsigned int i = 1; i < playerName.size(); i++){
        playerName[i] = tolower(playerName[i]);
    }
}
void gameBoard::loadTextureFiles(){
    sf::Texture debugImage;
    if (!debugImage.loadFromFile("images/debug.png")) {
        cout << "Debug image not opened." << endl;
    }
    textureFiles.emplace("debug", debugImage);

    sf::Texture digitsImage;
    if (!digitsImage.loadFromFile("images/digits.png")) {
        cout << "Digits image not opened." << endl;
    }
    textureFiles.emplace("digits", digitsImage);

    sf::Texture happyFaceImage;
    if (!happyFaceImage.loadFromFile("images/face_happy.png")) {
        cout << "face_happy image not opened." << endl;
    }
    textureFiles.emplace("face_happy", happyFaceImage);

    sf::Texture loseFaceImage;
    if (!loseFaceImage.loadFromFile("images/face_lose.png")) {
        cout << "face_lose image not opened." << endl;
    }
    textureFiles.emplace("face_lose", loseFaceImage);

    sf::Texture winFaceImage;
    if (!winFaceImage.loadFromFile("images/face_win.png")) {
        cout << "face_win image not opened." << endl;
    }
    textureFiles.emplace("face_win", winFaceImage);

    sf::Texture flagImage;
    if (!flagImage.loadFromFile("images/flag.png")) {
        cout << "Flag image not opened." << endl;
    }
    textureFiles.emplace("flag", flagImage);

    sf::Texture leaderboardImage;
    if (!leaderboardImage.loadFromFile("images/leaderboard.png")) {
        cout << "leaderboard image not opened." << endl;
    }
    textureFiles.emplace("leaderboard", leaderboardImage);

    sf::Texture mineImage;
    if (!mineImage.loadFromFile("images/mine.png")) {
        cout << "mine image not opened." << endl;
    }
    textureFiles.emplace("mine", mineImage);

    sf::Texture number1Image;
    if (!number1Image.loadFromFile("images/number_1.png")) {
        cout << "number_1 image not opened." << endl;
    }
    textureFiles.emplace("number_1", number1Image);

    sf::Texture number2Image;
    if (!number2Image.loadFromFile("images/number_2.png")) {
        cout << "number_2 image not opened." << endl;
    }
    textureFiles.emplace("number_2", number2Image);

    sf::Texture number3Image;
    if (!number3Image.loadFromFile("images/number_3.png")) {
        cout << "number_3 image not opened." << endl;
    }
    textureFiles.emplace("number_3", number3Image);

    sf::Texture number4Image;
    if (!number4Image.loadFromFile("images/number_4.png")) {
        cout << "number_4 image not opened." << endl;
    }
    textureFiles.emplace("number_4", number4Image);

    sf::Texture number5Image;
    if (!number5Image.loadFromFile("images/number_5.png")) {
        cout << "number_5 image not opened." << endl;
    }
    textureFiles.emplace("number_5", number5Image);

    sf::Texture number6Image;
    if (!number6Image.loadFromFile("images/number_6.png")) {
        cout << "number_6 image not opened." << endl;
    }
    textureFiles.emplace("number_6", number6Image);

    sf::Texture number7Image;
    if (!number7Image.loadFromFile("images/number_7.png")) {
        cout << "number_7 image not opened." << endl;
    }
    textureFiles.emplace("number_7", number7Image);

    sf::Texture number8Image;
    if (!number8Image.loadFromFile("images/number_8.png")) {
        cout << "number_8 image not opened." << endl;
    }
    textureFiles.emplace("number_8", number8Image);

    sf::Texture pauseImage;
    if (!pauseImage.loadFromFile("images/pause.png")) {
        cout << "pause image not opened." << endl;
    }
    textureFiles.emplace("pause", pauseImage);

    sf::Texture playImage;
    if (!playImage.loadFromFile("images/play.png")) {
        cout << "play image not opened." << endl;
    }
    textureFiles.emplace("play", playImage);

    sf::Texture tileHiddenImage;
    if (!tileHiddenImage.loadFromFile("images/tile_hidden.png")) {
        cout << "tile_hidden image not opened." << endl;
    }
    textureFiles.emplace("tile_hidden", tileHiddenImage);

    sf::Texture tileRevealedImage;
    if (!tileRevealedImage.loadFromFile("images/tile_revealed.png")) {
        cout << "tile_revealed image not opened." << endl;
    }
    textureFiles.emplace("tile_revealed", tileRevealedImage);
}

void gameBoard::loadConfigFile() {
    ifstream configFile("config.cfg");
    if (!configFile.is_open()) {
        cout << "Error opening file: config" << endl;
    }
    configFile >> columns >> rows >> mineCounter;
    configFile.close();
}

Tile::Tile() {}

Tile::Tile(int x, int y, map<string, sf::Texture> &textureFiles) {
    mineLocation = false;
    flagged = false;
    gameTile = true;
    gamePaused = false;
    debugged = false;
    numAdjacentMines = 0;
    xCoordinate = x;
    yCoordinate = y;

    gameTileSprite.setTexture(textureFiles["tile_hidden"]);
    revealedImageSprite.setTexture(textureFiles["tile_revealed"]);
    flagImageSprite.setTexture(textureFiles["flag"]);
    pauseImageSprite.setTexture(textureFiles["pause"]);
    mineImageSprite.setTexture(textureFiles["mine"]);
    gameTileSprite.setColor(sf::Color(255, 255, 255, 255));
    revealedImageSprite.setColor(sf::Color::Transparent);
    flagImageSprite.setColor(sf::Color::Transparent);
    pauseImageSprite.setColor(sf::Color::Transparent);
    mineImageSprite.setColor(sf::Color::Transparent);
}

void Tile::setCoordinates(int x, int y) {
    xCoordinate = x;
    yCoordinate = y;

    gameTileSprite.setColor(sf::Color(255, 255, 255, 255));
    gameTileSprite.setPosition(xCoordinate, yCoordinate);
    revealedImageSprite.setPosition(xCoordinate, yCoordinate);
    flagImageSprite.setPosition(xCoordinate, yCoordinate);
    pauseImageSprite.setPosition(xCoordinate, yCoordinate);
}

bool Tile::uncoverTile(int& counter, bool lost) {
    if (gameTile && !flagged) {
        gameTile = false;
        revealedImageSprite.setColor(sf::Color(255, 255, 255, 255));
        revealedImageSprite.setPosition(xCoordinate, yCoordinate);

        if ((numAdjacentMines == 0) && (!mineLocation)) {
            for (int i = 0; i < adjacentTile.size(); i++) {
                if (!(adjacentTile[i]->mineLocation)) {
                    (adjacentTile[i])->uncoverTile(counter, lost);
                }
            }
        }

        if (numAdjacentMines > 0) {
            string numberTextureName = "number_" + to_string(numAdjacentMines);
            if (!textureFiles[numberTextureName].loadFromFile("images/" + numberTextureName + ".png")) {
                cout << numberTextureName << " image not opened." << endl;
            }
            numberSprite.setTexture(textureFiles[numberTextureName]);
            numberSprite.setPosition(xCoordinate, yCoordinate);
        }
    }
    return mineLocation;
}

void Tile::changeDebug(bool debugMode) {
    if (mineLocation && gameTile) {
        if (debugMode) {
            gameTileSprite.setColor(sf::Color(255, 255, 255, 0));

        }
        else {
            gameTileSprite.setColor(sf::Color(255, 255, 255, 255));
        }
    }
}

void Tile::tileRestart() {
    mineLocation = false;
    flagged = false;
    gameTile = true;
    debugged = false;
    gamePaused = false;

    numAdjacentMines = 0;
    gameTileSprite.setColor(sf::Color(255, 255, 255, 255));
    revealedImageSprite.setColor(sf::Color::Transparent);
    flagImageSprite.setColor(sf::Color::Transparent);
}

void Tile::draw(sf::RenderWindow &window, bool debugMode) {
    if (gameTile) {
        if (debugMode && mineLocation) {
            revealedImageSprite.setColor(sf::Color(255, 255, 255, 255));
            revealedImageSprite.setPosition(xCoordinate, yCoordinate);
            window.draw(revealedImageSprite);

            mineImageSprite.setColor(sf::Color(255, 255, 255, 255)); // Show mine
            mineImageSprite.setPosition(xCoordinate, yCoordinate);
            window.draw(mineImageSprite);
        }
        else if (!debugMode && mineLocation) {
            mineImageSprite.setColor(sf::Color::Transparent); // Hide mine
            revealedImageSprite.setColor(sf::Color::Transparent);
        }
        if (revealedImageSprite.getColor() != sf::Color::Transparent) {
            if (mineLocation) {
                mineImageSprite.setPosition(xCoordinate, yCoordinate);
                gameTileSprite.setColor(sf::Color(255,255,255,0));
                window.draw(revealedImageSprite);
                window.draw(mineImageSprite);
                window.draw(gameTileSprite);
            }
            else {
                window.draw(revealedImageSprite);
                if (numAdjacentMines > 0) {
                    numberSprite.setPosition(xCoordinate, yCoordinate);
                    window.draw(numberSprite);
                }
            }
        } else {
            window.draw(gameTileSprite);
        }
        if (flagged && flagImageSprite.getColor() != sf::Color::Transparent) {
            window.draw(revealedImageSprite);
            window.draw(flagImageSprite);
        }
    }
    else {
        if (revealedImageSprite.getColor() != sf::Color::Transparent) {
            if (mineLocation && flagged) {
                mineImageSprite.setPosition(xCoordinate, yCoordinate);
                gameTileSprite.setColor(sf::Color(255,255,255,0));
                window.draw(revealedImageSprite);
                window.draw(mineImageSprite);
                window.draw(gameTileSprite);
            }
            else if (mineLocation) {
                mineImageSprite.setPosition(xCoordinate, yCoordinate);
                gameTileSprite.setColor(sf::Color(255,255,255,0));
                window.draw(revealedImageSprite);
                window.draw(mineImageSprite);
                window.draw(gameTileSprite);
            }
            else {
                window.draw(revealedImageSprite);
                if (numAdjacentMines > 0) {
                    numberSprite.setPosition(xCoordinate, yCoordinate);
                    window.draw(numberSprite);
                }
            }
        }
    }
}

Tile::State Tile::getState() const {
    if (gameTile) {
        if (revealedImageSprite.getColor() != sf::Color::Transparent) {
            return State::Revealed;
        }
        else if (flagged && flagImageSprite.getColor() != sf::Color::Transparent) {
            return State::Flagged;
        } else {
            return State::Hidden;
        }
    } else {
        if (revealedImageSprite.getColor() != sf::Color::Transparent) {
            return State::Revealed;
        } else {
            return State::Hidden;
        }
    }
}

map<int, sf::Sprite> parseDigits(sf::Sprite digits){
    map<int, sf::Sprite> digitsMap;
    for(unsigned int i = 0; i <= 10; i++){
        sf::IntRect rect(i*21, 0, 21, 32);
        digits.setTextureRect(rect);
        sf::Sprite digitsSprite = digits;
        digitsMap.emplace(i, digitsSprite);
    }
    return digitsMap;
}

Board::Board(string player, int safeX, int safeY) {
    loadTextureFiles();
    loadConfigFile();
    tileVec.resize(rows * columns, vector<Tile>(columns, Tile(0, 0, textureFiles)));
    playerName = player;
    openLeaderboard = false;
    gamePaused = false;
    game_started = false;
    showLeaderboard = false;
    flagsPlaced = 0;
    flagMines = 0;
    numUncoveredTiles = 0;
    displayLeaderboardCheck = false;
    debugMode = false;
    initializeTiles();

    digitsMap = parseDigits(digitsSprite);

    smileFace.setTexture(textureFiles["face_happy"]);
    smileFace.setPosition((columns / 2.0 * 32) - 32, 32 * (rows + 0.5f));
    debugSprite.setTexture(textureFiles["debug"]);
    debugSprite.setPosition((columns * 32)-304, 32 * (rows + 0.5));
    pauseSprite.setTexture(textureFiles["pause"]);
    pauseSprite.setPosition((columns * 32)-240, 32 * (rows + 0.5));
    playSprite.setTexture(textureFiles["play"]);
    playSprite.setPosition((columns * 32) - 240, 32 * (rows + 0.5));
    leaderboardSprite.setTexture(textureFiles["leaderboard"]);
    leaderboardSprite.setPosition((columns * 32) - 176, 32 * (rows + 0.5));
    randomMines();
    AdjacentMines();
}

void Board::initializeTiles() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            tileVec[i][j].setCoordinates(j * 32, i * 32);
        }
    }
}

void Board::draw(sf::RenderWindow &window) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            tileVec[i][j].draw(window, debugMode);
        }
    }
    window.draw(smileFace);
    window.draw(debugSprite);
    window.draw(leaderboardSprite);
    if(showLeaderboard){
        sf::RenderWindow leaderboardBackground(sf::VideoMode((columns * 16), (rows * 16) + 50), "Minesweeper", sf::Style::Close);
        leaderboardBackground.clear(sf::Color::Blue);
        leaderboardBackground.display();
        sf::Font font;
        if (!font.loadFromFile("font.ttf")) {
            cout << "Error loading font file for leaderboard" << endl;
            return;
        }
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);

    }

}

void Board::randomMines() {
    random_device rand;
    mt19937 randominteger(rand());

    uniform_int_distribution<int> distRow(0, rows - 1);
    uniform_int_distribution<int> distCol(0, columns - 1);

    int count = 0;
    while (count < mineCounter) {
        int row = distRow(randominteger);
        int col = distCol(randominteger);
        if (!tileVec[row][col].mineLocation) {
            tileVec[row][col].mineLocation = true;
            tileVec[row][col].mineImageSprite.setTexture(textureFiles["mine"]);
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int newRow = row + i;
                    int newCol = col + j;
                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < columns) {
                        tileVec[newRow][newCol].numAdjacentMines++;
                    }
                }
            }
            count++;
        }
    }
    gameLost = false;
    gameOver = false;
    gamePaused = false;
    numWins = 0;
    numUncoveredTiles = 0;
}

void Board::AdjacentMines() {
    int mineCount = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if ((i + dx) >= 0 && (i + dx) < rows && (j + dy) >= 0 && (j + dy) < columns && !(dx == 0 && dy == 0)) {
                        if (tileVec[i + dx][j + dy].mineLocation){
                            mineCount++;
                        }
                        Tile* ptr = &(tileVec[i + dx][j + dy]);
                        tileVec[i][j].adjacentTile.push_back(ptr);
                    }
                }
            }
        }
    }
}

void Board::restartMinesweeper(){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            tileVec[i][j].tileRestart();

        }
    }
    startTime = chrono::high_resolution_clock::now();
    totalPauseDuration = 0;
    resetCounter();
    randomMines();
    AdjacentMines();
    smileFace.setTexture(textureFiles["face_happy"]);
}

void Board::updateTimer(){
    if (!gamePaused && !gameWin) {
        auto current_time = chrono::high_resolution_clock::now();
        auto game_duration = chrono::duration_cast<chrono::seconds>(current_time - startTime).count() - totalPauseDuration;
        boardMinutes = game_duration / 60;
        boardSeconds = game_duration % 60;
    }
}

int Board::getElapsedTime() const {
    if (!gamePaused) {
        auto current_time = chrono::high_resolution_clock::now();
        auto game_duration = chrono::duration_cast<chrono::seconds>(current_time - startTime).count() - totalPauseDuration;
        return game_duration;
    }
    return 0;
}

string Board::getTime() {
    int minutes = getMinutes() / 60;
    int seconds = getSeconds() ;

    string secondsString = to_string(seconds);
    if (seconds < 10) {
        secondsString = "0" + secondsString;
    }
    return to_string(minutes) + ":" + secondsString;
}


int Board::getMinutes() const {
    return boardMinutes;
}

int Board::getSeconds() const {
    return boardSeconds;
}

void Board::startPause() {
    pauseStartTime = chrono::high_resolution_clock::now();
}

void Board::endPause() {
    auto pauseEndTime = chrono::high_resolution_clock::now();
    totalPauseDuration += chrono::duration_cast<chrono::seconds>(pauseEndTime - pauseStartTime).count();
}

void Board::playingBoard(sf::RenderWindow &window  ,  sf::Event gameEventNew) {
    sf::Vector2i mouseCoordinates = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    int xCoordinate = mouseCoordinates.x / 32;
    int yCoordinate = mouseCoordinates.y / 32;

    static bool lock_left_click = false;
    if (gameEventNew.type == sf::Event::MouseButtonPressed) {
        if (gameEventNew.mouseButton.button == sf::Mouse::Left && !lock_left_click) {
            lock_left_click = true;
            if (smileFace.getGlobalBounds().contains(mousePosition)) {
                restartMinesweeper();
            }
            if (xCoordinate >= 0 && xCoordinate < columns && yCoordinate >= 0 && yCoordinate < rows && !gameOver && !gamePaused) {
                if (tileVec[yCoordinate][xCoordinate].gameTile && !tileVec[yCoordinate][xCoordinate].flagged) {
                    if (tileVec[yCoordinate][xCoordinate].uncoverTile(numUncoveredTiles, false)) {
                        gameLost = true;
                        gameOver = true;
                        for (int i = 0; i < rows; i++) {
                            for (int j = 0; j < columns; j++) {
                                if (tileVec[i][j].mineLocation) {
                                    tileVec[i][j].mineImageSprite.setColor(sf::Color(255,255,255,255));
                                    tileVec[i][j].uncoverTile(numUncoveredTiles, gameLost);
                                    tileVec[i][j].gameTileSprite.setColor(sf::Color(255,255,255,0));
                                }
                            }
                        }
                    }
                }
                updateCounter(false);
            }
            if (gameWin) {
                gameOver = true;
                displayLeaderboard();
            }
            if (debugSprite.getGlobalBounds().contains(mouseCoordinates.x, mouseCoordinates.y)) {
                debugMode = !debugMode;
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        tileVec[i][j].changeDebug(debugMode);
                    }
                }
            }
            if (leaderboardSprite.getGlobalBounds().contains(mouseCoordinates.x, mouseCoordinates.y)) {
                displayLeaderboard();
            }
            if (gamePaused) {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < columns; ++j) {
                        if (tileVec[i][j].getState() == Tile::Revealed) {
                            tileVec[i][j].uncoverTile(numUncoveredTiles, gameLost);
                        }
                    }
                }
            }
        }
    }
    if (gameEventNew.type == sf::Event::MouseButtonReleased) {
        if (gameEventNew.mouseButton.button == sf::Mouse::Left) {
            lock_left_click = false;
        }
    }
    static bool lock_right_click = false;
    if (gameEventNew.type == sf::Event::MouseButtonPressed) {
        if (gameEventNew.mouseButton.button == sf::Mouse::Right && !lock_right_click && !gameOver && !gamePaused) {
            lock_right_click = true;
            if (xCoordinate >= 0 && xCoordinate < columns && yCoordinate >= 0 && yCoordinate < rows && tileVec[yCoordinate][xCoordinate].gameTile) {
                auto& currentTile = tileVec[yCoordinate][xCoordinate];
                if (currentTile.gameTile) {
                    currentTile.flagged = !currentTile.flagged;
                    if (currentTile.flagged) {
                        currentTile.flagImageSprite.setColor(sf::Color(255, 255, 255, 255));
                        flagsPlaced++;
                    } else {
                        currentTile.flagImageSprite.setColor(sf::Color(255, 255, 255, 0)); // Hide the flag sprite
                        flagsPlaced--;
                    }
                    updateCounter(false);
                }
            }
        }
    }
    if (gameEventNew.type == sf::Event::MouseButtonReleased) {
        if (gameEventNew.mouseButton.button == sf::Mouse::Right) {
            lock_right_click = false;
        }
    }
    checkGameWin();
}

void Board::displayLeaderboard() {
    if(!openLeaderboard){
        openLeaderboard = true;
        showLeaderboard = true;
        gamePaused = true;
        sf::RenderWindow leaderboardWindow(sf::VideoMode(columns * 16, (rows * 16) + 50), "Minesweeper", sf::Style::Close);
        sf::Font font;
        if (!font.loadFromFile("font.ttf")) {
            cout << "Error loading font file for leaderboard" << endl;
            return;
        }

        while (leaderboardWindow.isOpen()) {
            sf::Event leaderboardEvent;
            while (leaderboardWindow.pollEvent(leaderboardEvent)) {
                if (leaderboardEvent.type == sf::Event::Closed) {
                    displayLeaderboardCheck = false;
                    leaderboardWindow.close();
                    return;
                }
            }
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::White);
            text.setStyle(sf::Text::Bold | sf::Text::Underlined);
            text.setString("LEADERBOARD");
            leaderboardWindow.clear(sf::Color::Blue);
            sf::FloatRect textBounds = text.getLocalBounds();
            text.setPosition((leaderboardWindow.getSize().x - textBounds.width) / 2, (leaderboardWindow.getSize().y - textBounds.height) / 2 - 120);
            leaderboardWindow.draw(text);
            topLeaderboard.drawLeaderboard(leaderboardWindow);
            leaderboardWindow.display();

            if(!leaderboardWindow.isOpen()){
                break;
            }
        }
    }
}

int Board::getRemainingMines() const{
    int flaggedMines = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (tileVec[i][j].flagged) {
                flaggedMines++;
            }
        }
    }
    return mineCounter - flaggedMines;
}

int Board::updateCounter(bool reset) {
    int flaggedMines = 0;
    if(!reset){
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (tileVec[i][j].flagged) {
                    flaggedMines++;
                }
            }
        }
    }
    remainingFlags = mineCounter - flaggedMines;
    return remainingFlags;
}


int Board::resetCounter() {
    flagMines = 0;
    return updateCounter(true);
}

bool Board::checkGameWin(){
    int nonMineTileCount = (rows * columns) - mineCounter;
    int revealedNonMineTiles = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (!tileVec[i][j].mineLocation && !tileVec[i][j].gameTile) {
                revealedNonMineTiles++;
            }
        }
    }

    if(revealedNonMineTiles == nonMineTileCount && !gameLost && !gameOver){
        gameWin = true;
        smileFace.setTexture(textureFiles["face_win"]);
        if(!gamePaused){
            gamePaused = true;
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (tileVec[i][j].mineLocation && !tileVec[i][j].flagged) {
                    tileVec[i][j].flagImageSprite.setColor(sf::Color(255, 255, 255, 255));
                    tileVec[i][j].mineImageSprite.setPosition(tileVec[i][j].xCoordinate, tileVec[i][j].yCoordinate);
                }
            }
        }
        topLeaderboard.updateLeaderboard(playerName, getTime());
        displayLeaderboardCheck = true;
    }
    else if (gameLost) {
        smileFace.setTexture(textureFiles["face_lose"]);
        if(!gamePaused){
            gamePaused = true;
        }
    }
    else {
        smileFace.setTexture(textureFiles["face_happy"]);
    }

    return gameWin;
}


Leaderboard::Leaderboard() : isWindowOpen(false) {
    readFromFile();
}

void Leaderboard::drawLeaderboard(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        cout << "Error loading font file" << endl;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    float offsetY = 20.0f;


    for (unsigned int i = 0; i < playerScores.size(); i++) {
        string entryText = to_string(i + 1) + "." + "\t" + playerScores[i].time + "\t" + playerScores[i].playerName + "\n\n";
        text.setString(entryText);
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition((window.getSize().x - textBounds.width) / 2, (window.getSize().y - textBounds.height) / 2 + offsetY);
        window.draw(text);
        offsetY += textBounds.height + 10.0f;
    }
}

void Leaderboard::updateLeaderboard(const string& playerName, string time) {
    insertScore(playerName, time);
    writeToFile();
}

void Leaderboard::readFromFile() {
    ifstream file("leaderboard.txt");
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string time;
        string name;

        if (getline(iss, time, ',') && getline(iss, name)) {
            Score newScore{name, time, false};
            playerScores.push_back(newScore);
        }
    }
    file.close();
    for (unsigned int i = 0; i < playerScores.size(); ++i) {
        for (size_t j = i + 1; j < playerScores.size(); ++j) {
            if (playerScores[j].time < playerScores[i].time) {
                swap(playerScores[i], playerScores[j]);
            }
        }
    }
    if (playerScores.size() > 5) {
        playerScores.resize(5);
    }
}

void Leaderboard::writeToFile() {
    ofstream file("leaderboard.txt", ios::app);
    if (!file.is_open()){
        cout << "unable to open file for writing" << endl;
    }
    for (const auto& score : playerScores) {
        file << score.time << ", " << score.playerName << "\n";
    }
    file.close();
}

void Leaderboard::insertScore(const string& playerName, string time) {
    Score newScore{playerName, time, false};
    auto it = playerScores.begin();
    while (it != playerScores.end() && newScore.time >= it->time) {
        it++;
    }
    playerScores.insert(it, newScore);
    if (playerScores.size() > 5) {
        playerScores.resize(5);
    }

}


int main() {
    string playerName;
    gameBoard welcomeScreen;
    gameBoard gameScreen;
    gameBoard scoreScreen;
    gameScreen.loadConfigFile();
    scoreScreen.loadConfigFile();
    welcomeScreen.loadTextureFiles();
    welcomeScreen.loadConfigFile();
    sf::RenderWindow window(sf::VideoMode((welcomeScreen.columns * 32), (welcomeScreen.rows * 32) + 100), "Minesweeper", sf::Style::Close);

    sf::Font welcomeScreenFont;
    if (!welcomeScreenFont.loadFromFile("font.ttf")) {
        cout << "Error loading font file" << endl;
        return false;
    }

    sf::Text welcomeScreenText;
    welcomeScreenText.setFont(welcomeScreenFont);
    welcomeScreenText.setCharacterSize(24);
    welcomeScreenText.setFillColor(sf::Color::White);
    welcomeScreenText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeScreenText.setString("WELCOME TO MINESWEEPER!");
    sf::Text playerNameText;
    playerNameText.setFont(welcomeScreenFont);
    playerNameText.setCharacterSize(20);
    playerNameText.setFillColor(sf::Color::White);
    playerNameText.setString("Enter your name: ");
    sf::Text inputPlayerName;
    inputPlayerName.setFont(welcomeScreenFont);
    inputPlayerName.setCharacterSize(18);
    inputPlayerName.setFillColor(sf::Color::Yellow);
    inputPlayerName.setString("");


    sf::FloatRect textBounds = welcomeScreenText.getLocalBounds();
    sf::FloatRect playerNameTextBounds = playerNameText.getLocalBounds();
    welcomeScreenText.setPosition((window.getSize().x - textBounds.width) / 2, (window.getSize().y - textBounds.height) / 2 - 150);
    playerNameText.setOrigin(playerNameTextBounds.left + playerNameTextBounds.width / 2.0f, playerNameTextBounds.top + playerNameTextBounds.height / 2.0f);
    playerNameText.setPosition((window.getSize().x) / 2, (window.getSize().y) / 2 - 75);

    bool entered = false;
    sf::RenderWindow gameWindow;
    sf::RenderWindow scoreWindow;

    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 1;
            }
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !playerName.empty()) {
                    playerName.pop_back();
                } else if (event.text.unicode == 13) {
                    if (!playerName.empty()) {
                        entered = true;
                    }
                } else if ((event.text.unicode >= 'a' && event.text.unicode <= 'z') ||
                           (event.text.unicode >= 'A' && event.text.unicode <= 'Z')) {
                    if (playerName.size() < 10) {
                        playerName += static_cast<char>(event.text.unicode);
                        nameValidation(playerName);

                        sf::FloatRect textBounds = inputPlayerName.getLocalBounds();
                        inputPlayerName.setPosition((window.getSize().x - textBounds.width) / 2,
                                                    (window.getSize().y - textBounds.height) / 2 - 45);
                    }
                }
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
                if (!playerName.empty()) {
                    window.close();
                    if (!gameWindow.isOpen()) {
                        gameWindow.create(sf::VideoMode((gameScreen.columns * 32), (gameScreen.rows * 32) + 100),
                                          "Minesweeper", sf::Style::Close);
                    }
                }
            }
        }
        window.clear(sf::Color::Blue);
        window.draw(welcomeScreenText);
        window.draw(playerNameText);
        if (entered) {
            inputPlayerName.setString(playerName);
        }
        else {
            inputPlayerName.setString(playerName + "|");
        }
        window.draw(inputPlayerName);
        window.display();

        if (!window.isOpen()) {
            break;
        }

    }
    Board mineBoard(playerName);
    sf::Texture digitsText;
    if (!digitsText.loadFromFile("images/digits.png")) {
        cout << "Digits image not opened." << endl;
    }
    sf::Sprite digits;
    digits.setTexture(digitsText);

    map<int, sf::Sprite> digitsMap = parseDigits(digits);

    sf::Texture pauseText;
    if (!pauseText.loadFromFile("images/pause.png")) {
        cout << "pause image not opened." << endl;
    }

    welcomeScreen.loadConfigFile();

    sf::Sprite pauseBttn;
    pauseBttn.setTexture(pauseText);
    pauseBttn.setPosition((gameScreen.columns * 32) - 240, 32 * (gameScreen.rows + 0.5));

    sf::Texture playText;
    if (!playText.loadFromFile("images/play.png")) {
        cout << "play image not opened." << endl;
    }
    sf::Sprite playBttn;
    playBttn.setTexture(playText);
    playBttn.setPosition((gameScreen.columns * 32) - 240, 32 * (gameScreen.rows + 0.5));


    auto current_time = chrono::high_resolution_clock::now();
    mineBoard.startTime = current_time;
    Board restartBoard(playerName);
    while (gameWindow.isOpen()) {
        sf::Event gameEvent;
        mineBoard.updateTimer();
        while (gameWindow.pollEvent(gameEvent)) {
            sf::Vector2i vec = sf::Mouse::getPosition(gameWindow);
            if (gameEvent.type == sf::Event::Closed) {
                gameWindow.close();
            }
            else if(sf::Event::MouseButtonPressed == gameEvent.type && sf::Mouse::Left == gameEvent.mouseButton.button){
                if(pauseBttn.getGlobalBounds().contains(vec.x, vec.y)){
                    if(!mineBoard.gamePaused){
                        mineBoard.startPause();
                        mineBoard.gamePaused = true;
                    }
                    else{
                        mineBoard.endPause();
                        mineBoard.gamePaused = false;

                    }
                }
                int elapsedTimeInSeconds = mineBoard.getElapsedTime();
            }
        }

        int minutes = mineBoard.getMinutes();
        int seconds = mineBoard.getSeconds();
        int minutes0 = minutes / 10 % 10;
        int minutes1 = minutes % 10;
        int seconds0 = seconds / 10 % 10;
        int seconds1 = seconds % 10;

        mineBoard.playingBoard(gameWindow , gameEvent);
        mineBoard.updateTimer();
        gameWindow.clear(sf::Color::White);
        mineBoard.draw(gameWindow);

        digitsMap[minutes1].setPosition((gameScreen.columns * 32) - 76, 32 * (gameScreen.rows + 0.5) + 16);
        gameWindow.draw(digitsMap[minutes1]);
        digitsMap[minutes0].setPosition((gameScreen.columns * 32) - 97, 32 *(gameScreen.rows + 0.5) + 16);
        gameWindow.draw(digitsMap[minutes0]);
        digitsMap[seconds1].setPosition((gameScreen.columns * 32) - 33, 32 *(gameScreen.rows + 0.5) + 16);
        gameWindow.draw(digitsMap[seconds1]);
        digitsMap[seconds0].setPosition((gameScreen.columns * 32) - 54, 32 *(gameScreen.rows + 0.5) + 16);
        gameWindow.draw(digitsMap[seconds0]);

        int remainingFlags = mineBoard.getRemainingMines();
        int digitX = 33;
        bool isNegative = remainingFlags < 0;
        int remainingFlagsAbs = abs(remainingFlags);

        int digit = remainingFlagsAbs % 10;
        int digit1 = remainingFlags / 10 % 10;
        digitsMap[10].setPosition(digitX - 21, 32 * (gameScreen.rows + 0.5) + 16);
        digitsMap[digit].setPosition(digitX + 21, 32 * (gameScreen.rows + 0.5) + 16);
        digitsMap[digit1].setPosition(digitX, 32 * (gameScreen.rows + 0.5) + 16);

        if(isNegative){

            gameWindow.draw(digitsMap[10]);
            gameWindow.draw(digitsMap[digit]);
            gameWindow.draw(digitsMap[digit1]);
        }
        else{
            gameWindow.draw(digitsMap[digit]);
            gameWindow.draw(digitsMap[digit1]);
        }
        if(mineBoard.gamePaused){
            gameWindow.draw(playBttn);
        }
        else if(!mineBoard.gamePaused){
            gameWindow.draw(pauseBttn);
        }
        gameWindow.display();
        if(mineBoard.displayLeaderboardCheck){
            mineBoard.displayLeaderboard();
        }
    }
    return 0;
}
