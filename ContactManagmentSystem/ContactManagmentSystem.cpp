#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;


class contact {
private:
	char fName[50], lName[50], address[50], email[50];
	long long phNo;

public:
	void CreateContact() 
	{
		cout << "\nenter your first name: ";
		cin >> fName;
		cout << "\nenter your last name: ";
		cin >> lName;
		cout << "\nenter your phone number: ";
		cin >> phNo;
		cout << "\nenter address: ";
		cin >> address;
		cout << "\nenter you email: ";
		cin >> email;
	}
	
	void showContact() 
	{
		cout << "name: " << fName << " " << lName << endl;
		cout << "phone: " << phNo << endl;
		cout << "address: " << address << endl;
		cout << "email: " << email << endl;
	}

	void writeOnFile() 
	{
		char ch;
		ofstream f1;
		f1.open("CMS.dat", ios::binary | ios::app);
		do 
		{
			CreateContact();
			f1.write(reinterpret_cast<char*>(this), sizeof(*this));
			cout << "Do you have next data?(y/n)" << endl;
			cin >> ch;
		} while (ch == 'y');
		cout << "contact has been succesfully created..." << endl;
		f1.close();
	}

	void readFromFile()
	{
		ifstream f2;
		f2.open("CMS.dat", ios::binary);

		cout << "\n_________________________________________________________\n" << endl;
		cout << "LIST OF CONTACTS" << endl;
		cout << "\n_________________________________________________________\n" << endl;

		while (!f2.eof())
		{
			if (f2.read(reinterpret_cast<char*>(this), sizeof(*this)))
			{
				showContact();
				cout << "\n_________________________________________________________\n" << endl;
			 }
		}
		f2.close();
	}

	void searchOnFile() 
	{
		fstream f3;
		long long phone;
		cout << "enter phone no.";
		cin >> phone;
		f3.open("CMS.dat", ios::binary, ios::in);

		while (!(f3.eof()))
		{
			if (f3.read(reinterpret_cast<char*>(this), sizeof(*this)))
			{
				if (phone == phNo)
				{
					showContact();
					return;
				}
			}
		}
		cout << "\n\n No record found" << endl;
		f3.close();
	}
	void deleteFromFile()
	{
		long long phone;
		int flag = 0;
		ofstream f4;
		ifstream f5;

		f5.open("CMS.dat", ios::binary);
		f4.open("temp.dat", ios::binary);
		cout << "enter phone number to delete: ";
		cin >> phone;

		while (!f5.eof())
		{
			if (f5.read(reinterpret_cast<char*>(this), sizeof(*this)))
			{
				if (phNo != phone)
				{
					f4.write(reinterpret_cast<char*>(this), sizeof(*this));
				}
				else  flag = 1;
				
			}
		}
		f5.close();
		f4.close();
		remove("CMS.dat");
		rename("temp.dat", "CMS.dat");

		if(flag == 1) {cout << "\ncontact deleted" << endl;}
		else{cout << "\n contact not found" << endl;}
		
	}

	void editContact() 
	{
		long long phone;
		fstream f6;

		cout << "edit contact" << endl;
		cout << "\n_________________________________________________________\n" << endl;
		cout << "enter th number to edit: ";
		cin >> phone;

		f6.open("CMS.dat", ios::binary | ios::out | ios::in);

		while(!f6.eof())
		{
			if (f6.read(reinterpret_cast<char*>(this), sizeof(*this)))
			{
				if (phone == phNo)
				{
					cout << "enter new record: ";
					CreateContact();

					int pos = -1 * sizeof(*this);
					f6.seekp(pos, ios::cur);
					f6.write(reinterpret_cast<char*>(this), sizeof(*this));
					cout << endl << endl << "\t contact successfully updated." << endl;
					return;
				}
			}
		}
		cout << "\n\n No record found" << endl;
		f6.close();
	}
};


int main()
{
	system("cls");
	system("color 3F"); // color xy, x= background color, y = text color
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t* WELCOME TO THE CONTACT MANAGMENT SYSTEM*" << endl << endl;
	_getch();
	while (1) 
	{
		contact c1;
		int choice;
		system("cls");
		system("color 03");
		cout << "\nCONTACT MANAGMENT SYSTEM" << endl;
		cout << "MAIN MENU" << endl;
		cout << "\n_________________________________________________________\n" << endl;
		cout << "[1] Add a new Contact\n";
		cout << "[2] List of contacts\n";
		cout << "[3] Search for contact\n";
		cout << "[4] Delete a contact\n";
		cout << "[5] Edit a contact\n";
		cout << "[0] Exit\n";
		cout << "\n_________________________________________________________\n" << endl;
		cout << "enter you choice: ";
		cin >> choice;

		switch (choice) 
			{
			case 1:
			system("cls");
			c1.writeOnFile();
			break;

			case 2:
			system("cls");
			c1.readFromFile();
			break;

			case 3:
			system("cls");
			c1.searchOnFile();
			break;

			case 4:
			system("cls");
			c1.deleteFromFile();
			break;

			case 5:
			system("cls");
			c1.editContact();
			break;

			case 0:
			system("cls");
			cout << "\n\n\n\t\t\tThank you for using CMS" << endl;
			exit(0);
			break;


			default:
			continue;
			}
			
		
			int opt;
			cout << "\n\n::Enter the choice:: [1] Main Menu\n[2] exit\n";
			cin >> opt;

			switch (opt)
			{
			case 0:
			system("cls");
			cout << "\n\n\n\t\t\tThank you for using CMS" << endl;
			exit(0);
			break;

			default:
			continue;
			}
		}
		return 0;
}
