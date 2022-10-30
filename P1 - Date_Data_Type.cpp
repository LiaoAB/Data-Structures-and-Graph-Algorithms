#include<iostream>
#include<sstream>

using namespace std;

class date{
	public:		
		/* define Date */
		struct Date{
			unsigned int day, month, year;
		};
		
		/* days of every month (not leap year) */
		const int nLM[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		
		/* name of every month */
		string Month[12] = {
				"January",
			    "February",
				"March",
			    "April",
			    "May",
			    "June",
			    "July",
			    "August",
			    "September",
			    "October",
			    "November",
			    "December"
			};
		
		/* count how many leap years */
		int countLeapYears(unsigned int year, unsigned int month){	 
			/* check if the current year needs to be considered or not */
			if (month <= 2)
		        year--; 
			/* return how many leap years */
			return year / 4 - year / 100 + year / 400;
		}
		
		/* check if year is leap year */
		bool isLeapYear(unsigned int year){
			if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)){
					return true;
				}
				else{
					return false;
				}
		}
			
		/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
		void DayOfWeek(string date){	
		
			Date d;
			
			/* part year, month, day out from input string */
			istringstream yy(date.substr(0,4));	
			yy >> d.year;
			istringstream mm(date.substr(5,2));	
			mm >> d.month;
			istringstream dd(date.substr(8,2));
			dd >> d.day;
			
			/* save month, year variable */		
			int _month = d.month;
			int _year = d.year;
			
			/* count how many days are there */
			int leapYears = countLeapYears(d.year, d.month);
			d.month = (d.month + 9) % 12;
			d.year -= d.month / 10;
			unsigned int day_num = 365 * d.year + leapYears + (d.month * 306 + 5) / 10 + d.day;
			
			string week_day[] = {
				"Tuesday",
			    "Wednesday",
			    "Thursday",
			    "Friday",
			    "Saturday",
			    "Sunday",
			    "Monday"
			};
			
			/* output */
			cout << Month[_month - 1] << " "<< d.day << ", " << _year << " is " << week_day[day_num % 7] << endl;
		}
		
		/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
		
		void DateSub(string date){
			Date d1;
			Date d2;
			
			/* part year1, month1, day1 out from input string */
			istringstream yy1(date.substr(0,4));	
			yy1 >> d1.year;
			istringstream mm1(date.substr(5,2));	
			mm1 >> d1.month;
			istringstream dd1(date.substr(8,2));
			dd1 >> d1.day;
			
			/* part year2, month2, day2 out from input string */
			istringstream yy2(date.substr(11,4));	
			yy2 >> d2.year;
			istringstream mm2(date.substr(16,2));	
			mm2 >> d2.month;
			istringstream dd2(date.substr(19,2));
			dd2 >> d2.day;
			
			/* count days of date1 */
			unsigned int n1 = d1.year * 365 + d1.day;
			for (int i = 0; i < d1.month - 1; i++){
				n1 += nLM[i];
			}
			n1 += countLeapYears(d1.year, d1.month);
			
			/* count days of date2 */
			unsigned int n2 = d2.year * 365 + d2.day;
			for (int i = 0; i < d2.month - 1; i++){
				n2 += nLM[i];
			}
			n2 += countLeapYears(d2.year, d2.month);
			
			/* calculate days between two dates */
			unsigned int gap = n1 - n2;
			
			/* output */
       		cout << gap << " days from "<<  Month[d1.month - 1] << " "<< d1.day << ", " << d1.year << " to " <<  Month[d2.month - 1] << " "<< d2.day << ", " << d2.year << endl; 
		}
		
		/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
		
		void DateAdd(string date){
			Date d;
			long long x;
			
			/* part year, month, day, x out from input string */
			istringstream yy(date.substr(0,4));	
			yy >> d.year;
			istringstream mm(date.substr(5,2));	
			mm >> d.month;
			istringstream dd(date.substr(8,2));
			dd >> d.day;
			int pos = date.find("+");
			istringstream xx(date.substr(pos + 1));	
			xx >> x;
			
			/* save month, year, day, x variable */
			unsigned int _year = d.year;
			unsigned int _month = d.month;
			unsigned int _day = d.day;
			long long _x = x;
			
			while (x > 0)
			{
				/* not leap year February */
				if (d.day == 28 && d.month == 2 && !isLeapYear(d.year))
				{
					d.day = 1;
					d.month++;
				}
				/* leap year February */
				else if (d.day == 29 && d.month == 2 && isLeapYear(d.year))
				{
					d.day = 1;
					d.month++;
				}
				/* small month */
				else if (d.day == 30 && (d.month == 2 || d.month == 4 || d.month == 6 || d.month == 9 || d.month == 11))
				{
					d.day = 1;
					d.month++;
				}
				/* big month */
				else if (d.day == 31 && (d.month == 1 || d.month == 3 || d.month == 5 || d.month == 7 || d.month == 8 || d.month == 10 || d.month == 12))
				{
					d.day = 1;
					d.month++;
				}
				/* normal day */
				else
				{
					d.day++;
				}
				/* year */
				if (d.month == 13)
				{
					d.month = 1;
					d.year++;
				}
				x--;
			}
			/* output */
			cout <<	_x <<" days after " <<  Month[_month - 1] << " "<< _day << ", " << _year << " is "<< Month[d.month - 1] << " "<< d.day << ", " << d.year << endl;	
		}			
};

int main(){
	date date;
	int num;
	string x;
	
	cout << "Input 1 to check which day of week is your date." << endl;
	cout << "Input 2 to do date subtraction." << endl;
	cout << "Input 3 to add day to date." << endl;	
	cin >> num;
	if (num == 1){
		cout << "Please input yyyy/mm/dd" << endl;
		cin >> x;
		date.DayOfWeek(x);
	}
	else if (num == 2){
		cout << "Please input yyyy/mm/dd-YYYY/MM/DD" << endl;
		cin >> x;
		date.DateSub(x);
	}
	else if (num == 3){
		cout << "Please input yyyy/mm/dd+x" << endl;
		cin >> x;
		date.DateAdd(x);
	}
	else{
		cout << "Invalid input" << endl;
	}
}

