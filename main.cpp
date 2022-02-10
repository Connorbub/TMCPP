// Main test program for the TuringMachine class.

#include <iostream>

#include "TuringMachine.h"

using std::cout;
using std::endl;

int main(int argc, const char * argv[]) {
    
    // Set initial variables according to the 7-tuple definition of a TM
    vector<char> inputAlphabet = {'0','1'};
    vector<string> states = {"right","carry","done"};
    string initialState = "right";
    vector<string> finalStates = {"done"};
    
    // Transitions are defined as: {currState, currHead, newState, writeValue, headDirection}
    vector<Transition> transitionFunction = {
        Transition("right",'1',"right",'1',R),
        Transition("right",'0',"right",'0',R),
        Transition("right",'~',"carry",'~',L),
        Transition("carry",'1',"carry",'0',L),
        Transition("carry",'0',"done",'1',L),
        Transition("carry",'~',"done",'1',L)
    };
    
    // Create new TM with given input parameters
    TuringMachine TM(inputAlphabet, states, initialState, finalStates, transitionFunction);
    
    // Set initial contents of the tape
    TM.setInput("1");
    
    // View initial contents and simulate the TM
    cout << TM;
    cout << ((TM.run()) ? "Accepted!" : "Rejected.") << endl;
    
    // Print final tape contents
    printVector(std::cout, TM.tape);
    std::cout << std::endl;
    
    return 0;
}
