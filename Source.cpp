// This program takes a list of movie titles and arranges them in alphabetical order by word. Once the words are arranged the remainder of the line that was assosiated with the word is
// added before and after the word when appropriet. 

#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

int main()
{
	list<string> intList;
	list<string>::iterator iterIntList;
	list<string> reference;
	list<string>::iterator iterReference;

	// Due to the fact that the code implementation for before and after the "|" symbol on the output is almost symetrical
	// variables are given a pre or post prefix to show where they are used.

	string hold;
	string holdplus;
	string input;
	string listCheck = "\0";
	string postBackUp = "\0";
	string preBackUp = "\0";
	string phrase = "\0";
	string space = " ";

	int postStore = 0;
	int preStore = 0;
	int count = 0;
	int preCount = 0;
	int postCount = 0;

	bool specialCase = true;
	bool preCheck = true;
	bool blank = false;
	bool postCheck = true;

	fstream dataFile("movieTitles.txt", ios::in);
	//the # is used as a marker to tell the search funtions when to stop looking
	reference.push_back("#");

	while(!dataFile.eof())
	{
		//reads the file in one line at a time
		getline(dataFile,input);
		int temp = 0, temp2 = 0;
		for( int i = 0; i < input.size(); i++)
		{
			//individual word starting and ending location is located by the space before and after the word
			if(isspace(input.at(i)))
			{
				if(temp != temp2)
				{
					//this is the list of individual words that will be sorted
					intList.push_back(input.substr(temp,temp2 - temp));
					//while this is the controlled list that will stay in the order it was read in
					reference.push_back(input.substr(temp,temp2 - temp));
					temp = i + 1;
					blank = true;
				}
					

			}	
			temp2++;
		}
			if(blank == true)
			{
				reference.push_back("#");
			}
			blank = false;
	}
	//now that we have a list of all the words we can sort them
	intList.sort();


	for (iterIntList = intList.begin();
        iterIntList != intList.end();
        iterIntList++)

   {
	   hold = *iterIntList;
	   //these checks are so the program can handle repeadted words in the lists
	   if(hold == listCheck)
	   {}
	   else
	   {
		   listCheck = hold;
		   postStore = 0;
		   preStore = 0;
		   preCount = 0;
		   postCount = 0;
	   }
	   
	   //for each entry into the iterTintList we will search through the iterRefence and look for its match
	   //this for loop handles the words that come before the current instance of the iterIntList
	   for (iterReference = reference.begin();
        iterReference != reference.end();
        iterReference++)

   {
	   
	   holdplus = *iterReference;
	   if(holdplus == preBackUp && preCheck)
	   {
		   //this allows for the line assosiated with the second, third and so on instance of the word to be accessed
			if(preCount == 0)
			{
			preCheck = false;
			preStore++;
			preCount = preStore;
			}
			else
			{
				preCount--;
			}
		   
		}
		else
		{
			//if the word from iterIntList and iterRefence match then all parts of the line before the word are stored in "phrase"
			if(holdplus == hold)
			 {
				 iterReference--;
				 count = 0;
				 while(*iterReference != "#")
				 {	
					iterReference--;
					count++;
				}
				for(int i = 0; i < count; i++)
				{
					iterReference++;
					phrase = phrase + space + *iterReference;
				}
				iterReference = reference.end();
				iterReference--;
			 }

		 
		}
	}
	    cout << setw(30) << phrase;
	    phrase = "\0";
		preBackUp = hold;
		preCheck = true;

		//outputs the current word that is being accessed
	   cout << "| " << hold << " ";
	  
	   
	   //for each entry into the iterTintList we will search through the iterRefence and look for its match
	   //this for loop handles the words that come after the current instance of the iterIntList
	   	for (iterReference = reference.begin();
        iterReference != reference.end();
        iterReference++)

   {
	   
	   holdplus = *iterReference;
	   if(holdplus == postBackUp && postCheck)
	   {
		   //this allows for the line assosiated with the second, third and so on instance of the word to be accessed
			if(postCount == 0)
			{
				postCheck = false;
				postStore++;
				postCount = postStore;
			}
			else
			{
				postCount--;
			 }
	   }
	  else
	  {
		  //if the word from iterIntList and iterRefence match then all parts of the line after the word are outputted
		 if(holdplus == hold)
		 {
			specialCase = false;
			iterReference++;
			while(*iterReference != "#")
			{	
				cout << *iterReference << " ";
				iterReference++;
			 }
			iterReference = reference.end();
			iterReference--;
			cout << endl;
		 }
      }
	}
		//in instances that the word was the last word in a line, the cout << endl; was not called so this handles those instances
		if(specialCase == true)
		cout << endl;
		specialCase = true;
		postBackUp = hold;
		postCheck = true;
   }
	return 0;
}