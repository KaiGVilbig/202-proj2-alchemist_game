#include "Game.h" 
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <direct.h>

using namespace std;
const int QUIT = 4;

//Default Constructor
Game::Game() {

	GameTitle();
	LoadElements();

	//Sets player name
	string name;
	cout << "\nWhat is the name of the Alchemist? ";
	getline(cin, name);
	m_myAlchemist.SetName(name);
	
	//sets starting elements
	Element Water("Water", "", "");
	Element Earth("Earth", "", "");
	Element Fire("Fire", "", "");
	Element Air("Air", "", "");
	
	m_myAlchemist.AddElement(Water);
	m_myAlchemist.AddElement(Earth);
	m_myAlchemist.AddElement(Fire);
	m_myAlchemist.AddElement(Air);
}

void Game::LoadElements() {
	fstream inputStream;

	inputStream.open(PROJ2_DATA);
	string elementName, element1, element2;

	//goes through each line and assigns the value before the first comma to elementName
	//and the second string to element1 and third to element2
	for (int i = 0; i < PROJ2_SIZE; i++) {
		Element element(elementName, element1, element2);
		getline(inputStream, elementName, ',');
		getline(inputStream, element1, ',');
		getline(inputStream, element2, '\n');
		//cout << elementName << ", " << element1 << ", " << element2 << endl;
		m_elements[i] = element;
	}

	inputStream.close();
	cout << PROJ2_SIZE << " elements loaded\n";
}

void Game::StartGame() {
	int playerChoice = 0;

	while (playerChoice != QUIT) {

		playerChoice = MainMenu();

		switch (playerChoice)
		{
		case 1:
			DisplayElements();
			break;

		case 2:
			CombineElements();
			break;

		case 3:
			CalcScore();
			break;

		default:
			break;
		}
	}
}

void Game::DisplayElements() {

	//Displays elements known to the player
	m_myAlchemist.DisplayElements();
}

int Game::MainMenu() {
	int playerChoice = 0;

	do {
		cout << endl;
		cout << "What would you like to do?\n";
		cout << "1. Display the Alchemist's Elements\n";
		cout << "2. Attempt to Combine Elements\n";
		cout << "3. See Score\n";
		cout << "4. Quit\n";
		cin >> playerChoice;
	} while (playerChoice < 1 || playerChoice > QUIT);

	return playerChoice;
}

void Game::CombineElements() {

	int choice1 = 0;
	int choice2 = 0;
	int yesCombine = -1;

	RequestElement(choice1);
	RequestElement(choice2);

	string choiceOneName = m_myAlchemist.GetElement(choice1).m_name;
	string choiceTwoName = m_myAlchemist.GetElement(choice2).m_name;

	//returns 1 if the two elements can combine and if they are not a repeat
	yesCombine = SearchRecipes(choiceOneName, choiceTwoName);

	//only adds the element to the player's known list if yesCombine is returned
	//as something not as -1 from the previous function call. 
	if (yesCombine != -1) {
		m_myAlchemist.AddElement(m_elements[yesCombine]);
	}
}

void Game::RequestElement(int &choice) {

	//input validation
	do {
		cout << endl;
		cout << "Which elements would you liek to merge?\n";
		cout << "To list known elements enter -1\n";
		cin >> choice;

		if (choice == -1) {
			m_myAlchemist.DisplayElements();
		}
	} while (choice <= 0 || choice > m_myAlchemist.GetNumElements());
}

int Game::SearchRecipes(string choiceOneName, string choiceTwoName) {
	bool repeats = false;
	bool noCombineError = false;
	int yesCombine = -1;

	//Adds new element to player's known list if it is a valid recipie
	for (int i = 0; i < PROJ2_SIZE; i++) {

		if (choiceOneName == m_elements[i].m_element1 &&
			choiceTwoName == m_elements[i].m_element2 ||
			choiceTwoName == m_elements[i].m_element1 &&
			choiceOneName == m_elements[i].m_element2) {

			//checks for repeats
			repeats = m_myAlchemist.CheckElement(m_elements[i]);

			//only adds element to player's known list if it is 
			//not a repeat. changes yesCombine to i.
			if (!repeats) {
				yesCombine = i;
			}

			m_myAlchemist.AddAttempt();
			noCombineError = true;
		}
		else {

			//message if the two elements dont combine to make anything. since this 
			//is in a for loop, the message will print out many times. in order to 
			//fix this, noCombineError is set to true if an element is added to the 
			//player's known elements list. this way the message will only print once
			if (!noCombineError && i == PROJ2_SIZE - 1) {
				cout << choiceOneName << " and " << choiceTwoName << " can't combine\n";
			}
		}
	}

	return yesCombine;
}

void Game::CalcScore() {
	string name = m_myAlchemist.GetName();
	float score = (float (m_myAlchemist.GetNumElements()) / float (PROJ2_SIZE)) * 100;

	cout << endl;
	cout << "***The Alchemist***\n";
	cout << "The Great Alchemist " << name << endl;
	cout << name << " has tried to combine and make " << m_myAlchemist.GetAttempts() << " elements\n";
	cout << name << " has repeated attempts " << m_myAlchemist.GetRepeats() << " times\n";
	cout << name << " found " << m_myAlchemist.GetNumElements() << " out of " << PROJ2_SIZE << " elements\n";
	cout << "You have completed " << std::setprecision(3) << score << "% of the elements\n";
}