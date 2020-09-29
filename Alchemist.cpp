#include "Alchemist.h" 
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

const int KNOWN_NUM_AT_START = 4;

//Default constructor
Alchemist::Alchemist() {

	m_myName = "Kai";
	m_attempts = 0;
	m_repeats = 0;
	m_numElements = 0;
}

//Overloaded constructor. name required
Alchemist::Alchemist(string name) {

	Alchemist();
	m_myName = name;
}

string Alchemist::GetName() {
	return m_myName;
}

void Alchemist::SetName(string name) {
	m_myName = name;
}

//WORK ON THIS AGAIN LATER!!!
void Alchemist::DisplayElements() {

	cout << endl;
	cout << "Known elements:\n";
	for (int i = 0; i < m_numElements; i++) {

		cout << i + 1 << ". " << m_myElements[i].m_name << endl;
	}
}

int Alchemist::GetNumElements() {
	return m_numElements;
}

//WORK ON THIS LATER!!!
bool Alchemist::CheckElement(Element element) {
	bool repeats = false;

	for (int j = 1; j < GetNumElements() + 1; j++) {
		if (GetElement(j).m_name == element.m_name) {

			AddRepeat();
			cout << "You already know that element\n";
			repeats = true;
		}
	}

	return repeats;
}

void Alchemist::AddElement(Element element) {

	//Adds element to the array of the player's known elements
	m_myElements[m_numElements] = element;
	m_numElements++;

	//For loop so that this message does not show up when adding starter
	//elements to the player's known elements
	if (m_numElements > KNOWN_NUM_AT_START) {

		cout << m_myName << " now knows " << element.m_name << endl;
	}
}

Element Alchemist::GetElement(int name) {

	//it is name - 1 because we are passing in a player input
	//whihc can be chosen from 1 but the array starts at 0
	return m_myElements[name - 1];
}

void Alchemist::AddAttempt() {
	m_attempts++;
}

int Alchemist::GetAttempts() {
	return m_attempts;
}

void Alchemist::AddRepeat() {
	m_repeats++;
}

int Alchemist::GetRepeats() {
	return m_repeats;
}