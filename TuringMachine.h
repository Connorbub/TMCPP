//
//  C++ description of a Turing machine.
//

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using std::vector;
using std::string;
using std::deque;
using std::ostream;

// Tape head movement direction (Left or Right)
enum Direction {L, R};

// Makes my life easier.
// INPUTS: ostream (usually std::cout) and an array-like object (vector,deque,etc)
// RETURNS: ostream with formatted contents of the array object
template <class T>
void printVector(ostream &os, T v) {
    os << "{";
    
    if (v.empty()) {
        os << "!! EMPTY SET !! }";
        return;
    }
    
    for (int i = 0; i < v.size()-1; ++i) {
        os << v[i] << ", ";
    }
    os << v[v.size()-1] << "}";
}

// Basic element of the transition function.
// func(old state, value at tape head) = (new state, write value, direction to move head)
struct Transition {
    string currState;
    char currHead;
    string newState;
    char newHead;
    Direction d;
    
    // Basic constructor. Can't be bothered to do deep copies right now.
    Transition(string currState_in, char currHead_in, string newState_in, char newHead_in, Direction d_in)
    :
                currState(currState_in),
                currHead(currHead_in),
                newState(newState_in),
                newHead(newHead_in),
                d(d_in) { }
    
};

// Overloaded cout on transition function.
// (a,b) -> (c,d,L/R)
ostream& operator<<(ostream& os, const Transition& t) {
    os << "(" << t.currState << ", " << t.currHead << ") -> (" << t.newState << ", " << t.newHead << ", " << t.d << ")";
    return os;
}

// Turing Machine class
// Member variables are the 7 elements necessary to define a TM.
// You probably just want to use the TM.run() function.
class TuringMachine {
public:
    
    // Basic constructor with deep copies
    TuringMachine(vector<char> inputAlphabet_in,
                  vector<string> states_in,
                  string initialState_in,
                  vector<string> finalStates_in,
                  vector<Transition> transitionFunction_in) {
        
        for (auto &elt : inputAlphabet_in) {
            inputAlphabet.push_back(elt);
        }
        
        for (auto &elt : states_in) {
            states.push_back(elt);
        }
        
        for (auto &elt : finalStates_in) {
            finalStates.push_back(elt);
        }
        
        for (auto &elt : transitionFunction_in) {
            transitionFunction.push_back(elt);
        }
        
        initialState = initialState_in;
        
    }
    
    // Set initial contents of tape
    void setInput(string x) {
        // Check for empty string
        if (x.length() != 0) {
            // Set tape value, grow tape if necessary
            for (int i = 0; i < x.length(); ++i) {
                tape[i] = x[i];
                tape.push_back('~');
            }
        }
    }
    
    bool run() {
        
        // Set initial state
        currState = initialState;
        
        while (true) {
            
            // Print tape contents for debug purposes
            //printVector(std::cout, tape);
            //std::cout << std::endl;
            
            // Accept if currently at an accepting (final) state
            if (std::find(finalStates.begin(), finalStates.end(), currState) != finalStates.end()) return true;
            
            bool found = false;
            
            // Try and find a valid transition function for our current state + head combo
            for (auto &elt : transitionFunction) {
                if (elt.currState == currState && elt.currHead == tape[headPos]) {
                    // Update state and write to head
                    currState = elt.newState;
                    tape[headPos] = elt.newHead;
                    
                    // Move tape head accordingly
                    (elt.d == L) ? --headPos : ++headPos;
                    
                    // If going past the right end of the tape, grow the tape
                    if (headPos >= static_cast<int>(tape.size())) {
                        tape.push_back('~');
                    }
                    
                    // If going past the left end of the tape, grow the tape in the negative direction
                    if (headPos < 0) {
                        tape.push_front('~');
                        // Keep the headPos >= 0 (makes it easier, trust me)
                        // Easier to "fudge" the headPos for high values than try and convert negatives
                        ++headPos;
                    }
                    
                    // we done with this transition
                    found = true;
                    break;
                }
            }
            // If no valid transition exists, the TM rejects on x
            if (!found) return false;
        }
        
    }
    
    // 7-tuple parameters
    vector<char> inputAlphabet;
    char blankChar = '~';
    vector<char> tapeAlphabet = {blankChar};
    vector<string> states;
    string initialState;
    vector<string> finalStates;
    vector<Transition> transitionFunction;
    
    // Other various important parameters
    deque<char> tape = {'~'};
    int headPos = 0;
    string currState;
    
    
};

// Overloaded cout on a TM to view its 7-tuple parameters and the current tape
// Note: usually called at the beginning of the program so tape = input
ostream& operator<<(ostream& os, const TuringMachine& TM) {
    
    os << "Input alphabet: ";
    printVector(os, TM.inputAlphabet);
    os << "\n";
    
    os << "Blank character: " << TM.blankChar << "\n";
    
    os << "Tape alphabet: ";
    printVector(os, TM.tapeAlphabet);
    os << "\n";
    
    os << "States: ";
    printVector(os, TM.states);
    os << "\n";
    
    os << "Initial State: " << TM.initialState << "\n";
    
    os << "Final States: ";
    printVector(os, TM.finalStates);
    os << "\n";
    
    os << "Current tape: ";
    printVector(os, TM.tape);
    os << "\n";
    
    os << "Transitions: {\n\t";
    for (int i = 0; i < TM.transitionFunction.size()-1; ++i) {
        os << TM.transitionFunction[i] << ",\n\t";
    }
    os << TM.transitionFunction[TM.transitionFunction.size()-1] << "\n}";
    os << "\n";
    
    return os;
}
