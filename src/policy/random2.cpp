#include <cstdlib>

#include "../state/state.hpp"
#include "./random2.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move player_one::get_move(State *state, int depth){
    if(!state->legal_actions.size())
        state->get_legal_actions();
  
    auto actions = state->legal_actions;
    Move max_i , min_i;
    if(!state->player){
        for(auto i : actions){
            State *nextstate = state -> next_state(i);
            int max = -10000;
            int next = nextstate->evaluate();
            if (next > max){
                max = next;
                max_i = i;
            }
        }

        return max_i;
    }

    else{
        for(auto i : actions){
            State *nextstate = state -> next_state(i);
            int min = 10000;
            int next = nextstate->evaluate();
            if (next < min){
                min = next;
                min_i = i;
            }
        }

        return min_i;
    } 
}