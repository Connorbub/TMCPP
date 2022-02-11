// Main test program for the TuringMachine class.

#include <iostream>

#include "TuringMachine.h"

using std::cout;
using std::endl;

int main(int argc, const char *argv[])
{

    // Binary Increment TM
    // {
    // Set initial variables according to the 7-tuple definition of a TM
    vector<char> inputAlphabet = {'0', '1'};
    vector<string> states = {"right", "carry", "done"};
    string initialState = "right";
    vector<string> finalStates = {"done"};

    // Transitions are defined as: {currState, currHead, newState, writeValue, headDirection}
    vector<Transition> transitionFunction = {
        Transition("right", '1', "right", '1', R),
        Transition("right", '0', "right", '0', R),
        Transition("right", '~', "carry", '~', L),
        Transition("carry", '1', "carry", '0', L),
        Transition("carry", '0', "done", '1', L),
        Transition("carry", '~', "done", '1', L)};
    // }

    // Divisible by 3 (decimal) TM
    // {
    // Set initial variables according to the 7-tuple definition of a TM
    // vector<char> inputAlphabet = {'0','1','2','3','4','5','6','7','8','9'};
    // vector<string> states = {"q0","q1","q2", "accept"};
    // string initialState = "q0";
    // vector<string> finalStates = {"accept"};

    // // Transitions are defined as: {currState, currHead, newState, writeValue, headDirection}
    // vector<Transition> transitionFunction = {
    //     Transition("q0",'0',"q0",'0',R),
    //     Transition("q0",'3',"q0",'3',R),
    //     Transition("q0",'6',"q0",'6',R),
    //     Transition("q0",'9',"q0",'9',R),

    //     Transition("q0",'1',"q1",'1',R),
    //     Transition("q0",'4',"q1",'4',R),
    //     Transition("q0",'7',"q1",'7',R),

    //     Transition("q0",'2',"q2",'2',R),
    //     Transition("q0",'5',"q2",'5',R),
    //     Transition("q0",'8',"q2",'8',R),

    //     Transition("q0",'~',"accept",'~',R),

    //     Transition("q1",'0',"q1",'0',R),
    //     Transition("q1",'3',"q1",'3',R),
    //     Transition("q1",'6',"q1",'6',R),
    //     Transition("q1",'9',"q1",'9',R),

    //     Transition("q1",'1',"q2",'1',R),
    //     Transition("q1",'4',"q2",'4',R),
    //     Transition("q1",'7',"q2",'7',R),

    //     Transition("q1",'2',"q0",'2',R),
    //     Transition("q1",'5',"q0",'5',R),
    //     Transition("q1",'8',"q0",'8',R),

    //     Transition("q2",'0',"q2",'0',R),
    //     Transition("q2",'3',"q2",'3',R),
    //     Transition("q2",'6',"q2",'6',R),
    //     Transition("q2",'9',"q2",'9',R),

    //     Transition("q2",'1',"q0",'1',R),
    //     Transition("q2",'4',"q0",'4',R),
    //     Transition("q2",'7',"q0",'7',R),

    //     Transition("q2",'2',"q1",'2',R),
    //     Transition("q2",'5',"q1",'5',R),
    //     Transition("q2",'8',"q1",'8',R)

    // };
    // }

    // // Palindrome Checker TM
    // // {
    // // Set initial variables according to the 7-tuple definition of a TM
    // vector<char> inputAlphabet = {'a', 'b'};
    // vector<string> states = {"start", "haveA", "haveB", "matchA", "matchB", "back", "accept", "reject"};
    // string initialState = "start";
    // vector<string> finalStates = {"accept"};

    // // Transitions are defined as: {currState, currHead, newState, writeValue, headDirection}
    // vector<Transition> transitionFunction = {
    //     Transition("start", 'a', "haveA", '~', R),
    //     Transition("start", 'b', "haveB", '~', R),
    //     Transition("start", '~', "accept", '~', R),

    //     Transition("haveA", 'a', "haveA", 'a', R),
    //     Transition("haveA", 'b', "haveA", 'b', R),
    //     Transition("haveA", '~', "matchA", '~', L),

    //     Transition("haveB", 'a', "haveB", 'a', R),
    //     Transition("haveB", 'b', "haveB", 'b', R),
    //     Transition("haveB", '~', "matchB", '~', L),

    //     Transition("matchA", 'a', "back", '~', L),
    //     Transition("matchA", 'b', "reject", 'b', R),
    //     Transition("matchA", '~', "accept", '~', R),

    //     Transition("matchB", 'a', "reject", 'a', R),
    //     Transition("matchB", 'b', "back", '~', L),
    //     Transition("matchB", '~', "accept", '~', R),

    //     Transition("back", 'a', "back", 'a', L),
    //     Transition("back", 'b', "back", 'b', L),
    //     Transition("back", '~', "start", '~', R),

    // };
    // // }

    // Create new TM with given input parameters
    TuringMachine TM(inputAlphabet, states, initialState, finalStates, transitionFunction);

    // Set initial contents of the tape
    TM.setInput("101010000000011101001101111111");

    // View initial contents and simulate the TM
    cout << TM;
    cout << ((TM.run()) ? "Accepted!" : "Rejected.") << endl;

    // Print final tape contents
    printVector(std::cout, TM.tape);
    std::cout << std::endl;

    return 0;
}
