// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "ReservationDatabase.h" // ReservationDatabase class definition
#include "FlightSchedule.h" // FlightSchedule class definition

// ReservationDatabase default constructor loads flight reservations from the file Reservations.dat
ReservationDatabase::ReservationDatabase()
{
   loadReservations();
}

// ReservationDatabase destructor stores flight reservations into the file Reservations.dat
ReservationDatabase::~ReservationDatabase()
{
   storeReservations();
}

void ReservationDatabase::addReservation( Reservation reservation )
{
   reservations.push_back( reservation );
}

void ReservationDatabase::cancelReservation( string id, int n )
{
	vector<Reservation> buffer;
	for (int i = 0; i < reservations.size(); i++)
	{
		if (reservations[i].getId() == id)
			buffer.push_back(reservations[i]);
	}
			
	vector<Reservation>::iterator p1 = reservations.begin();
	vector<Reservation>::iterator temp = nullptr;
	for (; p1 != reservations.end();)
	{
		temp = p1;
		++p1;
		if (temp->getFlightNo() == buffer[n - 1].getFlightNo())
		{
			reservations.erase(temp);
			break;
		}
	}
} // end function cancelReservation

bool ReservationDatabase::empty()
{
   return ( reservations.size() == 0 );
}

bool ReservationDatabase::existReservation( string id )
{
	//Reservation * currentReservation = getReservation(id);
	for (int i = 0; i < reservations.size(); i++)
		if (reservations[i].getId() == id)
			return true;
	return false;
}

bool ReservationDatabase::existReservation( Reservation reservation )
{
	for (int i = 0; i < reservations.size(); i++)
		if (reservations[i].getFlightNo() == reservation.getFlightNo() && reservations[i].getId() == reservation.getId())
			return true;
	return false;
}

void ReservationDatabase::display( string id )
{
	FlightSchedule fSchedule;
	int find = 0;

	for (int i = 0; i < reservations.size(); i++)
	{
		if (reservations[i].getId() == id)
		{
			find++;

			cout << endl << endl << find << ' ' << '.' << "Ticket information: " << endl;

			int money = 0;

			cout << endl << "Date: " << reservations[i].getDate() << endl;
			cout << "Flight: B7-" << reservations[i].getFlightNo() << endl << endl;

			cout << airportName[fSchedule.getDepartureAirport(reservations[i].getFlightNo())] << " -> " << airportName[fSchedule.getArrivalAirport(reservations[i].getFlightNo())] << endl;
			cout << fSchedule.getDepartureTime(reservations[i].getFlightNo()) << setw(8) << fSchedule.getArrivalTime(reservations[i].getFlightNo()) << endl << endl;

			int fare = fullFare[fSchedule.getDepartureAirport(reservations[i].getFlightNo())][fSchedule.getArrivalAirport(reservations[i].getFlightNo())];

			if (reservations[i].getTicket(1) != 0)
			{
				cout << setw(30) << right << "Full Fare " << " TWD " << fare * (discount[1] / 100.f) << " x " << reservations[i].getTicket(1) << endl;
				money += fare * reservations[i].getTicket(1) * (discount[1] / 100.f);
			}
			if (reservations[i].getTicket(2) != 0)
			{
				cout << setw(30) << right << "Child Fare " << " TWD " << fare * (discount[2] / 100.f) << " x " << reservations[i].getTicket(2) << endl;
				money += fare * reservations[i].getTicket(2) * (discount[2] / 100.f);
			}
			if (reservations[i].getTicket(3) != 0)
			{
				cout << setw(30) << right << "Infant Fare " << " TWD " << fare * (discount[3] / 100.f) << " x " << reservations[i].getTicket(3) << endl;
				money += fare * reservations[i].getTicket(3) * (discount[3] / 100.f);
			}
			if (reservations[i].getTicket(4) != 0)
			{
				cout << setw(30) << right << "Senior Citizen Fare " << " TWD " << fare * (discount[4] / 100.f) << " x " << reservations[i].getTicket(4) << endl;
				money += fare * reservations[i].getTicket(4) * (discount[4] / 100.f);
			}
			if (reservations[i].getTicket(5) != 0)
			{
				cout << setw(30) << right << "Impaired Fare " << " TWD " << fare * (discount[5] / 100.f) << " x " << reservations[i].getTicket(5) << endl;
				money += fare * reservations[i].getTicket(5) * (discount[5] / 100.f);
			}
			if (reservations[i].getTicket(6) != 0)
			{
				cout << setw(30) << right << "Impaired Companion Fare " << " TWD " << fare * (discount[6] / 100.f) << " x " << reservations[i].getTicket(6) << endl;
				money += fare * reservations[i].getTicket(6) * (discount[6] / 100.f);
			}
			if (reservations[i].getTicket(7) != 0)
			{
				cout << setw(30) << right << "Military Fare " << " TWD " << fare * (discount[7] / 100.f) << " x " << reservations[i].getTicket(7) << endl;
				money += fare * reservations[i].getTicket(7) * (discount[7] / 100.f);
			}

			cout << "Total: " << money << endl;
		}
	}
}

void ReservationDatabase::loadReservations()
{
	//SingleReservation r;
	Reservation r;
	ifstream inFile("Reservations.dat", ios::binary);
	while (inFile.read((char *)&r, sizeof(r)))
	{
		//Reservation reservation(r.flightNo, r.id, r.name, r.mobile, r.date);
		//reservation.setTickets(r.tickets);
		reservations.push_back(r);
	}
	inFile.close();
}

void ReservationDatabase::storeReservations()
{
	ofstream outFile("Reservations.dat", ios::binary);
	for (int i = 0; i < reservations.size(); i++)
		outFile.write((char *)&reservations[i], sizeof(reservations[i]));

	outFile.close();
}

/*Reservation * ReservationDatabase::getReservation(string id)
{
	for (int i = 0; i < reservations.size(); i++)
		if (reservations[i].getId() == id)
			return &reservations[i];
	return nullptr;
}*/