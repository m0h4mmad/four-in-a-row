#include <iostream>
#include "BoardGame_Classes.h"
#include "4_in_a_row.h"  // Add this line

using namespace std;

int main() {
    int gameChoice;
    cout << "Choose a game:\n";
    cout << "1. Tic-Tac-Toe\n";
    cout << "2. Four-in-a-Row\n";
    cin >> gameChoice;

    switch(gameChoice) {
        case 1: {
            // Existing Tic-Tac-Toe setup code...
            break;
        }
        case 2: {
            int choice;
            Player<char>* players[2];
            FourInARowBoard<char>* B = new FourInARowBoard<char>();
            string playerXName, player2Name;

            cout << "Welcome to Four-in-a-Row Game. :)\n";

            // Set up player 1
            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[0] = new FourInARowPlayer<char>(playerXName, 'X');
                    break;
                case 2:
                    players[0] = new FourInARowRandomPlayer<char>('X');
                    break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    return 1;
            }

            // Set up player 2
            cout << "Enter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[1] = new FourInARowPlayer<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new FourInARowRandomPlayer<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }

            // Create the game manager and run the game
            GameManager<char> four_in_a_row_game(B, players);
            four_in_a_row_game.run();

            // Clean up
            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
            break;
        }
        default:
            cout << "Invalid game choice.\n";
            return 1;
    }

    return 0;
}