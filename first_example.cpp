#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

int main()
{
const int NUM_STATES = 5;
const int NUM_ACTIONS = 2;

std::vector<std::vector<double>> Q(NUM_STATES, std::vector<double>(NUM_ACTIONS, 0.0));

double alpha = 0.1;
double gamma = 0.9;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution actionDist(0, NUM_ACTIONS - 1);
double reward{0};
for (int episode = 0; episode < NUM_STATES*2; ++episode) {
        int state = episode % NUM_STATES;

        int action = actionDist(gen);

        double newReward = (action == 1) ? 10.0 : 0.0;
        double oldReward = reward;

        reward = alpha * newReward + (1 - alpha) * oldReward;

        int nextState = (state + 1) % NUM_STATES;
        double maxQNext = *std::max_element(Q[nextState].begin(), Q[nextState].end());

        Q[state][action] = Q[state][action] + alpha * (reward + gamma * maxQNext - Q[state][action]);

        std::cout << "Episode " << episode << ", State " << state << ", Action " << action 
                  << ", Reward " << reward << ", Updated Q = " << Q[state][action] << "\n";
    }

}
