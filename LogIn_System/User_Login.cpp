#include <iostream>
#include <fstream> 
#include <string>
#include <cstdio>
#include <vector>
using namespace std;

//Folosim constante pentru numele fisierelor pentru modificari ulterioare
const string USER_FILE = "user.txt";
const string PASS_FILE = "password.txt";
const string TARGET_FILE = "target.txt";

class UserLogin {
private:
	vector<string> usernames; //Lista de username
	vector<string> passwords; // Lista de parole
	string userAttempted;
	string passwordAttempted;
	bool access;
	

	int getLastUserID(string file) {
		ifstream fin;

		fin.open(file, ifstream::in);

		if (fin.peek() == EOF) {    // nici un user pana aici
			return 0;
		}

		fin.seekg(0, ios_base::end);
		string line = "";

		for (int i = -1; line[0] != '#'; --i) {
			fin.seekg(i, ios_base::end);
			fin >> line;
		}

		fin.close();
		line.erase(0, 4);

		return stoi(line);
	}

public:

	// Constructor
	UserLogin() {
		this->access = false;
	}

	//Deconstructor
	~UserLogin() {
	}

	// Verifica fisierul pentru date si citeste
	void check_file() {
		string username, password;
		fstream file;

		file.open(USER_FILE.c_str(), ios::in);

		if (file.is_open()) {
			// Daca nu a ajuns la finalul fisierului, citeste date
			while (!file.eof()) {
				getline(file, username);
				this->usernames.push_back(username);
			}
		}

		file.close();

		file.open(PASS_FILE.c_str(), ios::in);

		if (file.is_open()) {
			//Daca nu a ajuns la finalul fisierului, citeste date
			while (!file.eof()) {
				getline(file, password);
				this->passwords.push_back(password);
			}
		}

		file.close();
	}

	//Afiseaza continutul fisierului
	void show_file(const string& FILE) const
	{
		string line;
		fstream showfile;

		showfile.open(FILE.c_str(), ios::in);

		if (!showfile.is_open())
		{
			cout << "\nError in opening file..!!\n";

			exit(0);
		}

		cout << "\n";

		while (!showfile.eof()) {
			getline(showfile, line);
			cout << line << "\n";
		}

		cout << "\n";

		showfile.close();
	}

	void saveFile(string text, string file, int id) {
		ofstream fout;

		fout.open(file, ofstream::app);
		fout.seekp(0, ios::end);

		if (fout.tellp() != 0) {
			fout << endl;
		}


		
		fout << "#ID:" << id;

		fout.close();
	}

	int authenticateUsername(string attempt, string file) {
		ifstream fin;

		fin.open(file, ifstream::in);

		string line = "";
		string username = "";
		int encryptedChar = 0;

		while (fin.peek() != EOF) {
			fin >> line;

			if (line.find("#ID:") != string::npos) {
				if (attempt == username) {
					fin.close();

					line.erase(0, 4);

					return stoi(line);      // return id

				}
				else {
					username.clear();
				}

			}
			
			line.clear();
		}

		fin.close();
		return 0;
	}

	bool authenticatePassword(string attempt, string file, int id) {
		ifstream fin;

		fin.open(file, ifstream::in);

		string line = "";
		string password = "";

		while (fin.peek() != EOF) {
			fin >> line;

			if (line.find("#ID:" + to_string(id)) != string::npos) {
				if (attempt == password) {
					fin.close();

					return true;      // return userID

				}
				else {
					return false;
				}

			}
			else {
				if (line.find("#ID:") != string::npos) {
					password.clear();

				}
				
			}

			line.clear();
		}
	}

	void registerUser(string username, string password) {
		if (this->authenticateUsername(username, USER_FILE)) {   // duplica username
			cout << "This username is used." << endl;
			return;
		}

		int id = this->getLastUserID(USER_FILE) + 1;

		this->saveFile(username, USER_FILE, id);
		this->saveFile(password, PASS_FILE, id);
	}

	// Permite userului sa se logheze solicitandui username si parola
	void login() {

		cout << "Please enter the following details to get access to the files :\n";

		cout << "Username : ";
		getline(cin, this->userAttempted);

		// Verifica daca emailul este in baza de date
		//Daca emailul nu este gasit in baza de date
		int id = this->authenticateUsername(this->userAttempted, USER_FILE);

		if (id != 0)
		{
			int user_attempts = 5;

			
			while (user_attempts != 0)
			{
				cout << "Password : ";
				getline(cin, this->passwordAttempted);

				if (this->authenticatePassword(this->passwordAttempted, PASS_FILE, id))
				{
					string file_name;

					cout << "\nBingo ! You now have access to the files\n";

					cout << "\nEnter the file name you want to look at: ";
					getline(cin, file_name);

					//Returneaza continutul fisierului
					this->show_file(file_name);
					user_attempts = 0;
					access=true;
					 
				}
				else
				{
					cout << "\nOops! Incorrect password\n";
					--user_attempts;
					if (user_attempts == 0) {
						cout << "Sorry you've reached the maximum limit for attempting password!" << endl;
						break;
					}
				}
			}
		}

		else {
			cout << "\nOops! Invalid user id\n\n"
				<< "Your id is not registered in our Database\n\n";
			this->login();
		}
	}

	bool search(const string& KEY, const vector<string> LIST) const {
		unsigned int index = 0;
		bool found = false;

		while (index < LIST.size() && !found) {
			if (KEY == LIST[index]) {
				found = true;
				return found;
			}
			else {
				++index;
			}
		}

		
		return found;
	}
};

int main() {
	UserLogin app;

	app.check_file();

	app.registerUser("gabi1@gmail.com", "test@3");

	app.login();

	string freezing_terminal;

	cout << "Enter any key to exit: " << endl;

	getline(cin, freezing_terminal);

	return 0;
}