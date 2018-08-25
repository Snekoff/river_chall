#define _CRT_SECURE_NO_WARNINGS
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
        return 0;
    }
    void action(char c, int StreamStrength) {
        printf("%s %c %s", "You chosed '", c, "' \n");
        printf("%s %d %s", "Stream strength is", StreamStrength, " ");
        if (EnemyHP > 0) {
            printf("%s %d %s", "Your Hp = ", hp, " ");
            printf("%s %d %s", "Enemy Hp = ", EnemyHP, " ");
        }
        printf("%s %d %s", "distance = ", distance, " \n");

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
        else {
            printf("%s", "You failed in typing right command, try again.{s,r,a}\n");
            while(c != 's' && c!= 'r' && c!= 'a'){
                cin >> c;
            }
            action(c,StreamStrength);
        }
        printf("%s", "\n");
    };

    ~canoe_rider() {};

};

int main() {
    setlocale(LC_ALL, "RU");
    int place = 0;
    srand(time(NULL));
    cout << "Welcome, to my game called river challenge\n";
    printf("%s", "In this game you will be given one or few canoe riders,\n");
    printf("%s", "your GREAT MISSION to have them reach the End of the river.\n");
    printf("%s", "That is easy, or not ?....\n");
    printf("%s", "Lets Start with choosing number of players, u can insert any number from 1 to 10, or '0' to generate randomly\n");
    int c = 0;
    scanf("%d", &c);
    while(c>10 || c<0){
        printf("%s", "Try another number (from 0 to 10)\n");
        scanf("%d", &c);
    }
    if(c == 0){
        c = rand() %10 +1;
        printf("%d \n",c);
    }
    int DeadRiverChallengers = 0;
    canoe_rider* player[10];
    for(int i = 0; i < c;i++){
        player[i] = new canoe_rider(rand() % 10 + 2, rand() % 100 + 10);
    }

    /*canoe_rider playerOne(rand() % 10 + 1, rand() % 100 + 1);
    canoe_rider playerTwo(rand() % 10 + 1, rand() % 100 + 1);
    canoe_rider playerThr(rand() % 10 + 1, rand() % 100 + 1);*/
    int end = rand() %10 +1;
    int StreamStrength = rand() % 9 + 1;
    int turn = 1;
    bool PlayerFinished[10] = {false};
    bool GamesDone = false;
    while(!GamesDone) {
        printf("%s %d %s", "Turn ", turn, "\n");
        for (int i = 0; i < c; i++) {
            int finished = 0;
            for(int j = 0; j < c;j++){
                if(PlayerFinished[i])finished++;
            }
            if(finished == c){GamesDone = true; break;}
            int chance = rand() % 10;
            int hp_, stamina_, distance_;
            hp_ = player[i]->get(0);
            if (hp_ < 1) { printf("%s %d \n", "Rest in peace, player",i); DeadRiverChallengers--; PlayerFinished[i] = true; continue; }
            stamina_ = player[i]->get(1);
            distance_ = player[i]->get(2);


            printf("%s %d %s", "######################  Player", i+1, "`s turn:  ######################\n");
            printf("%s %d %s", "## Hp =", hp_, " ");
            printf("%s %d %s", "Stamina =", stamina_, " ");
            printf("%s %d %s", "distance =", distance_, " ");
            printf("%s %*d %s", "End of the river on", -3, end, "##\n");// instead of -3 use some variable
            printf("%s %d %s", "## Stream strength =", StreamStrength, "##\n");
            if (chance < 1){
                player[i]->setEnemyHp(player[i]->get(3) + 1);
                printf("%s %s","\n", ">>>*Dramatic worrying music starts* Crocodile bite your arm!<<<\n");
                printf("%s %d %s", ">>> Enemy hp =", player[i]->get(3), " \n");
            }
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
                    if (player[i]->get(0) - 1 < 1) {
                        printf("%s %d \n", "Rest in peace, player",i+1);
                        DeadRiverChallengers--;
                        PlayerFinished[i] = true;
                        continue;
                    }
                    else {
                        player[i]->set(player[i]->get(0) - 1, player[i]->get(1));
                        player[i]->action(c, StreamStrength);
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
                    player[i]->action(c, StreamStrength);

            }
            if (player[i]->get(2) >= end && !PlayerFinished[i]) { PlayerFinished[i] = true; printf("%s %d %s %d %s", "Player",i+1,"FINISHED on", place++, "place\n"); }
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
//version 0.4