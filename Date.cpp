/*Date.h - Implementation file*/

#include <stdio.h>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include "Date.h"

using namespace std;

DateFormat Date::format;

Date w;

/* DateFormat class implementation begins */

DateFormat::DateFormat(const char* dateFormat, const char* monthFormat, const char* yearFormat){
	DateFormat::init(dateFormat, monthFormat, yearFormat);   //initialises the parameters
}

//allocates memory, initialises the private fields
void DateFormat::init(const char* dateFormat, const char* monthFormat, const char* yearFormat){
	if(!ValidDateFormat(dateFormat,monthFormat,yearFormat)){     
		throw invalid_argument("Invalid date format");			//Invalid format exception thrown
	}
	this->dateFormat = new char[strlen(dateFormat) + 1];        //allocates memory
	this->monthFormat = new char[strlen(monthFormat) + 1];
	this->yearFormat = new char[strlen(yearFormat) + 1];
	if(dateFormat != NULL)
		strcpy(this->dateFormat, dateFormat);					//copies memory
	else{
		delete this->dateFormat;								//deletes unused memory
		this->dateFormat = NULL;
	}
	if(monthFormat != NULL)
		strcpy(this->monthFormat, monthFormat);					//copies memory	
	else{
		delete this->monthFormat;								//deletes unused memory
		this->monthFormat = NULL;
	}
	if(yearFormat != NULL)
		strcpy(this->yearFormat, yearFormat);					//copies memory
	else{
		delete this->yearFormat;								//deletes unused memory
		this->yearFormat = NULL;
	}
}

//Take a format string and set the data members
DateFormat::DateFormat(const char* format){
	char *cpy, *temp, *dateFormat, *monthFormat , *yearFormat;
	cpy = new char[strlen(format)+1];
	strcpy(cpy, format);										//splits the string wrt "-"
	dateFormat = strtok (cpy,"-");
	monthFormat = strtok(NULL,"-");
	yearFormat = strtok(NULL,"-");
	if(yearFormat == NULL)										//checks validity of input
		throw invalid_argument("Invalid date format");
	DateFormat::init(dateFormat,monthFormat,yearFormat);		//initialises the parameters
}

//Default constructor
DateFormat::DateFormat(){
	DateFormat::init("dd","mmm","yy");
}

//Checks if the format is valid
bool DateFormat::ValidDateFormat(const char* dateFormat, const char* monthFormat, const char* yearFormat) const{
	//checks date format
	if(!(strcmp(dateFormat,"0")==0 || strcmp(dateFormat,"d")==0 || strcmp(dateFormat,"dd")==0 )){
		return false;
	}
	//checks month format
	if(!(strcmp(monthFormat,"0")==0 || strcmp(monthFormat,"m")==0 || strcmp(monthFormat,"mm")==0 || strcmp(monthFormat,"mmm")==0 )){
		return false;
	}
	//checks year format
	if(!(strcmp(yearFormat,"0")==0 || strcmp(yearFormat,"yy")==0 || strcmp(yearFormat,"yyyy")==0 )){
		return false;
	}
	//all tests passed
	return true;
}

//Getter methods
char* DateFormat::getDateFormat(){
	return this->dateFormat;
}

char* DateFormat::getMonthFormat(){
	return this->monthFormat;
}

char* DateFormat::getYearFormat(){
	return this->yearFormat;
}

//Assignment operator
DateFormat const& DateFormat::operator=(DateFormat const& d){
	if(this == &d)  	//self assignement exception
		return d;
	delete this->dateFormat;    //deallocates unused memory
	delete this->monthFormat;
	delete this->yearFormat;
	DateFormat::init(d.dateFormat, d.monthFormat, d.yearFormat);   //initailises the parameters
	return *this;				
}

//Destructor
DateFormat::~DateFormat(){}
/* DateFormat class implementation ends */

/* Date class implementation begins */

Date::Date(Day d, Month m, Year y) 
throw(invalid_argument, domain_error, out_of_range)
{
	Date::init(d,m,y);      	//initialises the values
}

bool IsValidInt(char* x)		//checks if the character array corresponds to an integer
{
	bool Checked = true;
	int i = 0;
	do{
		if (isdigit(x[i])){   	//checks digit by digit
			i++;
			Checked = true;
		}
		else{
			i++;
			Checked = false;
			break;
		}
	} while (x[i] != '\0');
	return Checked;
}

//initialises the parameters
void Date::init(Day d, Month m, Year y)
throw(invalid_argument, domain_error, out_of_range)
{
	if(!ValidDomain(d,m,y))		//checks domain
		throw domain_error("Domain error: not a valid date");
	if(OutOfRange(y))			//checks range
		throw out_of_range("Out of range");
	this->day = d;
	this->month = m;
	this->year = y;	
	this->wd = static_cast<WeekDay>(Date::dayofweek(d,m,y));
}

//cast operator
//calculates the week number of a date
Date::operator WeekNumber() const{
	Date dt1(*this);
	Date dt(static_cast<Day>(1),static_cast<Month>(1),static_cast<Year>(this->year));	//referent
	if(WeekDay(*this)<4){				//case 1
		Date temp(*this);
		while(WeekDay(++temp)!=4);
		if(temp.year!=this->year)		//first week
			return static_cast<WeekNumber>(1);
	}
	if(WeekDay(dt)>4){					//move to case 2
		while(WeekDay(dt)!=1)
			++dt;
		if(dt1<dt){
			Date temp(static_cast<Day>(1),static_cast<Month>(1),static_cast<Year>(this->year-1));
			dt = temp;
			if(WeekDay(dt)>4)			//internal case 1
				while(WeekDay(++dt)!=1);
			else						//internal case 2
				while(WeekDay(--dt)!=1);				
		}
	}
	else{
		while(WeekDay(dt)!=1)
			--dt;
	}
	int i = (dt1-dt)/7+1;			//weeknumber for the appropriate date, 1 corresponds to first week
	return static_cast<WeekNumber>(i) ;
}

//calculates the next date
inline Date nextDate(const Date& D){
	int d = D.day;
	int m = D.month;
	int y = D.year;
	Date newD;
	if(D.ValidDomain(d+1,m,y))		//three step validation, first day increment
		newD = Date(static_cast<Day>(d+1),D.month,D.year);
	else if(D.ValidDomain(1,m+1,D.year))	//then month
		newD = Date(D01,static_cast<Month>(m+1),D.year);
	else if(!D.OutOfRange(y))				//then year
		newD = Date(D01,Jan,static_cast<Year>(y+1));
	else									//finally exception
		throw out_of_range("New Date is out of range");
	return newD;	
}

inline Date prevDate(const Date& D){
	int d = D.day;
	int m = D.month;
	int y = D.year;
	Date newD;
	if(D.ValidDomain(d-1,m,y))			//three stage validation, first day
		newD = Date(static_cast<Day>(d-1), D.month, D.year);
	else if(D.ValidDomain(31, m-1, y))	//then month
		newD = Date(D31, static_cast<Month>(m-1), D.year);
	else if(D.ValidDomain(30, m-1, y))
		newD = Date(D30, static_cast<Month>(m-1), D.year);
	else if(D.ValidDomain(29, m-1, y))
		newD = Date(D29, static_cast<Month>(m-1), D.year);
	else if(D.ValidDomain(28, m-1, y))
		newD = Date(D28, static_cast<Month>(m-1), D.year);
	else if(!D.OutOfRange(y-1))			//finally year
		newD = Date(D31, Dec, D.year-1);
	else								//Out of range
		throw out_of_range("New Date is out of range");
	return newD;
}

//returns the day of the week
int Date::dayofweek(int d, int m, int y) const{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    if(m<3)
    	y--;
    return ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

//default constructor
Date::Date()
throw(domain_error, out_of_range)
{
	time_t t = time(0);					//takes current time from the system  
    struct tm * now = localtime(&t);
	int day = now->tm_mday;
	int month = now->tm_mon + 1;
	int year = now->tm_year + 1900;
	if(!ValidDomain(day,month,year))	//checks domain validity
		throw domain_error("Date is not valid");
	if(OutOfRange(year))				//checks range validity
		throw out_of_range("Date is out of range");
	this->day = static_cast<Day>(day);
	this->month = static_cast<Month>(month);
	this->year = year;
	this->wd = static_cast<WeekDay>(Date::dayofweek(day,month,year));
}

//copy constructor
Date::Date(const Date& q){
	this->day = q.day;
	this->month = q.month;
	this->year = q.year;
	this->wd = q.wd;
}

//destructor
Date::~Date(){}

//assignment operator
Date& Date::operator=(const Date& q){
	this->day = q.day;
	this->month = q.month;
	this->year = q.year;
	this->wd = q.wd;
	return *this;
}

//uses nextDate to compute the next date
//prefix operator
Date& Date::operator++(){
	*this = nextDate(*this);
	return *this;
}

//uses operator++ to calculate same day next week
//post fix operator
Date& Date::operator++(int){
	w = *this;
	for(int i=0;i<7;i++)
		++(*this);
	return w;
}	

//uses prevDate to compute the next date
//prefix operator
Date& Date::operator--(int){
	w = *this;
	for(int i=0;i<7;i++)
		--(*this);
	return w;
}

//uses operator++ to calculate same day next week
//post fix operator
Date& Date::operator--(){
	*this = prevDate(*this);
	return *this;
}

//checks if date is between 1949 & 2051
bool Date::OutOfRange(int year) const {
	if(year>2049 || year < 1950)
		return true;
	else
		return false;
}

//checks domain validity
bool Date::ValidDomain(int day, int month, int year) const {
	if (year <0)
		return false;
	if (month >12 || month <1)
		return false;
	if (day >31 || day <1)
		return false;
	if ((day ==31 &&
	(month ==2 || month ==4 || month ==6 || month ==9 || month ==11) ) )
		return false;
	if (day ==30 && month ==2)
		return false;
	if (year <2000){
	if ((day==29 && month==2) && !((year -1900)%4==0))
		return false;
	}
	if (year >2000){
	if ((day ==29 && month ==2) && !((year -2000)%4==0))
		return false;
	}
	return true;
}

//cout number of leap years till a month & year
inline int countLeapYears(int month, int years)
{
    if (month <= 2)
        years--;
    return years / 4 - years / 100 + years / 400;
}

//returns number of days between two dates
unsigned int Date::operator-(const Date& otherDate){
	const int monthDays[12] = {31, 28, 31, 30, 31, 30,
                           	   31, 31, 30, 31, 30, 31};
	const Date& dt1 = (*this); 
	const Date& dt2 = otherDate;	                           	   
	long int n1 = dt1.year*365 + dt1.day;
    for (int i=0; i<dt1.month - 1; i++)
        n1 += monthDays[i];
    n1 += countLeapYears(dt1.month, dt1.year);		//no. of days since base value
    long int n2 = dt2.year*365 + dt2.day;
    for (int i=0; i<dt2.month - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2.month, dt2.year);		//no. of days since base value
    return abs(n2 - n1);							//returns the difference
}

//checks date equality
bool Date::operator==(const Date& otherDate){
	if(this->day == otherDate.day && this->month == otherDate.month && this->year == otherDate.year)
		return true;
	else
		return false;
}

//checks date non-equality
bool Date::operator!=(const Date& otherDate){
	return !((*this)==otherDate);
}

//checks if given date appears before argument date
bool Date::operator<(const Date& dt2){
	Date &dt1 = *this;
	if(dt1.year < dt2.year)
		return true;
	else if(dt1.year > dt2.year)
		return false;
	else{
		if(dt1.month < dt2.month)
			return true;
		else if(dt1.month > dt2.month)
			return false;
		else{
			if(dt1.day < dt2.day)
				return true;
			else
				return false;
		}
	}
}

//checks if given date appears before argument date + equality check
bool Date::operator<=(const Date& dt){
	return (*this < dt) || (*this == dt);	
}

//checks if given date appears after argument date
bool Date::operator>(const Date& dt){
	return !(*this <= dt);
}

//checks if given date appears after argument date + equality check
bool Date::operator>=(const Date& dt){
	return !(*this < dt);
}

//calculates new date after a particular number of days
Date Date::operator+(int noOfDays) 
throw(domain_error, out_of_range)
{
	bool flag = true;
	if(noOfDays < 0)
		flag = false;
	Date newD = *this;
	for(int i = 0; i < abs(noOfDays); i++){
		if(flag)
			++newD;
		else
			--newD;
	}
	return newD;
}

//checks if a date is leapyear
bool Date::leapYear() const{
	if((this->year % 4 == 0 && this->year % 100 != 0) || this->year % 400 == 0)
		return true;
	else
		return false;
}

//cast to weekday
Date::operator WeekDay() const{
	return this->wd;
}

//cast to month
Date::operator Month() const{
	return this->month;
}

//sets the format
void Date::setFormat(DateFormat& d){
	format = d;
}

//gets the static format
DateFormat& Date::getFormat(){
	return format;
}

//sets a date string 
void Date::setstrdate(const char* date)
throw(invalid_argument, domain_error, out_of_range)
{
	if(strcmp("X",date)==0)				//checks exceptional cases
		throw invalid_argument("X");
	if(strcmp("0",format.getDateFormat())==0 || strcmp("0",format.getMonthFormat())==0 
		|| strcmp("mmm",format.getMonthFormat())==0 || strcmp("0",format.getYearFormat())==0){
		throw invalid_argument("Invalid argument: Input not allowed for this format");
	}
	char *cpy ,*day, *month, *year;		
	cpy = new char[strlen(date)+1];		//copies into a new string to apply strtok
	strcpy(cpy, date);
	day = strtok (cpy,"-");
	month = strtok(NULL,"-");
	year = strtok(NULL,"-");		
	if(year == NULL)					//checks if string has atleast two hyphens
		throw invalid_argument("Invalid argument: Not a valid date");
	if(!IsValidInt(day)||!IsValidInt(month)||!IsValidInt(year))		//checks the the splits are integers
		throw invalid_argument("Invalid argument: Contains non-integral strings");
	char* x0 = new char[2];
	char* x1 = new char[2];	
	strcpy(x0,"19");
	strcpy(x1,"20");			//special format cases
	if(strcmp(format.getYearFormat(),"yyyy")==0){
		if(strlen(year)!=4)
			throw invalid_argument("Invalid argument: Not in proper format");
	}
	if(strcmp(format.getYearFormat(),"yy")==0){		//special exception cases
		if(strlen(year)!=2)
			throw invalid_argument("Invalid argument: Not in proper format");
	}
	if(strcmp(format.getDateFormat(),"d")==0){
		if(strlen(day)==2 && atoi(day)/10 < 1){
			throw invalid_argument("Invalid argument: Not in proper format");
		}
	}
	if(strcmp(format.getDateFormat(),"m")==0){
		if(strlen(month)==2 && atoi(month)/10 < 1){
			throw invalid_argument("Invalid argument: Not in proper format");
		}
	}
	if(strcmp(format.getDateFormat(),"dd")==0){
		if(strlen(day)<2)
			throw invalid_argument("Invalid argument: Not in proper format");
	}
	if(atoi(year)/100 == 0){		//if last two digits of an year is entered
		if(atoi(year) > 49)
			year = strcat(x0,year);
		else
			year = strcat(x1,year);
	}
	Day d = static_cast<Day>(atoi(day));		//initialises
	Month m = static_cast<Month>(atoi(month));
	Year y = static_cast<Year>(atoi(year));
	Date::init(d,m,y);
}

//validates and assign date string
Date::Date(const char* date)
throw(invalid_argument, domain_error, out_of_range){
	Date::setstrdate(date);
}

//takes date object as input
istream& operator>>(istream& is, Date& d){
	char* ch = new char[10];
	is >> ch;
	d.setstrdate(ch);
	return is;
}

//outputs a date object in a particular format
ostream& operator<<(ostream& os, const Date& d){
	char const* p[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	char const* q[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	DateFormat& format = d.getFormat();
	char *dateFormat = format.getDateFormat();
	char *monthFormat = format.getMonthFormat();
	char *yearFormat = format.getYearFormat();
	//checks the corresponding formats and outputs corresponding to that
	if(strcmp("0",dateFormat)==0){
	}
	else if(strcmp("d",dateFormat)==0){
		os << d.day << "-";
	}
	else if(strcmp("dd",dateFormat)==0){
		if(d.day/10 > 0)
			os << d.day << "-";
		else
			os << "0" << d.day << "-";
	}
	if(strcmp("0",monthFormat)==0){
		os << p[d.month-1];
	}
	else if(strcmp("m",monthFormat)==0){
		os << d.month;
	}
	else if(strcmp("mm",monthFormat)==0){
		if(d.month/10 > 0)
			os << d.month;
		else
			os << "0" << d.month;
	}
	else if(strcmp("mmm",monthFormat)==0){
		// printf("%.*s", 3, p[d.month-1]);
		os << q[d.month-1];
	}
	if(strcmp("0",yearFormat)==0){
	}
	else if(strcmp("yy",yearFormat) == 0){
		if(d.year - 100*(d.year/100) > 9)
			os << "-" << d.year - 100*(d.year/100);
		else
			os << "-0" << d.year - 100*(d.year/100);
	}
	else if(strcmp("yyyy", yearFormat) == 0){
		os << "-" << d.year;
	}
	return os;			//returns for further linkages
}