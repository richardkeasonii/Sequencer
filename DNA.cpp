/*****************************************
File: DNA.cpp
Author: Richard Eason
Lab or Project: Project 3
Date: 3/31/21
Description: DNA contains the bulk of technical code in the project,
responsible for reversing sequences, comparing, and managing the sequences
themselves in the form of linked lists.
*******************************************/
#include "DNA.h"
using namespace std;

DNA::DNA() {
  //Default constructor, sets name to Default, otherwise normal values
  m_head = nullptr;
  m_tail = nullptr;
  m_name = "Default";
  m_size = 0;
}

DNA::DNA(string name){
  //Constructs DNA with given name
  m_head = nullptr;
  m_tail = nullptr;
  m_name = name;
  m_size = 0;
}

DNA::~DNA() {
  //Iterates through each Node and deletes
  Node *curr = m_head;
  Node *temp;
  while (curr != nullptr){
    temp = curr->m_next;
    delete curr;
    curr = temp;
  }
}

void DNA::InsertEnd(char data){
  //Fresh node and first node in list
  Node *toAdd = new Node();
  Node *curr = m_head;

  //Populates newest node with data and nullptr (since it will be last)
  toAdd->m_data = data;
  toAdd->m_next = nullptr;

  //For 0-size list, make new head the fresh node
  if (m_head == nullptr){
    m_head = toAdd;
  } else {
    //Otherwise, iterate until last node then place fresh node at end 
    while (curr->m_next != nullptr) {
      curr = curr->m_next;
    }
    curr->m_next = toAdd;
    m_tail = toAdd;
  }
  m_size++;
}

string DNA::GetName(){
  //Returns the name of the DNA sequence (suspect or evidence)
  return m_name;
}

int DNA::GetSize(){
  //Returns the size of the DNA sequence (0 for null, 1 for 1 nucleotide etc.)
  return m_size;
}

void DNA::ReverseSequence(){
  Node *curr = m_head;
  Node *temp = nullptr;
  Node *prev = nullptr;

  while(curr != nullptr){
    temp = curr->m_next;
    curr->m_next = prev;
    moreprev = prev;
    prev = curr;
    curr = temp;
  }
  m_head = prev;
}

bool DNA::CompareSequence(DNA &evidence){
  //Overall bool for return, true if evidence within suspect DNA
  bool comparison = false;
  //Used to check for failures in between matching nucleotides
  bool middle_check;
  //Size, pointers, and counter used for iterating and nucleotide access
  int evid_size = evidence.GetSize();
  Node *curr = m_head;
  Node *temp = nullptr;
  int counter = 0;

  //Checks for end of suspect DNA and checks if iterating through the length
  //of evidence would exceed m_size (therefore would be OOB)
  while(curr != nullptr && (counter + evid_size) != m_size){

    ///Checks if current data matches start of evidence
    if (curr->m_data == evidence.GetData(0)){

      //Sets check to true, so if at any point until the evidence has been
      //iterated through, it will set to false and indicate a mismatch.
      middle_check = true;
      temp = curr;
      for (int i = 1; i < evid_size; i++){
	temp = temp->m_next;
	if (temp->m_data != evidence.GetData(i)){
	  middle_check = false;
	}
      }

      //If middle_check is true and iteration was successful, the comparison
      //is complete and the evidence is within the suspect DNA
      if (middle_check){
	comparison = true;
      }
    }

    //Go to next node of suspect DNA, iterates counter
    curr = curr->m_next;
    counter++;
  }
  
  return comparison;
}

char DNA::GetData(int nodeNum){

  //Counter for iterating through the nodes until reaching the appropraite node
  int counter = 0;

  //Iteration starts from m_head
  Node *curr = m_head;

  //Checks for end of DNA sequence, continues to iterate through Node list
  //until the counter reaches the appropriate value
  while (curr != nullptr){
    if (counter == nodeNum){
      return (curr->m_data);
    }
    counter++;
    curr = curr->m_next;
  }

  //This return statement indicates that a failure has occurred
  //This happens with reversing. Massive error that I couldn't figure out
  //how to correct.
  return 'X';
}

ostream &operator<< (ostream &output, DNA &myDNA){

  //For each nucleotide in the DNA, print the character and arrow
  for (int i = 0; i < myDNA.GetSize(); i++){
    char curr = myDNA.GetData(i);
    output << curr << "->";
  }

  //Finishes the DNA code with an END and returns the completed output
  output << "END" << endl;
  return output;
}
