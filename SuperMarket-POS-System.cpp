#include<iostream>
#include"Interface.h"
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<ctime>
#include<dos.h>
using namespace std;

class Exception_handling{
	static int tot_exceptions;
	
	public:
	
		template<class Number>
		static bool checkcreditno(Number numc){													//checking the number of digits for creditcard
			int digits;
			
			try{
				while(numc!= 0){
					numc = numc/10;	
					digits+= 1;
				}
				if(digits == 16)
					return true;
				
				else{
					string str = "Exception occurred!";
					tot_exceptions+= 1;
					throw str;
				}
			}
			
			catch(string str){
				cout<< endl<< str<< endl<< "Re-Enter the CreditCard Number: ";
				return false;
			}	
		}
		
		static long long formnum(char cell[12]){														//convert an array to a number							
			long long num = 0;
			int cnt = 0;
			long long val = 0;
			int dig = 0, mult = 1;
			
			while(cell[cnt]!= '\0'){
				dig+= 1;
				cnt++;	
			}
			
			cnt = (dig-1);
			while(cnt != -1){
				val = cell[cnt] - 48;	
				num = num + (val * mult);
				mult*= 10;
				cnt--;
			}
			return num;
		}
		
		static int formid(char ID[10]){																	//convert an array to a number ie. ID						
			int id = 0;
			int cnt = 0;
			int val = 0;
			int dig = 0, mult = 1;
			
			while(ID[cnt]!= '\0'){
				dig+= 1;
				cnt++;	
			}
			
			cnt = (dig-1);
			while(cnt != -1){
				val = ID[cnt] - 48;
				id = id + (val * mult);
				mult*= 10;
				cnt--;
			}
			return id;
		}
		
		static bool checkid(const char ID[10]){														//function to check whether the id contains any invalid char or not					
			int flag = 0, cnt = 0;
			
			try{
				while(cnt != 10){
					if( ID[cnt]!= '\0' ){
						if( (ID[cnt]>47) && (ID[cnt]<58) ){}
						else
							throw ID[cnt];
					}
					cnt++;
				}
				return true;
			}
			catch(const char exception){
				tot_exceptions+= 1;
				cout<< endl<< "EXCEPTION OCCURRED!"<< endl<< "You're not supposed to Enter data consist of character(s), like: "<< exception<< endl;
				cout<< "RE-ENTER ID: "<< endl;
				return false;
			}	
		}
		
		static bool checkcontact(const char cont[12]){												//function to check whether the cell number contains any invalid char or not												
			int flag = 0, cnt = 0;
			
			try{
				while(cnt != 12){
					if( cont[cnt]!= '\0' ){
						if( (cont[cnt]>47) && (cont[cnt]<58) ){}
						else
							throw cont[cnt];
					}
					cnt++;
				}
				return true;
			}
			catch(const char exception){
				tot_exceptions+= 1;
				cout<< endl<< "EXCEPTION OCCURRED!"<< endl<< "You're not supposed to Enter data consist of character(s), like: "<< exception<< endl;
				cout<< "RE-ENTER Mobile Number: "<< endl;
				return false;
			}	
		}
		
		static bool checkcashiername(const char name[50]){											//function to check the entered name for exception handling.
			int cnt = 0, cnt2 = 0;
			int fg = 0;
			int len = strlen(name);
			char arr[50] = {'\0'};
			
			try{
				while(cnt != len){
					if( (name[cnt] != ' ') && (name[cnt] != '\0') ){
						if( ((name[cnt]<65) || (name[cnt]>129)) ){
							fg = 1;
							arr[cnt2] = name[cnt];
							cnt2+= 1;
						}	
					}
					cnt++;
				}
				if(fg == 1)
					throw arr;
					
				return true;
			}
			catch(char chars[50]){
				tot_exceptions+= 1;
				cout<< endl<< "EXCEPTION OCCURRED!"<< endl<< "You've entered invalid character(s), like: ";
				for(int cnt = 0; cnt<50; cnt++){
					cout<< chars[cnt];
					if(chars[cnt+1] != '\0')
						cout<< ", ";
				}	
				cout<< endl<< "RE-ENTER NAME: ";
				return false;
			}	
		}
		
		static bool checkidcashier(const int id){															//function to check the entered id for exception handling.
			try{
				if( !(id>=750) && (id<754) )
					throw id;
				else
					return true;
			}
			catch(...){
				cout<< endl<< "EXCEPTION OCCURRED!"<< endl;
				tot_exceptions+= 1;
				cout<< "RE-ENTER ID: ";
				fflush(stdin);
				return false;
			}	
		}
		
		static bool checkmail(const char email[50]){													//function to check the entered name for exception handling.
			int  cnt2 = 0;
			int fg = 0;
			int len = strlen(email);
			char arr[50] = {'\0'};
			
			try{
				for(int cnt=0;cnt<len;cnt++){
					if( (email[cnt] != ' ') && (email[cnt] != '\0') ){
						if((email[cnt]=='@' && email[cnt+1]=='g' && email[cnt+2]=='m' && email[cnt+3]=='a' && email[cnt+4]=='i' && email[cnt+5]=='l' && email[cnt+6]=='.' && email[cnt+7]=='c' && email[cnt+8]=='o' && email[cnt+9]=='m')){
							return true;
						}	
						else 
							fg = 1;
					}
				}
			
				if (fg == 1){
					string msg = "Kindly Enter a Valid EMAIL";
					throw msg;
				}
				
			}
			catch(string msg){
				tot_exceptions+= 1;
				cout<< endl<< "EXCEPTION OCCURRED!"<< endl<< msg<< endl
					<< endl<< "RE-ENTER EMAIL: ";
				return false;
			}	
		}
		
		int getexception()	const{
			return tot_exceptions;
		}
};

int Exception_handling::tot_exceptions = 0;


//Class for Credit Card:
class CreditCard{
	double tax;
	double total;
	long long CN;
	int PS;
	double amount;

	public:		
		CreditCard(){
			tax = 0.00;
			total = 0.00;
			CN = 0000;
			PS = 0;
		}
			
		void addtax(double a){
			tax = a*(12/100);			//12% tax
			total = a + tax;
		}
		
		bool Payment(const long long CC_N, const int pass, double amount){										//function to add the amount of bill as balance in the desired credit card 
			ifstream fin;
			ofstream fout;
			int count = 0;
			
			fin.open("Bank.dat");
			fout.open("BankTemp.dat");
			CreditCard Temp;
			
			if( !fin.is_open() ){
				cout << "An Error occured while opening file!"<< endl;
				return false;
			}
			else{
		        while(!fin.eof()){
		        	fin.read((char *)&Temp, sizeof(Temp));	
		            	if( (CC_N == Temp.CN) && (pass == Temp.PS) ){
		            		Temp.addtax(amount);
							cout<< endl<< endl<< "Payment of Rs."<< Temp.total<<" Successful against this Credit Card!"<< endl<< endl<< endl;
							Temp.amount+= Temp.total;
							count = 1;			//flag
							fout.write((char *)&Temp, sizeof(Temp));		
		        		}
		        		else
		        			fout.write((char *)&Temp, sizeof(Temp));
		        }
		        fin.close();
		        fout.close();
		        
				remove("Bank.dat");							//this statement updated
		        rename("BankTemp.dat", "Bank.dat");
		        fflush(stdin);
			}
			
			if(count == 1){
				return true;
			}
			
			if(count == 0){
				cout<< endl<< "No such Card Found!"<< endl<< endl;
				return false;
			}
		}
};

//function for password security:
void InputPassword(char p[20]){ 																						//function to take password in the form of asterisks
	char ch;
	int i = 0;
	
	while(1){
		ch = getch();
			
		if(ch == 13)
			break;
		else if(ch == '\b'){
			if(i > 0){
				i--;
				p[i] = '\0';
				cout << "\b \b";
			}
		}
		else{
			p[i] = ch;
			cout << "*";
			i++;
		}
	}
}

//converting an array of char to float:
float formnum(char pass[5]){																						
	int num = 0;
	int cnt = 0;
	float val = 0;
	int dig = 0, mult = 1;
	
	while(pass[cnt]!= '\0'){
		dig+= 1;
		cnt++;	
	}
	
	cnt = (dig-1);
	while(cnt != -1){
		val = pass[cnt] - 48;
		num = num + (val * mult);
		mult*= 10;
		cnt--;
	}
	return num;
}

//Class for items:
class Items{		
	char name[60];
	int quant;
	float price;
	long id;
	
	public:
		Items(){}
		
		Items(char nam[60], int quantity, float price){	
			strcpy(name, nam);
			this->quant = quantity;
			this->price = price;
		}
		
		long getid()	const{
			return id;
		}
		
		void setprice(const float price){
			this->price = price;
		}
		
		void setquant(const int quant){
			this->quant = quant;
		}
		
		void setname(char const nme[60]){
			strcpy(name, nme);
		}

		int getquant(){
			return quant;
		}
		
		void showproducts(){
			cout<< (*this);
		}
		
		void showproducts(int){																		//function to display the info of product in the bill
			cout << "ID: " << id;
			cout << "\tName: " << name;
			cout << "\tPrice: " << price<< endl;
		}
		
		float getprice(){
			return price;
		}
		
		char* getname(){
			char *ptr = &name[0];
			return ptr;
		}
		
	    void getproducts(const char name[60], const float price, const int quant){
			strcpy(this->name, name);
			this->quant = quant;
			this->price = price;
		}
	    
	    bool storeprod()	const{																	//to add a new item in the of inventory	(2 files)			
		    if( (price == 0) && (name == "-") ){
		        cout << "PRODUCT NOT INITIALISED"<< endl;
		        return false;
		    }
		    else{
		        ofstream fout, fout2;
		        fout.open("Inventory.dat", ios::app);
		        fout2.open("Inventorymain.dat", ios::app);
		        
		        fout.write((char *)this, sizeof(*this));
		        fout2.write((char *)this, sizeof(*this));
		        
		        fout.close();
		        fout2.close();
		       	return true;		
		    }
		}
		
		void deletepro(const long ID){																//to delete a new item in the of inventory	(2 files)	
		    ifstream fin;
		    ofstream fout, fout2;
		    fin.open("Inventory.dat");
		   
		    if (!fin.is_open()){
		        cout << "File Not Opened!";
		    }
		    else{
		        fout.open("tempfile.dat", ios::out);
		        fout2.open("tempfile2.dat", ios::out);
		        
		        fin.read((char *)this, sizeof(*this));
		        while(!fin.eof())
		        {
		            if (id == ID){
		                cout << "\n\nProduct: " << name << " Deleted Successfully!"<< endl<< endl;
		            }
		            else{
		                fout.write((char *)this, sizeof(*this));
		                fout2.write((char *)this, sizeof(*this));
		            }
		            fin.read((char *)this, sizeof(*this));
		        }
		        fin.close();
		        fout.close();
		        fout2.close();
		        
		        remove("Inventory.dat");
		        rename("tempfile.dat", "Inventory.dat");
		        remove("Inventorymain.dat");
		        rename("tempfile2.dat", "Inventorymain.dat");
		    }
		}
		
		bool setid(){																			//function to assign ID to each item of the inventory, 1st ID = 1
			ifstream fin;
			Items Temp;
			
			fin.open("Inventory.dat");
			if(fin.is_open()){
				while(!fin.eof()){
					if( fin.read((char *)&Temp, sizeof(Temp)) );
				}
				id = (Temp.id) + 1;
				fin.close();
				cout<< endl<< "Assigned-ID is: "<< id<< endl;
				return true;
			}
			else{
				cout<< endl<< "NEW FILE IS NOW BEING CREATED!"<< endl;
				id = 1;
				cout<< endl<< "Assigned-ID is: "<< id << endl;
				return false;
			}
		}
		
		//operator overloading:
		friend operator <<(ostream &out, Items Temp){														//to display the information of a specific product
			out << "ID: " << Temp.id;
			out << "\tName: " << Temp.name;
			out << "\tPrice: " << Temp.price;
			out << "\tQuantity: " << Temp.quant <<endl;
		}
};

//Class for the inventory:
class Inventory{
	Items *Item;	
	static int num_diffprod;
	
	public:
		
		Inventory(){
			Item = NULL;	
		}
		
		void setitem_ptr(Items &Itemm){																//to set the pointer of each item which we want to work on from the inventory
			Item = &Itemm;
		}
		
		void clritem_ptr(){		
			Item = NULL;
		}
		
		static int noofProducts(){
			ifstream fin;
			Items Temp;
			
			fin.open("Inventory.dat",ios::in);
			fin.read((char*)&Temp,sizeof(Temp));
			while(!fin.eof()){
				num_diffprod+= 1;
				fin.read((char*)&Temp,sizeof(Temp));
			}
			
			fin.close();
			return num_diffprod;
		}
		
		void updateinv(const long ID){															//function to update the information of the specific product
		    fstream file;
		    char nme[60];
		    float prc;
		    int quan;
		    Items Temp;
		    
		    file.open("Inventory.dat", ios::in | ios::out | ios::ate);
		    file.seekg(0);													//bringing pointer of file at the starting of record (first line first character)
		    file.read((char *)&Temp, sizeof(Temp));
		    while(!file.eof())
		    {
				if(Temp.getid() == ID){	
					char opt;
										
					fflush(stdin);
					
		        	cout<< endl<< "UPDATING INFORMATION OF THE PRODUCT WITH ID: "<< ID<< endl
		        		<< "1 = Update Product-Name"<< endl<< "2 = Update Product-Price"<< endl<< "3 = Update Product-Quantity"<< endl<< "OPT: ";
		        	opt = getch();											
		        	fflush(stdin);
		        	if(opt == '1'){
						cout << endl<< "Product-Name: ";
		   			    cin.getline(nme, 60);
	        			Temp.setname(nme);
	        		}
	        		else if(opt == '2'){
		        		cout << endl<< "Product-Price: ";
		        		cin>> prc;
		        		Temp.setprice(prc);
		        	}
		        	else if(opt == '3'){
		       			cout << endl<< "Product-Quantity: ";
		       			cin>> quan;
	        			Temp.setquant((Temp.getquant()+quan));	
					}
					
					else{
						cout<< endl<< "Invalid Input!"<< endl;
						
					}
					int b = file.tellp();				
		            file.seekp(b - sizeof(Temp));											//bringing character back to the state being updated
		            file.write((char *)&Temp, sizeof(Temp));
		        }
		    
		        file.read((char *)&Temp, sizeof(Temp));
		    }
		}
		
		void decrement_quant(const long ID){											//function to do a decrement of the specific item from the inventory when sold							
			ifstream fin;
			ofstream fout;
		    Items Temp;
		    
		    fin.open("Inventory.dat");
		    fout.open("Inventorytemp.dat");
		    if(!fin.is_open()){
		        cout << endl<< "File Not Opened!"<< endl;
		    }
		    else{
		        while(!fin.eof()){
		        	if(fin.read((char *)&Temp, sizeof(Temp))){
		            	if( Temp.getid() == ID ){
		            		int quant = Temp.getquant() - 1; 
		   					Temp.setquant(quant);
		            		fout.write((char *)&Temp, sizeof(Temp));
						}	
						else
							fout.write((char *)&Temp, sizeof(Temp));						
		            }
		        }   
		    }
		    fin.close();
		    fout.close();
		    
		    remove("Inventory.dat");
		    rename("Inventorytemp.dat", "Inventory.dat");
		}
		
		void viewallprod(){																//function to view the current status with all the items of the inventory
		    ifstream fin;
		    Items Temp;
		    
		    fin.open("Inventory.dat");
		    if(!fin.is_open()){
		        cout << "File Not Opened!"<< endl;
		    }
		    else{
		        while(!fin.eof())
		        {
		        	if(fin.read((char *)&Temp, sizeof(Temp))){
		            	Temp.showproducts();							
		            }
		        } 
		    }
		    fin.close();
		}
		
		static void display_specificprod(const long ID){								//function to display the current status of the item specific item of the inventory
		    ifstream fin;
		    int count = 0;
		    Items Temp;
		    
		    fin.open("Inventory.dat", ios::in);
		    if(!fin.is_open()){
		        cout << "File Not Opened!"<< endl;
		    }
		    else{
		        fin.read((char *)&Temp, sizeof(Temp));
		        while(!fin.eof())
		        {
		            if(Temp.getid() == ID){
		            	Temp.showproducts();
		            	count++;
		            }
		            fin.read((char *)&Temp, sizeof(Temp));
		        }
		        if (count == 0){
		            cout << "Product Not Found!"<< endl;
		        }
		        
		    }
		    fin.close();
		}
		
		static void display_specificprod(const long ID, int){							//function overloaded for the display of specific item for the customer
		    ifstream fin;
		    int count = 0;
		    Items Temp;
		    
		    fin.open("Inventory.dat", ios::in);
		    if(!fin.is_open()){
		        cout << "File Not Opened!"<< endl;
		    }
		    else{
		        fin.read((char *)&Temp, sizeof(Temp));
		        while(!fin.eof())
		        {
		            if(Temp.getid() == ID){
		            	Temp.showproducts(1);
		            	count++;
		            }
		            fin.read((char *)&Temp, sizeof(Temp));
		        }
		        if (count == 0){
		            cout << "Product Not Found!"<< endl;
		        }
		        
		    }
		    fin.close();
		}
		
		static float check_availability(const long ID){											//function to check the presence of the specific item from the inventory
			ifstream fin;
		    Items Temp;
		    
		    fin.open("Inventory.dat", ios::in);
		    if(!fin.is_open()){
		        cout << "File Not Opened!"<< endl;
		    }
		    else{
		        fin.read((char *)&Temp, sizeof(Temp));
		        while(!fin.eof())
		        {
		            if( (Temp.getid() == ID) && (Temp.getquant() > 0) ){
		            	fin.close();
		            	return (Temp.getprice());
		            }
		            fin.read((char *)&Temp, sizeof(Temp));
		        }
		        cout << endl<< "Product Not Found!"<< endl;
		        fin.close();
		        return 0;
		    }
		}
};

//Class for the customer:
class Customer{	
	int tot_items;	
	char bill_no[8];
	double bill;
	int count_cust;
	
	public:
		friend operator<<(ostream &out, Customer &cust){
			cout<< endl<< "TOTAL-ITEMS: "<< cust.tot_items;
			cout<< endl<< "BILL-NUMBER: ";
			for(int cnt = 0; cnt< 8; cnt++)
				cout<< cust.bill_no[cnt];
			cout<< endl<< "BILL: Rs."<< cust.bill<< endl;
		}
		
		char getbill_no(const int cnt)	const{
			return bill_no[cnt];
		}
		
		char* getbill_address(){
			char *ptr = &bill_no[0];
			return ptr;	
		}
		
		Customer(){
			for(int cnt = 0; cnt<8; cnt++){
				bill_no[cnt] = '\0';
			}
			bill = 0;
			tot_items = 0;
			count_cust = 0;
		}
				
		int gettot_items()	const{
			return tot_items;	
		}
		
		double get_billamount(){
			return bill;
		}
		
		int getcount_cust(){
			return count_cust;
		}
		
		bool generateBillno(){															//generates bill number according to today's date
			ifstream fcheck;
			fcheck.open("Inventory.dat");
			
			if( !fcheck.is_open() ){
				cout<< endl<< "No items are available in the Inventory."<< endl<< "FAILED TO ASSIGN BILL-NUMBER!"<< endl;
				return false;
			}
			else{
				fcheck.close();
				bill = 0;
				tot_items = 0;
				int day, month, count, i;	
				time_t now;
				struct tm nowLocal;
				
				now = time(NULL);
				nowLocal = *localtime(&now);
				
				day = nowLocal.tm_mday;
				month = nowLocal.tm_mon + 1;
				
				Customer Temp;
				ifstream in;
				in.open("Bill.dat");
				if(!in.is_open()){
					cout << "New Biling-file is being created!"<< endl<< endl<< endl<< "Proceeding with the new customer . . ."<< endl<< endl<< endl;
				}
		
				else{	
					while(!in.eof()){
						if( in.read((char*)&Temp, sizeof(Temp)) );
					}	
					in.close();
					count_cust = Temp.getcount_cust() + 1;
				}
	
				if( (Temp.bill_no[2] != ((day/10) + 48)) || (Temp.bill_no[3] != ((day%10) + 48)) )
					count_cust = 1;
				
				bill_no[0] = (month/10) + 48;						
				bill_no[1] = (month%10) + 48;
				bill_no[2] = (day/10) + 48;
				bill_no[3] = (day%10) + 48;
			    		    
			    i = 7;
			    count = count_cust;
			    
				while(i != 3){
					bill_no[i] = (count%10) + 48;
					count = count/10;
					i--;
				}
				return true;
			}
		}
		
		void calculateBill(const float price){													//function to add the price of each item in the customer's bill
			bill = bill + price;
			if(price>0){
				tot_items++;
			}
		}
				
		void displayallrecord(){												//display the bill of each customer
			ifstream fin;
			fin.open("Bill.dat");
			
			if(!fin.is_open())
				cout << "File could not open!"<< endl;
			
			else{
				cout<< endl<< "DISPLAYING THE RECORDS: ";
				while(!fin.eof()){
					if(fin.read((char*)this, sizeof(*this))){
						cout << endl<< "TOTAL-ITEMS: "<< tot_items
							 << endl<< "BILL-NUMBER: "; 
						for(int j = 0; j < 8; j++)
							cout << bill_no[j];
						cout << endl<< "BILL: Rs."<< bill<< endl<< endl<< endl;
					}
				}		
				fin.close();
			}
		}
		
		void AddRecord(){																	//will add this bill of the customer
			ofstream fout;
			fout.open("Bill.dat", ios :: app);
			
			if(!fout.is_open())
				cout << "File could not open!"<< endl;
			
			else{
				fout.write((char*)this, sizeof(*this));
				fout.close();
				cout<< endl<< "Billing-Info has been added successfully! " << endl << endl;
			}
		}
		
		void viewreciept(const long *ID, const int num) const{								//to view bill for recent customer
			cout<< "BILLING-ID: ";
			for(int j = 0; j < 8; j++)
				cout << bill_no[j];
			cout << endl;
			
			for(int cnt = 0; cnt< num; cnt++){
				Inventory::display_specificprod(*(ID + cnt), 1);
			}
			cout << endl;
		}
};

//Class for the employees:
class Employees{			//abstract class
	int id;
	char address[100], email[50], pass[20];						

	public:
		Employees(){
			id = 0;	
		}	
	
		void setaddress(const char add[100]){
			strcpy(address, add);	
		}	
		
		void setemail(const char mail[50]){
			strcpy(email, mail);	
		}	
		
		void setpswd(const char pswd[20]){
			strcpy(pass,pswd);	
		}
		
		char* getadd(){
			char *ptr = &address[0];
			return ptr;	
		}
		
		char* getmail(){
			char *ptr = &email[0];
			return ptr;	
		}
		
		char* getpswd(){
			char *ptr = &pass[0];
			return ptr;	
		}
			
		void setidm(const int identity){
			id = identity;
		}
		
		int getid()	const{
			return id;
		}
		
		virtual void viewrecord() = 0;
};

//Class for the cashier
class Cashier : public Employees{								
	long customers;
	Customer *C;												
	long long Mobile;
	char name[50];
	
	public:
		
		void setcustom_ptr(Customer &Cust){								//Cashier me customer se related koi bhi functionality call krne se pehle ye function call krna must hai
			C = &Cust;
		}
		
		void setname(const char nme[50]){
			strcpy(name, nme);
		}
		
		void setMobile(const long long mob){
			Mobile = mob;
		}
		
		bool checkitem(const long ID){							//calls check_availability for each item from inventory	and call another func to add it's price of available			
			float price;
			price = Inventory::check_availability(ID);
			C->calculateBill(price);
			return (price > 0);
		}
		
		long long getcell(){
			return Mobile;
		}
		
		void freecustom_ptr(){									//to free the pointer of the customer
			C = NULL;
		}	
		
		int setid(){
			ifstream fin;
			Cashier Temp;
			int iden;
			
			fin.open("Employees.dat");
			if(fin.is_open()){
				while(!fin.eof()){
					if( fin.read((char *)&Temp, sizeof(Temp)) );
				}
				iden = (Temp.getid()) + 1;
				fin.close();
			}
			else{
				cout<< endl<< "NEW FILE IS NOW BEING CREATED!"<< endl;
				iden = 750;																//first cashier's ID = 750
			}
			cout<< endl<< "Assigned-ID is: "<< iden << endl;
			return iden;
		}
		
		char* setpass(int rnd){										//automatic generator for password on the basis of First name, Cashier-id, & 3 random number
			char password[20] = {'\0'};
			int random = rnd;
			int cnt = 0, data[3] = {0}, cnt2 = 0;	
			int num;
			char *ptr;
			
			while(1){
				if( name[cnt] != ' ' ){
					password[cnt] = name[cnt];
				}
				else{
					break;
				}
				cnt++;
			}

			int a = cnt;
			
			num = getid();
			cnt = 2;
			
			while(cnt!= -1){
				data[cnt] = (num%10);
				num/= 10;
				cnt--;
			}	
			
			num = 0;
			cnt = a;
			a = cnt + 3;
			
			for(; cnt<a; cnt++){
				password[cnt] = (data[cnt2] + 48);
				cnt2++;	
			}
			
			a = cnt;
			cnt2 = 0;
			num = random;
			cnt = 2;
			
			while(num != 0){
				data[cnt] = (num%10);
				num/= 10;
				cnt-= 1;
			}	
			
			cnt = a;
			a = cnt + 3;
			
			for(; cnt<a; cnt++){
				password[cnt] = (data[cnt2] + 48);
				cnt2++;
			}
			
			for(int cnt = 0; cnt<20; cnt++)
				cout<< " ";
			
			ptr = &password[0];
			return ptr;
		}
		
		Cashier(char nme[50], char add[100], char Email[50], long long Mobile){										//parametrised cstr
			customers = 0;
			int cnt, flag = 0, n;
			int random, num[3];
			int id;
			char pass[20] = {'\0'};
			
			customers = 0;
			C = NULL;
			setemail(Email);
			setaddress(add);
			strcpy(name, nme);	
			fflush(stdin);
			
			id = setid();						
			setidm(id);
			fflush(stdin);
			
			cout<< endl<< "Enter a number of 3 UNEQUAL digits to add it in the password (each digit should be Greater than 0):"<< endl;					//ye input setpass() me hi na lelen?
			do{
				cin>> random;
				n = random;
				cnt = 2;
				while(n!= 0){
					num[cnt] = (n%10);
					n/= 10;
					cnt-= 1;
				}	
				
				if( ((num[0]!= num[1]) && (num[0]!= num[2])) && (num[1]!= num[2]) ){
					flag = 1;
				}
				else{
					cout<< endl<< "Maybe the numbers are equal!"<< endl<< "RE-ENTER your number: ";
				}	
			}while(flag!= 1);
				
			char *pass_ptr = setpass(random);
			cnt = 0;
			while( (*(pass_ptr + cnt)!= '\0') || (cnt != 20) ){
				pass[cnt] = *(pass_ptr + cnt);
				cnt++;
			}
			
			setpswd(pass);
			
			cout<< endl<< "CASHIER'S LOGIN INFORMATION: "<< endl<< "E-mail: "<< Email;
			cout<< endl<< "Password: "<< pass<< endl;
			
			this->Mobile = Mobile;
			cout<< endl<< endl<< endl;			
		}
		
		void updaterecord(){												//updating/modifying the info of cashier
			ifstream fin;
			ofstream fout;
			int fg = 0;
			Cashier Temp;
			
			fin.open("Employees.dat");
			fout.open("Employeestemp.dat");
			
			if( (!fin.is_open()) ){
				cout << "File could not open!"<< endl;
				fout.close();
			}
			else{
				while(!fin.eof()){
					if( fin.read((char *)&Temp, sizeof(Temp)) ){
						if( getid() == Temp.getid() ){
							fout.write((char *)this, sizeof(*this));
							fg = 1;
						}
						else
							fout.write((char *)&Temp, sizeof(Temp));
					}
				}
				fin.close();
				fout.close();
				
				remove("Employees.dat");
				rename("Employeestemp.dat", "Employees.dat");
				
				if(fg != 1)
					cout<< endl<< "An error occured while updating the Cashier Record!" << endl << endl;
			}
		}
		
		void updaterecord(const int ID){									//function overloaded to update the record of the cashiers
		    ifstream file;
		    ofstream temp;
			char nme[50], email[50], address[100];
		    long long mobile;
			Cashier Temp;
			int flag = 0;
		    
		    file.open("Employees.dat");
		    temp.open("Employeestemp.dat");
		    
		    while(!file.eof()){
		    	if(file.read((char *)&Temp, sizeof(Temp))){
					if(Temp.getid() == ID){	
						char opt;
						flag = 1;				
						fflush(stdin);
						
			        	cout<< endl<< "UPDATING INFORMATION OF THE CASHIER WITH ID: "<< ID<< endl
			        		<< "1) Name"<< endl<< "2) Mobile number"<< endl<< "3) Email"<< endl << "4) Address"<< endl << "OPT: ";
			        	opt = getchar();											
			        	fflush(stdin);
			        	bool chk = false;
			        	if(opt == '1'){
							cout << endl<< "Enter Name (FirstName + LastName): ";
			   			    do{
								cin.getline(name, 50);	
								chk = Exception_handling::checkcashiername(name);
								if(chk == true)
									Temp.setname(name);
								fflush(stdin);
							}while(chk != true);
		        		}
		        		
		        		else if(opt == '2'){
			        		char mob[12]={'\0'};
			        		bool chec=false;
							do{
								cout << "Mobile number: ";
								fflush(stdin);
								cin.getline(mob, 12);
								
								chec = Exception_handling::checkcontact(mob);
								if(chec == true){
									mobile = Exception_handling::formnum(mob);
									Temp.setMobile(mobile);
								}
								for(int ct = 0; ct<12; ct++)
									mob[ct] = '\0';
							}while(chec!=true);
			        	
			        	}
			        
						else if(opt == '3'){
			        		bool chk = false;
			       			cout << endl<< "Enter Email: ";
			       			do{
								cin.getline(email,50);
								chk = Exception_handling::checkmail(email);
								if(chk == true){	
									Temp.setemail(email);
									break;
								}
							}while(chk != true);
		        			
						}
			        
						else if(opt == '4'){
			        		fflush(stdin);
			       			cout << endl<< "Enter Address: ";
			       			cin.getline(address, 100);
		        			Temp.setaddress(address);	
						}
						
						else{
							cout<< endl<< "Invalid Input!"<< endl;
							flag = -1;
						}
						
			            temp.write((char *)&Temp, sizeof(Temp));
			        }
			        else
			        	temp.write((char *)&Temp, sizeof(Temp));
			    }
		    }
		    if(flag == 1)
		    	cout << "\nRecord got updated successfully!\n";
		    else if(flag == 0)
		    	cout << "\nNo cashier with the ID '" << ID << "' exists\n";
		    	
		    file.close();
		    temp.close();
		    
		    remove("Employees.dat");
		    rename("Employeestemp.dat", "Employees.dat");
		}
				 
		Cashier(){
			customers = 0;
		}
		
		void increamentcustomers(){												//to do an increment of the customer for each cashier
			customers+= 1;
		}
		
		void viewreciept(long *ptr, const int num){								//function to call the view reciept function for each customer
			C->viewreciept(ptr, num);
		}
		
		//file-handling functions:
		bool update_cashierrecord(){											//add the current cashier in the file
			ofstream fout;
		    
			fout.open("Employees.dat", ios::app);    
			if( (!fout.is_open()) ){
		        cout << "An error occured while opening file!"<< endl;
		        return false;	
		    }
		    else{
		        fout.write((char *)this, sizeof(*this));
		        fout.close();
		       	return true;
		    }  
		}
		
		bool delete_Cash_Record(const int id)	const{							//function to delete a specific cashier record
			ifstream in;
			ofstream out;
			int flag = 0;
			
			in.open("Employees.dat");
			out.open("EmployeeTemp.dat");
			
			if( (!in.is_open()) && (!out.is_open()) ){
				cout << "An error Occured while opening the file! " << endl;
				return 0;
			}
			
			while(!in.eof()){
				if( in.read((char*)this, sizeof(*this)) ){
					if(id != getid()){
						out.write((char*)this, sizeof(*this));
					}
					else
						flag = 1;
				}
			}
			
			in.close();
			out.close();
			
			remove("Employees.dat");
			rename("EmployeeTemp.dat","Employees.dat");
			
			if(flag == 1)
				cout << "Record Deletion done Succesfully!"<< endl;
				
			else
				cout<< "No Cashier with this ID exists!"<< endl;	
		}
		
		bool VerifyPassAndEmail(char *mail, char *pass){											//function to verify email and password
			int flag = 0;
			ifstream in;
			in.open("Employees.dat");
			
			if(!in.is_open()){
				cout << "File could not open!"<< endl<< endl;
				return 0;
			}
			
			while(!in.eof()){
				if(in.read((char*)this, sizeof(*this))){
					if(!strcmp(getpswd(), pass)  && !strcmp(getmail(), mail))
						flag = 1;
				}
			}
			return flag;
		}
		
		void viewrecord(){															//pure virtual func to display cashier_info
			cout<< endl<< "CASHIER'S-INFORMATION:"<< endl
				<< "Name:    "<< name << endl
				<< "ID:      "<< getid() << endl
				<< "Address: "<< getadd() <<endl
				<< "Email:   "<< getmail() <<endl
				<< "Cell:    +92"<< getcell() << endl;	
		}
		
		//billings:
		void finaliseBill(){									//jb saare items ki price add hou jayegi bill me tou uske baad record file me add krne ke liye
			C->AddRecord();	
			customers+= 1;
			updaterecord();
		}
	
		//total customers of each cashier:
		long get_totcustomers()	const{
			return customers;
		}
};

//Class for manager:
class Manager : public Employees{							
	const int identity;
	
	public:
		// Print the customers' records of each day
		Manager() : identity(999){
			setidm(identity);
			setemail("manager123@gmail.com");
			setpswd("manager000123");
			setaddress("L-345, ABC area");
		}
		
		void view_Inventory(){
			Inventory I;
			I.viewallprod();
		}
		
		void update_Inventory(const long Prod_ID){
			Inventory I;
			I.updateinv(Prod_ID);
		}
		
		void showSpecificProduct(const long Prod_ID){
			Inventory::display_specificprod(Prod_ID);
		}
		
		void remove_cashier(const int ID){												//function to call the function for the deletion of a cashier record
			Cashier Temp;
			Temp.delete_Cash_Record(ID);
		}
		
		void display_salesperday(){														//function to display the amount in Rupees for the sales of each day
			ifstream Customers;
			Customers.open("Bill.dat");
			Customer Temp;
			float salesperday = 0;
			char date[2] = {'\0'}, month[2] = {'\0'};
			int flag = 0;
								
			if( !Customers.is_open() ){
				cout<< endl<< "An error occured while opening file!"<< endl;
			}
			else{
				
				cout << "           DATE                       SALES PER DAY"<< endl<< endl;
				while(1){
					if( Customers.read((char*)&Temp, sizeof(Temp))){
												
						if( ((date[0] != Temp.getbill_no(2)) || (date[1] != Temp.getbill_no(3))) && flag == 1 ){
							cout << '\t' << date[0] << date[1] << "/" 
							<< month[0] << month[1] << "/" << "2020"
							<< "\t\t\t" << "Rs."<< salesperday << endl;
							salesperday = 0;
						}
						salesperday += Temp.get_billamount();
						
						date[0] = Temp.getbill_no(2);
						date[1] = Temp.getbill_no(3);
						month[0] = Temp.getbill_no(0);
						month[1] = Temp.getbill_no(1);
						flag = 1;
					}
					
					else if(Customers.eof()){
						cout << '\t' << Temp.getbill_no(2) << Temp.getbill_no(3)
						<< "/"<< Temp.getbill_no(0)<< Temp.getbill_no(1) 
						<< "/" << "2020" << "\t\t\tRs."<< salesperday << endl;
						break;
					}
				}
				Customers.close();
			}

		}
		
		void viewrecord(){									
			char *ptr = getpswd();
			char password[20] = {'\0'};
			for(int cnt = 0; cnt< 10; cnt++)
				password[20] = *(ptr + cnt);		
			cout<< endl<< "MANAGER'S-INFORMATION:"<< endl
				<< "ID:   "<< getid() << endl
				<< "PASSWORD: "<< password<< endl;
		}

		void disp_Salesperitem(){
			Items item1, item2;
			ifstream inventory_cpy;		
			ifstream inventory;									
			double price = 0;
			int quant = 0;
			char name[60] = {'\0'};
			
			inventory_cpy.open("Inventory.dat");
			inventory.open("Inventorymain.dat");					//the main file which uses to create on the first moment of the creation of inventory and adds/deletes product too
			
			cout<< endl;
			if( (inventory_cpy.is_open()) && (inventory.is_open()) ){
				while(!inventory_cpy.eof()){
					if( inventory_cpy.read((char*)&item1, sizeof(item1)) ){
							if( inventory.read((char*)&item2, sizeof(item2)) ){
								quant = (item2.getquant() - item1.getquant());
								item2.setquant(quant);
								char *ptr = item1.getname();
								for(int cnt = 0; cnt< 60; cnt++){
									name[cnt] = *(ptr + cnt);
								}
								cout<< item2;
							}
					}
				}
				inventory_cpy.close();
				inventory.close();
			}
			else
				cout << "An error occured while opening file!"<< endl;
		}
		
};

//Class for supermarket, it has a Has-a relationship with the classes:
class SuperMarket{				
	long long totcustomers;
	int totcashiers;
	Inventory *Invent;				//has-an inventory
	Cashier *C;						//has-a cashier
	Manager *M;						//has-a manager
	Customer *Cust;					//has-a customer
	
	public:
		
		SuperMarket(){
			C = NULL;
			M = NULL;
			Cust = NULL;
			Invent = NULL;
			totcustomers = 0;
			totcashiers = 0;
		}
		
		void set_Inventoryptr(Inventory &Inven){							//sets the object of inventory in the pointer *Invent
			Invent = &Inven;	
		}	
			
		void set_Cashierptr(Cashier &Cash){									//sets the object of cashier in the pointer *C
			C = &Cash;
		}
		
		void set_Managerptr(Manager &Manag){								//sets the object of manager in the pointer *M
			M = &Manag;
		}
		
		void set_Customerptr(Customer &Custom){								//sets the object of customer in the pointer *Cust
			Cust = &Custom;	
		}
		
		//function to clear the pointers:
		void clr_Inventoryptr(){
			Invent = NULL;	
		}	
			
		void clr_Cashierptr(){
			C = NULL;
		}
		
		void clr_Managerptr(){
			M = NULL;
		}
		
		void clr_Customerptr(){
			Cust = NULL;	
		}
		
		void find_totalcashiers(){												//calculates the total cashiers currently employed in the supermarket
			ifstream Read;
			Cashier Temp;
			totcashiers = 0;
			Read.open("Employees.dat");
			if(Read.is_open()){
				while(!Read.eof()){
					if( Read.read((char*)&Temp, sizeof(Temp)) ){
						totcashiers+= 1;
					}
				}
				Read.close();
			}
			else{
				cout<< endl<< "An error occured while accessing the data!"<< endl;
			}
		}

		void find_totalcustomers(){												//calculates the total cashiers currently employed in the supermarket
			totcustomers = 0;
			ifstream Read;
			Cashier Temp;
			
			Read.open("Employees.dat");
			if(Read.is_open()){
				while(!Read.eof()){
					if( Read.read((char*)&Temp, sizeof(Temp)) ){
						totcustomers+= Temp.get_totcustomers();
					}
				}
				Read.close();
			}
			else{
				cout<< endl<< "An error occured while accessing the data!"<< endl;
			}
		}

		long long get_totcustomers()	const{
			return totcustomers;
		}
		
		int get_totcashiers()	const{
			return totcashiers;
		}
		
		int get_totemployees()	const{
			return (totcashiers + 1);
		}
		
		void disp_emprecords(){													//function to display the information of each cashier
			Cashier Temp;
			ifstream in;
			
			in.open("Employees.dat");
			if(in.is_open()){
				cout<< endl<< endl<< "DISPLAYING THE INFORMATION OF EACH CASHIER:"<< endl;
				while(!in.eof()){
					if( in.read( (char*)&Temp, sizeof(Temp)) ){
						Temp.viewrecord();
						cout<< endl;
					}
				}
				in.close();
				cout<< endl;
			}
			else
				cout<< endl<< "An error occured while fetching the records!"<< endl;
		}
		
		void disp_saleseachday(){										//display Total sales of each day with each customer's info
			ifstream Customers;
			char date[2] = {'\0'};
			Customer Temp;
			
			Customers.open("Bill.dat");
			if( Customers.is_open() ){
				cout<< endl<< endl<< "Displaying all the Customers-Records with respect to DATE:"<< endl<< endl;
				while(!Customers.eof()){
					if( Customers.read((char*)&Temp, sizeof(Temp))){
						if( (date[0] != Temp.getbill_no(2)) || (date[1] != Temp.getbill_no(3)) ){
							cout<< endl<< "SALES FOR THE DAY: "<< Temp.getbill_no(2)<< Temp.getbill_no(3)<< "/"<< Temp.getbill_no(0)<< Temp.getbill_no(1)<< "/"
								<< "2020"<< endl;
						}
						cout<< Temp;
						date[0] = Temp.getbill_no(2);
						date[1] = Temp.getbill_no(3);
					}
				}	
			}
			else{
				cout<< endl<< "An error occured while displaying the Total sales each day!"<< endl;
			}
		}
		
};

int Inventory::num_diffprod = 0;

//Scope of main:
int main(){	

	SuperMarket Supermarket;
	Manager ManagerH;
	Cashier Cash;
	Inventory In;
	Items I;
	Exception_handling E;
	char Email[50] = {'\0'}, Pass[20] = {'\0'}, choice;
	int option = 0, hold = 0;
	
	interface();
	while(1){
		cout<< endl<< endl<< endl;
		system("pause");
		system("cls");
		
		cout<< "YOU'VE THE FOLLOWING CHOICES TO PROCEED: "<< endl<< endl<< endl
			<< "0) Cashier\n1) Manager\nx) To exit."<< endl<< endl<< endl<< "Enter Your respective Choice: ";
			
		while(1){
			fflush(stdin);
			choice = getchar();
			if(choice == '0' || choice == '1')
				break;
			else if( (choice == 'x') || (choice == 'X') ){
				char a;
				cout << endl<< endl<< endl<< "Process exited with exception(s) value "<< E.getexception();			//yahan exception handling ki total values rkhni hai (IBAD)
				a = getch();
				exit(1);	
			}
				
			cout << "\nWRONG INPUT!"<< endl<< "Re-Enter Your respective Choice: ";
		}
		
		system("cls");
		
		if(choice == '0'){ 												// Cashier's Module
			char option = '\0';
			bool chk=false;
			cout << "ENTER CASHIER'S LOGIN INFORMATION:"<< endl;
			while(true){
				for(int j=0; j<50; j++)
					Email[j] = '\0';
				for(int j=0; j<20; j++)
					Pass[j] = '\0';
					
				fflush(stdin);
				cout << "\nEMAIL: ";
				do{
					cin.getline(Email,50);
					chk = Exception_handling::checkmail(Email);
					if(chk == true)
					{
						Cash.setemail(Email);
					}
				}while(chk != true);
				
				fflush(stdin);
				cout << "PASSWORD: ";
				InputPassword(Pass);
				hold = Cash.VerifyPassAndEmail(Email, Pass);
				
				if( hold ){
					cout<< endl<< endl<< endl<< "You're now being Logged in as the Cashier with Email: "<< Email<< endl<< endl<< endl;
					break;
				}
				system("cls");
				cout << "\n\nACCESS DENIED!\nEither EMAIL or PASSWORD is Incorrect!"<< endl<< endl<< "RE-ENTER YOU LOGIN INFORMATION: "<< endl;	
			}
						
			do{
				system("PAUSE");
				system("cls");
	
				cout<< "MENU: ENTER 0 TO ENTER THE BILLING MODULE"<< endl<< "      ENTER 1 TO VIEW THE INFORMATION OF THE SPECIFIC PRODUCT"
					<< endl<< "      ENTER X TO LOGOUT THE CASHIER"<< endl<<  endl;
				cin>> option;
	
				bool chec, opt, check;
				int cnt = 0, num = 0;
				Customer Client;
				long ID, Item_ID[1000] = {0};
				if(option == '1'){
					int id;
					char i[10] = {'\0'};
					
					do{
						chec = false;
						
						cout << endl<< "ENTER PRODUCT-ID TO SEARCH: ";
						fflush(stdin);
						cin.getline(i, 10);
						chec = Exception_handling::checkid(i);
						if(chec == true){
							id = Exception_handling::formid(i);
							break;
						}
						for(int ct = 0; ct<10; ct++)
							i[ct] = '\0';
					}while(chec != true);
					
					In.setitem_ptr(I);
					cout<< endl<< endl;
					In.display_specificprod(id);
					cout<< endl<< endl<< endl<< endl;
					In.clritem_ptr();
				}
				
				else if( ( option == 'X') || ( option == 'x') ){
					cout << endl << endl << endl<<"The User is now being Logged out shortly!" << endl;
					break;
				}
						
				else if( option == '0'){
					bool chec, opt, check;
					int cnt = 0, num = 0;
					Customer Client;
					long ID, Item_ID[1000] = {0};
																				
					cout<< endl<< endl;
					system("PAUSE");
					system("cls");
					cout<< "NOTE: ENTER 0 TO FINALISE EACH CUSTOMER'S BILL"<< endl<<endl;	
					cout<< endl<< endl<< "Enter each PRODUCT-ID to add in New Customer's Bill."<< endl;
					opt = Client.generateBillno();
					if(opt == true){
						Cash.setcustom_ptr(Client);
						do{
							cin>> ID;
							
							if(ID == 0)
								break;
									
							check = Cash.checkitem(ID);
							if(check == true){
								Item_ID[cnt] = ID;
								In.decrement_quant(ID);
								cnt++;
							}
							fflush(stdin);	
						}while(1);
							
						num = Client.gettot_items();
						Cash.finaliseBill();
						Cash.viewreciept(&Item_ID[0], num);
						cout<< "TOTAL-AMOUNT: Rs."<< Client.get_billamount()<< endl<< endl<< endl;
							
						cnt = 0;
						for(int iterate = 0; iterate<1000; iterate++)
							Item_ID[iterate] = 0;
							
						int option;
						cout << "PAYMENT METHOD(S):\n    0)Cash"<< endl<< "    1)Credit card"<< endl<< endl<< "Select your method option: ";
						do{
							cin >> option;
							if( !option ){
								cout<< endl<< "Cash of Amount: Rs."<< Client.get_billamount()<< " PAID Successfully!"<< endl<< endl<< endl;
							}
							else if( option == 1){
								char pass[5] = {'\0'};
								int passc = 0;
								long long numc;
								CreditCard CredCard;													//credit card's object
								int counter = 0;
								bool decision;
								bool dec_CC;
								
								do{
									cout<< endl<< "CREDIT-CARD NUMBER: ";
									do{
										numc = 0;
										dec_CC = false;
										fflush(stdin);
										
										cin>> numc;
										dec_CC = Exception_handling::checkcreditno<long long>(numc);
										if(dec_CC == true)
											break;
									}while(1);
									
									fflush(stdin);
									cout<< "PASSWORD: ";
									InputPassword(pass);
									passc = formnum(pass);
													
									decision = CredCard.Payment(numc, passc, Client.get_billamount());	
									if(decision == false){
										if(counter == 4){
											counter = 0;
											cout<< endl<< endl<< "CREDIT-CARD PAYMENT METHOD HAS BEEN DISABLED FOR THIS BILL NUMBER!"<< endl<< endl<< "Payment Method:\nCash Only"<< endl<< endl;
											system("PAUSE");
											break;
										}
										else
											counter+= 1;
									}	
									for(int inc = 0; inc<5; inc++)
										pass[inc] = '\0'; 
										
								}while(decision!= true);					
							}
							else
								cout << "Invalid input!\nRe-Enter Payment Method: ";
						}while(option != 0 && option != 1); 
						
						Cash.freecustom_ptr();
					}
				}
				
				else
					cout<< endl<< "\nINVALID INPUT!"<< endl;
				
			}while(true);
		}
			
		else if(choice == '1'){ 													// Manager's module
			cout << "ENTER MANAGER'S LOGIN INFORMATION:"<< endl;		
			while(true){
				for(int j=0; j<50; j++)
					Email[j] = '\0';
				for(int j=0; j<20; j++)
					Pass[j] = '\0';
					bool chk=false;
				fflush(stdin);
				cout << "\nEMAIL: ";
				do{
					cin.getline(Email,50);
					chk = Exception_handling::checkmail(Email);
					if(chk == true)
					{
					
						ManagerH.setemail(Email);
					}
				}while(chk != true);
				
				fflush(stdin);
				cout << "PASSWORD: ";
				InputPassword(Pass);		
				
				if( !strcmp(Email, ManagerH.getmail()) && !strcmp(Pass, ManagerH.getpswd()) ){
					cout<< endl<< endl<< endl<< "You're now being Logged in as the Manager of the SuperMarket with Email: "<< Email<< endl;
					break;
				}
				
				cout << "\n\nAccess denied!\nEither the EMAIL -or- PASSWORD -or- both are Incorrect!\n\nRe-Enter the information: ";
			}
			
			do{
				cout << endl << endl;
				system("pause");
				system("cls");
				char menu[7] = {'\0'};
				
				cout<< "MENU: 1)  ADD A NEW CASHIER"<< endl<< "      2)  DELETE THE SPECIFIC CASHIER'S INFO"<< endl
					<<"      3)  VIEW TOTAL NUMBER OF CASHIERS"<< endl<< "      4)  VIEW ALL CASHIER'S INFORMATION"<< endl<< "      5)  UPDATE CASHIER INFORMATION" << endl
					<< "      6)  ADD PRODUCT IN THE INVENTORY"<< endl << "      7)  DELETE PRODUCT FROM THE INVENTORY"<< endl<< "      8)  MODIFY PRODUCT IN THE INVENTORY"<< endl
					<< "      9)  VIEW ALL PRODUCTS OF THE INVENTORY"<< endl<< "      10) VIEW INFO OF THE SPECIFIC PRODUCT OF THE INVENTORY"<< endl<< "      11) VIEW SALES PER DAY"<< endl
					<< "      12) VIEW NUMBER OF EACH ITEM SOLD"<< endl<< "      13) VIEW TOTAL NUMBER OF CUSTOMERS OF THE SUPERMARKET"<< endl<< "      14) DISPLAY EACH BILL OF EACH DAY"<< endl<< "      0)  LOG-OUT FROM THE CURRENT MODULE"<< endl
					<< "\nEnter your Respective choice to Proceed: ";
				
				for (int i=0;i<7;i++)
					menu[i] = '\0';
				fflush(stdin);
				cin.getline(menu , 7);
				
				if(strcmp(menu, "1") == 0){
					long long mobile;
					char mob[12]={'\0'};
					char name[50] = {'\0'}, email[50] = {'\0'}, pass[20] = {'\0'}, address[100] = {'\0'};
					bool chk=false;
					cout << "\nEnter the information of the New-Cashier:"<< endl<< "Name (FirstName + LastName): ";
					fflush(stdin);
					do{
						cin.getline(name, 50);	
						chk = Exception_handling::checkcashiername(name);
						if(chk == true)
							Cash.setname(name);
						fflush(stdin);
					}while(chk != true);
					bool chec = false;
					bool lencheck=false;
					int s = 0;	
					do{
						cout << "Mobile number: ";
						fflush(stdin);
						cin.getline(mob, 12);
						s = strlen(mob);
						chec = Exception_handling::checkcontact(mob);
						if(chec == true){
							mobile = Exception_handling::formnum(mob);
						}
						for(int ct = 0; ct<12; ct++)
							mob[ct] = '\0';
					}while(chec!=true);
				
					fflush(stdin);
					cout << "Email: ";
					do{
						cin.getline(email,50);
						chk = Exception_handling::checkmail(email);
						if(chk == true)
						{	
							break;
						}
					}while(chk != true);
					fflush(stdin);
					cout << "Address: ";
					cin.getline(address, 100);
					
					Cashier Cash2(name, address, email, mobile);
					Cash2.update_cashierrecord();
				}
				
				else if(strcmp(menu, "2") == 0){
					int id;
					char i[10]={'0'};
					bool chec = false;

					do{
						cout << "\nEnter the ID of the Cashier to DELETE his/her information: ";
						fflush(stdin);
						cin.getline(i, 10);
						chec = Exception_handling::checkid(i);
						if(chec == true){
							id = Exception_handling::formid(i);
						}
						for(int ct = 0; ct<10; ct++)
							i[ct] = '\0';
					}while(chec!=true);		
					ManagerH.remove_cashier(id);
				}
				
				else if(strcmp(menu, "3") == 0){
					int totalcashiers;
					
					Supermarket.find_totalcashiers();
					totalcashiers = Supermarket.get_totcashiers();
					cout << "\nTotal Number of Cashiers: " << totalcashiers << endl;
				}
				
				else if(strcmp(menu, "4") == 0){
					Supermarket.disp_emprecords();
				}
				
				else if(strcmp(menu, "5") == 0){
					int id;
					char i[10]={'0'};
					bool chec = false;

					do{
						cout << "\nEnter the ID of the Cashier: ";
						fflush(stdin);
						cin.getline(i, 10);
						chec = Exception_handling::checkid(i);
						if(chec == true){
							id = Exception_handling::formid(i);
						}
						for(int ct = 0; ct<10; ct++)
							i[ct] = '\0';
					}while(chec!=true);		
					Cash.updaterecord(id);
				}
				
				else if(strcmp(menu, "6") == 0){
					float price = 0;
					int quant = 0;
					char name[60]= {'\0'};
					
					fflush(stdin);
					cout << endl << "Product-Name: ";
					cin.getline(name, 60);
					cout << "Product-Price: ";
					cin >> price;
					cout << "Product-Quantity: ";
					cin >> quant;
					
					Items I(name, quant, price);
					I.setid();
					I.storeprod();
				}
				
				else if(strcmp(menu, "7") == 0){
					long id;
					
					char i[10]={'0'};
					bool chec = false;

					do{
						cout << endl<< "Enter ID to delete product: ";
						fflush(stdin);
						cin.getline(i, 10);
						chec = Exception_handling::checkid(i);
						if(chec == true){
							id = Exception_handling::formid(i);
						}
						for(int ct = 0; ct<10; ct++)
							i[ct] = '\0';
					}while(chec!=true);
					I.deletepro(id);
				}
				
				else if (strcmp(menu, "8") == 0){
					long id;
					char i[10]={'\0'};
					bool chec = false;

					do{
						cout << endl<< "Enter ID to update product: ";
						fflush(stdin);
						cin.getline(i, 10);
						chec = Exception_handling::checkid(i);
						if(chec == true){
							id = Exception_handling::formid(i);
						}
						for(int ct = 0; ct<10; ct++)
							i[ct] = '\0';
					}while(chec!=true);
					In.updateinv(id);
				}
				
				else if (strcmp(menu, "9") == 0){
					In.setitem_ptr(I);
					cout<< endl<< endl<< "DISPLAYING ALL THE ITEMS OF THE INVENTORY: "<< endl<< endl;
					In.viewallprod();
				}
			
				else if (strcmp(menu, "10") == 0){
					long id;
					char i[10]={'\0'};
					bool chec=false;
					do{
						cout << endl<< "Enter ID to search product: ";
						fflush(stdin);
						cin.getline(i, 10);
						chec = Exception_handling::checkid(i);
						if(chec == true){
						id = Exception_handling::formid(i);
						}
						for(int ct = 0; ct<10; ct++)
							i[ct] = '\0';
					}while(chec!=true);
					In.setitem_ptr(I);
					cout<< endl<< endl;
					In.display_specificprod(id);
					cout<< endl<< endl;
					In.clritem_ptr();						//agr koi error aaya tou yahan aasakta hai otherwise delete this comment
				}
				
				else if (strcmp(menu, "11") == 0){
					cout << endl;
					ManagerH.display_salesperday();
				}
				
				else if (strcmp(menu, "12") == 0){
					ManagerH.disp_Salesperitem();
				}
				
				else if (strcmp(menu, "13") == 0){
					Supermarket.find_totalcustomers();
					cout<< endl<< "The Total Number of Customers of the SuperMarket is: "<< Supermarket.get_totcustomers()<< endl;
				}			
				
				else if(strcmp(menu, "14") == 0){
					Supermarket.disp_saleseachday();
				}
				
				else if (strcmp(menu, "0") == 0){
					cout << endl<< endl<< "The System is now Exiting the Manager Module shortly . . . "<< endl;
					break;
				}
				
				else{
					cout << "\nInvalid Input!\nRE-ENTER YOUR CHOICE!";
				}
				
			}while(1);			
		}	
	}

	cout<< endl<< endl<< endl;
	system("PAUSE");
	return 0;
}
