#ifndef ZOINKERS_H_
#define ZOINKERS_H_


#include <cstdlib>
#include <ctime>
#include<iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;



/*	TODO:
	Done	1.) MAKE LOGIN() FUNCTION
	Done	2.) HARD CODE SOME EXHIBITS
	Done	3.) CREATE SCHEDULE FUNCTIONS
	Done	4.) GENERATE PLAN FUNCTION
	Done	5.) SEARCH EXHIBIT FUNCTION
			6.) BUILD TESTING CLIENT
	Done	7.) UPDATE LOGGING TO BE REGULAR FUNCTRIONS NOT ATTACHED TO A CLASS
	Done	8.) DO HAPINESS CALCULATIONS AND (done)ARRIVAL TIME SCHEDULING 
	Done	9.) ALL LOG EVENTS
*/




class schedule {

public:
	schedule();
	void addTime(int);
	void addTimeName(string,int);
	//bool checkTime(int);
	//void removeTime(int);
	void printSchedule();
	bool checkTime(int x);
	void setArrival(int time);

private:

	bool times[24];
	string timeName[24];

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

	void generatePlan(vector<exhibit>);
	vector<exhibit> setFav(vector<exhibit>); // should this take in an exhibit
	int checkSchedule(int favNum, vector<exhibit> ExList);
	void setSchedules(schedule userSchedule, schedule ExhibitSchedule, string name);
	string returnUsername();
	string returnPassword();
	void setUsername(string);
	void setPassword(string);
	void setBudget(double);
	void setArrival(int time);

	void INPUTgeneratePlan(vector<exhibit>);
private:
	schedule mySchedule;
	double budget;
	string username;
	string password;
};

class directory {

public:
	
	user Login();
	void createUser();
	void createExhibit();
	user searchUser(string username);
	exhibit searchExhibit(string exhibitName);
	bool userExists(string);
	vector<exhibit> returnExhibitDir();

	void INPUTcreateUser();
	void INPUTcreateExhibit();
	user INPUTLogin();
private:
	vector <exhibit> exhibitDir;
	vector <user> userDir;

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
	//logging event
	logging test;
	test.logEvent("System Started ");

	char end;
	cout << "what would you like to do?: " << endl;
	cout << "USER SCENARIOS (u)" << endl;
	cout << "INPUT SCENARIOS (i)" << endl;
	cin >> end;
	if (end == 'u') {
		user myUser;
		mainDirectory.createUser();
		myUser = mainDirectory.Login();

		mainDirectory.createExhibit();
		mainDirectory.createExhibit();

		cout << "Now begining to generate plan" << endl;
		myUser.generatePlan(mainDirectory.returnExhibitDir());
	}
	else if (end == 'i') {
	

		directory dir;
		user myUser;
		dir.INPUTcreateUser();
		system("PAUSE");
		myUser = dir.INPUTLogin();
		system("PAUSE");
		dir.INPUTcreateExhibit();
		system("PAUSE");
		myUser.INPUTgeneratePlan(dir.returnExhibitDir());
		system("PAUSE");
	}

	
	//logEvent("System Shut Down");
	test.logEvent("system shutdown ");
	system("PAUSE");
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
	userDir.push_back(newUser);

	cout << "username:	" << userDir.at(0).returnUsername() << "\npassword:	" << userDir.at(0).returnPassword() << endl;
	cout << "account creation successful" << endl;

	cout << "current size of user directory:	" << userDir.size() << endl;

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

inline user directory::searchUser(string username)
{
	user tmp;
	int dirSize = userDir.size();
	for (int x = 0; x < dirSize; x++) {
		string tmpUsername = userDir[x].returnUsername();
		if (tmpUsername == username) {
			tmp = userDir[x];
			return tmp;
		}
	}
}

inline exhibit directory::searchExhibit(string exhibitName)
{
	exhibit tmp;
	int dirSize = userDir.size();
	for (int x = 0; x < dirSize; x++) {
		string tmpUsername = userDir[x].returnUsername();
		if (tmpUsername == exhibitName) {
			tmp = exhibitDir[x];
			return tmp;
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

inline void user::generatePlan(vector<exhibit> dir)
{
	
	vector<exhibit> myExList;
	exhibit exhibitToSet;
	cout << "Please eneter your budget(minimum of 15$ is reccomended):	";
	cin >> budget;

	int arrivalTime;
	cout << "what time will you be arriving to the park?: (0-23) EX: 2 = 0200:	):	";
	cin >> arrivalTime;

	if(arrivalTime < 0 || arrivalTime > 23){
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
inline int user::checkSchedule(int favNum,vector<exhibit> ExList)
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
				setSchedules(mySchedule, tmp.returnSchedule(),exhibitName);
				count++;
				budget = budget - tmp.returnPrice();
				
			}
			else { return count; }
		}
	}
	return count;
	
}

//will check schedule compadibillity then set time
inline void user::setSchedules(schedule userSchedule, schedule ExhibitSchedule,string name)
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

inline void schedule::addTimeName(string name,int x)
{
	timeName[x] = name;
}

inline void schedule::printSchedule()
{
	for (int i = 0; i < 24; i++) {
		cout << i << "00:  ";
		cout << times[i] << "  " << timeName[i] <<endl;
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

	myfile << setw(20) << str << "				";
	cout << setw(20) << str << "				";

	getDate(myfile);
	myfile.close();
}



//input scenario functions





inline void user::INPUTgeneratePlan(vector<exhibit> dir)
{
	ifstream in("../data/order.txt");
	string inStr;

	vector<exhibit> myExList;
	exhibit exhibitToSet;
	cout << "Please eneter your budget(minimum of 15$ is reccomended):	";

	//file input
	getline(in, inStr);
	budget = atof(inStr.c_str());
	//cin >> budget;

	int arrivalTime;
	cout << "what time will you be arriving to the park?: (0-23) EX: 2 = 0200:	):	";
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

inline void directory::INPUTcreateExhibit()
{
	ifstream in("../data/exhibit.txt");
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

inline void directory::INPUTcreateUser()
{
	ifstream in("../data/user.txt");
	user newUser;
	string username;
	string password;

	cout << "please enter a username: \n";
	string inStr;
	//fileinput
	getline(in, inStr);
	//price = stoi(inStr);
	username = inStr;
	//cin >> username;


	//checks if username exists already in the system
	while (userExists(username) == true) {
		cout << "Please enter a different username, chosen username is taken: " << endl;
		cin >> username;
	}

	newUser.setUsername(username);
	cout << "please enter a password: \n" << endl;;
	//fileinput
	getline(in, inStr);
	//price = stoi(inStr);
	password = inStr;
	//cin >> password;
	newUser.setPassword(password);
	userDir.push_back(newUser);

	cout << "\n username:	" << userDir.at(0).returnUsername() << "\n password:	" << userDir.at(0).returnPassword() << endl;
	cout << "account creation successful" << endl;

	cout << "current size of user directory:	" << userDir.size() << endl;

	//log event
	//logEvent("User Created");
	logging test;
	test.logEvent("User Created ");
}

inline user directory::INPUTLogin()
{
	ifstream in("../data/user.txt");
	user currentUser;
	user empty;
	string user;
	string password;

	string inStr;
	//fileinput
	getline(in, inStr);

	cout << "Please enter your username: \n";
	user = inStr;
	//cin >> user;
	cout << "test:" <<endl;
	cout << user << endl;
	currentUser = searchUser(user);

	cout << "test:" <<endl;

	cout << "please enter your password: \n";
	//fileinput
	getline(in, inStr);
	password = inStr;
	//cin >> password;

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

#endif
