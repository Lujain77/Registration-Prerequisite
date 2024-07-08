//Hagar Mekhemer Ismail_202000737 
//RodeenMustafa_202002557
//Toqa Tamer _202001985
//Lujain Mohamed Elsaid_202002670
//**********************************************************************
#include<iostream>
#include<sstream>
#include<string>
using namespace std;
// creating node struct
struct node {
    int Icount; 	// variable for holding course name initials number 
    int code;		// variable to hold code number of course
    node* left;     // pointer to left 
    node* right;    // pointer to right
	string condition = "undetermined";	
    };
class Tree {  // We create a class for tree 
node* root;  // We create a root pointer 
// Variables to serve member functions 
	int iteration = 0; 
	int preReq[3]= {};	// array to hold prerequired - base courses of a specific course
//End of variable declarations 
// Private functions to access member variables without interaction in main:
// convert string to array for counting number of letters:
    int count(string word)
    {
    	int iteration = 0;
    	for(int i = 0; word[i]; i++)
    	{
    		iteration++;
		}
		return iteration;
	}
node* add(int num, int code_num, node* ptr)    	// It's a function to  add nodes to Tree
    {
// base case - no nodes
if(ptr == NULL)
    {
    ptr = new node;
    ptr->Icount = num;
    ptr->code = code_num;
    ptr->left = ptr->right = NULL;
    }
// some courses have the same number of initials count:
    else if(num == ptr->Icount)
    {
        if (ptr->left == NULL)
    {
        ptr->left = add(num, code_num, ptr->left);	
	}
		else
	{
		ptr->right = add(num, code_num, ptr->right);
	}
	}
// adding nodes based on number of initials in course name
    else if(num > ptr->Icount)
        ptr->left = add(num,code_num, ptr->left);
    else if(num < ptr->Icount)
        ptr->right = add(num,code_num, ptr->right);
	return ptr;
    }  
// function to print full Tree 
	void print_BT(node * root, int distance)
	{  int space = 3;
    if (root == NULL)  
        return;  
// Increase distance between levels  
    distance += space;  
// Process right child first  
    print_BT(root->right, distance);  
// Print current node after space  
// count  
    cout<<endl;  
    for (int i = space; i < distance; i++)  
        cout<<" ";  
    	cout<<root->code<<"\n";  
// Process left child  
    print_BT(root->left, distance);  
	}	
// Searching function - based on number of initials in a course name 
	bool prereq(node* root, int C_code) 
	{
        if (root == NULL)
    {
        return false;
    }
        if (root->code == C_code)
    {
// No prerequisits
        return true;
    }
        if (prereq(root->left, C_code) || prereq(root->right, C_code))
    {
        cout << root->code << ", ";
        preReq[iteration] = root->code;
        iteration++;
		return true;
    }
        return false;
	} 	
// function to compare base courses with taken courses
	bool comp_courses(int taken[3], int req[3], int iteration)
	{
		int count = 0;
		for(int i=0; i<3; i++)	// number of taken courses must not exceed 3 courses
	{
		for(int j=0; j<3; j++)	//maximum number of base courses in the Tree are 3
	{
		if(preReq[j]==0)
	{
		break;
	}
		else
	{
		if (preReq[j] == taken[i])
	{
		count++;
	}
	}
	}
	}
		if(count == iteration)
	{
		return true;
	}
		else if(count != iteration)
	{
		return false;
	}
	}
// End of private variables and members functions 
//********************************************************
public:  // tree class that has two constructors
//create constructor for initialization
	Tree()     // creates an empty tree with no root node
	{
		root = NULL;
	}
	void add(string Couse_name,int Couse_number)	// add takes the cousre number as an input
	{	// how many letters are in this particular string
		int num_of_letters = count(Couse_name);
		root = add(num_of_letters, Couse_number, root); // child to the current node
	}
	void print_BT()  {// function prints out "two nodes in the tree with distance between them"
		int distance = 0; 	//distance from side
		print_BT(root, distance);
	}
	void prereq( int Couse_number)  // input a course number , checking if a certain course has been taken before or not.
	{
		iteration = 0; // how many times this function has been called 
		preReq[0] = preReq[1] = preReq[2] = 0; // keep track of which courses have already been checked.
		cout<<" The following courses are OK to take :";
	bool result;
		result = prereq(root, Couse_number);
		if(result == false) // if the course number is not found
	{
		cout<<"Required Course Not Found"<<endl;
	}
	    cout<<endl;
	}
// printing preRequired Courses:
	void print_prereq() //  print a list of required courses.
	{
		cout<<" Required Courses are : ";
		for(int i=0;i<3;i++)  // for loop iterates through three elements in the preReq array
	{
		cout<<preReq[i]<<", ";   // outputs each course name followed by a comma.
	}
		cout<<endl;
	}
// func. checking whether a course could be taken or not considering the Pre-Req courses
		void comp_courses(int taken[3], int course)
	{
		prereq(course); //set to Boolean value
		bool result = comp_courses(taken, preReq, iteration); //taken courses, the needed courses to open another needed course,iterate to take only 3 courses in the input(Taken courses)
		print_prereq();
		if (result == true) //set to TRUE when the upcoming course Pre-Req is finished or it does not have Pre-Req
	{
		cout<<" The following courses are OK to take : "<< course << endl;
	} 
		else if(result == false) //set to False when the upcoming course PreReq is not finished or it cannot be taken as it needs a Pre-Req(Pre-Req course for the Pre-Req course)
	{
		cout<<" The following courses are CANNOT be taken : "<< course << " - Required Courses Not finished"<< endl;
	}
	}		
// function takes string & integrs then return integrs only >>Tkae the curse name & code then return the course code only	 
		int* get_int(string str) 
	{	 
    	int arr[3] = {};
    	int i= 0;
		stringstream ss;  //Declared to an object>> Reads & stores the STRINGS from the INPUT (course name)   
    	ss << str; 
    	string temp; //Looping till the end of the stringstream>> ss 
    	int found; 
    	while (!ss.eof()) //*End of file func.* Returns true when there are no more data to be read in a file
	{	 
        ss >> temp; //extract each word in the string from the stringstream
        if (stringstream(temp) >> found) //checking if the given word is intger or not
    {
		arr[i] = found;
		i++;	 
    }
		temp = ""; //to save from space at the end of a string
    } 
    	return arr;
	}
 };
 int main()
{
  	cout<<"Courses checker    "<<endl;   // Taking a course number:
  	cout<<"--------------------------------------------------"<<endl;
 	cout<<"For Example: initials "<< endl;
	// initialization list:	
int *p;
string taken[50] = {}; //regarding the taken courses names
int taken_c[3] = {};	// regrading the taken courses code
string wanted[50] = {}; //regrading the wanted courses names
int wanted_c[3] = {};	//regrading the wanted courses codes
int lines; //regrading the NOTEPAD line checking
int course_num;
string course_name;
Tree obj; 	// Create object of Tree
// VIP: to add course numbers/codes - operations are based on course code not name
	cout<<" Enter the courses which you already studied : "<<endl;
	for(int i=0; i<3; i++) // 3 courses 
	{
	getline(cin, taken[i]); // read a string or a line from an input 
	p = obj.get_int(taken[i]); // course numbers are stored as integers " get_int"
	taken_c[i] = *p;  //  this integer value is assigned to the variable "taken_c[i]"
	}
	cout<<endl<<" Enter the courses that you want to study : "<<endl;
	for(int i=0; i<3; i++)
	{
	getline(cin, wanted[i]);
	p = obj.get_int(wanted[i]);
	wanted_c[i] = *p;
	}				
freopen("list_courses.txt","r",stdin);  // Take the input from file txt 
  	cin>>lines;
  	cin.ignore();
// take each line from file and create new node in Tree
for(int i=1; i<=lines; i++)
	{
   	cin>>course_num; 
   	i++;
   	cin>>course_name;
	obj.add(course_name, course_num);
  	}
  	cout<< " The courses of the tree :  " << endl;
  	obj.print_BT(); 	// Display all courses of the tree
  	cout<<" Processing . . ."<< endl;
  	for(int i=0; i<3; i++)
  	{
  		int temp = wanted_c[i];
  		obj.comp_courses(taken_c, temp);
  		cout<<endl<<endl;
	}
	return 0;}
