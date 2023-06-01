 /*Department maintains a student information. The file contains roll
number, name, division and address. Allow user to add, delete information of
student. Display information of particular employee. If record of student does
not exist an appropriate message is displayed. If it is, then the system displays
the student details. Use sequential file to main the data.*/
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
class Student
{
int rno;
char sname[20];
char subject[20];
int sub_code;
float internal;
float university;
public:
Student()
{
rno=0;
strcpy(sname,"\0");
strcpy(subject,"\0");
sub_code=0;
internal=0.0;
university=0.0;
}
int acceptRollno()
{
return(rno);
}
void acceptDetails()
{
cout<<"\nEnter details:";
cout<<"\nRoll no:";
cin>>rno;
cout<<"\nSname:";
cin>>sname;
cout<<"Subject Code:";
cin>>sub_code;
cout<<"Subject Sname:";
cin>>subject;
cout<<"Internal AssessMent Marks:";
cin>>internal;
}
void putData()
{cout<<"\nRoll No:";
cout<<rno;
cout<<"\t\tSname:";
cout<<sname;
cout<<"\nSubject code:";
cout<<sub_code;
cout<<"\tSubject Sname:";
cout<<subject;
cout<<"\nInternal AssessMent Marks:";
cout<<internal;
cout<<"\nUniversity Exam Marks:";
cout<<university<<"\n\n";
}
};
class Operations
{
ifstream fin;
ofstream fout;
fstream fs;
public:
void addRecord();
void show();
void search(int);
int DelRecord(int);
int edit(int);
};
void Operations::addRecord()
{
Student r;
r.acceptDetails();
fout.open("Data",ios::ate|ios::app);
fout.write((char*)&r,sizeof(r));
fout.close();
}
void Operations::show()
{
Student r;
fin.open("Data");
fin.seekg(0,ios::beg);
while(fin.read((char*)&r,sizeof(r)))
{
r.putData();
}
fin.close();
}
void Operations::search(int rno)
{
Student r;
int flag=0;fin.open("Data");
fin.seekg(0,ios::beg);
while(fin.read((char*)&r,sizeof(r)))
{
if(r.acceptRollno()==rno)
{
flag=1;
break;
}
}
fin.close();
if(flag==1)
{
cout<<"\nStudent Found:";
r.putData();
}
else
{
cout<<"\nStudent Not Found";
}
}
int Operations::DelRecord(int rno)
{
Student r;
int flag=0;
fin.open("Data");
fout.open("Temp",ios::ate|ios::app);
fin.seekg(0,ios::beg);
while(fin.read((char *)&r,sizeof(r)))
{
if(r.acceptRollno()==rno)
{
flag=1;
}
else
{
fout.write((char *)&r,sizeof(r));
}
}
fin.close();
fout.close();
remove("Data");
rename("Temp","Data");
return(flag);
}
int Operations::edit(int rno)
{
Student r;
int flag=0;fs.open("Data");
fs.seekg(0,ios::beg);
while(fs.read((char*)&r,sizeof(r)))
{
if(r.acceptRollno()==rno)
{
flag=1;
cout<<"\nEnter New Details:";
r.acceptDetails();
fs.seekp((int)fs.tellg()-sizeof(r),ios::beg);
fs.write((char*)&r,sizeof(r));
}
}
fs.close();
return flag; }
int main()
{
Operations ops;
int choice, rno;
do {
cout << "\n**** Menu ****";
cout << "\n1. Add Record";
cout << "\n2. Show Records";
cout << "\n3. Search Record";
cout << "\n4. Edit Record";
cout << "\n5. Delete Record";
cout << "\n6. Exit";
cout << "\nEnter your choice: ";
cin >> choice;
switch (choice) {
case 1:
ops.addRecord();
break;
case 2:
ops.show();
break;
case 3:
cout << "\nEnter the roll number to search: ";
cin >> rno;
ops.search(rno);
break;
case 4:
cout << "\nEnter the roll number to edit: ";
cin >> rno;
if (ops.edit(rno))
cout << "\nRecord updated successfully.";
else
cout << "\nRecord not found.";
break;case 5:
cout << "\nEnter the roll number to delete: ";
cin >> rno;
if (ops.DelRecord(rno))
cout << "\nRecord deleted successfully.";
else
cout << "\nRecord not found.";
break;
case 6:
cout << "\nExiting...";
break;
default:
cout << "\nInvalid choice. Please try again.";
break;
}
} while (choice != 6);
return 0;
}
