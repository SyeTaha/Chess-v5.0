#ifndef BOARDSTATS_H
#define BOARDSTATS_H

#include "StatisticalConstants.h"


class BoardStats {
private:

    //Evaluation Column
    float whiteProportion;
    float blackProportion;

    std::chrono::high_resolution_clock::time_point TimerStart;

    StatisticalConstants constants;

    //Wether to Show Move History or Not
    bool displayMoveHistory;
   

    int winner;
    //Message Regarding Who won
    std::string EndMessage;

    //Methods:

    void getData(const ChessEngine& engine, const User& player, const ChessBoard& chessboard, std::vector<std::string>& container);
    void DrawPlayerElos(int elo_W, int elo_B);

    void DrawStatistics(const std::vector<std::string>& EngineData);
    void DisplayPlayerTitles(const ChessBoard& chessboard);

    //Display Last Move or Move History based on flag
    void MovesAndHistory(std::string LastMovePlayed, const std::vector<std::string>& moveHistory);

    float Evaluate(const ChessBoard& chessboard, int Player) const;

public:
    bool SaveData;


    BoardStats();

    //Methods:

    void DisplayEndMessage();

    //Display Game Statistics in Single Player Mode

    void DisplayStats(ChessBoard& chessboard, ChessEngine& engine, User& player);

    //Display Game Statistice in Multiplayer Mode
    void DisplayStats(ChessBoard& chessboard);

    //Reset Stats
    void Reset();

    //Displays the Move History
    void DrawMoveHistory(const std::vector<std::string>& moveHistory) const;

    void DrawEvaluationColumn(ChessBoard& chessboard);


    //Check if Gamr ended or not
    bool GameIsEnded(ChessBoard& board);

    //Functions related to FENs and Depth
    void DisplayNewDepthMessage(const int& newdepth);
    void DisplayNewFENMessage(const std::string& fen);

    void toggleHistory();

    int getWinner() const;

    bool ShowMoveHistory() const;
    
};

#endif // !BOARDSTATS_H


