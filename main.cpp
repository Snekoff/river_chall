#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <clocale>

using namespace std;

class canoe_rider {
private:
    int hp;
    int MaxHp;
    int stamina;
    int MaxStamina;
    int distance;
    int EnemyHP;
public:
    canoe_rider (int a, int b) {
        distance = 0;
        MaxHp = a;
        EnemyHP = 0;
        MaxStamina = b;
        set(a, b);
    };
    void set(int a, int b) {
        if (a > 0 && b > 0) {
            hp = a;
            stamina = b;
            if (MaxHp < hp) { MaxHp = hp; }
            if (MaxStamina < stamina) { MaxStamina = stamina; }
        }
        else {
            while (a < 0 || b < 0) {
                cout << "wrong input, try again..\n";
                cin >> a >> b;
            }
        }
    };
    void setEnemyHp(int a) {
        if (a > 0) {
            EnemyHP = a;
        }
        else {
            while (a < 0) {
                cout << "wrong input, try again.\n";
                cin >> a;
            }
        }
    }
    int get(int a) {
        if (a == 0) {
            return hp;
        }
        else if (a == 1) {
            return stamina;
        }
        else if (a == 2) {
            return distance;
        }
        else if (a == 3) {
            return EnemyHP;
        }
    }
    void action(char c, int StreamStrength) {
        printf("%s %d %s", "*** Stream strength is ", StreamStrength, " ");
        if (EnemyHP > 0) {
            printf("%s %d %s", "Your Hp = ", hp, " ");
            printf("%s %d %s", "Enemy Hp = ", EnemyHP, " ");
        }
        printf("%s %d %s", "distance = ", distance, " ");
        printf("%s %c %s", "You chosed '", c, "' ***\n");
        if (c == 'a' || c == 'A') {
            if (stamina < 2) {
                printf("%s", "You need a rest, good luck!");
                //c = 'r';
                action('r', StreamStrength);
            }
            else if(EnemyHP > 0){
                printf("%s", "*Satisfying sound of victory* You hit the creature with your arm and killed it, congratulations\n");
                EnemyHP--;
                stamina -= 2;
                printf("%s %d %s", "Hp = ", hp, " ");
                printf("%s %d %s", "stamina = ", stamina, " ");
                printf("%s %d %s", "distance = ", distance, "\n");
            }
            else {
                cout << "nobody to atack, chose swim or rest.\n";
                cin >> c;
                action(c, StreamStrength);
            }
        }
        else if (c == 's' || c == 'S') {
            if (EnemyHP > 0) { printf("%s", "Crocodile still follows and atacks you\n"); hp--; }
            if (stamina > StreamStrength) {
                stamina -= StreamStrength;
                distance++;
                printf("%s %d %s", "Hp = ", hp, " ");
                printf("%s %d %s", "stamina = ", stamina, " ");
                printf("%s %d %s", "distance = ", distance, "\n");
            }
            else{ cout << "you need rest a while...\n";
                action('r', StreamStrength);
            }
        }
        else if (c == 'r' || c == 'R') {
            if (EnemyHP > 0) { printf("%s","Crocodile still follows and atacks you\n"); hp--; }
            if (stamina < MaxStamina) { stamina += 5;
                if (stamina > MaxStamina) { stamina = MaxStamina; }
            }
            if (hp < MaxHp && EnemyHP < 0) { hp++; }
            distance -= StreamStrength / 5;
            if (distance < 0) distance = 0;
            printf("%s %d %s", "Hp = ", hp, " ");
            printf("%s %d %s", "stamina = ", stamina, " ");
            printf("%s %d %s", "distance = ", distance, "\n");
        }
        printf("%s", "\n");
    };

    ~canoe_rider() {};

};

int main() {
    setlocale(LC_ALL, "RU");
    srand(time(NULL));
    cout << "Welcome, to my game called river challange\n";
    printf("%s", "In this game you will be given one or few canoe riders,\n");
    printf("%s", "your GREAT MISSION to have them reach the End of the river.\n");
    printf("%s", "That is easy, or not ?....\n");
    int c = 3;
    int DeadRiverChallengers = 0;
    /*c = rand() % 4 + 1;
    for (int i = 0; i < c; i++) {

    }*/

    canoe_rider playerOne(rand() % 10 + 1, rand() % 100 + 1);
    canoe_rider playerTwo(rand() % 10 + 1, rand() % 100 + 1);
    canoe_rider playerThr(rand() % 10 + 1, rand() % 100 + 1);
    int end = rand() %10 +1;
    int StreamStrength = rand() % 10 + 1;
    int turn = 1;
    bool playerOneFinished = false, playerTwoFinished = false, playerThrFinished = false;
    while(!playerOneFinished || !playerTwoFinished || !playerThrFinished) {
        printf("%s %d %s", "Turn ", turn, "\n");
        for (int i = 1; i <= c; i++) {
            if (i == 1 && playerOneFinished) { continue; } // distance
            if (i == 2 && playerTwoFinished) { continue; }
            if (i == 3 && playerThrFinished) { continue; }
            int chance = rand() % 10;
            int hp_, stamina_, distance_;
            if (i == 1) {
                hp_ = playerOne.get(0);
                if (hp_ < 1) { printf("%s", "Rest in peace, player 0ne.\n"); DeadRiverChallengers--; playerOneFinished = true; continue; }
                stamina_ = playerOne.get(1);
                distance_ = playerOne.get(2);
                if (chance < 1) playerOne.setEnemyHp(playerOne.get(3) + 1);
            }
            else if (i == 2) {
                hp_ = playerTwo.get(0);
                if (hp_ < 1) { printf("%s", "Rest in peace, player Two.\n"); DeadRiverChallengers--; playerTwoFinished = true; continue; }
                stamina_ = playerTwo.get(1);
                distance_ = playerTwo.get(2);
                if (chance < 1) playerTwo.setEnemyHp(playerTwo.get(3) + 1);
            }
            else if (i == 3) {
                hp_ = playerThr.get(0);
                if (hp_ < 1) { printf("%s", "Rest in peace, player tHree.\n"); DeadRiverChallengers--; playerThrFinished = true; continue; }
                stamina_ = playerThr.get(1);
                distance_ = playerThr.get(2);
                if (chance < 1) playerThr.setEnemyHp(playerThr.get(3) + 1);
            }
            printf("%s %d %s", "######################  Player", i, "`s turn:  ######################\n");
            printf("%s %d %s", "## Hp =", hp_, " ");
            printf("%s %d %s", "Stamina =", stamina_, " ");
            printf("%s %d %s", "distance =", distance_, " ");
            printf("%s %*d %s", "End of the river on", -3, end, "##\n");// instead of -3 use some variable

            if(i == 1){if(playerOne.get(3) > 0) printf("%s %d %s", "-> Enemy hp =", playerOne.get(3), " \n");}
            else if(i == 2){ if (playerTwo.get(3) > 0) printf("%s %d %s", "-> Enemy hp =", playerTwo.get(3), " \n"); }
            else if(i == 3){ if (playerThr.get(3) > 0) printf("%s %d %s", "-> Enemy hp =", playerThr.get(3), " \n"); }

            if(chance < 1) printf("%s %s %s","\n", ">>>*Dramatic worrying music starts* Crocodile bite your arm!<<<\n", "\n");

            printf("%s", "## type 's' to swim, type 'r' to rest, type 'a' to atack       ##\n");
            printf("%s", "#################################################################\n");
            char c;
            cin >> c;
            while (c != 'S' && c != 's' && c != 'R' && c != 'r' && c != 'A' && c != 'a') {
                printf("%c %s", c, "\n");
                printf("%s", "Game won`t proceed until you type valid key\n");
                cin >> c;
            }

            if (chance < 1) {

                if (i == 1) {
                    if (playerOne.get(0) - 1 < 1) {
                        printf("%s", "Rest in peace, player One.\n");
                        DeadRiverChallengers--;
                        playerOneFinished = true;
                        continue;
                    }
                    else {
                        playerOne.set(playerOne.get(0) - 1, playerOne.get(1));
                        playerOne.action(c, StreamStrength);
                    }
                }
                else if (i == 2) {
                    if (playerTwo.get(0) - 1 < 1) {
                        printf("%s", "Rest in peace, player two.\n");
                        DeadRiverChallengers--;
                        playerTwoFinished = true;
                        continue;
                    }
                    else { playerTwo.set(playerTwo.get(0) - 1, playerTwo.get(1));
                        playerTwo.action(c, StreamStrength); }
                }
                else if (i == 3) {
                    if (playerThr.get(0) - 1 < 1) {
                        printf("%s", "Rest in peace, player three.\n");
                        DeadRiverChallengers--;
                        playerThrFinished = true;
                        continue;
                    }
                    else { playerThr.set(playerThr.get(0) - 1, playerThr.get(1));
                        playerThr.action(c, StreamStrength); }
                }

            }
            else {
                if (turn == 1) {
                    printf("%s", "There is always the view...\n");
                }
                else {
                    int ViewMessage = rand() % 4;
                    if(ViewMessage == 0){ printf("%s", "Threes and bushes passing by...\n"); }
                    else if(ViewMessage == 1){ printf("%s", "Sun covered with clouds made landscape gone faded.\n"); }
                    else if (ViewMessage == 2) { printf("%s", "Really big shiny carp jumped in the air right near you.\n"); }
                    else if (ViewMessage == 3) { printf("%s", "Sun is smiles through small space betwen few clouds.\n"); }

                }
                if (i == 1) {
                    playerOne.action(c, StreamStrength);
                }
                else if (i == 2) {
                    playerTwo.action(c, StreamStrength);
                }
                else if (i == 3) {
                    playerThr.action(c, StreamStrength);
                }

            }
            if (playerOne.get(2) >= end && !playerOneFinished) { playerOneFinished = true; printf("%s %d %s", "Player One FINISHED on", playerOneFinished + playerTwoFinished + playerThrFinished + DeadRiverChallengers, "place\n"); }
            if (playerTwo.get(2) >= end && !playerTwoFinished) { playerTwoFinished = true; printf("%s %d %s", "Player Two FINISHED on", playerOneFinished + playerTwoFinished + playerThrFinished + DeadRiverChallengers, "place\n"); }
            if (playerThr.get(2) >= end && !playerThrFinished) {
                playerThrFinished = true; printf("%s %d %s", "Player Three FINISHED on", playerOneFinished + playerTwoFinished + playerThrFinished + DeadRiverChallengers, "place\n");
            }
        }
        turn++;
    }
    //printf("", "");
    return 0;
}
//
//
//
//
//
//version 0.31