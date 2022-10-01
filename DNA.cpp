//Title: Project 3 
//Author: Danny Zheng
//Date: 3/28/2021
//Description: This is DNA cpp for main file



#include "DNA.h"
#include "Sequencer.h"
using namespace std;


// Name: DNA() - Default Constructor
// Desc: Used to build a new DNA sequence
// Preconditions: None
// Postconditions: Creates a new DNA where m_head and m_tail point to nullptr
DNA::DNA() {
	m_name = "";
	m_head = nullptr;
	m_tail = nullptr;
	m_size = 0;
}
// Name: DNA(string) - Overloaded Constructor
  // Desc: Used to build a new DNA sequence with the name passed
  // Preconditions: None
  // Postconditions: Creates a new DNA where m_head and m_tail point to nullptr and name is passed
DNA::DNA(string data) {
	m_name = data;
	
	for (int i = 0; i < data.length(); i++)
	{
		cout << i << endl;
		InsertEnd(data[i]);
	}
	
}
// Name: ~DNA() - Destructor
  // Desc: Used to destruct a strand of DNA
  // Preconditions: There is an existing DNA strand with at least one node
  // Postconditions: DNA is deallocated (including all dynamically allocated nodes)
  //                 to have no memory leaks!
DNA::~DNA() {
	//sets node temp to head
	Node* temp = m_head;
	// while temp is not null we keep deleting head
	while (temp != nullptr)
	{
		m_head = temp;
		temp = temp->m_next;
		delete m_head;
	}
	m_head = nullptr;
	m_tail = nullptr;
	m_size = 0;
	//sets to nullptr and sets size to 0
	
}
// Name: InsertEnd
  // Preconditions: Takes in a char. Creates new node. 
  //                Requires a DNA strand
  // Postconditions: Adds the new node to the end of the DNA strand.
void DNA::InsertEnd(char data) {
	//if head is null then we make size 1 and create a node 
	if (m_head == nullptr) {
		m_size = 1;
		m_head = new Node;
		m_head->m_data = data;
		m_tail = m_head;
		m_head->m_next = nullptr;
	}
	//else we just add the nodes into the linked list
	else
	{
		m_size = m_size + 1;
		Node* temp = m_tail;
		m_tail->m_next = new Node;
		m_tail = m_tail-> m_next;
		m_tail->m_data = data;
		m_tail->m_next = nullptr;
		temp->m_next = m_tail;
	}
}
// Name: GetName()
 // Preconditions: Requires a DNA sequence
 // Postconditions: Returns m_name;
string DNA::GetName() {
	return m_name;
}
// Name: GetSize()
// Preconditions: Requires a DNA sequence
// Postconditions: Returns m_size;
int DNA::GetSize() {
	return m_size;
}
// Name: ReverseSequence
// Preconditions: Reverses the DNA sequence
// Postconditions: DNA sequence is reversed in place; nothing returned
void DNA::ReverseSequence() {
	//sets a temp var for the head
	Node* current = m_head;
	Node* prev = nullptr;
	Node* next = nullptr;
	//while theres something in current we set next to next node and set a prev node and set the head as prev node
	while (current != nullptr) {
		next = current->m_next;
		current->m_next = prev;
		prev = current;
		current = next;
	}
	m_head = prev;
}
// Name: CompareSequence
// Preconditions: Requires two DNA sequence (suspect and passed evidence DNA)
// Postconditions: Returns true if evidence sequence exists; else false
bool DNA::CompareSequence(DNA& evidence) {
	int sizeofevidence = evidence.GetSize();
	int counter = 0;
	Node* evidencelist = evidence.m_head;
	Node* suspectlist = m_head;
	for (int i = 0; i < m_size; i++)
	{
		//checks if the DNA letter matches or not
		if (evidencelist->m_data == suspectlist->m_data)
		{
			counter = counter + 1;
			evidencelist = evidencelist->m_next;
			if (counter == sizeofevidence)
			{
				//if we have correct amount we return true
				return true;
			}
		}
		else
		{
			//make sure it doesnt skip to next letter and will recheck the next letter before moving to next suspect DNA
			evidencelist = evidence.m_head;
			counter = 0;
			if (evidencelist->m_data == suspectlist->m_data)
			{
				counter = counter + 1;
				evidencelist = evidencelist->m_next;
				if (counter == sizeofevidence)
				{
					return true;
				}
			}
		}
		suspectlist = suspectlist->m_next;
	//check again after the loop is over to make sure last letter did not impact results
	}
	if (counter == sizeofevidence)
	{
		return true;
	}
	else
	//else we just return false if they dont match
	{
		return false;
	}
	
}
// Name: GetData
// Desc: Returns the data at a specific location in the DNA sequence
// Preconditions: Requires a DNA sequence
// Postconditions: Returns a single char from a node
char DNA::GetData(int nodeNum) {
	Node* datalist = m_head;
	for (int i = 0; i < nodeNum; i++)
	{
		datalist = datalist->m_next;
	}
	return datalist->m_data;
}
ostream& operator<< (ostream& output, DNA& myDNA) {
	
	//checks to see if the linked list is empty or not
	if (myDNA.m_head == nullptr)
	{
		output << "The list is empty";
	}
	else
	{
		Node* temp = myDNA.m_head;
		while (temp!= nullptr)
		{
			//while temp isnt null we set temp to m_data and go to next node and do the same
			output << temp->m_data;
			output << "->";
			temp = temp->m_next;
			
		}
		//outputs the END
		
		output << "END";
	}
	//return the output
	return output;
}