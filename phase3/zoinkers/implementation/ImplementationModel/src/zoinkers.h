#ifndef ZOINKERS_H_
#define ZOINKERS_H_
/*-----------------------------------------------------------------
System Name: Zoinkers!
Artifact Name: Zoinkers.h
Create Date: May 1, 2018
Author: Matt Skeins
Version: 3.0
------------------------------------------------------------------*/

#include <cstdlib>
#include <ctime>
#include<iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
//#include <chrono>
//#include <thread>
using namespace std;



/*TODO:
  Done1.) MAKE LOGIN() FUNCTION
  Done2.) HARD CODE SOME EXHIBITS
  Done3.) CREATE SCHEDULE FUNCTIONS
  Done4.) GENERATE PLAN FUNCTION
  Done5.) SEARCH EXHIBIT FUNCTION
  Done6.) BUILD TESTING CLIENT
  Done7.) UPDATE LOGGING TO BE REGULAR FUNCTRIONS NOT ATTACHED TO A CLASS
  Done8.) DO HAPINESS CALCULATIONS AND (done)ARRIVAL TIME SCHEDULING
  Done9.) ALL LOG EVENTS
  Done10.) SPECIAL PASS BUYING
  Done11.) USE CASES
  Done12.) API STUFF (CREDIT CARD MUST FAIL RANDOMLY SOMETIMES (5%))
  Done13.) AUTO CREATE USER
  Done14.) AUTO CREATE EXHIBIT
  Done15.) AUTO CREATE DISCOUNT FOR PASS BUYING
  14.) NEED TO UPDATE TEST CLIENT
  Done16.) DO LOG IN/ OUT FUNCTIONALITY NEED TO UPDATE VECTOR AFTER LOG OUT
  Done17.) ADD DISCOUNT TO GENERATE PLAN
  Done18.) PRINT USERS,EXHIBITS
  Done19.) FIX ERASE FUNCTION
  Done20.) KEEPER FUNCTIONS
  21.) REFINE USER ERRORS
*/




class schedule {

 public:
  schedule();
  void addTime(int);
  void addTimeName(string, int);
  //bool checkTime(int);
  //void removeTime(int);
  void printSchedule();
  bool checkTime(int x);
  void setArrival(int time);

 private:

  bool times[24];
  string timeName[24];

};

class API {

 public:
  void creditValidator();

};

class discount {

 public:
  string returnName();
  int returnPercent();
  void setName(string tmp);
  void setPercent(int tmp);
 private:
  string name;
  double percent;

};

class exhibit {

 public:
  exhibit();
  void setDetails(string);
  void setPrice(double);
  void setName(string);
  void setFav(int);
  string returnName();
  double returnPrice();
  int returnFav();
  schedule returnSchedule();
  string returnDetails();

 private:
  //details should include: (name, parents, type, birthdate, picture, history, dietary info, sleeping info,and bathing info
  string details;
  string name;
  schedule exhibitSchedule;
  double price;
  int favorabillity;

};



class user {

 public:

  void generatePlan(vector<exhibit>, vector<discount>);
  vector<exhibit> setFav(vector<exhibit>); // should this take in an exhibit
  int checkSchedule(int favNum, vector<exhibit> ExList);
  void setSchedules(schedule userSchedule, schedule ExhibitSchedule, string name);

  string returnUsername();
  string returnPassword();
  string returnRole();

  void setUsername(string);
  void setPassword(string);
  void setBudget(double);
  void setArrival(int time);
  void setRole(string newRole);


  void manageProfile();

  //needs updated
  void INPUTgeneratePlan(vector<exhibit>);
  void INPUTmanageProfile();

 private:
  schedule mySchedule;
  double budget;
  string username;
  string password;
  string role;
};

class directory {

 public:

  user Login();
  void createUser();
  void createExhibit();

  //needs input
  void createDiscount();

  void autoCreateUser(string, string, string);
  void autoCreateExhibit(string, double);
  void autoCreateDiscount(string, int);

  user searchUser(string username);
  int searchUserReturnIndex(string username);
  discount searchDiscount(string code);
  exhibit searchExhibit(string exhibitName);


  //needs input
  void manageUsers();
  void manageExhibits();
  //

  void deleteExhibit(string);
  void deleteUser(string);

  void printUsers();
  void printExhibits();

  void updateUser(user);
  void updateExhibit(exhibit);

  //prints and executes menu stuff
  void menuAction(user&, bool&);


  bool userExists(string);
  vector<exhibit> returnExhibitDir();

  //input funcitons for test client
  void INPUTmanageExhibits();
  void INPUTmanageUsers();
  void INPUTcreateDiscount();
  void INPUTmenuAction(user&, bool&);
  void INPUTcreateUser();
  void INPUTcreateExhibit();
  user INPUTLogin();
 private:
  vector <exhibit> exhibitDir;
  vector <user> userDir;
  vector <discount> allDiscounts;
};

class zoinkers {

 public:
  void systemStart();
 private:
  directory mainDirectory;

};
class testing {


 public:
  bool returnAuth();
  void authenticate();
  string returnUsername();
  string returnPassword();
  bool logIn();
  void start();

  void systemStart();
 private:
  string username = "WARPIGS";
  string password = "SABBATH";
  bool authenticated = false;
  zoinkers zoinkersSystem;
};

class logging {

 public:
  void logEvent(string str);
  void getDate(ofstream& myfile);
};

//api functions 
void API::creditValidator()
{
  string creditNumber;
  string csv;

  cout << "enter credit card number: ";
  cin >> creditNumber;
  cout << "eneter csv: ";
  cin >> csv;

  int fail;
  srand(time(NULL));
  fail = rand() % 10;
  if (fail < 2) {
    cout << "card declined" << endl;
  }
  else {
    cout << "card verified" << endl;
  }


}

//discount functions
inline string discount::returnName()
{
  return name;
}

int discount::returnPercent()
{
  return percent;
}

inline void discount::setName(string tmp)
{
  name = tmp;
}

inline void discount::setPercent(int tmp)
{
  percent = tmp;
}

//testing functions

inline bool testing::returnAuth()
{
  return authenticated;
}

inline void testing::authenticate()
{
  authenticated = true;
}


string testing::returnUsername()
{
  return username;
}

inline string testing::returnPassword()
{
  return password;
}

inline bool testing::logIn()
{
  string username;
  string password;
  cout << "eneter the username for testing: ";
  cin >> username;


  if (username == returnUsername()) {
    cout << "Please enter the password: ";
    cin >> password;
    if (password == returnPassword()) {
      authenticate();
    }

  }

  if (returnAuth() == true) {
    cout << "Login successfull" << endl;
    return returnAuth();
  }
  else {
    cout << "INVALID LOGIN, you will now be directed to the main system" << endl;
  }
  return returnAuth();
}



inline void testing::systemStart()
{
  zoinkersSystem.systemStart();
}

//system functions
void zoinkers::systemStart()
{
  //NEED TO ADD LOOP FOR USERS LOGGING OUT OR LOGGING IN
  //logging event
  logging test;
  

  test.logEvent("System Started ");
  mainDirectory.autoCreateUser("FLOYD", "SHEEP", "manager");
  mainDirectory.autoCreateUser("ZEPPELIN", "BLACKDOG", "customer");
  mainDirectory.autoCreateUser("APE", "NIRVANA", "keeper");

  mainDirectory.autoCreateExhibit("lion", 5);
  mainDirectory.autoCreateExhibit("sheep", 3);
  mainDirectory.autoCreateExhibit("zebra", 7);

  mainDirectory.autoCreateDiscount("pass", 30);

  char testChoice;
  cout << "what would you like to do?: " << endl;
  cout << "USER SCENARIOS (u)" << endl;
  cout << "INPUT SCENARIOS (i)" << endl;
  cin >> testChoice;
  if (testChoice == 'u') {

    bool exit = false;
    //loops system until user wants to close
    while (exit != true) {

      user myUser;
      bool loggedIn;

      //ask if they want to log in or create user
      string choice;
      cout << "would you like to log in or create a new user?\n1.) new user\n2.) log in\n3.) exit system\n";
      cin >> choice;

      if (choice == "1") {
	mainDirectory.createUser();
      }
      else if (choice == "2") {
	myUser = mainDirectory.Login();
	loggedIn = true;
	while (loggedIn == true) {
	  mainDirectory.menuAction(myUser, loggedIn);
	  //update user after action occured
	  mainDirectory.updateUser(myUser);
	  
	}
      }
      else {
	exit = true;
      }
    }


  }
  else if (testChoice == 'i') {
    bool exit = false;
    //loops system until user wants to close
    user myUser;
    bool loggedIn;
    myUser = mainDirectory.INPUTLogin();
    loggedIn = true;
    
    while (loggedIn == true) {
      mainDirectory.INPUTmenuAction(myUser, loggedIn);
      //update user after action occured
      mainDirectory.updateUser(myUser);
      //system("pause");
      //std::this_thread::sleep_for(std::chrono::milliseconds(1500));
      cin.get();
    }

    myUser = mainDirectory.INPUTLogin();
    loggedIn = true;

    while (loggedIn == true) {
      mainDirectory.INPUTmenuAction(myUser, loggedIn);
      //update user after action occured
      mainDirectory.updateUser(myUser);
      //system("pause");
      //std::this_thread::sleep_for(std::chrono::milliseconds(1500));
      cin.get();
    }

    myUser = mainDirectory.INPUTLogin();
    loggedIn = true;

    while (loggedIn == true) {
      mainDirectory.INPUTmenuAction(myUser, loggedIn);
      //update user after action occured
      mainDirectory.updateUser(myUser);
      //system("pause");
      //std::this_thread::sleep_for(std::chrono::milliseconds(1500));
      cin.get();
    }

  }


  //logEvent("System Shut Down");
  test.logEvent("system shutdown ");
  cin.get();
  //system("PAUSE");
  //std::this_thread::sleep_for(std::chrono::milliseconds(1500));
}

//directory functions

inline user directory::Login()
{
  user currentUser;
  user empty;
  string user;
  string password;


  cout << "Please enter your username: ";
  cin >> user;
  while (userExists(user) != true) {
    cout << "Please enter your username: ";
    cin >> user;
  }
  currentUser = searchUser(user);

  cout << "please enter your password: ";
  cin >> password;

  if (password != currentUser.returnPassword()) {
    cout << "Log in failed, incorrect password" << endl;
    //log event
    //logEvent("User Log In (failed)");
    //logging event
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

void directory::createUser()
{
  //NEED TO ADD ROLE FUNCTIONALITY

  user newUser;
  cout << "please enter a username: ";
  string username;
  string password;
  cin >> username;


  //checks if username exists already in the system
  while (userExists(username) == true) {
    cout << "Please enter a different username, chosen username is taken: " << endl;
    cin >> username;
  }

  newUser.setUsername(username);
  cout << "please enter a password: ";
  cin >> password;
  newUser.setPassword(password);




  //assigning role to user
  char choice;
  cout << "what type of account are you creating? \n 1.)customer \n 2.)manager \n 3.)keeper \n";
  cin >> choice;
  if (choice == '1') {
    newUser.setRole("customer");
  }
  else if (choice == '2') {
    string code;
    cout << "Please eneter verification code for manager creation (for testing use 0000):" << endl;
    cin >> code;
    if (code == "0000") {
      cout << "VERIFIED \n";
      newUser.setRole("manager");
    }
    else {
      cout << "verification failed defaulting to customer account" << endl;
      newUser.setRole("customer");
    }
  }
  else {
    string code;
    cout << "Please eneter verification code for keeper creation (for testing use 1111):" << endl;
    cin >> code;
    if (code == "1111") {
      cout << "VERIFIED \n";
      newUser.setRole("keeper");
    }
    else {
      cout << "verification failed defaulting to customer account" << endl;
      newUser.setRole("customer");
    }
  }

  //pushing new user to directory of users
  userDir.push_back(newUser);
  cout << "username:" << userDir.at(0).returnUsername() << "\npassword:" << userDir.at(0).returnPassword() << "\nrole: " << userDir.at(0).returnRole() << endl;
  cout << "account creation successful" << endl;

  cout << "current size of user directory:" << userDir.size() << endl;

  //log event
  //logEvent("User Created");
  logging test;
  test.logEvent("User Created ");
}

inline void directory::createExhibit()
{
  exhibit newExhibit;
  string name;
  double price;

  cout << "enter name for exhibit: ";
  cin >> name;
  cout << "enter price for exhibit: ";
  cin >> price;

  newExhibit.setName(name);
  newExhibit.setPrice(price);

  exhibitDir.push_back(newExhibit);
  cout << "Number of exhibits: " << exhibitDir.size() << endl;

  //log event
  //logEvent("Exhibit Created");
  logging test;
  test.logEvent("Exhibit Created ");
}

inline void directory::createDiscount()
{
  discount newDiscount;
  string newName;
  int disPercent;

  cout << "eneter code for new discount: ";
  cin >> newName;
  cout << "eneter percent of discount: ";
  cin >> disPercent;

  newDiscount.setName(newName);
  newDiscount.setPercent(disPercent);

  allDiscounts.push_back(newDiscount);
  cout << "Number of discounts: " << allDiscounts.size() << endl;

  logging test;
  test.logEvent("Discount Created ");
}

inline void directory::autoCreateUser(string name, string newPassword, string userRole)
{
  //can hard code users for testing
  user newUser;
  newUser.setUsername(name);
  newUser.setPassword(newPassword);
  newUser.setRole(userRole);

  userDir.push_back(newUser);
  logging test;
  test.logEvent("User Created ");
}

inline void directory::autoCreateExhibit(string name, double price)
{
  //can hard exhibits for testing
  exhibit newExhibit;
  newExhibit.setName(name);
  newExhibit.setPrice(price);

  exhibitDir.push_back(newExhibit);

  logging test;
  test.logEvent("Exhibit Created ");

}

inline void directory::autoCreateDiscount(string name, int percent)
{
  discount tmp;
  tmp.setName(name);
  tmp.setPercent(percent);


  allDiscounts.push_back(tmp);
  logging test;
  test.logEvent("Discount Created ");
}

inline user directory::searchUser(string username)
{
  cout << "username passed in :  " << username <<"$$$"<< endl;
  user tmp;
  int dirSize = userDir.size();
  for (int x = 0; x < dirSize; x++) {
    cout << "user from vector user: \n";
    cout << userDir[x].returnUsername() << "\n";
     cout << endl;
    cout << endl;
    string tmpUsername = userDir[x].returnUsername();
    cout << "-" << tmpUsername << "-" << endl;
    cout << "userpassedin -" << username << "- thisisatest" << endl;
    if (tmpUsername == username) {
      tmp = userDir[x];
      cout << "user being returned: ";
      cout<< tmp.returnUsername()<< "\n";
      return tmp;
    }
  }
}

inline int directory::searchUserReturnIndex(string username)
{
  user tmp;
  int dirSize = userDir.size();
  for (int x = 0; x < dirSize; x++) {
    string tmpUsername = userDir[x].returnUsername();
    if (tmpUsername == username) {
      return x;
    }
  }
}

inline discount directory::searchDiscount(string code)
{
  discount tmp;
  int dirSize = allDiscounts.size();
  for (int x = 0; x < dirSize; x++) {
    string tmpName = allDiscounts[x].returnName();
    if (tmpName == code) {
      tmp = allDiscounts[x];
      return tmp;
    }
  }
}

inline exhibit directory::searchExhibit(string exhibitName)
{
  exhibit tmp;
  int dirSize = exhibitDir.size();
  for (int x = 0; x < dirSize; x++) {
    string tmpUsername = exhibitDir[x].returnName();
    if (tmpUsername == exhibitName) {
      tmp = exhibitDir[x];
      return tmp;
    }
  }
}

inline void directory::manageUsers()
{
  string choice;
  cout << "What would you like to do?" << endl;
  cout << "1.) Print Users\n";
  cout << "2.) Edit User\n";
  cout << "3.) Delete User\n";
  cout << "4.) Create User\n";
  cin >> choice;
  if (choice == "1") {
    printUsers();
  }
  else if (choice == "2") {
    user tmpUser;
    string userName;
    cout << "what user would you like to edit: ";
    cin >> userName;
    tmpUser = searchUser(userName);
    updateUser(tmpUser);
    cout << "Account successfully updated" << endl;
  }
  else if (choice == "3") {
    string userDelete;
    cout << "enter user to be deleted" << endl;
    cin >> userDelete;
    deleteUser(userDelete);
  }
  else if (choice == "4") {
    createUser();
  }
  else { cout << "invalid input"; }
}

inline void directory::manageExhibits()
{
  string choice;
  cout << "What would you like to do?" << endl;
  cout << "1.) Print Exhibits\n";
  cout << "2.) Edit Exhibit\n";
  cout << "3.) Delete Exhibit\n";
  cout << "4.) Create Exhibit\n";
  cin >> choice;
  if (choice == "1") {
    printExhibits();
  }
  else if (choice == "2") {
    //need edit user function manage profile?
  }
  else if (choice == "3") {
    string exhibitToDelete;
    cout << "enter exhibit to be deleted" << endl;
    cin >> exhibitToDelete;
    deleteExhibit(exhibitToDelete);
  }
  else if (choice == "4") {
    createExhibit();
  }
  else { cout << "invalid input"; }
}

//takes user by reference then performs action based on input
inline void directory::menuAction(user &currentUser, bool& loggedStatus)
{
  string choice;
  if (currentUser.returnRole() == "customer") {
    cout << "What would you like to do?" << endl;
    cout << "1.) Generate Order\n";
    cout << "2.) Manage Account\n";
    cout << "3.) Log Out\n";
    cin >> choice;
    if (choice == "1") {
      currentUser.generatePlan(exhibitDir, allDiscounts);
    }
    else if (choice == "2") {
      currentUser.manageProfile();
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
    cin >> choice;
    if (choice == "1") {
      manageUsers();
    }
    else if (choice == "2") {
      manageExhibits();
    }
    else if (choice == "3") {
      createDiscount();
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
    cin >> choice;
    if (choice == "1") {
      createExhibit();
    }
    else if (choice == "2") {
      string exhibitToDelete;
      cout << "input exhibit to delete";
      cin >> exhibitToDelete;
      deleteExhibit(exhibitToDelete);
    }
    else if (choice == "3") {
      //need to be able to add details
      string exhibitToChange;
      exhibit tmpExhibit;

      cout << "eneter exhibit you wish to add details to:  ";
      cin >> exhibitToChange;
      tmpExhibit = searchExhibit(exhibitToChange);

      string details;
      cout << "enter correct details for the exhibit:";
      cin.ignore();
      getline(std::cin, details);
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
inline void directory::deleteExhibit(string exhibitName)
{
  exhibit tmp;
  int dirSize = userDir.size();
  for (int x = 0; x < dirSize; x++) {
    string tmpName = exhibitDir[x].returnName();
    if (tmpName == exhibitName) {
      exhibitDir.erase(exhibitDir.begin() + x);
      cout << "directory size: " << userDir.size() << endl;
      return;
    }
  }

}

inline void directory::deleteUser(string username)
{
  user tmp;
  int dirSize = userDir.size();
  for (int x = 0; x < dirSize; x++) {
    string tmpUsername = userDir[x].returnUsername();
    if (tmpUsername == username) {
      userDir.erase(userDir.begin() + x);
      cout << "directory size: " << userDir.size() << endl;
      return;
    }
  }

}



//prints all users in the vector
inline void directory::printUsers()
{
  int dirSize = userDir.size();
  for (int x = 0; x < dirSize; x++) {
    cout << userDir[x].returnUsername() << endl;
    cout << userDir[x].returnRole() << endl;
    cout << endl;
  }
}

inline void directory::printExhibits()
{
  int dirSize = exhibitDir.size();
  for (int x = 0; x < dirSize; x++) {
    cout << exhibitDir[x].returnName() << endl;
    cout << exhibitDir[x].returnPrice() << endl;
    cout << endl;
  }
}

inline void directory::updateUser(user tmp)
{
  //iterates through directoiry of users and finds the user in vecor and updates
  int dirSize = userDir.size();
  for (int x = 0; x < dirSize; x++) {
    string tmpUsername = userDir[x].returnUsername();
    if (tmpUsername == tmp.returnUsername()) {
      userDir[x] = tmp;
    }
  }
}

inline void directory::updateExhibit(exhibit tmp)
{
  int dirSize = exhibitDir.size();
  for (int x = 0; x < dirSize; x++) {
    string tmpUsername = exhibitDir[x].returnName();
    if (tmpUsername == tmp.returnName()) {
      exhibitDir[x] = tmp;
    }
  }
}



inline bool directory::userExists(string username)
{
  string tmpUsername;
  int dirSize = userDir.size();
  for (int x = 0; x < dirSize; x++) {
    tmpUsername = userDir[x].returnUsername();
    if (tmpUsername == username) {
      return true;
    }
  }
  return false;
}

inline vector<exhibit> directory::returnExhibitDir()
{
  return exhibitDir;
}

//functions for users

inline void user::generatePlan(vector<exhibit> dir, vector<discount> allDiscounts)
{

  vector<exhibit> myExList;
  exhibit exhibitToSet;
  API credit;

  credit.creditValidator();
  cout << "Please eneter your budget(minimum of 15$ is reccomended):";
  cin >> budget;

  int arrivalTime;
  cout << "what time will you be arriving to the park?: (0-23) EX: 2 = 0200:):";
  cin >> arrivalTime;

  if (arrivalTime < 0 || arrivalTime > 23) {
    cout << "you have enetered an invalid time, please enter a number between 0-23";
    cin >> arrivalTime;
  }
  mySchedule.setArrival(arrivalTime);

  bool favSet = false;

  while (favSet != true) {
    string input;
    int favNum;

    cout << "search for an exhibit you would like to see: ";
    cin >> input;

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
    cin >> favNum;
    exhibitToSet.setFav(favNum);

    myExList.push_back(exhibitToSet);

    char finished;
    cout << "Are you finished choosing exhibits to see? (y/n)";
    cin >> finished;
    if (finished == 'y') {
      favSet = true;
    }

  }

  //now we will generate a schedule based on favourablillity
  //need to loop through fav 1-5 and subtract from budget
  //also need to check that the exhibit schedule and user schedule line up
  //already have mySchedule
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


  cout << "If special pass was purchased, please eneter code for discount (for testiing code is: pass) :";
  string codeName;
  cin >> codeName;
  double discountPercent = 0;
  //search vector of discounts to see if exists
  int dirSize = allDiscounts.size();
  for (int x = 0; x < dirSize; x++) {
    string tmpName = allDiscounts[x].returnName();
    if (tmpName == codeName) {
      discountPercent = allDiscounts[x].returnPercent();
      cout << "discount found, discount percent: " << discountPercent << endl;
    }
  }

  //lets user know if discount didnt exist
  if (discountPercent == 0) {
    cout << "No Discount Found For That Code" << endl;
  }

  //must calculate money spent with discount
  //tmp budget carries original budget amount 
  double moneySpent;
  moneySpent = tmpBudget - budget;

  if (discountPercent != 0) {
    //discount percent will now hold actual percent of discount
    discountPercent = 100 - discountPercent;
    discountPercent = discountPercent / 100.00;

    //moneySpent is now correct
    moneySpent = moneySpent * discountPercent;

    //making budget correct
    budget = tmpBudget - moneySpent;
  }
  //calculate final hapiness rating
  happinessRating = happinessRating - moneySpent;

  cout << "Your happiness score for this schedule is: " << happinessRating << endl;
cout << "Your Schedule for the day" << endl;
mySchedule.printSchedule();

//log event
//logEvent("Plan Generated");
logging test;
test.logEvent("Plan Generated ");

}
inline int user::checkSchedule(int favNum, vector<exhibit> ExList)
{
//loops and checks the favorbillity or number that was passed.
int count = 0;
exhibit tmp;
int dirSize = ExList.size();
for (int x = 0; x < dirSize; x++) {
int tmpFav = ExList[x].returnFav();
if (tmpFav == favNum) {
tmp = ExList[x];

//checks if user can affird to schedule this exhibit before scheduling
double budgetTest = budget - tmp.returnPrice();
if (budgetTest >= 0) {

string exhibitName = tmp.returnName();
setSchedules(mySchedule, tmp.returnSchedule(), exhibitName);
count++;
budget = budget - tmp.returnPrice();

}
else { return count; }
}
}
return count;

}

//will check schedule compadibillity then set time
inline void user::setSchedules(schedule userSchedule, schedule ExhibitSchedule, string name)
{
for (int i = 0; i < 24; i++) {

if (userSchedule.checkTime(i) == false && ExhibitSchedule.checkTime(i) == false) {

mySchedule.addTime(i);
mySchedule.addTimeName(name, i);
break;
}

}

}
inline vector<exhibit> user::setFav(vector<exhibit>)
{
return vector<exhibit>();
}

string user::returnUsername()
{
return username;
}

inline string user::returnPassword()
{
return password;
}

inline string user::returnRole()
{
return role;
}

inline void user::setUsername(string str)
{
username = str;
}

inline void user::setPassword(string str)
{
password = str;
}

inline void user::setBudget(double num)
{
budget = num;
}

inline void user::setArrival(int time)
{
mySchedule.setArrival(time);
}

inline void user::setRole(string newRole)
{
role = newRole;
}

inline void user::manageProfile()
{
string choice;
cout << "what would you like to change? :" << endl;
cout << "1.) change budget" << endl;
cout << "2.) change password" << endl;
cin >> choice;
if (choice == "1") {
double newBudget;
cout << "please enter a new budget amount: ";
cin >> newBudget;
setBudget(newBudget);
cout << "new budget amount set" << endl;
}
else if (choice == "2") {
string newPassword;
cout << "please enter a new password: ";
cin >> newPassword;
setPassword(newPassword);
cout << "new password has been set" << endl;
}
else { cout << "invalid input" << endl; }

}


//exhibit functions

exhibit::exhibit()
{
name = "null";
details = "details have not been set";
price = 100000;
exhibitSchedule;
favorabillity = 0;
}

inline void exhibit::setDetails(string text)
{
details = text;
}

inline void exhibit::setPrice(double num)
{
price = num;
}

inline void exhibit::setName(string text)
{
name = text;
}

inline void exhibit::setFav(int num)
{
favorabillity = num;
}

inline string exhibit::returnName()
{
return name;
}

inline double exhibit::returnPrice()
{
return price;
}

inline int exhibit::returnFav()
{
return favorabillity;
}

inline schedule exhibit::returnSchedule()
{
return exhibitSchedule;
}

inline string exhibit::returnDetails()
{
  return details;
}


//schedule functions


schedule::schedule()
{


  for (int i = 0; i < 24; i++) {
    times[i] = false;
    timeName[i] = " ";
  }

  //this is hard coded for testing purposes for phase two
  //remove once added apropriate functionallity
  //srand(time(NULL));
  //times[rand() % 24] = true;
  //times[rand() % 24] = true;
  //times[rand() % 24] = true;
  //times[rand() % 24] = true;
  //times[rand() % 24] = true;
}

inline void schedule::addTime(int x)
{
  if (times[x] == true) {
    cout << "ERROR time taken" << endl;
    return;
  }
  else { times[x] = true; }

}

inline void schedule::addTimeName(string name, int x)
{
  timeName[x] = name;
}

inline void schedule::printSchedule()
{
  for (int i = 0; i < 24; i++) {
    cout << i << "00:  ";
    cout << times[i] << "  " << timeName[i] << endl;
  }

}

inline bool schedule::checkTime(int x)
{
  return times[x];
}

inline void schedule::setArrival(int time)
{
  for (int i = 0; i < time; i++) {
    times[i] = true;
  }
}

//functions for logging service
//make these stand alone functions
//ofstream myfile and logfile is the name of the txt file
inline void logging::getDate(ofstream & myfile)
{
  time_t tt;

  struct tm * ti;

  // Applying time()
  time(&tt);

  // Using localtime()
  ti = localtime(&tt);

  myfile << "DATETIME: " << asctime(ti);
  cout << "DATETIME: " << asctime(ti);
  myfile.close();
}
void logging::logEvent(string str)
{
  ofstream myfile;

  myfile.open("../log/log_DATETIME.txt", std::ofstream::app);

  myfile << setw(20) << str << "";
  cout << setw(20) << str << "";

  getDate(myfile);
  myfile.close();
}



//input scenario functions






//NEEDS DONE





#endif
