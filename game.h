struct tictactoe{
private:
	//scores
	int player1;
	int player2;
	
	//win condition depending on number of matches being played
	int win_condition;
	
	//true = turn of player 1, false = turn of player 2/AI
	bool turn;
	
	//true = against AI, false = PvP
	bool with_comp;
	
	//state of the gameboard
	char game[3][3];
	
	//set the desired number of matches
	int set_count();
	
	//print the board on screen
	void print();
	
	//clean the state of the board for a new game
	void clean_board();
	
	//is the round over?
	bool is_over();
	
	//did someone win?
	bool is_won();
	
	//does this point exist on the gameboard?
	bool validate(int, int);
	
public:
	//constructer
	tictactoe();
	//start the game
	void play(bool);
};