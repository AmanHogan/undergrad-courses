#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef Q_LEARNING_H
#define Q_LEARNING_H

#define STATES 100
#define ACTIONS 2
#define ALPHA 0.1
#define GAMMA 0.9
#define EPSILON 0.1

void initialize_q_table(double q_table[STATES][ACTIONS]);
int choose_action(int state, double q_table[STATES][ACTIONS]);
int get_next_state(int state, int action);
double get_reward(int state, int action);
void update_q_table(int state, int action, int next_state, double reward, double q_table[STATES][ACTIONS]);

#endif // Q_LEARNING_H


void initialize_q_table(double q_table[STATES][ACTIONS]) {
    for (int i = 0; i < STATES; i++) {
        for (int j = 0; j < ACTIONS; j++) {
            q_table[i][j] = 0.0;
        }
    }
}

int choose_action(int state, double q_table[STATES][ACTIONS]) {
    if ((double)rand() / RAND_MAX < EPSILON) {
        return rand() % ACTIONS; // Explore
    } else {
        // Exploit
        int best_action = 0;
        for (int i = 1; i < ACTIONS; i++) {
            if (q_table[state][i] > q_table[state][best_action]) {
                best_action = i;
            }
        }
        return best_action;
    }
}

int get_next_state(int state, int action) {
    // Define your state transition logic here
    // For simplicity, let's assume state + action (0 or 1)
    return (state + action) % STATES;
}

double get_reward(int state, int action) {
    // Define your reward function here
    return (state == 4 && action == 1) ? 1.0 : 0.0;
}

void update_q_table(int state, int action, int next_state, double reward, double q_table[STATES][ACTIONS]) {
    double best_next_action_value = q_table[next_state][0];
    for (int i = 1; i < ACTIONS; i++) {
        if (q_table[next_state][i] > best_next_action_value) {
            best_next_action_value = q_table[next_state][i];
        }
    }
    q_table[state][action] += ALPHA * (reward + GAMMA * best_next_action_value - q_table[state][action]);
}

int main() {
    srand(time(NULL));

    double q_table[STATES][ACTIONS];
    initialize_q_table(q_table);

    for (int episode = 0; episode < 1000; episode++) {
        int state = rand() % STATES;
        for (int step = 0; step < 100; step++) {
            int action = choose_action(state, q_table);
            int next_state = get_next_state(state, action);
            double reward = get_reward(state, action);
            update_q_table(state, action, next_state, reward, q_table);
            state = next_state;
        }
    }

    printf("Q-Table after training:\n");
    for (int i = 0; i < STATES; i++) {
        for (int j = 0; j < ACTIONS; j++) {
            printf("%f ", q_table[i][j]);
        }
        printf("\n");
    }

    return 0;
}
