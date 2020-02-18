// MakingReservation.cpp
// Member-function definitions for class MakingReservation.
#include <iostream>
#include <iomanip>
#include "MakingReservation.h" // MakingReservation class definition

// MakingReservation constructor initializes data members
MakingReservation::MakingReservation( ReservationDatabase &theReservationDatabase,
                                      FlightSchedule &theFlightSchedule )
   : reservationDatabase( theReservationDatabase ),
     flightSchedule( theFlightSchedule )
{
} // end MakingReservation constructor

void MakingReservation::execute()
{
	ReservationDatabase &rDataBase = reservationDatabase;
	FlightSchedule & fDataBase = flightSchedule;

	int departureAirport;
	do {
		cout << "\nDeparture airport:\n";
		for (int i = 1; i <= 12; i++)
			cout << setw(2) << i << ". " << airportName[i] << endl;
		cout << "? ";

		cin >> departureAirport;
	} while (departureAirport < 1 || departureAirport > 12);

	int arrivalAirport;
	// choose arrival airport by input its code, and assign the code to arrivalAirport
	chooseArrivalAirport(departureAirport, arrivalAirport);

	cout << "\nDeparture date (yyyy/mm/dd): ";
	char date[12];
	cin >> date;

	Reservation newRes;
	//rDataBase.addReservation(newRes);

	newRes.setDate(date);
	cout << endl;

	fDataBase.display(departureAirport, arrivalAirport, date);

	cout << "Flight number: ";
	char No[5];
	cin >> No;

	newRes.setFlightNo(No);

	int tickets[8];
	
	inputNumTickets(tickets);
	
	newRes.setTickets(tickets);

	displayReservation(newRes);

	cout << "\nID number: ";
	char id[12];
	cin >> id;
	newRes.setId(id);

	cout << "\nName: ";
	char name[8];
	cin >> name;
	newRes.setName(name);

	cout << "\nMobile: ";
	char mobile[12];
	cin >> mobile;
	newRes.setMobile(mobile);

	rDataBase.addReservation(newRes);

	cout << "\nReservation completed!\n";
}

// choose arrival airport by input its code, and assign the code to arrivalAirport
void MakingReservation::chooseArrivalAirport( int departureAirport, int &arrivalAirport )
{
	cout << "\nArrival airport:\n";
	for (int i = 1; i < 13; i++)
	{
		if (fullFare[departureAirport][i] != 0)
		{
			cout << setw(2) << i << ". " << airportName[i] << endl;
		}
	}
	cout << "? ";
	cin >> arrivalAirport;
}

// input the number of tickets for each ticket type, and assign them to tickets
void MakingReservation::inputNumTickets( int tickets[] )
{
	int infant, full, child, senior, impaired, companion, military;
	int total;

	cout << endl;

	do
	{
		cout << "Number of infant tickets(0 ~4) : ";
		cin >> infant;
		tickets[3] = infant;
	} while (infant > 4 || infant < 0);

	do
	{
		total = 0;
		do
		{
			cout << "Number of full fare tickets(0 ~4) : ";
			cin >> full;
			tickets[1] = full;
		} while (full > 4 || full < 0);
		total += full;

		if (total > 4)
		{
			cout << "You can buy at most 4 tickets in one transaction!" << endl;
			continue;
		}

		do
		{
			cout << "Number of child tickets(0 ~4) : ";
			cin >> child;
			tickets[2] = child;

		} while (child > 4 || child < 0);
		total += child;

		if (total > 4)
		{
			cout << "You can buy at most 4 tickets in one transaction!" << endl;
			continue;
		}

		do
		{
			cout << "Number of senior citizen tickets(0 ~4) : ";
			cin >> senior;
			tickets[4] = senior;
		} while (senior > 4 || senior < 0);
		total += senior;

		if (total > 4)
		{
			cout << "You can buy at most 4 tickets in one transaction!" << endl;
			continue;
		}

		do
		{
			cout << "Number of impaired tickets(0 ~4) : ";
			cin >> impaired;
			tickets[5] = impaired;
		} while (impaired > 4 || impaired < 0);
		total += impaired;

		if (total > 4)
		{
			cout << "You can buy at most 4 tickets in one transaction!" << endl;
			continue;
		}

		do
		{
			cout << "Number of impaired companion tickets(0 ~4) : ";
			cin >> companion;
			tickets[6] = companion;
		} while (companion > 4 || companion < 0);
		total += companion;

		if (total > 4)
		{
			cout << "You can buy at most 4 tickets in one transaction!" << endl;
			continue;
		}

		do
		{
			cout << "Number of military tickets(0 ~4) : ";
			cin >> military;
			tickets[7] = military;
		} while (military > 4 || military < 0);
		total += military;

		if (total > 4)
		{
			cout << "You can buy at most 4 tickets in one transaction!" << endl;
			continue;
		}

	} while (total > 4 || total < 1);
}

void MakingReservation::displayReservation( Reservation reservation )
{
	int money = 0;

	cout << endl << "Date: " << reservation.getDate() << endl;
	cout << "Flight: B7-" << reservation.getFlightNo() << endl << endl;

	cout << airportName[flightSchedule.getDepartureAirport(reservation.getFlightNo())] << " -> " << airportName[flightSchedule.getArrivalAirport(reservation.getFlightNo())] << endl;
	cout << flightSchedule.getDepartureTime(reservation.getFlightNo()) << setw(8) << flightSchedule.getArrivalTime(reservation.getFlightNo()) << endl << endl;

	int fare = fullFare[flightSchedule.getDepartureAirport(reservation.getFlightNo())][flightSchedule.getArrivalAirport(reservation.getFlightNo())];

	if (reservation.getTicket(1) != 0)
	{
		cout << setw(30) << right << "Full Fare " << " TWD " << fare * (discount[1] / 100.f) << " x " << reservation.getTicket(1) << endl;
		money += fare * reservation.getTicket(1) * (discount[1] / 100.f);
	}
	if (reservation.getTicket(2) != 0)
	{
		cout << setw(30) << right << "Child Fare " << " TWD " << fare * (discount[2] / 100.f) << " x " << reservation.getTicket(2) << endl;
		money += fare * reservation.getTicket(2) * (discount[2] / 100.f);
	}
	if (reservation.getTicket(3) != 0)
	{
		cout << setw(30) << right << "Infant Fare " << " TWD " << fare * (discount[3] / 100.f) << " x " << reservation.getTicket(3) << endl;
		money += fare * reservation.getTicket(3) * (discount[3] / 100.f);
	}
	if (reservation.getTicket(4) != 0)
	{
		cout << setw(30) << right << "Senior Citizen Fare " << " TWD " << fare * (discount[4] / 100.f) << " x " << reservation.getTicket(4) << endl;
		money += fare * reservation.getTicket(4) * (discount[4] / 100.f);
	}
	if (reservation.getTicket(5) != 0)
	{
		cout << setw(30) << right << "Impaired Fare " << " TWD " << fare * (discount[5] / 100.f) << " x " << reservation.getTicket(5) << endl;
		money += fare * reservation.getTicket(5) * (discount[5] / 100.f);
	}
	if (reservation.getTicket(6) != 0)
	{
		cout << setw(30) << right << "Impaired Companion Fare " << " TWD " << fare * (discount[6] / 100.f) << " x " << reservation.getTicket(6) << endl;
		money += fare * reservation.getTicket(6) * (discount[6] / 100.f);
	}
	if (reservation.getTicket(7) != 0)
	{
		cout << setw(30) << right << "Military Fare " << " TWD " << fare * (discount[7] / 100.f) << " x " << reservation.getTicket(7) << endl;
		money += fare * reservation.getTicket(7) * (discount[7] / 100.f);
	}

	cout << "Total: " << money << endl;
	
}