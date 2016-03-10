#include <iostream>
#include <exception>
#include <stdexcept>
#include <cstring>
#include <fstream>
#include "Date.cpp"

using namespace std;

ofstream outputfile;	//outputfile stream for output
ifstream inputfile;		//taking input from input.txt
ifstream displayfile;	//seperate input stream for displaying input

void inputall(Date&);	//tests all input formats
void outputall(Date&);	//tests all output formats
void testFormat();		//tests all date formats

int main(){
	outputfile.open ("output.txt");		//opens corresponding stream
	inputfile.open("input.txt");
	displayfile.open("input.txt"); 
	Date A;								//default constructor, takes current date
	outputfile << "New Date A (Current)" <<  endl;
	outputfile << "\nTESTING DATE FORMATS\n" << endl;
	testFormat();						//test all date formats
	outputall(A);						//tests all output formats
	Date B;
	outputfile << "\nNew Date B (for input testing)" << endl;
	outputfile << "INPUT (in all possible formats with proper exception handling)" << endl;
	outputfile << "To skip input testing at any point of time, enter X" << endl;
	inputall(B);
	DateFormat df = DateFormat("dd","mm","yy");
	Date::setFormat(df);
	outputfile << "\nFrom now on all input/output will be in the format (dd/mm/yy)" << endl;
	outputfile << "\nTESTING DATE CONSTRUCTORS\n" << endl;		//testing date constructors
	outputfile << "# Date(Day, Month, Year)\n" << endl;
	outputfile << "Date(D31,Mar,2012)                  :  " << Date(D31,Mar,2012) << endl;
	outputfile << "Date(static_cast<Day>(87),Feb,1)    :  ";
	try{														//handling exception cases
		Date temp(static_cast<Day>(87),Feb,1);
	}catch(exception& e){
		outputfile << e.what() << endl;
	}
	outputfile << "Date(D31,Feb,2010)                  :  ";
	try{
		Date temp(D31,Feb,2010);
	}catch(exception& e){
		outputfile << e.what() << endl;
	}
	outputfile << "Date(D31,Dec,2060)                  :  ";
	try{
		Date temp(D31,Dec,2060);
	}catch(exception& e){
		outputfile << e.what() << endl;
	}
	outputfile << "\n# Date(\"Day - Month -Year\")\n" << endl;
	outputfile << "Date(\"01-04-12\")                    :  " << Date("11-04-12") << endl;
	outputfile << "Date(\"30-12-26\")                    :  " << Date("30-12-26") << endl;
	outputfile << "Date(\"30-12-216\")                   :  ";
	try{
		Date("30-12-216");
	}catch(exception& e){
		outputfile << e.what() << endl;
	}
	outputfile << "Date(\"30-02-31\")                    :  ";
	try{
		Date("30-02-26");
	}catch(exception& e){
		outputfile << e.what() << endl;
	}	 
	Date C("09-02-11");
	outputfile << "\nDate C(\"09-02-11\")                  : " << C << endl; 
	outputfile << "\nOPERATORS:" <<  endl;						//testing all operators
	outputfile << "\nBASIC ASSIGNMENT OPERATOR" << endl;
	outputfile << "C = A" << endl;
	C = A;
	outputfile << "New C: " << C << endl;
	outputfile << "\nCOPY CONSTRUCTOR" << endl;
	outputfile << "Date D = A" << endl;
	Date D = A;
	outputfile << "D: " << C << endl;
	outputfile << "\nUNARY ARITHMETIC OPERATORS" << endl;
	outputfile << "\n++A (next day)" << endl;
	++A;
	outputfile << "New A: " << A << endl;
	outputfile << "Special cases:" << endl;
	outputfile << "Month Change case: D as \"28-02-61\"" << endl;
	outputfile << "++D" << endl;
	D = Date("28-02-61");
	++D;
	outputfile << "New D: " << D << endl;
	outputfile << "Year Change case: D as \"31-12-64\"" << endl;
	outputfile << "++D" << endl;
	D = Date("31-12-64");
	++D;
	outputfile << "New D: " << D << endl;
	outputfile << "Boundary case: D as \"31-12-49\"" << endl;
	D = Date("31-12-49");
	outputfile << "++D" << endl;								//handling exception cases
	try{
		++D;
	}
	catch(exception& e){
		outputfile << "Exception: " << e.what() << endl;
	}
	outputfile << "\nA++ (Same day next week)" << endl;
	A++;
	outputfile << "New A: " << A << endl;
	outputfile << "Special cases:" << endl;
	outputfile << "Month Change case: D as \"25-02-61\"" << endl;
	outputfile << "D++" << endl;
	D = Date("25-02-61");
	D++;
	outputfile << "New D: " << D << endl;
	outputfile << "Year Change case: D as \"28-12-64\"" << endl;
	outputfile << "D++" << endl;
	D = Date("28-12-64");
	D++;
	outputfile << "New D: " << D << endl;
	outputfile << "Boundary case: D as \"27-12-49\"" << endl;
	D = Date("27-12-49");
	outputfile << "D++" << endl;
	try{
		D++;
	}
	catch(exception& e){
		outputfile << "Exception: " << e.what() << endl;
	}
	outputfile << "\n++A (next day)" << endl;
	++A;
	outputfile << "New A: " << A << endl;
	outputfile << "Special cases:" << endl;
	outputfile << "Month Change case: D as \"28-02-61\"" << endl;
	outputfile << "++D" << endl;
	D = Date("28-02-61");
	++D;
	outputfile << "New D: " << D << endl;
	outputfile << "Year Change case: D as \"31-12-64\"" << endl;
	outputfile << "++D" << endl;
	D = Date("31-12-64");
	++D;
	outputfile << "New D: " << D << endl;
	outputfile << "Boundary case: D as \"31-12-49\"" << endl;
	D = Date("31-12-49");
	outputfile << "++D" << endl;
	try{
		++D;
	}
	catch(exception& e){
		outputfile << "Exception: " << e.what() << endl;
	}
	outputfile << "\nA++ (Same day next week)" << endl;
	A++;
	outputfile << "New A: " << A << endl;
	outputfile << "Special cases:" << endl;
	outputfile << "Month Change case: D as \"25-02-61\"" << endl;
	outputfile << "D++" << endl;
	D = Date("25-02-61");
	D++;
	outputfile << "New D: " << D << endl;
	outputfile << "Year Change case: D as \"28-12-64\"" << endl;
	outputfile << "D++" << endl;
	D = Date("28-12-64");
	D++;
	outputfile << "New D: " << D << endl;
	outputfile << "Boundary case: D as \"27-12-49\"" << endl;
	D = Date("27-12-49");
	outputfile << "D++" << endl;
	try{
		D++;
	}
	catch(exception& e){
		outputfile << "Exception: " << e.what() << endl;
	}
	/*-------------------------*/
	outputfile << "\n--A (previous day)" << endl;
	--A;
	outputfile << "New A: " << A << endl;
	outputfile << "Special cases:" << endl;
	outputfile << "Month Change case: D as \"01-02-61\"" << endl;
	outputfile << "--D" << endl;
	D = Date("01-02-61");
	--D;
	outputfile << "New D: " << D << endl;
	outputfile << "Year Change case: D as \"01-12-64\"" << endl;
	outputfile << "--D" << endl;
	D = Date("01-12-64");
	--D;
	outputfile << "New D: " << D << endl;
	outputfile << "Boundary case: D as \"01-01-50\"" << endl;
	D = Date("01-01-50");
	outputfile << "--D" << endl;
	try{
		--D;
	}
	catch(exception& e){
		outputfile << "Exception: " << e.what() << endl;
	}
	outputfile << "\nA-- (Same day previous week)" << endl;
	A--;
	outputfile << "New A: " << A << endl;
	outputfile << "Special cases:" << endl;
	outputfile << "Month Change case: D as \"03-02-61\"" << endl;
	outputfile << "D--" << endl;
	D = Date("03-02-61");
	D--;
	outputfile << "New D: " << D << endl;
	outputfile << "Year Change case: D as \"04-01-64\"" << endl;
	outputfile << "D--" << endl;
	D = Date("04-01-64");
	D--;
	outputfile << "New D: " << D << endl;
	outputfile << "Boundary case: D as \"01-01-50\"" << endl;
	D = Date("01-01-50");
	outputfile << "D--" << endl;
	try{
		D--;
	}
	catch(exception& e){
		outputfile << "Exception: " << e.what() << endl;
	}
	char const* w[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	char const* m[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	char const* boo[2] = {"False", "True"};
	outputfile << "\nBINARY ARITHMETIC OPERATORS" << endl;
	outputfile << "A: " << A << endl;
	outputfile << "C: " << C << endl;
	outputfile << "D: " << D << endl;	
	outputfile << "A - D = " << A - D << endl;
	outputfile << "C - A = " << C - A << endl;
	C = A + 35;
	outputfile << "C = A + 35\nNew C: " << C << endl;
	D = Date("12-08-49");
	outputfile << "New D: " << D << endl;
	outputfile << "Boundary case: " << endl;
	outputfile << "C = D + 260" << endl;
	try{
		C = D + 260;
	}
	catch(exception& e){
		outputfile << e.what() << endl;
	}
	outputfile << "\nCAST OPERATORS" << endl;
	A = Date("06-12-00");
	D = Date("03-01-16");
	B = Date("31-12-14");
	C = Date("27-02-94");
	outputfile << "A:             " << A << endl;
	outputfile << "B:             " << B << endl;
	outputfile << "C:             " << C << endl;
	outputfile << "D:             " << D << endl;
	outputfile << "(Month)A:      " << m[(Month)A-1] << endl;
	outputfile << "(Month)D:      " << m[(Month)D-1] << endl;
	outputfile << "(WeekDay)B:    " << w[(WeekDay)B] << endl;
	outputfile << "(WeekDay)C:    " << w[(WeekDay)C] << endl;
	outputfile << "(WeekNumber)A: " << (WeekNumber)A  << endl;
	outputfile << "(WeekNumber)B: " << (WeekNumber)B << endl; 
 	outputfile << "(WeekNumber)D: " << (WeekNumber)D << endl; 
 	outputfile << "A.leapYear():  " << boo[A.leapYear()] << endl;
 	outputfile << "B.leapYear():  " << boo[B.leapYear()] << endl;
 	outputfile << "D.leapYear():  " << boo[D.leapYear()] << endl;
 	outputfile << "\nBINARY RELATIONAL OPERATORS" << endl;
 	A = Date("06-12-00");
	D = Date("03-01-16");
	B = Date("31-12-14");
	C = Date("27-02-94");
	Date E = Date("06-12-00");
	outputfile << "A:       " << A << endl;
	outputfile << "B:       " << B << endl;
	outputfile << "D:       " << D << endl;
 	outputfile << "E:       " << E << endl;
 	outputfile << "A == E:  " << boo[A==E] << endl;
 	outputfile << "A == D:  " << boo[A==D] << endl;
 	outputfile << "A != E:  " << boo[A!=E] << endl;
 	outputfile << "A != D:  " << boo[A!=D] << endl;
 	outputfile << "A > E:   " << boo[A>E] << endl;
 	outputfile << "A >= E:  " << boo[A>=E] << endl;
 	outputfile << "E > A:   " << boo[E>A] << endl;
 	outputfile << "E >= A:  " << boo[E>=A] << endl;
 	outputfile << "A < B:   " << boo[A < B] << endl;
 	outputfile << "B <= A:  " << boo[B <= A] << endl;
 	outputfile << "B < A:   " << boo[B < A] << endl;
 	outputfile << "A <= B:  " << boo[A <= B] << endl;
 	outputfile.close();
 	return 0;
}

void testFormat(){
	try{
		DateFormat DF1("dd","mm","yyyy");
		DateFormat DF2("d","m","0");
		DateFormat DF3("0","mmm","yyyy");
		DateFormat DF4("0","0","yy");
		DateFormat DF5("dd-mm-yyyy");
		DateFormat DF6("d-m-0");
		DateFormat DF7("0-mmm-yyyy");
		DateFormat DF8("d-0-yy");
		DateFormat DF9("0-0-0");
		Date d;
		outputfile << "Default                             :  "  << d << endl;  
		d.setFormat(DF1);
		outputfile << "DateFormat(\"dd\",\"mm\",\"yyyy\")        :  " << d << endl ;
		d.setFormat(DF2); 
		outputfile << "DateFormat(\"d\",\"m\",\"0\")             :  " << d << endl ;
		d.setFormat(DF3); 
		outputfile << "DateFormat(\"0\",\"mmm\",\"yyyy\")        :  " << d << endl ;	
		d.setFormat(DF4);
		outputfile << "DateFormat(\"0\",\"0\",\"yyyy\")          :  " << d << endl ;
	    d.setFormat(DF5);     
	    outputfile << "DateFormat(\"dd-mm-yyyy\")            :  " << d << endl ;
	    d.setFormat(DF6);
	    outputfile << "DateFormat(\"d-m-0 \")                :  " << d << endl ;
	    d.setFormat(DF7);
		outputfile << "DateFormat(\"0-mmm-yyyy\")            :  " << d << endl ;
		d.setFormat(DF8);     
		outputfile << "DateFormat(\"d-0-yy\")                :  " << d << endl ; 
		d.setFormat(DF9);
		outputfile << "DateFormat(\"0-0-0\")                 :  " << d << endl;
		d.setFormat(DF5);
	} 
	catch(exception& e){     
		outputfile << "Exception:" << e.what() << endl; 
	}
	try{
		DateFormat DF("yyyy-mm-dd");   //incorrect order
	}
	catch(exception& e){
		outputfile << "DateFormat(\"yyyy-mm-dd\")            :  " << "Exception: " << e.what() << endl ;
	}
	try{
		DateFormat DF("fds0-fdsa-jbsf");   //invalid string
	}
	catch(exception& e){
		outputfile << "DateFormat(\"fds0-fdsa-jbsf\")        :  " << "Exception: " << e.what() << endl ;
	}
	try{
		DateFormat DF("0");
	}
	catch(exception& e){
		outputfile << "DateFormat(\"0\")                     :  " << "Exception: " << e.what() << endl ;
	}
}

bool input(Date& X){
	DateFormat s = Date::getFormat();
	char * str;
	try{
		str = new char[20];
		outputfile << "Enter a date (" << s.getDateFormat() << "-" << s.getMonthFormat() << "-" <<s.getYearFormat() <<"): ";
		displayfile >> str;
		outputfile << str << endl;
		inputfile >> X;
		outputfile << "Input successfully taken" << endl;
	}
	catch(exception& e){
		delete str;
		if(strcmp(e.what(),"X")==0)
			return false;
		outputfile << e.what() << endl;
	}
	return true;
}

void inputall(Date& d){
	DateFormat df = DateFormat("dd","mmm","yyyy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("dd","mmm","0");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("dd","mm","yy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("dd","mm","yyyy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("dd","mm","0");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("dd","m","yy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("dd","m","yyyy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("dd","m","0");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("dd","0","yy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("dd","0","yyyy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("dd","0","0");
	d.setFormat(df);
	if(!input(d)) return;
	/*--------------------*/
	df = DateFormat("d","mmm","yyyy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("d","mmm","0");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("d","mm","yy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("d","mm","yyyy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("d","mm","0");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("d","m","yy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("d","m","yyyy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("d","m","0");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("d","0","yy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("d","0","yyyy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("d","0","0");
	d.setFormat(df);
	if(!input(d)) return;
	/*--------------------*/
	df = DateFormat("0","mmm","yyyy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("0","mmm","0");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("0","mm","yy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("0","mm","yyyy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("0","mm","0");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("0","m","yy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("0","m","yyyy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("0","m","0");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("0","0","yy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("0","0","yyyy");
	d.setFormat(df);
	if(!input(d)) return;
	df = DateFormat("0","0","0");
	d.setFormat(df);
	if(!input(d)) return;
}

void outputall(Date& d){
	outputfile << "\nOUTPUT (in all possible formats)\n" << endl;
	outputfile << "dd-mmm-yy                           :  " << d << " (Default)" << endl;		//prints in default set format dd/mmm/yy
	DateFormat df = DateFormat("dd","mmm","yyyy");
	d.setFormat(df);
	outputfile << "dd-mmm-yyyy                         :  " << d << endl;  //prints in the new set format 
	df = DateFormat("dd","mmm","0");
	d.setFormat(df);
	outputfile << "dd-mmm-0                            :  " << d << endl;  //prints in the new set format 

	df = DateFormat("dd","mm","yy");
	d.setFormat(df);
	outputfile << "dd-mm-yy                            :  " << d << endl;	//prints in default set format dd/mmm/yy
	df = DateFormat("dd","mm","yyyy");
	d.setFormat(df);
	outputfile << "dd-mm-yyyy                          :  " << d << endl;  	//prints in the new set format 
	df = DateFormat("dd","mm","0");
	d.setFormat(df);
	outputfile << "dd-mm-0                             :  " << d << endl;  //prints in the new set format 

	df = DateFormat("dd","m","yy");
	d.setFormat(df);
	outputfile << "dd-m-yy                             :  " << d << endl;	//prints in default set format dd/mmm/yy
	df = DateFormat("dd","m","yyyy");
	d.setFormat(df);
	outputfile << "dd-m-yyyy                           :  " << d << endl;  //prints in the new set format 
	df = DateFormat("dd","m","0");
	d.setFormat(df);
	outputfile << "dd-m-0                              :  " << d << endl;  //prints in the new set format 

	df = DateFormat("dd","0","yy");
	d.setFormat(df);
	outputfile << "dd-0-yy                             :  " << d << endl;	//prints in default set format dd/mmm/yy
	df = DateFormat("dd","0","yyyy");
	d.setFormat(df);
	outputfile << "dd-0-yyyy                           :  " << d << endl;  //prints in the new set format 
	df = DateFormat("dd","0","0");
	d.setFormat(df);
	outputfile << "dd-0-0                              :  " << d << endl;  //prints in the new set format 

	/*--------------------*/

	df = DateFormat("d","mmm","yy");
	d.setFormat(df);
	outputfile << "d-mmm-yy                            :  " << d << endl;		//prints in default set format dd/mmm/yy
	df = DateFormat("d","mmm","yyyy");
	d.setFormat(df);
	outputfile << "d-mmm-yyyy                          :  " << d << endl;  //prints in the new set format 
	df = DateFormat("d","mmm","0");
	d.setFormat(df);
	outputfile << "d-mmm-0                             :  " << d << endl;  //prints in the new set format 

	df = DateFormat("d","mm","yy");
	d.setFormat(df);
	outputfile << "d-mm-yy                             :  " << d << endl;	//prints in default set format dd/mmm/yy
	df = DateFormat("d","mm","yyyy");
	d.setFormat(df);
	outputfile << "d-mm-yyyy                           :  " << d << endl;  	//prints in the new set format 
	df = DateFormat("d","mm","0");
	d.setFormat(df);
	outputfile << "d-mm-0                              :  " << d << endl;  //prints in the new set format 

	df = DateFormat("d","m","yy");
	d.setFormat(df);
	outputfile << "d-m-yy                              :  " << d << endl;	//prints in default set format dd/mmm/yy
	df = DateFormat("d","m","yyyy");
	d.setFormat(df);
	outputfile << "d-m-yyyy                            :  " << d << endl;  //prints in the new set format 
	df = DateFormat("d","m","0");
	d.setFormat(df);
	outputfile << "d-m-0                               :  " << d << endl;  //prints in the new set format 

	df = DateFormat("d","0","yy");
	d.setFormat(df);
	outputfile << "d-0-yy                              :  " << d << endl;	//prints in default set format dd/mmm/yy
	df = DateFormat("d","0","yyyy");
	d.setFormat(df);
	outputfile << "d-0-yyyy                            :  " << d << endl;  //prints in the new set format 
	df = DateFormat("d","0","0");
	d.setFormat(df);
	outputfile << "d-0-0                               :  " << d << endl;  //prints in the new set format 

	/*--------------------*/

	outputfile << "0-mmm-yy                            :  " << d << endl;		//prints in default set format dd/mmm/yy
	df = DateFormat("0","mmm","yyyy");
	d.setFormat(df);
	outputfile << "0-mmm-yyyy                          :  " << d << endl;  //prints in the new set format 
	df = DateFormat("0","mmm","0");
	d.setFormat(df);
	outputfile << "0-mmm-0                             :  " << d << endl;  //prints in the new set format 

	df = DateFormat("0","mm","yy");
	d.setFormat(df);
	outputfile << "0-mm-yy                             :  " << d << endl;	//prints in default set format dd/mmm/yy
	df = DateFormat("0","mm","yyyy");
	d.setFormat(df);
	outputfile << "0-mm-yyyy                           :  " << d << endl;  	//prints in the new set format 
	df = DateFormat("0","mm","0");
	d.setFormat(df);
	outputfile << "0-mm-0                              :  " << d << endl;  //prints in the new set format 

	df = DateFormat("0","m","yy");
	d.setFormat(df);
	outputfile << "0-m-yy                              :  " << d << endl;	//prints in default set format dd/mmm/yy
	df = DateFormat("0","m","yyyy");
	d.setFormat(df);
	outputfile << "0-m-yyyy                            :  " << d << endl;  //prints in the new set format 
	df = DateFormat("0","m","0");
	d.setFormat(df);
	outputfile << "0-m-0                               :  " << d << endl;  //prints in the new set format 

	df = DateFormat("0","0","yy");
	d.setFormat(df);
	outputfile << "0-0-yy                              :  " << d << endl;	//prints in default set format dd/mmm/yy
	df = DateFormat("0","0","yyyy");
	d.setFormat(df);
	outputfile << "0-0-yyyy                            :  " << d << endl;  //prints in the new set format 
	df = DateFormat("0","0","0");
	d.setFormat(df);
	outputfile << "0-0-0                               :  " << d << endl;  //prints in the new set format 	
}