/*****************************************
File: Sequencer.cpp
Author: Richard Eason
Lab or Project: Project 3
Date: 4/3/21
Description: Sequencer contains the major framework of project 3, using the
resources and functions of DNA while providing a menu for the user to
interact with the data.
*******************************************/

#include "Sequencer.h"


Sequencer::Sequencer(string fileName){
  //Loads in given file
  m_fileName = fileName;
  ReadFile();

  //Checks for successful loading, if so, goes to main menu
  if (m_suspects.size() == 0 || m_evidence.size() == 0){
    cout << "Error loading in the DNA." << endl;
  } else {
    MainMenu();
  }
}

Sequencer::~Sequencer(){
  //Vector sizes for complete deletion
  int evid_size = m_evidence.size();
  int susp_size = m_suspects.size();

  //Iterate through each vector and delete each DNA
  for (int i = 0; i < evid_size; i++){
    DNA *curr = m_evidence[i];
    delete curr;
  }

  for (int j = 0; j < susp_size; j++){
    DNA *curr = m_suspects[j];
    delete curr;
  }
}

void Sequencer::DisplayStrands(){
  //Vector sizes for complete displays
  int evid_size = m_evidence.size();
  int susp_size = m_suspects.size();

  //For each DNA in the vectors, uses their overloaded << to print
  for (int i = 0; i < evid_size; i++){
    cout << *m_evidence[i] << endl;
  }

  for (int j = 0; j < susp_size; j++){
    cout << *m_suspects[j] << endl;
  }

}

void Sequencer::ReadFile(){
  //Name of DNA (subject/evidence), contents of the strand (ACGT etc.)
  string name, strand;

  //Reads in given file
  ifstream infile(m_fileName);

  //Checks for successful file opening
  if (infile.is_open()){

    //Due to the formatting, can check getline for a name-line, and there
    //will be a strand-line associated
    while (getline(infile, name, '\n')){
      getline(infile, strand, '\n');

      //Makes the new DNA sequence and writes each strand character to end
      DNA *curr = new DNA(name);

      for (int i = 0; i < strand.size(); i++){
	if (strand[i] != ','){
	  curr->InsertEnd(strand[i]);
	}
      }
	
      //Sorts the DNA into their vectors
      if (name[0] == 'E'){
	m_evidence.push_back(curr);
      } else {
	m_suspects.push_back(curr);
      }
    }

    //Error opening file
  } else {
    cout << "Error loading file." << endl;
  }
}

void Sequencer::MainMenu(){
  //Exit condition and user input
  bool exit = false;
  int input = 0;
    

  do {
    cout << "What would you like to do?:" << endl;
    cout << "1. Display Strand" << endl;
    cout << "2. Reverse Sequence" << endl;
    cout << "3. Check Suspects" << endl;
    cout << "4. Exit" << endl;

    //Gets user input and checks against switch cases
    cin >> input;
    
    switch (input){
    case 1:
      DisplayStrands();
      break;
    case 2:
      ReverseSequence();
      break;
    case 3:
      CheckSuspects();
      break;
    case 4:
      exit = true;
      break;
    }

    //Only exits the main menu loop when user satisfies exit condition (4)
  } while (!exit);

}

void Sequencer::CheckSuspects(){
  //Vector sizes for iterating through all DNA in each vector
  int susp_size = m_suspects.size();
  int evid_size = m_evidence.size();

  //DNA holders for the respective vector's access
  DNA susp;
  DNA evid;

  //True for matching inside sequences, false otherwise
  bool isMatch;

  cout << "Checking all suspects vs evidence" << endl;

  //Uses the DNA CompareSequence on each suspect DNA, comparing to each of the
  //evidence DNAs
  for (int i = 0; i < susp_size; i++){
    susp = *m_suspects[i];
    for (int j = 0; j < evid_size; j++){
      evid = *m_evidence[j];
      isMatch = susp.CompareSequence(evid);

      if (isMatch){
	cout << "Suspect " << (i + 1) << " matches Evidence "
	     << (j + 1) << endl;
      } else {
	cout << "Suspect " << (i + 1) << " does NOT match Evidence "
	     << (j + 1) << endl;
      }
    }
  }
}

void Sequencer::ReverseSequence(){
  //Input management/checking
  bool inputCheck = false;
  int input;

  //DNA manipulation placeholders
  string strand_name;
  DNA curr;

  do {
    cout << "Which type of sequence to reverse?" << endl;
    cout << "1. Suspect" << endl;
    cout << "2. Evidence" << endl;

    //Gets and validates user input based on given choices
    cin >> input;

    if (input == 1 || input == 2){
      inputCheck = true;
    }
  } while (!inputCheck);

  //For suspects or evidence, take each DNA and call ReverseSequence on them
  if (input == 1){
    int susp_size = m_suspects.size();

    for (int i = 0; i < susp_size; i++){
      curr = *m_suspects[i];
      curr.ReverseSequence();

      strand_name = curr.GetName();
      cout << "Done reversing " << strand_name << "'s sequence." << endl;
    }
  } else {
    int evid_size = m_evidence.size();

    for (int i = 0; i < evid_size; i++){
      curr = *m_evidence[i];
      curr.ReverseSequence();    
      strand_name = curr.GetName();
      cout << "Done reversing " << strand_name << "'s sequence." << endl;
    }
  }
}
 
