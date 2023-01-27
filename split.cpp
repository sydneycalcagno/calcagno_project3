// CSCI1300 Fall 2021
// Author: Sydney Calcagno
// Recitation: 215 Luis Mieses Gomez
// Homework 5 - Problem 5


#include "split.h"
#include <iostream> // get libraries 
#include <iomanip>


using namespace std; 


int split(string line, char del, string arr[], int s ){ //declare function with all the components of it

string s1 = "";  // when the string has a ""
int length = line.length(); // declare a variable for the string length 
int thing =0;  // set the index of the array that represnts the words/number/characters and ect.
int i = 0; // declare i and make it equal to 0


for(i=0; i != length && s != thing; i++){ // make a for loop when i isn't the same as the length and 

if(line[i] == del ){ // if the orginal string place has a delimiter then..
if( s1 != ""){ // if it also isn't a "" then..

    arr[thing] = s1; // make the array placement be thing and make it into s1
    thing++; // add a plus one to thing so it can move on to the next
    s1 = ""; 
}
}
else{
    s1 += line[i]; // otherwise add
}


if(i == length - 1){ // since it's an array index starts at 0, so - 1

if(s1 != ""){  // same from earlier

arr[thing] = s1; 
thing++;
s1 = ""; 

}
}
}

if( i != length && thing == s){ // if i doesn't = the length and the word index doesn't equal length then

    return -1; //return -1 because it's invalid
}

return thing; // return back to thing so you can use a different "word"

}






