# Ichor

Ichor is a systems programming language with an embedded-first design.

This repo will hold the compiler, maybe some sort of standard library, and if I get *really* bored, documentation lol

### Why?
I wanted a challenge and making a language seemed fun.

### Plan
The plan is to write the initial compiler in C. The backend will use LLVM because I can't be asked to do code-gen for all the different types of hardware out there.

The ultimate end-goal for now is to make the compiler bootstrapped. The super strech goal would be to write a backend that is optimized for MCUs.
Idk how optimized LLVM is when targeting MCU architecure, so that might be a fun research project once the compiler is bootstrapped.

### Name
Ichor (pronounced eye-kore) is the blood of the gods in Greek mythology. The goal is to have this language be the "blood" of a MCU.


