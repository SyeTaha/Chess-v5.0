#include "../../headers/GameFlow/GameModes.h"
#include "../../headers/Other/Resources.h"
//#include "../../headers/Other/Menu.h"

static void CalculateAIMove(ChessEngine& engine, ChessBoard& board) {
    while (true) {
        if (engine.state.isSearchStarted() && !board.isCurrentPlayerWhite()) {

            //string move;
            std::string move;
            board.ComputeOpponentMoves();
            std::cout << "Running...\n";
            move = engine.GenerateMove(board);
            if (move != "") {
                engine.PlayMove(move, board);
            }
            engine.state.StopSearching();
        }
    }
}


int main() {
    InitWindow(screenWidth, screenHeight, "Chess");
    InitAudioDevice();
    GameModes Game;
    Menu GameMenu;
    
    //Game.Horizon.SetDepth(1);
    Game.BoardSetUp();
    
    Settings::save(Game.Horizon.state.getDepth(), Game.Player.ELO, Game.Horizon.state.getELO());

    ChessPiecePlaced = LoadSound(ChessPiecePlacedFile.c_str());
    ChessPieceCaptured = LoadSound(ChessPieceCapturedFile.c_str());
    KingChecked = LoadSound(KingCheckedFile.c_str());
    GameStarts = LoadSound(GameStartsFile.c_str());
    GameEnds = LoadSound(GameEndsFile.c_str());
    myFont = LoadFont(fontFile.c_str());
    Image icon = LoadImage(program_icon.c_str());



    SetWindowIcon(icon);
    SetTargetFPS(60);

    std::thread EngineThread(CalculateAIMove, std::ref(Game.Horizon), std::ref(Game.chessboard));
    EngineThread.detach();
    int index = 0;

    // Main menu loop
    while (!WindowShouldClose()) {

        // Draw
        BeginDrawing();
        ClearBackground(Background);
        GameMenu.DrawMenuBox();

        // Check if the game has started
        if (Flags::isGameStarted()) {
            if (Flags::isSinglePlayer()) Game.SinglePlayerMode();
            else if (Flags::isMultiplayerGame()) Game.MultiplayerMode();
        }
        else if (Flags::isFENSettingsOpened()) Game.FENSettings();
        else if (Flags::SettingsOpened()) Game.Settings();
        else {
            if (GameMenu.StartSingleplayer || GameMenu.StartMultiplayer) {
                Flags::StartGame();
                if (GameMenu.StartSingleplayer) Flags::SinglePlayerMode();
                else if (GameMenu.StartMultiplayer) Flags::MultiplayerMode();
            }
            if (GameMenu.OpenSettings) Flags::OpenSettings();
            if (GameMenu.LoadFromFen) Flags::OpenFENSettings();
            Game.DisplayBoard();
            GameMenu.ShowMenu();
        }
        EndDrawing();
    }
    //Game.SaveTranspositions();
    Game.chessboard.saveCurrentFENtofile("UnexpectedExits.txt");
    Game.Destroy();
    UnloadSound(ChessPiecePlaced);
    UnloadSound(ChessPieceCaptured);
    UnloadSound(KingChecked);
    UnloadSound(GameEnds);
    UnloadSound(GameStarts);
    UnloadFont(myFont);
    UnloadImage(icon);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}