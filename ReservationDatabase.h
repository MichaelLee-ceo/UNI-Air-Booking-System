// ReservationDatabase.h
// ReservationDatabase class definition. Represents the reservation database.
#ifndef RESERVATION_DATABASE_H
#define RESERVATION_DATABASE_H

#include "Vector.h"
//#include <vector>
#include "Reservation.h" // Reservation class definition

extern const int discount[ 8 ];

struct SingleReservation
{
	char flightNo[8]; // flight number
	char id[12];      // id number
	char name[8];     // name
	char mobile[12];  // mobile phone number
	char date[12];    // departure date
	int tickets[8];
};

class ReservationDatabase
{
public:
   ReservationDatabase(); // calls loadReservations()

   ~ReservationDatabase(); // calls storeReservations()

   void addReservation( Reservation reservation ); // add a reservation at the end of reservations

   // cancels the n-th reservation object containing specified id
   void cancelReservation( string id, int n );

   bool empty(); // check if reservations.size() is 0

   // return true if and only if there exists a Reservation object containing specified id
   bool existReservation( string id );

   bool existReservation( Reservation reservation );

   // display the information of all reservations containing specified id
   void display( string id );

private:
   vector< Reservation > reservations; // vector of the flight reservations
   //Reservation * getReservation(string id);
   void loadReservations(); // loads flight reservations from the file Reservations.dat
   void storeReservations(); // stores flight reservations into the file Reservations.dat
}; // end class ReservationDatabase

#endif // RESERVATION_DATABASE_H