#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<map>
using namespace std;
#define MIN_BALANCE 100 //#define directive is a preprocessor directive used to 
                        // define a constant value or a macro. by a NAME
//easily modify the value of the constant by changing it at a single location
class deficient_funds{};
class Cl_Accounts
{
private:
// inserted in private since used at many place 
long Accnt_No; 
string client_fname;
string client_lname;
float client_balance;
static long Nxt_Accnt_No;

public:
Cl_Accounts(){}
Cl_Accounts(string fname,string lname,float client_balance);
long getAccNo(){return Accnt_No;}
string getFName(){return client_fname;}
string getLName(){return client_lname;}
float getBlnce(){return client_balance;}
void Deposit(float amount);
void Withdraw(float amount);
static void setLstAccntNo(long Accnt_No);
static long getLstAccntNo();// "<<" - this operator is commonly used for outputting data(from acc)to an output stream(To ofs)sucha as file.
friend ofstream & operator<<(ofstream &ofs,Cl_Accounts &acc); //friend-grand access to private of C1_Accounts
friend ifstream & operator>>(ifstream &ifs,Cl_Accounts &acc); //allows an ifstream object (ifs) to be chained with the >> operator to read 
                                                                //data from the input stream and store it in a Cl_Accounts object (acc).
friend ostream & operator<<(ostream &os,Cl_Accounts &acc);
};
long Cl_Accounts::Nxt_Accnt_No=0;

class Bank
{
private:
map<long,Cl_Accounts> accounts_cl;// allows you to store and access Cl_Accounts objects using their associated long keys.
public:
Bank();
Cl_Accounts Cl_Open_Account(string fname,string lname,float balance); // function returns an object of type Cl_Accounts
Cl_Accounts Cl_Balance_Enquiry(long Account_no); // require account no. info 
Cl_Accounts Deposit(long Account_no,float amt);// require account no. info  and amt to be deposited
Cl_Accounts Withdraw(long Account_no,float amt);
void CloseAccount(long Account_no);
void ShowAllAccounts();
// ~Bank();
};
int main()
{
Bank b;
Cl_Accounts acc;
int option;
string fname,lname;
long account_no;
float blnced;
float amnts;
cout<<"***Bank Management System***"<<endl;
do
{
cout<<"\n\tSelect One Option Below ";
cout<<"\n\t1 Open an Account";
cout<<"\n\t2 Balance Enquiry";
cout<<"\n\t3 Deposit";
cout<<"\n\t4 Withdrawal";
cout<<"\n\t5 Close an Account";
cout<<"\n\t6 Show All Accounts";
cout<<"\n\t7 Quit";
cout<<"\nEnter your choice: ";
cin>>option;
switch(option)
{
case 1:
cout<<"Enter First Name: ";
cin>>fname;
cout<<"Enter Last Name: ";
cin>>lname;
cout<<"Enter Initial Balance: ";
cin>>blnced;
acc=b.Cl_Open_Account(fname,lname,blnced);  // function returns an object of type Cl_Accounts to acc
cout<<endl<<"Congratulations Account is Created"<<endl;
cout<<acc; // return the info avai in acc(which is an obj of class C1_accounts AND have info from its CONSTRUCTOR )
break;
case 2:
cout<<"Enter Account Number:";
cin>>account_no;
acc=b.Cl_Balance_Enquiry(account_no);
cout<<endl<<"Your Account Details"<<endl;
cout<<acc;
break;
case 3:
cout<<"Enter Account Number:";
cin>>account_no;
cout<<"Enter Balance:";
cin>>amnts;
acc=b.Deposit(account_no, amnts);
cout<<endl<<"Amount is Deposited"<<endl;
cout<<acc;
break;
case 4:
cout<<"Enter Account Number:";
cin>>account_no;
cout<<"Enter Balance:";
cin>>amnts;
acc=b.Withdraw(account_no, amnts);
cout<<endl<<"Amount Withdrawn"<<endl;
cout<<acc;
break;
case 5:
cout<<"Enter Account Number:";
cin>>account_no;
b.CloseAccount(account_no); // HERE SINCE WE ARE CLOSING an account so NO need to increment the account no.
// hence info of acc is not updated by writing acc=b.CloseAccount();
cout<<endl<<"Account is Closed"<<endl;
cout<<acc; 
case 6:
b.ShowAllAccounts();
break;
case 7: break;
default:
cout<<"\nEnter corret choice";
exit(0); // CLOSE THE PROGRAM COMPLETLY
}
}while(option!=7);
return 0;
}

//Function declaration of CLASS 01

Cl_Accounts::Cl_Accounts(string fname,string lname,float client_balance) //CONSTRUCTOR OF CLASS- C1_Accounts
{
Nxt_Accnt_No++; //ensure that each new account will have a unique account number.
Accnt_No=Nxt_Accnt_No;
client_fname=fname;
client_lname=lname;
this->client_balance=client_balance;
}

void Cl_Accounts::Deposit(float amt)
{
client_balance+=amt;
}
void Cl_Accounts::Withdraw(float amt)
{
if(client_balance-amt<MIN_BALANCE)// min balance is 100
throw deficient_funds(); // CLASS CONSTRUCTOR CALLED , 
//throw -used to call an error witn class name and terminates the program
else{
client_balance-=amt;
}
}
void Cl_Accounts::setLstAccntNo(long Accnt_No)
{
Nxt_Accnt_No=Accnt_No; //func used to assign value of accnt_no 
}
long Cl_Accounts::getLstAccntNo()
{
return Nxt_Accnt_No;
}
ofstream & operator<<(ofstream &ofs,Cl_Accounts &acc)
{ //this "<<" operator is commonly used for outputting data(from acc)to an output stream(To ofs)sucha as file.
ofs<<acc.Accnt_No<<endl;
ofs<<acc.client_fname<<endl;
ofs<<acc.client_lname<<endl;
ofs<<acc.client_balance<<endl;
return ofs;
}
ifstream & operator>>(ifstream &ifs,Cl_Accounts &acc)
{
ifs>>acc.Accnt_No;
ifs>>acc.client_fname;
ifs>>acc.client_lname;
ifs>>acc.client_balance;
return ifs;
}
ostream & operator<<(ostream &os,Cl_Accounts &acc)
{
os<<"First Name:"<<acc.getFName()<<endl;           
os<<"Last Name:"<<acc.getLName()<<endl;
os<<"Account Number:"<<acc.getAccNo()<<endl;
os<<"Balance:"<<acc.getBlnce()<<endl;
return os;
} 
//Below are the funcs  of class C1-Account AND os is using them as data 

// long getAccNo(){return Accnt_No;}
// string getFName(){return client_fname;}
// string getLName(){return client_lname;}
// float getBlnce(){return client_balance;}

Bank::Bank()
{
Cl_Accounts acnt;
ifstream infile; //used for reading data from a file.
infile.open("Bank.data");

if(!infile)// if there was an error opening the file.
{
//cout<<"Error in Opening! File Not Found!!"<<endl;
return;
}
while(!infile.eof())// as long as the end-of-file (EOF) marker is not reached in the infile
{//means the loop will iterate until all the data in the file has been read.
infile>>acnt;// The extraction operator (>>) is used to extract data from the file and assign it to the acnt object.

accounts_cl.insert(pair<long,Cl_Accounts>(acnt.getAccNo(),acnt));//accounts_cl is a map or a similar container that allows key-value pairs.
}// pair is having "acnt"-object itself as the value AND key as long(acnt.getaccno());

Cl_Accounts::setLstAccntNo(acnt.getAccNo());//Static fun calling
infile.close(); //Good practice to close files after USE
}

Cl_Accounts Bank::Cl_Open_Account(string fname,string lname,float balance)
{//The return type of the function is Cl_Accounts, indicating that it returns an object of the Cl_Accounts class.
ofstream outfile;
Cl_Accounts acnt(fname,lname,balance);
accounts_cl.insert(pair<long,Cl_Accounts>(acnt.getAccNo(),acnt));

//The ios::trunc flag ensures that if the file already exists, its contents are cleared before writing new data.
outfile.open("Bank.data", ios::trunc);
//itr for iterating over the elements of the "accounts_cl" container created ABOVE;
map<long,Cl_Accounts>::iterator itr;
for(itr=accounts_cl.begin();itr!=accounts_cl.end();itr++)
{
outfile<<itr->second;// '<<'operator writes the value of the Cl_Accounts object (acnt);
}
outfile.close();
return acnt;// returns the created account object.
}

Cl_Accounts Bank::Cl_Balance_Enquiry(long Accnt_No)
{
map<long,Cl_Accounts>::iterator itr=accounts_cl.find(Accnt_No);
return itr->second;
}

Cl_Accounts Bank::Deposit(long Accnt_No,float amt)
{
map<long,Cl_Accounts>::iterator itr=accounts_cl.find(Accnt_No);// searches for the Accnt_No (account number) in the accounts_cl map, 
itr->second.Deposit(amt);/// calls the Deposit function on the second element of the iterator itr.
//due  to deposit fun calling some changes are occured in itr->second of MAP accounts_cl;
return itr->second;//function returns the modified account object after the deposit operation has been performed.
}

Cl_Accounts Bank::Withdraw(long Accnt_No,float amt)
{
map<long,Cl_Accounts>::iterator itr=accounts_cl.find(Accnt_No);
itr->second.Withdraw(amt);
return itr->second;
}

void Bank::CloseAccount(long Accnt_No)
{
map<long,Cl_Accounts>::iterator itr=accounts_cl.find(Accnt_No);
cout<<"Account Deleted"<<itr->second;// outputs the string "Account Deleted" followed by the value of itr->second to the console.

accounts_cl.erase(Accnt_No);//erase function is used to delete an element 
//from a map by "specifying its key- which is Accnt_No (from accnt.getaccnt())".
}

void Bank::ShowAllAccounts()
{
map<long,Cl_Accounts>::iterator itr;
for(itr=accounts_cl.begin();itr!=accounts_cl.end();itr++)
{
cout<<"Account "<<itr->first<<endl<<itr->second<<endl;// prints the Key(account no) and its value(all info about the acount)

}
}

Bank::~Bank()
{
ofstream outfile;
//The ios::trunc flag ensures that if the file already exists, its contents are cleared before writing new data.
outfile.open("Bank.data", ios::trunc);
map<long,Cl_Accounts>::iterator itr;
for(itr=accounts_cl.begin();itr!=accounts_cl.end();itr++)
{
outfile<<itr->second;
}
outfile.close();
}
