#include <iostream>
#include "MakingReservation.h" // MakingReservation class definition
#include "InquiryRefund.h" // InquiryRefund class definition

const char airportName[ 13 ][ 12 ] = { "", "Taipei",    "Taichung", "Chiayi",  "Tainan",
                                           "Kaohsiung", "Henchun",  "Hualien", "Taitung",
                                           "Penghu",    "Kinmen",   "Beigan",  "Nangan" };

// row 0 and column 0 are not used,
// fullFare[ i ][ j ] is the full fare from airport i to airport j
const int fullFare[ 13 ][ 13 ] = {
   { 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
   { 0,    0,    0,    0,    0,    0, 2433, 1663, 2280, 2098, 2298, 2007, 2007 },
   { 0,    0,    0,    0,    0,    0,    0,    0,    0, 1640, 2038,    0, 2455 },
   { 0,    0,    0,    0,    0,    0,    0,    0,    0, 1621, 2031,    0,    0 },
   { 0,    0,    0,    0,    0,    0,    0,    0,    0, 1590, 2039,    0,    0 },
   { 0,    0,    0,    0,    0,    0,    0,    0,    0, 1748, 2174,    0,    0 },
   { 0, 2433,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
   { 0, 1663,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
   { 0, 2280,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
   { 0, 2098, 1640, 1621, 1590, 1748,    0,    0,    0,    0, 1600,    0,    0 },
   { 0, 2298, 2038, 2031, 2039, 2174,    0,    0,    0, 1600,    0,    0,    0 },
   { 0, 2007,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
   { 0, 2007, 2455,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 } };

const int discount[ 8 ] = { 0, 100, 75, 0, 50, 50, 50, 95 };
// discount[ 0 ]: not used
// discount[ 1 ]: Full Fare Ticket
// discount[ 2 ]: Child Ticket:              25% off of the full fare
// discount[ 3 ]: Infant Ticket:             Free of charge
// discount[ 4 ]: Senior Citizen Ticket:     50% off of the full fare
// discount[ 5 ]: Impaired Ticket:           50% off of the full fare
// discount[ 6 ]: Impaired Companion Ticket: 50% off of the full fare
// discount[ 7 ]: Military Ticket:            5% off of the full fare

int enterChoice();

int main()
{
   cout << "Welcome to the TransAsia Airways Flight Reservation System\n";

   ReservationDatabase reservationDatabase;
   FlightSchedule flightSchedule;
   MakingReservation makingReservation( reservationDatabase, flightSchedule );
   InquiryRefund inquiryRefund( reservationDatabase, flightSchedule );
   string id;

   int choice;
   while ( ( choice = enterChoice() ) != 4 )
   {
      switch ( choice )
      {
      case 1:
         makingReservation.execute();
         break;
      case 2:
         cout << "\nEnter ID number: ";
         cin >> id;
         inquiryRefund.bookingInquiry( id );
         break;
      case 3:
         cout << "\nEnter ID number: ";
         cin >> id;
         inquiryRefund.refundApplication( id );
         break;
      default:
         cerr << "Incorrect choice" << endl;
         break;
      }
   }

   cout << endl;
   system( "pause" );
}

int enterChoice()
{
   cout << "\nInput your choice:\n"
        << "1. Booking\n"
        << "2. Booking enquiry\n"
        << "3. Refund application\n"
        << "4. End\n? ";

   int menuChoice;
   cin >> menuChoice;
   return menuChoice;
}