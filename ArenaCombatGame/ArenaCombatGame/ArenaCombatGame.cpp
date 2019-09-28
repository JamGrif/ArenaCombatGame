#include "pch.h"
#include <iostream>
#include <string>
#include <string.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <windows.h>

//Made by Jamie Griffiths

using namespace std;

//Enumerations here

enum Action 
{
	Attack = 1,
	Special = 2,
	Recharge = 3,
	Dodge = 4,
	Heal = 5,
	
};

//Structures here

struct Character 
{
	string Name;
	const int MaxHealth = 100;
	const int MinHealth = 0;
	int Health = MaxHealth;
	const int MaxEnergy = 50;
	const int MinEnergy = 0;
	int Energy = MaxEnergy;
	int ChargingRate = 10;
	bool Dead = false;
	bool HealedThisTurn = false;
	int ChanceToHit = 0;
	int IncreasedChance = 0;
	int DecreasedChance = 0;
	int Damage = 0;
	int Healing = 0;
	int Recharge = 10;
	int RechargeRate = 1;
	int Score = 0;



};

//Below the structures are made and assigned names 
Character Player;
Character Computer;


//Variables here


//Below is used for the computer when deciding what action to use. The numbers below are the default numbers the computer will start with. The TotalChance is sum of the 5 actions added together
int AttackChance = 22;
int SpecialChance = 22;
int RechargeChance = 12;
int DodgeChance = 22;
int HealChance = 22;
int TotalChance = 0;

int ChanceNumber = 0; //
const int MaxChance = 100; // used in finding the characters chance to land a hit
const int MinChance = 0; // used in finding the characters chance to land a hit



int Action = 0; //Used in the Enumration to decide what action will be used. Can only be a value between 1 and 5

int RolledNumber = 0; //This is a variable that is only used when rolling for a random number. It is reset after it is used.

string MenuChoice; //This variable is used for selecting what action to use on the main menu depending on what the user selected.
string EndChoice; //This variable is used for selecting what action to use on the end game menu depending on what the user selected.

bool InvalidKey = false; //Used for the endgame function and when set to true means the user entered an invalid key and must re-enter a valid one

//Functions here

//Functions below are related to the menu 
void Menu();
void SelectName();
void Instructions();
void EndGame();

//Funcitons below are used for the player
void PlayerAction();
void PlayerOutcome();
void PlayerEndOfRound();

//Functions below are used for the computer
void ComputerChance();
void ComputerPicker();
void ComputerAction();
void ComputerEndOfRound();




//for sleep 1000 = 1 second

//This is the starting function and simply introduces the user to the game. It immediatly goes to the Menu
int main()
{
	//Expected lose of data below
	srand(time(0));
	cout << "Made by Jamie Griffiths" << endl;
	cout << "Welcome to Kill The Knight Simulator 2018" << endl;
	cout << "" << endl;
	Computer.Name = "The Knight";
	Menu();
}


//This is used for the player and asks them for what action they want to use.
void PlayerAction() 
{
	
	cout << "" << endl;
	Sleep(500);
	cout << Player.Name << " has " << Player.Health << " health with a total amount of " << Player.Energy << " energy!" << endl;
	cout << Computer.Name << " has " << Computer.Health << " health with a total amount of " << Computer.Energy << " energy!" << endl;
	cout << "" << endl;
	Sleep(500);
	
	
	PlayerOutcome();

}

//This funciton takes in the input the player entered in the PlayerAction function and performs an action related to their choice. If the action can't be done the game will return back to PlayerAction function.
void PlayerOutcome()
{
	switch (Action) 
	{
	//Attack action
	case Attack: 
		cout << Player.Name << " attempts to attack." << endl;
		cout << " " << endl;
		Player.ChanceToHit = 80 + Player.IncreasedChance - Player.DecreasedChance;
		RolledNumber = (1 + (rand() % MaxChance));
		if (RolledNumber > MinChance && RolledNumber <= Player.ChanceToHit) 
		{
			Player.Damage = (1 + (rand() % 10));
			Computer.Health = Computer.Health - Player.Damage;
			//Player hit the computer
			cout << Player.Name << " successfully hit " << Computer.Name << " dealing " << Player.Damage << " damage!" << endl;
			if (Computer.Health >= 1) 
			{
				//The computer is still alive 
				cout << Computer.Name << " is now on " << Computer.Health << " health!" << endl;
				
			}
			
			else 
			{
				//The computer has died
				cout << Computer.Name << " has died!" << endl;
				Computer.Dead = true;
				
			}
			
		}
		
		else 
		{
			//Player missed
			cout << Player.Name <<  " swung his sword and missed!" << endl;
		}
		break;

	//Special action
	case Special:
		cout << Player.Name << " attempts to perform a special attack!" << endl;
		if (Player.Energy == Player.MaxEnergy) 
		{
			Player.ChanceToHit = 50 + Player.IncreasedChance - Player.IncreasedChance;
			Player.Energy = Player.Energy - 50;
			RolledNumber = (1 + (rand() % MaxChance));

			if (RolledNumber > 0 && RolledNumber <= Player.ChanceToHit) 
			{
				Player.Damage = (1 + (rand() % 20));
				if (Player.Damage <= 4)
				{
					Player.Damage = Player.Damage + 4;
				}
				Computer.Health = Computer.Health - Player.Damage;
				//Player hit computer with special
				cout << Player.Name << " successfully hit " << Computer.Name << " dealing " << Player.Damage << " damage!" << endl;
				if (Computer.Health >= 1)
				{
					//Computer is still alive
					cout << Computer.Name << " is now on " << Computer.Health << " health!" << endl;
					
				}

				else
				{
					//The computer has died
					cout << Computer.Name << " has died!" << endl;
					Computer.Dead = true;
					
				}
				


			}

			else 
			{
				//The player has missed
				cout << Player.Name << " attempted to perform a special attack but missed!" << endl;
				
			}

			cout << "Your energy has been drained as a result of performing the special attack!" << endl;


		}

		else 
		{
			//Player cant perform action via lack of energy
			cout << "You do not have enough energy to perform a special attack, pick another action" << endl;
			PlayerAction();
		}
		break;

	//Recharge action
	case Recharge:
		cout << Player.Name << " attempts to re-charge their energy!" << endl;
		if (Player.Energy != Player.MaxEnergy) 
		{
			//Player will recharge more energy at the end of the round but be more likely to get hit
			cout << Player.Name << " will recharge additional energy this turn! But " << Player.Name << " is more vulnerable to attacks!" << endl;
			Player.RechargeRate = 4; 
			Computer.IncreasedChance = 10;
		}


		else 
		{
			//Player cant recharge as they are on maximum energy
			cout << Player.Name << " is already at max energy! Pick another action.";
			PlayerAction();
		}


		break;

	//Dodge action
	case Dodge:
		//Player will try to dodge next attack but be more likely to get hit
		cout << Player.Name << " will attempt to dodge the next attack!" << endl;
		Computer.DecreasedChance = 30;
		//Expected loss of data below
		Player.RechargeRate = 0.5;

		break;

	//Heal action
	case Heal:
		cout << Player.Name << " attempts to heal!" << endl;
		if (Player.HealedThisTurn == false)
		{
			if (Player.Energy >= 2)
			{
				if (Player.Health != Player.MaxHealth) 
				{
					
					Player.Healing = Player.Energy / 4;
					Player.Energy = Player.Energy / 4;
					if (Player.Energy < Player.MinEnergy)
					{
						Player.Energy = Player.MinEnergy;
					}
					Player.Health = Player.Health + Player.Healing;
					if (Player.Health > Player.MaxHealth)
					{
						Player.Health = Player.MaxHealth;
					}
					//Player has healed for half of their total energy 
					cout << Player.Name << " has healed for " << Player.Healing << "!" << endl;
					cout << Player.Name << " now has " << Player.Health << " health!" << endl;
					Player.HealedThisTurn = true;
					PlayerAction();
				}
				
				else 
				{
					//Player cant healas they are on maximum health
					cout << "You are already on maximum health, pick another action" << endl;
					//Player.HealedThisTurn = true;
					PlayerAction();

				}

			}
			else 
			{
				//Player cant heal as they dont have enough energy
				cout << "You do not have enough energy to heal this turn, pick another action." << endl;
				PlayerAction();
			}


		}
		
		else 
		{
			//Player cant heal as they have already healed this turn
			cout << "You have already healed this turn, pick another action." << endl;
			PlayerAction();
		}


		break;

	default:
		//If the user doesnt select a number between 1 and 5 it will go below and the program will ask the user to reselect an action by going back to the PlayerAction function
		cout << "You must select a value between 1 and 5, try again." << endl;
		PlayerAction();

	}

	if (Computer.Dead == true) 
	{
		EndGame();
	}

	//Once the action has been calculated the program will go to the players end of round funciton to reset any values.
	PlayerEndOfRound();


}




//This function will be run only at the end of the players turn and is used to reset any values used throughout the players turn. It will also add the end of round energy to the players energy. Once finished it will go to the ComputerChances turn
void PlayerEndOfRound() 
{
	Player.HealedThisTurn = false;
	Player.Healing = 0;
	Player.Energy = Player.Energy + (Player.Recharge * Player.RechargeRate);
	if (Player.Energy > Player.MaxEnergy) 
	{
		Player.Energy = Player.MaxEnergy;
	}
	Player.RechargeRate = 1;
	
	RolledNumber = 0;
	Player.Damage = 0;
	Player.IncreasedChance = 0;
	Player.DecreasedChance = 0;
	Action = 0;

	

	//cout << "Press any key to end your turn." << endl;
	//_getch();
	system("pause");
	system("CLS");
	cout << Player.Name << " has ended his turn" << endl;
	cout << " " << endl;
	cout << "" << endl;
	cout << Player.Name << " is gaining end of round energy!" << endl;
	cout << "" << endl;
	ComputerChance();
	


}

//This function is used to calculate the chance numbers for each action the computer has access to. Each action value is changed as a result of multiple different statements.
void ComputerChance()
{
	// significantly = 15 while slightly = 5
	cout << Computer.Name << " is deciding what action to use..." << endl;
	cout << "" << endl;
	Sleep(1000);
	if ((Computer.Health == Computer.MaxHealth) || (Computer.HealedThisTurn == true) || (Computer.Energy <= 1))	//This means the computer will not heal this round because they either don't need to, already healed this turn or don't have enough energy
	{
		HealChance = 0;
	}

	if (Computer.Energy == Computer.MaxEnergy) // This means the computer will not recharge this round because they are already at maximum energy
	{
		RechargeChance = 0;
	}

	if (Computer.Energy != 50) //This means the computer will not use their special attack as they do not have enough energy
	{
		SpecialChance = 0;
	}

	//The code above will run no matter what

	if (Player.Health <= Player.MaxHealth / 4) //If the players health is low the computer will attempt to kill them quickly
	{
		AttackChance = AttackChance + 15;
		if (SpecialChance != 0)
		{
			SpecialChance = SpecialChance + 5;
		}

		if (Computer.Health <= (Computer.MaxHealth / 4)) //Additionally if the computers health is also low their healing and dodge chance is also slightly increased
		{
			DodgeChance = DodgeChance + 5;
			if (HealChance != 0)
			{
				HealChance = HealChance + 5;
			}

		}

		if (RechargeChance != 0) //This means the computer will not use their special attack as they do not have enough energy
		{
			RechargeChance = RechargeChance / 2;
		}

		
		ComputerPicker();
	}

	//If the players health is not less then 25% then the computer will go into a larger algorithm which changes chances of different actions depending on the computers health

	if ((Computer.Health <= Computer.MaxHealth) && (Computer.Health >= 85)) //This happens if the computers health is between 100 and 85
	{
		AttackChance = AttackChance + 15;
		if (SpecialChance != 0)
		{
			SpecialChance = SpecialChance + 15;
		}
		DodgeChance = 0;
		HealChance = 0;

	}

	else if ((Computer.Health <= 84) && (Computer.Health >= 75)) //This happens if the computers health is between 84 and 75
	{
		AttackChance = AttackChance + 15;
		if (SpecialChance != 0)
		{
			SpecialChance = SpecialChance + 15;
		}
		DodgeChance = DodgeChance - 15;
		if (HealChance != 0)
		{
			HealChance = HealChance - 15;
		}

	}

	else if ((Computer.Health <= 74) && (Computer.Health >= 50)) //This happens if the computers health is between 74 and 50
	{
		AttackChance = AttackChance + 5;
		if (SpecialChance != 0)
		{
			SpecialChance = SpecialChance + 5;
		}
		DodgeChance = DodgeChance + 5;
		if (HealChance != 0)
		{
			HealChance = HealChance + 5;
		}

	}

	else if ((Computer.Health <= 49) && (Computer.Health >= 25)) //This happens if the computers health is between 49 and 25
	{
		AttackChance = AttackChance - 15;
		if (SpecialChance != 0)
		{
			SpecialChance = SpecialChance - 15;
		}
		DodgeChance = DodgeChance + 15;
		if (HealChance != 0)
		{
			HealChance = HealChance + 15;
		}

	}

	else //This happens if the computers health is below 25
	{
		DodgeChance = DodgeChance + 15;
		if (HealChance != 0)
		{
			HealChance = HealChance + 15;
		}
		AttackChance = 0;
		SpecialChance = 0;

	}

	if ((Computer.Energy < Computer.MaxEnergy) && (Computer.Energy > Computer.MinEnergy)) //If the computers energy level is either not empty and not full the computers recharge chance will increase by a small amount
	{
		RechargeChance = RechargeChance + 5;


	}

	else if (Computer.Energy == Computer.MinEnergy) //If the computers energy level is 0 then the recharge chance will be increased by a modest amount
	{
		RechargeChance = RechargeChance + 10;
	}

	ComputerPicker();

}


//This function is used to find what action the computer will use by using the chances in the previous ComputerChance function and by picking a random number to decide what action the computer will pick
void ComputerPicker() 
{
	//cout << "attack chance is " << AttackChance << endl;
	//cout << "special chance is " << SpecialChance << endl;
	//cout << "recharge chance is " << RechargeChance << endl;
	//cout << "dodge chance is " << DodgeChance << endl;
	//cout << "heal chance is " << HealChance << endl;

	TotalChance = AttackChance + SpecialChance + RechargeChance + DodgeChance + HealChance;
	ChanceNumber = (1 + (rand() % TotalChance));

	if ((ChanceNumber > 0) && (ChanceNumber < AttackChance)) //chancenumber is between 0 and attackchance
	{
		//Attack 
		Action = 1;
		ComputerAction();
	}

	else if ((ChanceNumber >= (AttackChance + 1)) && (ChanceNumber < (AttackChance + SpecialChance))) //chancenumber is between attackchance and specialchance
	{
		//Special Attack
		Action = 2;
		ComputerAction();
	}

	else if (ChanceNumber >= (AttackChance + SpecialChance + 1) && (ChanceNumber < (AttackChance + SpecialChance + RechargeChance))) //chancenumber is between specialchance and rechargechance
	{
		//ReCharge
		Action = 3;
		ComputerAction();
	}

	else if (ChanceNumber >= (AttackChance + SpecialChance + RechargeChance + 1) && (ChanceNumber < (AttackChance + SpecialChance + RechargeChance + DodgeChance))) //chancenumber is between rechargechance and dodgechance
	{
		//Dodge
		Action = 4;
		ComputerAction();
	}

	else if (ChanceNumber >= (AttackChance + SpecialChance + RechargeChance + DodgeChance + 1) && (ChanceNumber < TotalChance)) //chancenumber is between dodgechance and total chance
	{
		//Heal
		Action = 5;
		ComputerAction();
	}

	else 
	{
		//something failed so the number gets picked again. Shouldn't happen but here just in case.
		ComputerPicker();
	}


}


void ComputerAction() 
{
	
	switch (Action) 
	{
		//Attack action
		case Attack:
		{
			//cout << "the knight wants to attack" << endl;
			cout << Computer.Name << " tries to attack " << Player.Name << " with his sword!"  << endl;
			//cout << " " << endl;
			Computer.ChanceToHit = 80 + Computer.IncreasedChance - Computer.DecreasedChance;
			RolledNumber = (1 + (rand() % MaxChance));
			if (RolledNumber > MinChance && RolledNumber <= Computer.ChanceToHit)
			{
				Computer.Damage = (1 + (rand() % 10));
				Player.Health = Player.Health - Computer.Damage;
				//The computer hit the player
				cout << Computer.Name << " successfully hit you for " << Computer.Damage << " damage!" << endl;
				if (Player.Health >= 1)
				{
					//The player is still alive
					cout << "You are now on " << Player.Health << " health!" << endl;

				}

				else
				{
					//The player has died
					cout << Player.Name << " has died from his wounds!" << endl;
					Player.Dead = true;
				}

			}

			else
			{
				//The computer missed the player
				cout << Computer.Name << " failed to hit " << Player.Name << " with his sword! " << endl;


			}
			

			break;
		}

		//Special action
		case Special:
		{
			//cout << "the knight wants to special" << endl;
			cout << Computer.Name << " goes for a special attack!" << endl;
			
			//The computers energy is drained
			Computer.ChanceToHit = 50 + Computer.IncreasedChance - Computer.IncreasedChance;
			Computer.Energy = Computer.Energy - 50;
			RolledNumber = (1 + (rand() % MaxChance));
			if (RolledNumber > MinChance && RolledNumber <= Computer.ChanceToHit)
			{
				Computer.Damage = (1 + (rand() % 20));
				if (Computer.Damage <= 4)
				{
					Computer.Damage = Computer.Damage + 4;
				}
				Player.Health = Player.Health - Computer.Damage;
				//The computer hit the player
				cout << Computer.Name << " successfully hit you dealing " << Computer.Damage << " damage!" << endl;
				if (Player.Health >= 1)
				{
					//The player is still alive
					cout << Player.Name << " is now on " << Player.Health << " health!" << endl;

				}

				else
				{
					//The player is dead
					cout << Player.Name << " has died!" << endl;
					Player.Dead = true;
					
				}


			}
				

			else
			{
				//The computer missed
				cout << Computer.Name << " attempted to perform a special attack but missed!" << endl;

			}
			cout << "" << endl;
			cout << Computer.Name << " has had their energy drained as a result of the special attack!" << endl;
			cout << "" << endl;
			break;
		}

		//recharge action
		case Recharge:
		{
			//cout << "the knight wants to recharge" << endl;
			//The computer will recharge more energy next round but be more likely to get hit
			cout << Computer.Name << " is recharging his energy!" << endl;
			cout << Computer.Name << " will recharge additional energy this turn! But " << Computer.Name << " will be more vulnerable to attacks next turn!";
			Computer.RechargeRate = 4;
			Player.IncreasedChance = 10;
			
		
			break;
		}

		//dodge action
		case Dodge:
		{
			//cout << "the knight wants to dodge" << endl;
			//The computer will try to dodge the next attack, reducing hit chance to be hit 
			cout << Computer.Name << " will try to dodge the next attack" << endl;
			Player.DecreasedChance = 30;
			//Expected loss of data below
			Computer.RechargeRate = 0.5;



			break;
		}

		//heal chance
		case Heal:
		{
			//cout << "the knight wants to heal" << endl;
			//The computer will heal for half of their energy
			cout << Computer.Name << " will heal this turn" << endl;
			Computer.Healing = Computer.Energy / 4;
			Computer.Energy = Computer.Energy / 4;
			if (Computer.Energy < Computer.MinEnergy) 
			{
				Computer.Energy = Computer.MinEnergy;
			}
			Computer.Health = Computer.Health + Computer.Healing;
			if (Computer.Health > Computer.MaxHealth)
			{
				Computer.Health = Computer.MaxHealth;
			}
			//The computer has healed for half of their energy
			cout << Computer.Name << " has healed for " << Computer.Healing << "!" << endl;
			cout << Computer.Name << " now has " << Computer.Health << " health!" << endl;
			cout << " " << endl;
			//The computer is allowed to pick a second action as a result of healing
			cout << "As " << Computer.Name << " decided to heal, he can pick a second action." << endl;
			Computer.HealedThisTurn = true;
			Sleep(500);
			ComputerChance();
			

			break;
		}

		default:
			//this will only run if something goes wrong. It will try to repick an action to do.
			//cin.clear();
			ComputerChance();


	}

	if (Player.Dead == true)
	{
		EndGame();
	}
	//Once the computers action has been decided and performed, the program will go to the end of computer round
	ComputerEndOfRound();
	

}


//Similar to the players end of round function, this function will reset all variables used, increase the computers energy by a set amount and then go back to the players turn
void ComputerEndOfRound() 
{

	Computer.IncreasedChance = 0;
	Computer.DecreasedChance = 0;

	Computer.Damage = 0;
	Computer.Healing = 0;
	Computer.RechargeRate = 1;
	RolledNumber = 0;
	Action = 0;
	Computer.HealedThisTurn = false;
	Computer.Energy = Computer.Energy + (Computer.Recharge * Computer.RechargeRate);
	if (Computer.Energy > Computer.MaxEnergy)
	{
		Computer.Energy = Computer.MaxEnergy;
	}

	int AttackChance = 22;
	int SpecialChance = 22;
	int RechargeChance = 12;
	int DodgeChance = 22;
	int HealChance = 22;
	int TotalChance = 0;
	int ChanceNumber = 0;

	

	system("pause");
	//cout << "Press any key to end the computers turn" << endl;
	//_getch();
	system("CLS");
	cout << Computer.Name << " has finished his round!" << endl;
	cout << " " << endl;
	
	cout << Computer.Name << " is gaining end of round energy!" << endl;
	cout << "" << endl;

	PlayerAction();
}











// This is the Menu function which is only displayed when the player first starts the game. It allows the user to select a variety of options
void Menu(){
	cout << "" << endl;
	cout << "Would you like to (P)lay the game, (V)iew the game instructions or (E)xit the game?" << endl;

	cin >> MenuChoice;
	cin.sync();

	//This if statement will allow the user to start the game 
	if ((MenuChoice == "p") || (MenuChoice == "P"))
	{
		SelectName();
	}

	//This if statement will allow the user to view the game instructions
	else if ((MenuChoice == "v") || (MenuChoice == "V")) 
	{
		Instructions();
	}

	//This if statement will allow the user to exit the game by closing the program
	else if ((MenuChoice == "e") || (MenuChoice == "E")) 
	{
		exit(0);

	}

	//If the user doesn't enter a valid character, they will be asked again what action they want to do. this is done by recalling the funciton
	else 
	{
		cout << "Invalid letter, try again," << endl;
		Menu();

	}

}

//This function is only used once and is used for the user to name their character. Once finished will begin the game by going to the PlayerAction function.
void SelectName()
{
	cout << "Please enter a name for your character. (No spaces please)" << endl;
	cin >> Player.Name;
	system("CLS");
	cout << Player.Name << " is wandering through a forest when suddenly an armed knight appears infront of him, challenging him to a duel!" << endl;
	
	PlayerAction();
}

//This function can be only used from the main menu and simply prints out the instructions to the player. Once finished, the program will go back to the main menu function.
void Instructions() 
{

	cout << "This is a basic turn based game. The human player and computer player take turns giving commands to their creatures. Both characters begin with equal health points and energy points. " << endl;
	cout << "Press enter to see next instruction" << endl;
	cout << " " << endl;
	system("pause");
	//getchar();
	Sleep(100);
	cout << "The human player moves first, followed by the computer, and so on, until one creature or the other has no health remaining. " << endl;
	//cout << "Press enter to see next instruction" << endl;
	cout << " " << endl;
	//getchar();
	system("pause");
	//Sleep(100);
	cout << "Both the player and the computer have the same choices of actions during their turn: Attack, Special Attack, Re-Charge, Dodge, and Heal." << endl;
	//cout << "Press enter to see next instruction" << endl;
	cout << " " << endl;
	//getchar();
	system("pause");
	//Sleep(100);
	cout << "- Attack is a standard attack on the other character." << endl;
	cout << "- A Special Attack is a different attack type on the other character that can deal more damage but uses up energy to perform." << endl;
	cout << "- Recharge is another action type and means the character will recharge more energy at the end of the round. (that turn only)" << endl;
	cout << "- A dodge means the other character is less likely to hit you next turn but lowers the amount of energy you recharge at the end of the round" << endl;
	cout << "- Heal action is performed by taking half of your current energy and transforming it into health." << endl;
	//cout << "Press enter to return to menu" << endl;
	cout << " " << endl;
	system("pause");
	//getchar();
	//Sleep(100);
	system("CLS");
	Menu();


}

//This function will only be used when either the player or the computer character has died. It allows the user to see the score of each characters wins and allow the user to start a rematch.
void EndGame()
{
	if (InvalidKey != true) {

		//cout << "Press any key to finish this round." << endl;
		//_getch();
		system("pause");
		system("CLS");
		cout << " " << endl;
		//This chooses wheather the player or the computer won and depending on who will add a value to their score
		if (Player.Dead == true)
		{
			Computer.Score = Computer.Score + 1;
			cout << Player.Name << " falls to the ground... You lose!" << endl;
		}
		else if (Computer.Dead == true)
		{
			Player.Score = Player.Score + 1;
			cout << Computer.Name << " falls to the ground in a pool of blood, you are victorious!" << endl;
		}

		cout << " " << endl;

		//this prints out the score to the user and says who is currently leading in wins or says that both players are tied
		if (Player.Score > Computer.Score)
		{
			cout << "You are leading the round wins with " << Player.Score << " win(s) while " << Computer.Name << " has " << Computer.Score << " win(s)!" << endl;
		}

		else if (Computer.Score > Player.Score)
		{
			cout << Computer.Name << " is leading the wins with " << Computer.Score << " win(s) while " << Player.Name << " has " << Player.Score << " win(s)!" << endl;
		}

		else
		{
			cout << "Both players have equal wins at " << Player.Score << " win(s) each!" << endl;
		}
		cout << " " << endl;

	}
	//This asks the user if they want to have a rematch or exit the program
	cout << "Would you like a (R)ematch or would you like to (E)xit the game?" << endl;
	cin >> EndChoice;

	//Rematch
	if ((EndChoice == "r") || (EndChoice == "R"))
	{
		cout << "Restarting the match, good luck!" << endl;
		Sleep(1000);
		cout << " " << endl;
		cout << Player.Name << " is wandering through a forest when suddenly an armed knight appears infront of him, challenging him to a duel!" << endl;
		cout << " " << endl;

		//This resets all variables used in the game to their original state.

		//The variables that the computer uses is being reset below
		Computer.IncreasedChance = 0;
		Computer.DecreasedChance = 0;
		Computer.Damage = 0;
		Computer.Healing = 0;
		Computer.RechargeRate = 1;
		Computer.Dead = false;
		RolledNumber = 0;
		Action = 0;
		Computer.HealedThisTurn = false;
		int AttackChance = 22;
		int SpecialChance = 22;
		int RechargeChance = 12;
		int DodgeChance = 22;
		int HealChance = 22;
		int TotalChance = 0;
		int ChanceNumber = 0;

		//The variables that the player uses is being reset below
		Player.HealedThisTurn = false;
		Player.Healing = 0;
		Player.RechargeRate = 1;
		Player.Damage = 0;
		Player.IncreasedChance = 0;
		Player.DecreasedChance = 0;
		Player.Dead = false;

		//Resetting both characters health and energy
		Player.Health = Player.MaxHealth;
		Computer.Health = Computer.MaxHealth;
		Player.Energy = Player.MaxEnergy;
		Computer.Energy = Computer.MaxEnergy;

		

		InvalidKey = false;
		
		PlayerAction();
		
		
	}

	//Leave game
	else if ((EndChoice == "e") || (EndChoice == "E"))
	{
		exit(0);

	}

	else 
	{
		cout << "Invalid key, try again" << endl;
		InvalidKey = true;
		EndGame();
	}


}