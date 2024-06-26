#ifndef ENGINE_STATE_H
#define ENGINE_STATE_H

#include "TranspositionTables.h"
#include "ChessEngineStatistics.h"

class EngineState {

    // Maximum depth for the Minimax algorithm
    int MAX_DEPTH;

    //Represents the Color the Engine Plays as(Black by Default)
    int EngineColor;

    //Time Limit for Search, (0 means no Time limit)
    float timeLimit = 0;

    const std::unordered_map<int, int> pieceValues = { { PAWN, 100 }, { KNIGHT, 320 }, { BISHOP, 330 }, { ROOK, 500 }, { QUEEN, 900 }, { KING, 1000 } };
    
    int engineEloRating;

    int getELOFromSettings() const;

public:
    //Transpostion Tables to Store Positional Data
    TranspositionTables transpostionTable;
    //Flags Defining Wether to Use Features
    const bool useTranspositions = true;
    const bool useAlphaBetaPruning = true;

    //Flags to start or End search
    bool terminateSearch;
    bool startSearch;

    EngineState();

    int GetEngineColor() const;
    void setEngineColor(int color);

    float getTimeLimit() const;

    void LoadSavedSettings();


    void TerminateSearch();
    bool isSearchStarted() const;
    void StartSearch();
    // Set the stop flag to stop the search
    void StopSearching();

    int getELO() const;
    void setElO(int newELO);

    int getDepth() const;
    void setDepth(int NewDepth);

    void SaveTranspositionTable();
    double getSizeOfTranspositionTable() const;

    int getPieceValue(int index) const;

    void reset();
};





#endif // !ENGINE_STATE_H


