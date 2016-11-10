// PhoneBookAppRedo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <regex>

using namespace std;



class Contact
{
public:
	string ContactName;
	list<string> ContactNo;
};

class PhoneBookMethods
{
public:

	
	string PhoneNo;
	list<Contact> Contacts;
	Contact ObjContact;

	double NumOfContacts();

	string GetName();

	string GetNum();
	
	void AddContacts();

	void DisplayContacts();

	void UpdateContact();

	void DeleteContact();

	void SearchContact();

	void AddNewContact(Contact&);

	int DisplaySpecificContacts(string);

	void UpdateContactDetails(string, char);

	void DeleteContactDetails(string, char);

	char MergeContacts(string);

	bool CheckExistingContact(string);

	void FillPhoneBook();

	int SearchByName(string);

};


bool SortMethod(Contact a, Contact b);

int j{ 0 };
int main()
{
	PhoneBookMethods ObjPhoneBookMethods;

	char choice{ '0' };

	while (choice != '6')
	{
		cout << "\t\t+---------------------------------------------------------+";
		cout << "\n\t\t|              Welcome To Arash's Phone Book              |";
		cout << "\n\t\t+---------------------------------------------------------+";
		cout << "\n\t\t  Enter Option Number:\n\t\t  1. Add Contact(s)\n\t\t  2. Delete Contact\n\t\t  3. Display Contacts\n\t\t  4. Update Contact\n\t\t  5. Search Contact\n\t\t  6. Exit\n\t\t  Enter Option Here: ";
		(cin >> choice).get();

		switch (choice)

		{
		case '1':

			system("cls");

			ObjPhoneBookMethods.AddContacts();

			cout << "\n\n\t\t";
			system("pause");

			system("cls");

			break;

		case '2':

			system("cls");

			ObjPhoneBookMethods.DeleteContact();

			system("cls");

			break;

		case '3':
			system("cls");
			ObjPhoneBookMethods.Contacts.sort(SortMethod);
			ObjPhoneBookMethods.DisplayContacts();
			cout << "\n\n\t\t";
			system("pause");
			system("cls");
			break;

		case '4':
			system("cls");
			ObjPhoneBookMethods.UpdateContact();
			system("cls");
			break;


		case '5':
			system("cls");
			ObjPhoneBookMethods.SearchContact();
			system("cls");
			break;

		case '6':
			break;

		default:
			system("cls");
			cout << "\n\tTry Again\n";
			break;
		}
	}
	return 0;
}


double PhoneBookMethods::NumOfContacts() 
{
	double NumOfEntries;
	while ((cout << "\n\n\tEnter Number of Contacts you wish to add: ") && !(cin >> NumOfEntries) || (NumOfEntries < 0))
	{
		cout << "\n\t\t\tPlease enter a valid number.";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return NumOfEntries;
}

string PhoneBookMethods::GetName()
{
	string FName, LName, Name;

	cout << "\n\n\t\tEnter First Name: ";
	cin >> FName;

	cin.ignore();
	cout << "\n\n\t\tEnter Last Name: ";
	getline(cin, LName, '\n');

	Name = (FName + " " + LName);

	transform(Name.begin(), Name.end(), Name.begin(), toupper);

	return Name;
}

string PhoneBookMethods::GetNum()
{
	string PhoneNo;
	cout << "\n\n\t\tEnter Phone Number: ";
	regex r("^(([0]|(\\+1-)|(\\+1))\\d{10})|\\d{10}$");
	cin >> PhoneNo;
	while (!regex_match(PhoneNo, r))
	{
		cout << "\n\n\t\tPlease Enter a valid Number";
		cout << "\n\n\t\tEnter Phone Number: ";
		cin >> PhoneNo;
	}
	if (PhoneNo.at(0) == '+' && PhoneNo.length() > 10)
	{
		if (PhoneNo.at(3) == '-')
		{

		}
		else
		{
			PhoneNo.replace(0, 3, "1");
		}
	}
	if (PhoneNo.at(0) == '0')
	{
		PhoneNo.replace(0, 1, "(+1)");
	}
	if (PhoneNo.at(0) != '0' && PhoneNo.at(0) != '+')
	{
		PhoneNo = "(+1)" + PhoneNo;
	}
	return PhoneNo;
}

bool SortMethod(Contact a, Contact b) 
{
	if (a.ContactName == b.ContactName)
	{
		return a.ContactNo < b.ContactNo;
	}
	else
	{
		return a.ContactName < b.ContactName;
	}
}






void PhoneBookMethods::AddContacts() 
{
	cout << "\n\t\t+----------------------------+";
	cout << "\n\t\t|         Add Contact        |";
	cout << "\n\t\t+----------------------------+";
	char ch{ 'a' };
	int temp = (int)NumOfContacts();
	int i;
	for (i = 1; i <= temp; i++)
	{
		cout << "\n\n\t\tEntry Number " << i;
		Contact AddContact;
		ObjContact.ContactName = GetName();
		if (CheckExistingContact(ObjContact.ContactName))
		{
			cout << "\n\n\t\tContact Name Already Exists.\n\n\t\tDo you want to add a new contact number to this existing contact?";
			cout << "\n\n\t\ty = Yes add more numbers.\n\n\t\tn = Number Add as a new contact.\n\n\t\tEnter your choice: ";
			cin >> ch;
			if (ch == 'y' || ch == 'Y')
			{
				if (DisplaySpecificContacts(ObjContact.ContactName) > 1)
				{
					    cout << "\n\t\t+----------------------------+";

					cout << "\n\n\t\tEnter the Existing Contact No of the Contact: ";


					PhoneNo = GetNum();
					for (Contact& ExistingContact : Contacts)
					{
						if (ExistingContact.ContactName == ObjContact.ContactName)
						{
							for (string No : ExistingContact.ContactNo)
							{
								if (No == PhoneNo)
								{
									    cout << "\n\t\t+----------------------------+";
									cout << "\n\n\t\tEnter the New Contact Number:";
									PhoneNo = GetNum();
									ch = MergeContacts(PhoneNo);
									while (ch != 'n' && ch != 'N')
									{
										if (ch == 'y' || ch == 'Y')
										{
											ExistingContact.ContactNo.push_back(PhoneNo);
											cout << "\n\n\t\tDo you want to add more contact numbers to " << ObjContact.ContactName << "?";
											cout << "\n\n\t\ty = Yes  n = No\n\n\t\tEnter your choice: ";
											cin >> ch;
											if (ch == 'y' || ch == 'Y')
											{
												PhoneNo = GetNum();
											}
										}
									}
									ch = 'c'; 
									break;
								}
							}
						}
						if (ch == 'c') 
						{
							break;
						}
					}
				}
				else
				{
					for (Contact& ExistingContact : Contacts)
					{
						if (ExistingContact.ContactName == ObjContact.ContactName)
						{
							    cout << "\n\t\t+----------------------------+";
							cout << "\n\n\t\tEnter the New Contact Numbers:";
							PhoneNo = GetNum();
							ch = MergeContacts(PhoneNo);
							while (ch != 'n' && ch != 'N')
							{
								if (ch == 'y' || ch == 'Y')
								{
									ExistingContact.ContactNo.push_back(PhoneNo);
									cout << "\n\n\t\tDo you want to add more contact numbers to " << ObjContact.ContactName << "?";
									cout << "\n\n\t\ty = Yes  n = No\n\n\t\tEnter your choice: ";
									cin >> ch;
									if (ch == 'y' || ch == 'Y')
									{
										PhoneNo = GetNum();
									}
								}
							}
							ch = 'x'; 
							break;
						}
					}
				}
			}
			if (ch == 'n' || ch == 'N')
			{
				AddNewContact(AddContact);
				j++;
			}
		}
		else
		{
			AddNewContact(AddContact);
			j++;
		}
	}
	cout << "\n\n\t\t" << j << " Contacts Added.\n\n\t\t";
	j = 0;
}

void PhoneBookMethods::DisplayContacts() 
{
	cout << "\n\t\t+----------------------------+";
	cout << "\n\t\t|       Contact Details      |";
	cout << "\n\t\t+----------------------------+";
	if (Contacts.empty())
	{
		cout << "\n\n\t\tNo Contacts in the phone book.";
	}
	else
	{
		cout << "\n\t\tThe list of " << Contacts.size() << " contacts are: \n";
		for (Contact& DisplayContacts : Contacts)
		{
			cout << "\n\t\tContact Name: " << DisplayContacts.ContactName;
			cout << "\n\t\tContact Number(s): ";
			DisplayContacts.ContactNo.sort();
			DisplayContacts.ContactNo.unique();
			for (string N : DisplayContacts.ContactNo)
			{
				cout << N << " ";
			}
			cout << "\n";
		}
	}
}

void PhoneBookMethods::UpdateContact() 
{
	char ch{ 'a' };
	int F = 1;
	while (ch != '3')
	{
		cout << "\n\t\t+----------------------------+";
		cout << "\n\t\t|      Update Contact        |";
		cout << "\n\t\t+----------------------------+";
		cout << "\n\n\t\t Enter Option Number:\n\t\t 1. Update Contact By Name\n\t\t 2. Update Contact By Number\n\t\t 3. Main Menu\n\t\t Enter your choice: ";
		(cin >> ch).get();
		switch (ch)
		{
		case '1': 
			cout << "\n\n\t\tEnter the Contact Name to be updated: ";
			ObjContact.ContactName = GetName();
			if (DisplaySpecificContacts(ObjContact.ContactName) == 0)
			{
				system("cls");
				cout << "\n\t\t+----------------------------+";
				cout << "\n\t\tNo Contacts with " << ObjContact.ContactName << " available.";
				cout << "\n\t\t+----------------------------+";
				cout << "\n\t\t";
				system("pause");
			}
			system("cls");
			UpdateContactDetails(ObjContact.ContactName, ch);
			break;

		case '2':
			cout << "\n\n\t\tEnter the Contact Number to update contact: ";
			PhoneNo = GetNum();
			if (DisplaySpecificContacts(PhoneNo) == 0)
			{
				system("cls");
				cout << "\n\t\t+----------------------------+";
				cout << "\n\t\tNo Contacts with " << PhoneNo << " available.";
				cout << "\n\t\t+----------------------------+";
				cout << "\n\t\t";
				system("pause");
			}
			system("cls");
			UpdateContactDetails(PhoneNo, ch);
			break;

		case '3':
			break;


		default:
			cout << "\n\tInvaild Option Please Select A Vaild Option.\n";
			break;
		}
	}
}

void PhoneBookMethods::DeleteContact() 
{
	char ch{ 'a' };

	int F = 1;
	while (ch != '3')
	{
		cout << "\n\t\t+------------------------------+";
		cout << "\n\t\t|        Delete Contact        |";
		cout << "\n\t\t+------------------------------+";
		cout << "\n\t\t  Enter Option Number:\n\t\t  1. Delete Contact via Name\n\t\t  2. Delete Contact via Number\n\t\t  3. Return to Main Menu\n\t\t  Enter your choice: ";
		(cin >> ch).get();
		switch (ch)
		{
		case '1':
			cout << "\n\t\tEnter the Contact Name you wish to delete: ";
			ObjContact.ContactName = GetName();
			if (DisplaySpecificContacts(ObjContact.ContactName) == 0)
			{
				system("cls");
				cout << "\n\t\t+----------------------------+";
				cout << "\n\t\tContacts with " << ObjContact.ContactName << "are not available.";
				cout << "\n\t\t+----------------------------+";
				cout << "\n\t\t";
				system("pause");
			}
			system("cls");
			DeleteContactDetails(ObjContact.ContactName, ch);
			break;

		case '2':
			cout << "\n\t\tEnter the Contact Number you wish to delete: ";
			PhoneNo = GetNum();
			if (DisplaySpecificContacts(PhoneNo) == 0)
			{
				system("cls");
				cout << "\n\t\t+----------------------------+";
				cout << "\n\n\t\tNo Contacts with " << PhoneNo << " available.";
				cout << "\n\t\t+----------------------------+";
				cout << "\n\n\t\t";
				system("pause");
			}
			system("cls");
			DeleteContactDetails(PhoneNo, ch);
			break;

		case '3':
			break;

		default:
			cout << "\n\tPlease choose a correct option.\n";
			break;
		}
	}
}

void PhoneBookMethods::SearchContact() 
{
	char ch{ 'a' };
	while (ch != '3')
	{
		cout << "\n\t\t+-----------------------------+";
		cout << "\n\t\t|        Search Contact       |";
		cout << "\n\t\t+-----------------------------+";
		cout << "\n\t\t  Enter Option Number:\n\t\t 1. Search Contact By Name\n\t\t 2. Search Contact By Number\n\t\t 3. Main Menu\n\t\t Enter your choice: ";
		(cin >> ch).get();

		switch (ch)
		{
		case '1': 
			system("cls");
			cout << "\n\n\t\tEnter the Contact Name you wish to search: ";
			getline(cin, ObjContact.ContactName);
			transform(ObjContact.ContactName.begin(), ObjContact.ContactName.end(), ObjContact.ContactName.begin(), toupper);
			if (DisplaySpecificContacts(ObjContact.ContactName) == 0)
			{
				if (system("cls") || SearchByName(ObjContact.ContactName) > 0)
				{
					cout << "\n\n\t";
					cout << "\n\n\t\t";
					system("pause");
					system("cls");
				}
				else
				{
					system("cls");
					cout << "\n\tNo Contacts with " << ObjContact.ContactName << " available.";
				}
			}
			else if (DisplaySpecificContacts(ObjContact.ContactName) != 0)
			{
				system("cls");
				DisplaySpecificContacts(ObjContact.ContactName);
			}

			break;

		case '2':
			system("cls");
			cout << "\n\n\t\tEnter the Contact Number to be searched: ";
			PhoneNo = GetNum();
			if (DisplaySpecificContacts(PhoneNo) == 0)
			{
				system("cls");
				cout << "\n\n\t\tNo Contacts with " << PhoneNo << " available.";
			}
			else if (DisplaySpecificContacts(ObjContact.ContactName) != 0)
			{
				system("cls");
				DisplaySpecificContacts(PhoneNo);
			}
			break;

		case '3':
			break;


		default:
			cout << "\n\tPlease choose a correct option.\n";
			break;
		}
	}
}






void PhoneBookMethods::AddNewContact(Contact& NewContact) 
{
	char ch = 'a';
	NewContact.ContactName = ObjContact.ContactName;
	PhoneNo = GetNum();
	NewContact.ContactNo.push_back(PhoneNo);
	ch = MergeContacts(PhoneNo);
	if (ch == 'n')
	{
		j--;
	}
	else if (ch == 'y')
	{
		while (ch != 'n' && ch != 'N')
		{
			cout << "\n\t\tDo you want to add more contact numbers to " << NewContact.ContactName << "?";
			cout << "\n\t\ty = Yes \n\t\t n = No\n\n\t\tEnter your choice: ";
			cin >> ch;
			if (ch == 'y' || ch == 'Y')
			{
				NewContact.ContactNo.push_back(GetNum());
			}
			if (ch == 'n' || ch == 'N')
			{
				Contacts.push_back(NewContact);
			}
		}
	}
}

int PhoneBookMethods::DisplaySpecificContacts(string Detail) 
{
	int i = 0;
	cout << "+----------------------------+";
	cout << "|  Display Specific Contact  |";
	cout << "+----------------------------+";
	if (Detail.at(0) == '+')
	{
		cout << "\n\t\tThe Contact Details are: \n";
		for (Contact DisplayContact : Contacts)
		{
			for (string DisplayNo : DisplayContact.ContactNo)
			{
				if (DisplayNo == Detail)
				{
					cout << "\n\n\t\tContact Name: " << DisplayContact.ContactName << "\n";
					for (string DisplayNo : DisplayContact.ContactNo)
					{
						cout << "\n\t\tContact Number(s): ";
						cout << DisplayNo << " ";
					}
					i++;
					cout << "\n\n";
				}
			}
		}
	}
	else
	{
		cout << "\n\n\t\tThe Contact Details are: \n";
		for (Contact DisplayContact : Contacts)
		{
			if (DisplayContact.ContactName == Detail)
			{
				cout << "\n\t\tContact Name: " << DisplayContact.ContactName << "\n";
				for (string DisplayNo : DisplayContact.ContactNo)
				{
					cout << "\n\t\tContact Number(s): ";
					cout << DisplayNo << " ";
				}
				i++;
				cout << "\n\n";
			}
		}
	}
	return i;
}

void PhoneBookMethods::UpdateContactDetails(string Detail, char ch) 
{
	int F = 1;
	string Temp;
	if (DisplaySpecificContacts(Detail) > 1)
	{
		if (ch == '1')
		{
			    cout << "\n\t\t+----------------------------+";
			cout << "\n\n\t\tEnter the Contact Number to Update Contact.";
			PhoneNo = GetNum();
			for (list<Contact>::iterator It = Contacts.begin(); It != Contacts.end(); It++)
			{
				if (It->ContactName == Detail)
				{
					for (string& TempNo : It->ContactNo)
					{
						if (TempNo == PhoneNo)
						{
							    cout << "\n\t\t+----------------------------+";
							cout << "\n\t\tDo you want to Update Specific Number or Update Contact Name?";
							cout << "\n\t\ta. Update Contact Number\n\n\t\tb. Update Contact Name\n\n\t\tEnter your choice : ";
							cin >> ch;
							if (ch == 'a' || ch == 'A')
							{
								cout << "\n\n\t\tEnter the Updated Contact Number: ";
								Temp = GetNum();
								if (Temp == TempNo)
								{
									cout << "\n\n\t\tContact Number Not Updated.";
								}
								else
								{
									TempNo = Temp;
									cout << "\n\n\t\tContact Number Updated.";
								}
								F = 0;
								break;
							}
							else if (ch == 'b' || ch == 'B')
							{
								    cout << "\n\t\t+----------------------------+";
								cout << "\n\n\t\tEnter the Updated Contact Name: ";
								ObjContact.ContactName = GetName();
								if (It->ContactName == ObjContact.ContactName)
								{
									cout << "\n\n\t\tContact Name Not Updated.";
								}
								else
								{
									It->ContactName = ObjContact.ContactName;
									cout << "\n\n\t\tContact Name Updated.";
								}
								F = 0;
								break;
							}
						}
					}
				}
				if (F == 0)
				{
					break;
				}
			}
		}

		if (ch == '2')
		{
			    cout << "\n\t\t+----------------------------+";
			cout << "\n\n\t\tEnter the Contact Name to Delete Contact.";
			ObjContact.ContactName = GetName();
			for (list<Contact>::iterator It = Contacts.begin(); It != Contacts.end(); It++)
			{
				if (It->ContactName == ObjContact.ContactName)
				{
					for (string& TempNo : It->ContactNo)
					{
						if (TempNo == PhoneNo)
						{
							    cout << "\n\t\t+----------------------------+";
							cout << "\n\n\t\tDo you want to Update Specific Number or Update Contact Name?";
							cout << "\n\n\t\ta. Update Contact Number\n\n\t\tb. Update Contact Name\n\n\t\tEnter your choice (a or b): ";
							cin >> ch;
							if (ch == 'a' || ch == 'A')
							{
								cout << "\n\n\t\tEnter the Updated Contact Number: ";
								Temp = GetNum();
								if (Temp == TempNo)
								{
									cout << "\n\n\t\tContact Number Not Updated.";
								}
								else
								{
									TempNo = Temp;
									cout << "\n\n\t\tContact Number Updated.";
								}
								F = 0;
								break;
							}
							else if (ch == 'b' || ch == 'B')
							{
								    cout << "\n\t\t+----------------------------+";
								cout << "\n\n\t\tEnter the Updated Contact Name: ";
								ObjContact.ContactName = GetName();
								if (It->ContactName == ObjContact.ContactName)
								{
									cout << "\n\n\t\tContact Name Not Updated.";
								}
								else
								{
									It->ContactName = ObjContact.ContactName;
									cout << "\n\n\t\tContact Name Updated.";
								}
								F = 0;
								break;
							}
						}
					}
				}
				if (F == 0)
				{
					break;
				}
			}

		}
	}

	else if (system("cls") || DisplaySpecificContacts(Detail) == 1)
	{
		for (list<Contact>::iterator It = Contacts.begin(); It != Contacts.end(); It++)
		{
			if (ch == '1')
			{
				if (It->ContactName == Detail)
				{
					    cout << "\n\t\t+----------------------------+";
					cout << "\n\n\t\tDo you want to Update Specific Number or Update Contact Name?";
					cout << "\n\n\t\ta. Update Contact Number\n\n\t\tb. Update Contact Name\n\n\t\tEnter your choice : ";
					cin >> ch;
					if (ch == 'a' || ch == 'A')
					{
						cout << "\n\n\t\tEnter the Contact Number to be update: ";
						PhoneNo = GetNum();
						for (string& TempNo : It->ContactNo)
						{
							if (TempNo == PhoneNo)
							{
								cout << "\n\n\t\tEnter the Updated Contact Number: ";
								Temp = GetNum();
								if (Temp == TempNo)
								{
									cout << "\n\n\t\tContact Number Not Updated.";
								}
								else
								{
									TempNo = Temp;
									cout << "\n\n\t\tContact Number Updated.";
								}
								F = 0;
								break;
							}
						}
					}
					else if (ch == 'b' || ch == 'B')
					{
						    cout << "\n\t\t+----------------------------+";
						cout << "\n\n\t\tEnter the Updated Contact Name: ";
						ObjContact.ContactName = GetName();
						if (It->ContactName == ObjContact.ContactName)
						{
							cout << "\n\n\t\tContact Name Was Not Updated.";
						}
						else
						{
							It->ContactName = ObjContact.ContactName;
							cout << "\n\n\t\tContact Was Name Updated.";
						}
						F = 0;
						break;
					}
				}
			}

			if (ch == '2')
			{
				for (string& No : It->ContactNo)
				{
					if (No == Detail)
					{
						    cout << "\n\t\t+----------------------------+";
						cout << "\n\n\t\tDo you want to Update Specific Number or Update Contact Name?";
						cout << "\n\n\t\ta. Update Contact Number\n\n\t\tb. Update Contact Name\n\n\t\tEnter your choice : ";
						cin >> ch;
						if (ch == 'a' || ch == 'A')
						{
							cout << "\n\n\t\tEnter the Contact Number to be update: ";
							PhoneNo = GetNum();
							for (string& No : It->ContactNo)
							{
								if (No == PhoneNo)
								{
									cout << "\n\n\t\tEnter the Updated Contact Number: ";
									Temp = GetNum();
									if (Temp == No)
									{
										cout << "\n\n\t\tContact Number Not Updated.";
									}
									else
									{
										No = Temp;
										cout << "\n\n\t\tContact Number Updated.";
									}
									F = 0;
									break;
								}
							}
						}
						else if (ch == 'b' || ch == 'B')
						{
							    cout << "\n\t\t+----------------------------+";
							cout << "\n\n\t\tEnter the Updated Contact Name: ";
							ObjContact.ContactName = GetName();
							if (It->ContactName == ObjContact.ContactName)
							{
								cout << "\n\n\t\tContact Name Not Updated.";
							}
							else
							{
								It->ContactName = ObjContact.ContactName;
								cout << "\n\n\t\tContact Name Updated.";
							}
							F = 0;
							break;
						}
					}
				}
			}
			if (F == 0)
			{
				break;
			}
		}
	}
	else
	{
		system("cls");
	}

}

void PhoneBookMethods::DeleteContactDetails(string Detail, char ch) 
{
	int F = 1;
	if (DisplaySpecificContacts(Detail) > 1)
	{
		if (ch == '1')
		{
			    cout << "\n\t\t+----------------------------+";
			cout << "\n\n\t\tEnter the Contact Number to Delete Contact.";
			PhoneNo = GetNum();
			for (list<Contact>::iterator It = Contacts.begin(); It != Contacts.end(); It++)
			{
				if (It->ContactName == Detail)
				{
					for (string& TempNo : It->ContactNo)
					{
						if (TempNo == PhoneNo)
						{
							cout << "\n\n\t\tDo you want to Delete Specific Number or Entire Contact?";
							cout << "\n\n\t\ta. Delete Contact\n\n\t\tb. Delete Specific Number\n\n\t\tEnter your choice : ";
							cin >> ch;
							if (ch == 'a' || ch == 'A')
							{
								Contacts.erase(It);
								cout << "\n\n\t\tContact Deleted.";
								F = 0;
								break;
							}
							else if (ch == 'b' || ch == 'B')
							{
								if (It->ContactName == Detail && TempNo == PhoneNo)
								{
									It->ContactNo.remove(TempNo);
									cout << "\n\n\t\tContact Number Deleted.";
									F = 0;
									break;
								}
							}
						}
					}
				}
				if (F == 0)
				{
					break;
				}
			}
		}
		if (ch == '2')
		{
			    cout << "\n\t\t+----------------------------+";
			cout << "\n\n\t\tEnter the Contact Name to Delete Contact.";
			ObjContact.ContactName = GetName();
			for (list<Contact>::iterator It = Contacts.begin(); It != Contacts.end(); It++)
			{
				if (It->ContactName == ObjContact.ContactName)
				{
					for (string& TempNo : It->ContactNo)
					{
						if (TempNo == PhoneNo)
						{
							cout << "\n\n\t\tDo you want to Delete Specific Number or Complete Contact?";
							cout << "\n\n\t\ta. Delete Contact\n\n\t\tb. Delete Specific Number\n\n\t\tEnter your choice : ";
							cin >> ch;
							if (ch == 'a' || ch == 'A')
							{
								Contacts.erase(It);
								cout << "\n\n\t\tContact Deleted.";
								F = 0;
								break;
							}
							else if (ch == 'b' || ch == 'B')
							{
								if (It->ContactName == Detail && TempNo == PhoneNo)
								{
									It->ContactNo.remove(TempNo);
									cout << "\n\n\t\tContact Number Deleted.";
									F = 0;
									break;
								}
							}
						}
					}
				}
				if (F == 0)
				{
					break;
				}
			}

		}
	}

	else if (system("cls") || DisplaySpecificContacts(Detail) == 1)
	{
		for (list<Contact>::iterator It = Contacts.begin(); It != Contacts.end(); It++)
		{
			if (ch == '1')
			{
				if (It->ContactName == Detail)
				{
					    cout << "\n\t\t+----------------------------+";
					cout << "\n\n\t\tDo you want to Delete Specific Number or Complete Contact?";
					cout << "\n\n\t\ta. Delete Contact\n\n\t\tb. Delete Specific Number\n\n\t\tEnter your choice : ";
					cin >> ch;
					if (ch == 'a' || ch == 'A')
					{
						Contacts.erase(It);
						cout << "\n\n\t\tContact Deleted.";
						F = 0;
						break;
					}
					else if (ch == 'b' || ch == 'B')
					{
						    cout << "\n\t\t+----------------------------+";
						cout << "\n\n\t\tEnter the Contact Number to be Deleted: ";
						PhoneNo = GetNum();
						for (string& TempNo : It->ContactNo)
						{
							if (TempNo == PhoneNo && It->ContactName == Detail)
							{
								It->ContactNo.remove(TempNo);
								cout << "\n\n\t\tContact Number Deleted.";
								F = 0;
								break;
							}
						}
						if (F == 1)
						{
							system("cls");
							    cout << "\n\t\t+----------------------------+";
							cout << "\n\n\t\tContacts Number " << PhoneNo << " not available.";
						}
					}
				}
			}

			if (ch == '2')
			{
				for (string& No : It->ContactNo)
				{
					if (No == Detail)
					{
						    cout << "\n\t\t+----------------------------+";
						cout << "\n\n\t\tDo you want to Delete Specific Number or Complete Contact?";
						cout << "\n\n\t\ta. Delete Contact\n\n\t\tb. Delete Specific Number\n\n\t\tEnter your choice : ";
						cin >> ch;
						if (ch == 'a' || ch == 'A')
						{
							Contacts.erase(It);
							cout << "\n\n\t\tContact Deleted.";
							F = 0;
							break;
						}
						else if (ch == 'b' || ch == 'B')
						{
							It->ContactNo.remove(No);
							cout << "\n\n\t\tContact Number Deleted.";
							F = 0;
							break;
						}
					}
				}
			}
			if (F == 0)
			{
				break;
			}
		}
	}
	else
	{
		system("cls");
	}
}




char PhoneBookMethods::MergeContacts(string PhoneNo) 
{
	char ch;
	for (Contact& MergeContact : Contacts)
	{
		for (string& MergeNo : MergeContact.ContactNo)
		{
			if (MergeNo == PhoneNo)
			{
				DisplaySpecificContacts(PhoneNo);
				    cout << "\n\t\t+----------------------------+";
				cout << "\n\n\t\tContact with this Contact Number Already Exist.";
				cout << "\n\n\t\tDo you wish to merge it with existing contact?";
				cout << "\n\n\t\ty = Yes  n = No\n\n\t\tEnter your choice: ";
				cin >> ch;
				if (ch == 'y' || ch == 'Y')
				{
					return 'n';
				}
				else if (ch == 'n' || ch == 'N')
				{
					return 'y';
				}
			}
		}
	}
	return ch = 'y';
}

bool PhoneBookMethods::CheckExistingContact(string Name) 
{
	for (Contact CheckContact : Contacts)
	{
		if (CheckContact.ContactName == Name)
		{
			return true;
		}
	}
	return false;
}

int PhoneBookMethods::SearchByName(string Detail) 
{
	cout << "\n\n\t\t+----------------------------+";
	cout << "\n\n\t\t|      Search Contact        |";
	cout << "\n\n\t\t+----------------------------+";
	int Counter = 0;
	for (Contact SearchContact : Contacts)
	{
		
		if (!SearchContact.ContactName.find(Detail))
		{
			cout << "\n\n\t\tContact Name: " << SearchContact.ContactName << "\n\n ";
			for (string DisplayNo : SearchContact.ContactNo)
			{
				cout << "\n\t\tContact Numbers: ";
				cout << DisplayNo << " ";
			}
			cout << "\n\n";
			Counter++;
		}
	}
	return Counter;
}




string GetRandomString() 
{
	string s1, s2, s;
	for (int i = 1; i <= 10; i++)
	{
		while (s1.length() != 5)
		{
			char c = ((rand() % 26) + 65);
			s1 += c;
		}
		while (s2.length() != 2)
		{
			char c = ((rand() % 26) + 65);
			s2 += c;
		}
		s = s1 + " " + s2;
	}
	return s;
}

void PhoneBookMethods::FillPhoneBook() 
{
	for (int i = 1; i <= 5; i++)
	{
		Contact Temp;
		Temp.ContactName = GetRandomString();
		transform(Temp.ContactName.begin(), Temp.ContactName.end(), Temp.ContactName.begin(), toupper);
		do
		{
			PhoneNo += ((rand() % 4) + 29);
			if (PhoneNo.length() == 10)
			{
				Temp.ContactNo.push_back(PhoneNo);
				PhoneNo.clear();
			}
			if (Temp.ContactNo.size() > 2)
			{
				break;
			}
		} while (Temp.ContactNo.size() != ((rand() % 10) + 32));
		Contacts.push_back(Temp);
	}
}
