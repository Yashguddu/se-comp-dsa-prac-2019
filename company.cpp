/*company maintains employee information as employee ID, name,
designation and salary. Allow user to add, delete information of employee. Display
information of particular employee. If employee does not exist an appropriate
message is displayed. If it is, then the system displays the employee details. Use index
sequential file to maintain
the data.*/
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
class Employee
{
int id;
char emp_name[20];
char designation[20];
int salary;
public:
Employee()
{
id=0;
strcpy(emp_name,"\0");
strcpy(designation,"\0");
salary=0;
}
int acceptId()
{
return(id);
}
void acceptDetails()
{
cout<<"\nEnter details:";
cout<<"\nEmployee Id:";
cin>>id;
cout<<"\nEmployee Name:";
cin>>emp_name;
cout<<"Designation:";
cin>>designation;
cout<<"Salary:";
cin>>salary;
}
void putData()
{
cout<<"\nEmployee Id:";
cout<<id;
cout<<"\t\tEmployee Name:";
cout<<emp_name;
cout<<"\nDesignation:";
cout<<designation;
cout<<"\tSalary:";
cout<<salary;}
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
Employee r;
r.acceptDetails();
fout.open("Data",ios::ate|ios::app);
fout.write((char*)&r,sizeof(r));
fout.close();
}
void Operations::show()
{
Employee r;
fin.open("Data");
fin.seekg(0,ios::beg);
while(fin.read((char*)&r,sizeof(r)))
{
r.putData();
}
fin.close();
}
void Operations::search(int id)
{
Employee r;
int flag=0;
fin.open("Data");
fin.seekg(0,ios::beg);
while(fin.read((char*)&r,sizeof(r)))
{
if(r.acceptId()==id)
{
flag=1;
break;
}
}
fin.close();
if(flag==1)
{
cout<<"\nEmployee Found:";
r.putData();
}else
{
cout<<"\nEmployee Not Found";
}
}
int Operations::DelRecord(int id)
{
Employee r;
int flag=0;
fin.open("Data");
fout.open("Temp",ios::ate|ios::app);
fin.seekg(0,ios::beg);
while(fin.read((char *)&r,sizeof(r)))
{
if(r.acceptId()==id)
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
int Operations::edit(int id)
{
Employee r;
int flag=0;
fs.open("Data");
fs.seekg(0,ios::beg);
while(fs.read((char*)&r,sizeof(r)))
{
if(r.acceptId()==id)
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
int choice, id;do {
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
cout << "\nEnter the Employee Id to search: ";
cin >> id;
ops.search(id);
break;
case 4:
cout << "\nEnter the Employee Id to edit: ";
cin >> id;
if (ops.edit(id))
cout << "\nRecord updated successfully.";
else
cout << "\nRecord not found.";
break;
case 5:
cout << "\nEnter the Employee Id to delete: ";
cin >> id;
if (ops.DelRecord(id))
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
