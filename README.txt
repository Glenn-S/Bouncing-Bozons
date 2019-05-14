CPSC 441 Assignment 4
Glenn Skelton
10041868

----------------------------------------------------------------------------------------------------------
COMPILE

If your system has make intalled please enter the following to build:
    >>>make all
    >>>./simulator

Alternatively to just build and run at the same time type:
    >>>make run

If make is not enabled type:
    >>>g++ -Wall -g bozon.cpp -c
    >>>g++ -Wall -g atmosphere.cpp -c
    >>>g++ -Wall -g simulator.cpp -c
    >>>g++ -Wall -g main.cpp *.o -o simulator
    >>>./simulator

----------------------------------------------------------------------------------------------------------
OPERATION

Once the system is up the user will be prompted to either enter 1 to commence running a simulation 
or 2 to exit. In order to set up the simulation once 1 has been pressed, the user will be asked to 
enter 3 values (M S Y). The 3 values require a space to seperate each number. Afer inputting the 
parameters, press enter and the simulation will output the results to standard output.

----------------------------------------------------------------------------------------------------------
TESTING

Testing was performed by running simulations of various size and plotting the data to observe the trends. 
Individual component testing was also done as the modules were being buitl to verify correctness of the
assignment components. 
