# TMCPP
An implementation of a Turing Machine framework in C++

Based on the 7-tuple definition of a Turing Machine.

## Usage

Modify the initial variables in `main.cpp`. 

The transition function is in the format: `Transition(currState, currHead, newState, writeValue, headDirection)`.

## Notes

This code is pretty bad, as it was more just a test/proof of concept for myself. It is horribly inefficient and tedious to encode machines in, but I still think it's pretty cool.

## TODO

- Make an automatic TM code generator to make it easier to design a machine
- Make the code run more gooder (i.e. don't loop through the entire vector of states and check string equivalency!)
