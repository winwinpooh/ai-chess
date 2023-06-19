#include <cstdlib>

#include "../state/state.hpp"
#include "./alpha_beta.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

int alphabeta(State* child, int depth , int alpha, int beta, bool maximizingPlayer){
    if(depth == 0 || child->legal_actions.size() == 0){
        return child->evaluate();
    }

    if(!child->legal_actions.size())
        child->get_legal_actions();

    auto actions = child->legal_actions;
    if(maximizingPlayer){
        int value = -10000;
        for(auto i : actions){
            State *nextstate = child ->next_state(i);
            value = std::max(value , alphabeta(nextstate , depth - 1 , alpha, beta, false));
            alpha = std::max(alpha, value);
            if (alpha >= beta){
                break;
            }
        }
        return value ;
    }

    else{
        int value = 10000;
        for (auto i : actions){
            State *nextstate = child ->next_state(i);
            value = std::min(value , alphabeta(nextstate , depth - 1 , alpha, beta, true));
            beta = std::min(beta , value);
            if (beta <= alpha){
                break;
            }
        }

        return value ;
    }
}

Move alpha_beta::get_move(State *state, int depth){
    if(!state->legal_actions.size())
        state->get_legal_actions();
  
    auto actions = state->legal_actions;
    Move max_i , min_i;
    if(!state->player){
        int max = -10000;
        for(auto i : actions){
            State *nextstate = state -> next_state(i);
            int next = alphabeta(nextstate, depth - 1 , -10000 , 10000, false);
            if (next > max){
                max = next;
                max_i = i;
            }
        }

        return max_i;
    }

    else{
        int min = 10000;
        for(auto i : actions){
            State *nextstate = state -> next_state(i);
            int next = alphabeta(nextstate, depth - 1, -10000, 10000, true);
            if (next < min){
                min = next;
                min_i = i;
            }
        }

        return min_i;
    } 
}