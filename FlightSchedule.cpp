// FlightSchedule.cpp
// Member-function definitions for class FlightSchedule.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "FlightSchedule.h" // FlightSchedule class definition
using namespace std;

// FlightSchedule default constructor loads flight schedule from the file Flight Schedule.dat
FlightSchedule::FlightSchedule()
{
   loadFlightSchedule();
}

FlightSchedule::~FlightSchedule()
{
}

int FlightSchedule::getDepartureAirport( string flightNo )
{
   vector< Flight >::iterator it = getFlight( flightNo );

   if( it != flights.end() )
      return it->getDepartureAirport();

   return 0;
}

int FlightSchedule::getArrivalAirport( string flightNo )
{
   vector< Flight >::iterator it = getFlight( flightNo );

   if( it != flights.end() )
      return it->getArrivalAirport();

   return 0;
}

string FlightSchedule::getDepartureTime( string flightNo )
{
   vector< Flight >::iterator it = getFlight( flightNo );

   return it->getDepartureTime();
}

string FlightSchedule::getArrivalTime( string flightNo )
{
   vector< Flight >::iterator it = getFlight( flightNo );

   return it->getArrivalTime();
}

bool FlightSchedule::exist( string flightNo, int departureAirport, int arrivalAirport )
{
	vector<Flight>::iterator p1 = getFlight(flightNo);
	if (p1->getDepartureAirport() == departureAirport && p1->getArrivalAirport() == arrivalAirport)
		return true;
	else
		return false;
}

void FlightSchedule::display( int departureAirport, int arrivalAirport, string date )
{
	cout << "Flight   Departure   Arrival   Fare" << endl;
	for (int i = 0; i < flights.size(); i++)
	{
		if (flights[i].getDepartureAirport() == departureAirport && flights[i].getArrivalAirport() == arrivalAirport)
			cout << setw(6) <<flights[i].getFlightNo() << setw(12) << right << flights[i].getDepartureTime() << setw(10) << right << flights[i].getArrivalTime() << setw(7) << right << fullFare[flights[i].getDepartureAirport()][flights[i].getArrivalAirport()] << endl;
	}
	cout << endl;
}

vector< Flight >::iterator FlightSchedule::getFlight( string flightNo )
{
   // loop through flightSchedule searching for matching flight number
   for( vector< Flight >::iterator it = flights.begin(); it != flights.end(); ++it )
      if( it->getFlightNo() == flightNo ) // ( it.operator->() )->getFlightNo()
         return it;

   return flights.end(); // if no matching flight was found, return flights.end()
}

void FlightSchedule::loadFlightSchedule()
{
	ifstream inFile("Flight Schedule.dat", ios::binary);
	Flight f;
	//SingleFlight f;
	while (inFile.read((char *)&f, sizeof(f)))
	{
		//Flight flight(f.flightNo, f.departureAirport, f.arrivalAirport, f.departureTime, f.arrivalTime);
		flights.push_back(f);
	}
	inFile.close();
}