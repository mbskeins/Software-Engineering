#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS


/*-----------------------------------------------------------------
System Name: Zoinkers!
Artifact Name: Zoinkers.cpp
Create Date: May 1, 2018
Author: Matt Skeins
Version: 3.0
------------------------------------------------------------------*/

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include "zoinkers.h"
#include <vector>
#include <fstream>
#include <string>
using namespace std;

//global functions
ifstream in;

int main() {
  

  testing testClient;
  testClient.start();
  bool login = testClient.logIn();

  if (login == true) {
  
  testClient.systemStart();
  
  }
  else {}

  //zoinkers mainSystem;
  //mainSystem.systemStart();
  cout << "Now exiting the system" << endl;

  system("PAUSE");
  return 0;
}


void testing::start()
{
  in.open("../data/Test.txt");
}

void directory::INPUTcreateExhibit()
{
  exhibit newExhibit;
  string name;
  double price;

  cout << "enter name for exhibit: \n";
  //fileinput
  string inStr;
  getline(in, inStr);
  //price = stoi(inStr);
  name = inStr;
  //cin >> name;

  cout << "enter price for exhibit: \n";
  getline(in, inStr);
  price = atof(inStr.c_str());
  //cin >> price;

  newExhibit.setName(name);
  newExhibit.setPrice(price);

  exhibitDir.push_back(newExhibit);
  cout << "Number of exhibits: " << exhibitDir.size() << endl;

  //log event
  //logEvent("Exhibit Created");
  logging test;
  test.logEvent("Exhibit Created ");
}

inline void user::INPUTgeneratePlan(vector<exhibit> dir)
{
   
  string inStr;

  vector<exhibit> myExList;
  exhibit exhibitToSet;
  cout << "Please eneter your budget(minimum of 15$ is reccomended):";

  //file input
  getline(in, inStr);
  budget = atof(inStr.c_str());
  //cin >> budget;

  int arrivalTime;
  cout << "what time will you be arriving to the park?: (0-23) EX: 2 = 0200:):";
  //file input
  getline(in, inStr);
  arrivalTime = atoi(inStr.c_str());

  //cin >> arrivalTime;
  mySchedule.setArrival(arrivalTime);

  bool favSet = false;

  while (favSet != true) {
    string input;
    int favNum;

    cout << "search for an exhibit you would like to see: ";

    //file input
    getline(in, inStr);
    input = inStr;
    //cin >> input;

    //use found to see if user searched correctly
    bool found = false;
    int dirSize = dir.size();
    for (int x = 0; x < dirSize; x++) {
      string tmpUsername = dir[x].returnName();
      if (tmpUsername == input) {
	exhibitToSet = dir[x];
	found = true;
      }
    }
    //bool exists checks if the exhibit is there or not. if not go to next iteration
    cout << "name of exhibit you searched: " << exhibitToSet.returnName() << endl;
    cout << "How important is it you see this exhibit?(1-5) ";

    //file input
    getline(in, inStr);
    favNum = atoi(inStr.c_str());
    //cin >> favNum;

    exhibitToSet.setFav(favNum);

    myExList.push_back(exhibitToSet);

    char finished;
    cout << "Are you finished choosing exhibits to see? (y/n)";

    //file input
    getline(in, inStr);
    finished = inStr[0];
    //cin >> finished;

    if (finished == 'y') {
      favSet = true;
    }
  }

  //these will iterate through user preference and schedule more preferred exhibits first then workt to less preferred
  double happinessRating;
  int tmpCounter;
  double tmpBudget = budget;

  tmpCounter = checkSchedule(5, myExList);

  // 5 * number of 5 fav levels scheduled
  happinessRating = tmpCounter * 5;

  tmpCounter = checkSchedule(4, myExList);
  //4 * number of fav levels scheduled
  happinessRating += (tmpCounter * 4);

  tmpCounter = checkSchedule(3, myExList);
  happinessRating += (tmpCounter * 3);

  tmpCounter = checkSchedule(2, myExList);
  happinessRating += (tmpCounter * 2);

  tmpCounter = checkSchedule(1, myExList);
  happinessRating += (tmpCounter * 1);

  //must calculate money spent
  tmpBudget = tmpBudget - budget;
  //calculate final hapiness rating
  happinessRating = happinessRating - tmpBudget;

  cout << "Your happiness score for this schedule is: " << happinessRating << endl;
  cout << "Your Schedule for the day" << endl;
  mySchedule.printSchedule();

  //log event
  //logEvent("Plan Generated");
  logging test;
  test.logEvent("Plan Generated ");

}

//NEEDS CHANGED
inline void user::INPUTmanageProfile()
{
  string choice;
  string inStr;
  cout << "what would you like to change? :" << endl;
  cout << "1.) change budget" << endl;
  cout << "2.) change password" << endl;

  //starts line 21
  getline(in, inStr);
  choice = inStr;

  if (choice == "1") {
    double newBudget;
    cout << "please enter a new budget amount: ";

    getline(in, inStr);
    newBudget = atof(inStr.c_str());

    setBudget(newBudget);
    cout << "new budget amount set" << endl;
  }
  else if (choice == "2") {
    string newPassword;
    cout << "please enter a new password: ";

    //line 25 start
    getline(in, inStr);
    newPassword = inStr;

    setPassword(newPassword);
    cout << "new password has been set" << endl;
  }
  else { cout << "invalid input" << endl; }
}


inline void directory::INPUTmanageUsers()
{
  string choice;
  cout << "What would you like to do?" << endl;
  cout << "1.) Print Users\n";
  cout << "2.) Edit User\n";
  cout << "3.) Delete User\n";
  cout << "4.) Create User\n";

  string inStr;
  //starting line 30
  getline(in, inStr);
  choice = inStr;
  if (choice == "1") {
    printUsers();
  }
  else if (choice == "2") {
    //starts line 32
    //ends 33
    user tmpUser;
    string userName;
    cout << "what user would you like to edit: ";

    getline(in, inStr);
    userName = inStr;

    tmpUser = searchUser(userName);
    updateUser(tmpUser);
    cout << "Account successfully updated" << endl;
  }
  else if (choice == "3") {
    //starts line 35 text.txt
    string userDelete;
    cout << "enter user to be deleted" << endl;
    getline(in, inStr);
    userDelete = inStr;
    deleteUser(userDelete);
  }
  else if (choice == "4") {
    //starts line 38
    INPUTcreateUser();
  }
  else { cout << "invalid input"; }
}

inline void directory::INPUTcreateUser()
{
   
  user newUser;
  string username;
  string password;

  cout << "please enter a username: \n";
  string inStr;
  //fileinput
  //starts line 39
  getline(in, inStr);
  //price = stoi(inStr);
  username = inStr;
  //cin >> username;



  newUser.setUsername(username);
  cout << "please enter a password: \n" << endl;;
  //fileinput
  //line 40
  getline(in, inStr);
  //price = stoi(inStr);
  password = inStr;
  //cin >> password;
  newUser.setPassword(password);


   
  newUser.setRole("keeper");
  

  userDir.push_back(newUser);

  cout << "\n username:" << userDir.at(0).returnUsername() << "\n password:" << userDir.at(0).returnPassword() << endl;
  cout << "account creation successful" << endl;

  cout << "current size of user directory:" << userDir.size() << endl;

  //log event
  //logEvent("User Created");
  logging test;
  test.logEvent("User Created ");
}


inline void directory::INPUTmanageExhibits()
{
  string choice;
  string inStr;
  cout << "What would you like to do?" << endl;
  cout << "1.) Print Exhibits\n";
  cout << "3.) Delete Exhibit\n";
  cout << "4.) Create Exhibit\n";
  getline(in, inStr);
  choice = inStr;
  if (choice == "1") {
    //starts line 42
    printExhibits();
  }
  else if (choice == "3") {
    string exhibitToDelete;
    cout << "input exhibit to delete";
    //input from file for exhibit deletion
    //starts line 44
    getline(in, inStr);
    exhibitToDelete = inStr;
    deleteExhibit(exhibitToDelete);
  }
  else if (choice == "4") {
    //starts line 47
    //creates zebra price 7
    INPUTcreateExhibit();
  }
  else { cout << "invalid input"; }
}

inline void directory::INPUTcreateDiscount()
{
  discount newDiscount;
  string newName;
  int disPercent;
  string inStr;

  cout << "eneter code for new discount: ";
  //line 51
  getline(in, inStr);
  newName = inStr;

  cout << "eneter percent of discount: ";

  //test.txt line 52
  getline(in, inStr);
  disPercent = atof(inStr.c_str());

  newDiscount.setName(newName);
  newDiscount.setPercent(disPercent);

  allDiscounts.push_back(newDiscount);
  cout << "Number of discounts: " << allDiscounts.size() << endl;

  logging test;
  test.logEvent("Discount Created ");
}


//NEEDS DONE
void directory::INPUTmenuAction(user &currentUser, bool &loggedStatus)
{

  string inStr;
  string choice;

  if (currentUser.returnRole() == "customer") {
    cout << "What would you like to do?" << endl;
    cout << "1.) Generate Order\n";
    cout << "2.) Manage Account\n";
    cout << "3.) Log Out\n";
    //starts line 14 of test.txt
    //choice 2 starts 20
    getline(in, inStr);
    choice = inStr;
    if (choice == "1") {
      currentUser.INPUTgeneratePlan(exhibitDir);
    }
    else if (choice == "2") {
      currentUser.INPUTmanageProfile();
    }
    else if (choice == "3") {
      //will cause system start to exit loop
      loggedStatus = false;
      cout << "LOG OUT SUCCESSFUL" << endl;
    }
    else { cout << "invalid input"; }
  }
  else if (currentUser.returnRole() == "manager") {
    cout << "What would you like to do?" << endl;
    cout << "1.) Manage Users\n";
    cout << "2.) Manage Exhibits\n";
cout << "3.) Add Discount\n";
cout << "4.) Log Out\n";

//starting line 29
getline(in, inStr);
choice = inStr;

if (choice == "1") {
INPUTmanageUsers();
}
else if (choice == "2") {
INPUTmanageExhibits();
}
else if (choice == "3") {
//starts line 50
INPUTcreateDiscount();
}
else if (choice == "4") {
//will cause system start to exit loop
loggedStatus = false;
cout << "LOG OUT SUCCESSFUL" << endl;
}
else { cout << "invalid input"; }
}
else if (currentUser.returnRole() == "keeper") {
cout << "What would you like to do?" << endl;
cout << "1.) Add Exhibit\n";
cout << "2.) Remove Exhibit\n";
cout << "3.) Add Details\n";
cout << "4.) Log Out\n";
//cin >> choice;
//input from file
getline(in, inStr);
choice = inStr;
if (choice == "1") {
INPUTcreateExhibit();
}
else if (choice == "2") {
string exhibitToDelete;
cout << "input exhibit to delete";
//input from file for exhibit deletion
getline(in, inStr);
exhibitToDelete = inStr;
deleteExhibit(exhibitToDelete);
}
else if (choice == "3") {
//need to be able to add details
string exhibitToChange;
exhibit tmpExhibit;

cout << "eneter exhibit you wish to add details to:  ";
getline(in, inStr);
exhibitToChange = inStr;
tmpExhibit = searchExhibit(exhibitToChange);

string details;
cout << "enter correct details for the exhibit:";

//takes test details for details line 10
getline(in, details);
tmpExhibit.setDetails(details);

updateExhibit(tmpExhibit);
cout << "exhibit updated" << endl;

//delete this
cout << tmpExhibit.returnDetails() << endl;

}
else if (choice == "4") {
//will cause system start to exit loop
loggedStatus = false;
cout << "LOG OUT SUCCESSFUL" << endl;
}
else { cout << "invalid input"; }
}

}

user directory::INPUTLogin()
{
  user currentUser;
  user empty;
  string user;
  string password;

  string inStr;
  //fileinput
  getline(in, inStr);

  cout << "Please enter your username: \n";
  user = inStr;

  cout << "output from file: " << user << "\n";
  currentUser = searchUser(inStr);
  cout << "current user info: "<< endl;
  cout << currentUser.returnUsername() << "    " << currentUser.returnPassword() << "\n";
  

  cout << "please enter your password: \n";
  //fileinput
  getline(in, inStr);
  password = inStr;
  cout << "output from file: " << password << "\n";

  string currentPassword = currentUser.returnPassword();

  if (password != currentPassword) {
    cout << "Log in failed, incorrect password" << endl;
    
    logging test;
    test.logEvent("User Log In (failed) ");
    return empty;
  }
  else {
    cout << "LOG IN SUCCESSFUL" << endl;
    //log event
    //logEvent("User Log In (success)");
    logging test;
    test.logEvent("User Log In (success) ");
    return currentUser;
  }
}
