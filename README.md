# IntelligentTicTacToe
The attempt to create a neural network capable of learning TicTacToe.

# Theoretical  background 
[Neural Networks (David Kriesel)](http://www.dkriesel.com/_media/science/neuronalenetze-en-zeta2-2col-dkrieselcom.pdf)

# Getting everything running
1. Compile the project with the command 'make'!
2. Run the generated binary './IntelligentTicTacToe'!
3. Use the standard input, to control the programm during runtime (see Commands section)!

# Commands
1. Instruction: If you type '-1', the current time in sec. since the system epoch is taken as seed for the random number generator. If you specify a number, probably from a previous run, this seed is taken and you can generate the same behaviour as in the previous run, useful for debugging!
2. Instruction: Specify the way, you want to construct your neural network. Implemented is a fully connected non-recurrent network, which is only characterized by the number of hidden neurons, a layered network, characterized by the number of layers and the number of neurons per layer, and the possibility to load an already trained network from file, specified by the file name.
3a-b. Instruction: Depending on the previous choice, you have to give detailed information on your neural network.
4. Instruction: From now on you have to specify simulation details. You are asked, if you want to train the neural network against a human, an implemented automated player based on an algorithm, or against itself. The human option should be used only for playing against an already trained network, since the training process takes at least 10.000 games to be significantly.
5. Instruction: Now you have to specify the learning rate for this simulation run.
6. Instruction: Specify the number of games, the simulation should run with the previous given configuration.

The simulation should run now and give you information on how long the training process takes. During the training process a file is generated and written to. The winSeries.txt, where a value for each game is given, with reaching 1=100% being a very sophisticated game. At the end of each simulation the current state of the network is printed to 'network.nn' and can be used to laod into a different training session. Both files get overwritten after a new simulation run. At the end the programm doesn't terminate but steps 4-6 are repated. To exit the programm, press 'Ctrl-C'!