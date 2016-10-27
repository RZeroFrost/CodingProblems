#include "stdafx.h"
#include "iostream"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <thread>


using namespace std;

//Problem: find length of longest substring of unique characters given string s
int longestUniqueSub(string s) {
	int ans = 0;
	int currAns = 0;
	string tempS = "";
	string tempT = "";
	tempS += s[0];
	//Iterate through chars in s[1] -> s.length()-1
	for (int i = 1; i < s.length();) {
		//Case1: character not in current temp string -> add to string, calculate temp max.
		if (tempS.find(s[i]) == tempS.npos) {
			tempS += s[i];
			i++;
			currAns = max(tempS.length(), tempT.length());
		}
		//Case2: character duplicate -> move string, clear, calculate temp max.
		else {
			tempT = tempS;
			tempS = s[i];
			i++;
			currAns = max(tempS.length(), tempT.length());
		}
		//Compute the larger max -> store as answer.
		ans = max(ans, currAns);
	}
	return ans;	
}

//Main program execution to test
int main() {
	int max = longestUniqueSub("helloqwerttopiuykjhgnbvcx");		//Implies max = 15;
	cout << " The maximum substring of unique characters is of length: " << max << endl;
	Sleep(500);
}
