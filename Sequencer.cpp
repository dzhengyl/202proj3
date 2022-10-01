//Title: Project 3 
//Author: Danny Zheng
//Date: 3/28/2021
//Description: This is sequencer file for proj 3

#include <fstream>
#include "DNA.h"
#include "Sequencer.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;


// Name: Sequencer (constructor)
// Desc: Creates a Sequencer to hold multiple DNA strands from a file
// Preconditions:  None
// Postconditions: A sequencer created to populate m_suspects and m_evidence

Sequencer::Sequencer(string fileName) {
	m_dna.resize(2);
	m_fileName = fileName;
	ReadFile();
	MainMenu();

}
// Name:  Sequencer (destructor)
// Desc: Deallocates all dynamic aspects of a Sequencer
// Preconditions: There is an existing DNA strand (linked list)
// Postconditions: All vectors are cleared of DNA strands
Sequencer::~Sequencer() {
	cout << "DNA removed from memory" << endl;
	for (int i = 0; i < m_dna[0].size(); i++)
	{
		delete m_dna[0][i];
		m_dna[0][i] = nullptr;
	}
	cout << "deleting suspects..." << endl;
	for (int i = 0; i < m_dna[1].size(); i++)
	{
		delete m_dna[1][i];
		m_dna[1][i] = nullptr;
	}
	cout << "deleting evidence..." << endl;
}
// Name:  DisplayStrands
// Desc: Displays each strand in both m_suspects and m_evidence
// Preconditions: At least one linked list is in either m_suspects or m_evidence
// Postconditions: Displays DNA strand from one of the vectors
void Sequencer::DisplayStrands() {
	//loops to get all suspect dnas
	for (int i = 0; i < m_dna[0].size(); i++)
	{
		if (m_dna[0][i] != nullptr)
		{
			cout << "Suspect " << i + 1 << endl;
			cout << *m_dna[0][i] << endl;
		}
		
	//loops to check for evidence 
	}
	for (int i = 0; i < m_dna[1].size(); i++)
	{
		if (m_dna[1][i] != nullptr) {
			cout << "Evidence " << i + 1 << endl;
			cout << *m_dna[1][i] << endl;
		}
	}
}
// Name:  ReadFile
// Desc: Reads in a file that has the name on one line then the sequence on the next
//       All sequences will be an indeterminate length. There are an indeterminate number of
//       sequences in a file. Hint: Read in the entire sequence into a string then go char
//       by char until you hit a new line break. Then insert to the correct vector
// Preconditions: Valid file name of characters (Either A, T, G, or C)
// Postconditions: Populates each DNA strand and puts in either m_suspects or m_evidence
void Sequencer::ReadFile() {
	const char Suspect_char = 'S';
	const char Evidence_char = 'E';
	const string Suspect = "Suspect";
	const string Evidence = "Evidence";
	int counterstrands = 0;
	//opens the file
	ifstream myfile(m_fileName);
	if (myfile.is_open()) {
		cout << "Opened file" << endl;
		string file;
		string dna;
		DNA* ptr;
		//declares the pointer for the vector
		while (getline(myfile, file, '\n'))
		{

			if (file[0] == Suspect_char)
			{
				dna = Suspect;
				counterstrands = counterstrands + 1;
				//keeps track of the strands to display how many total strands there are
			}
			else if (file[0] == Evidence_char) {
				dna = Evidence;
				counterstrands = counterstrands + 1;
			}
			else
			{
				DNA* dnastrand = new DNA();
				//ptr = &dnastrand;
				for (int i = 0; i < file.length(); i++)
				{
					if (file[i] != ',')
					{
						dnastrand->InsertEnd(file[i]);
					}
				}
				//checks if dna is suspect
				if (dna == Suspect)
				{
					m_dna[0].push_back(dnastrand);
				}
				//checks if dna is evidence
				else if (dna == Evidence)
				{
					m_dna[1].push_back(dnastrand);
				}
				//dnastrand = nullptr;
			}
		}
		myfile.close();
		cout << counterstrands << " Strands loaded." << endl;
	}
	else
	{
		cout << "File failed to open" << endl;
	}
	
}
// Name:  MainMenu
// Desc: Displays the main menu and manages exiting
// Preconditions: Populated m_suspects and m_evidence
// Postconditions: None
void Sequencer::MainMenu() {
	int userinput;
	const int Reversefunc = 2;
	const int CheckSusFunc = 3;
	const int total_choices = 4;
	//loops to check for invalid inputs
	do
	{
		do
		{
			cin.clear();
			cout << "What would you like to do?: \n 1. Display Strand \n 2. Reverse Sequence \n 3. Check Suspects \n 4. Exit" << endl;
			cin >> userinput;
			cin.ignore(256, '\n');
		} while (userinput < 1 || userinput > 4);
		// cin.clear();
		// cout << "What would you like to do?: \n 1. Display Strand \n 2. Reverse Sequence \n 3. Check Suspects \n 4. Exit" << endl;
		// cin >> userinput;
		// cin.ignore(256, '\n');
		if (userinput == 1) {
			DisplayStrands();
			//calls disaplystarnds() after 1 is inputted
		}
		else if (userinput == Reversefunc)
		{
			ReverseSequence();
			//reverses sequence after 2 is called
		}
		else if (userinput == CheckSusFunc) {
			CheckSuspects();
			//checks suspects with input 3
		}
		
	} while (userinput != total_choices);
	
}
// Name:  CheckSuspects
// Desc: Iterates through each DNA strand in m_suspects to see if there is a match from
//       m_evidence. Displays each suspect strand where the evidence matches
// Preconditions: Populated m_suspects and m_evidence
// Postconditions: Displays each suspect that has a match
void Sequencer::CheckSuspects() {
	cout << "Checking all suspects vs evidence" << endl;
	int counter = 0;
	//loops through both evidence and the suspects 
	for (int i = 0; i < m_dna[1].size(); i++)
	{
		for (int j = 0; j < m_dna[0].size(); j++)
		{
			if (m_dna[0][j]->CompareSequence(*m_dna[1][i]))
			{
				cout << "Suspect " << j + 1 << " DOES match with evidence " << i + 1 << endl;
				counter = counter + 1;
				//adds to counter
				if (counter == m_dna[1].size())
				{
					cout << "Suspect " << j + 1 << " matches with ALL evidence" << endl;
				 //checks to make sure if it matches with alll evidence or not
				}
			}
			else
			{
				cout << "Suspect " << j + 1 << " does NOT match with evidence " << i + 1 << endl;
				//if it doesnt match with evidence
			}
		}
	}

}
// Name: ReverseSequence
// Desc: User chooses a sequence from m_suspects or m_evidence and the sequence is reversed
// Preconditions: Populated m_suspects and m_evidence
// Postconditions: Reverses a specific sequence replacing in place
void Sequencer::ReverseSequence() {
	int userinput;
	const int choice = 2;
	do
	{
		//asks the user to choose which to reverse
		cin.clear();
		cout << "Which type of sequence to reverse? \n 1. Suspect \n 2. Evidence" << endl;
		cin >> userinput;
		cin.ignore(256, '\n');
	} while (userinput != 1 && userinput != choice);
	if (userinput == 1)
	{
		if (m_dna[0].size() == 1)
		{
			m_dna[0][0]->ReverseSequence();
			cout << "Done reversing Suspect 1 sequence." << endl;
			//reverses sequence if theres only one option

		}
		else
		{
			do
			{
				//asks the user to choose which to reverse
				cin.clear();
				cout << "Choose 1-" << m_dna[0].size() << endl;
				cin >> userinput;
				cin.ignore(256, '\n');
			} while (userinput < 1 || userinput > m_dna[0].size());
			m_dna[0][userinput-1]->ReverseSequence();
			cout << "Done reversing Suspect " << userinput << " sequence." << endl;
		}
	}
	else if (userinput == choice)
	{
		if (m_dna[1].size() == 1)
		{
			m_dna[1][0]->ReverseSequence();
			cout << "Done reversing Evidence 1 sequence." << endl;
			//reverses the evidence sequence if theres only 1 option
		}
		else
		{
			do
			{
				//asks the user to choose which to reverse
				cin.clear();
				cout << "Choose 1-" << m_dna[1].size() << endl;
				cin >> userinput;
				cin.ignore(256, '\n');
			} while (userinput < 1 || userinput > m_dna[1].size());
			m_dna[1][userinput - 1]->ReverseSequence();
			cout << "Done reversing Evidence " << userinput << " sequence." << endl;
			
		}
	}

}
