//
// Name: Emily Puth
// ID: 28239807
//
// This theater program is used by a small theater to sell
// tickets for performances.

#ifndef THEATER_PROGRAM_HPP_
#define THEATER_PROGRAM_HPP_

#include <iostream>
#include <fstream>

// Displays the seating chart of the theater
void printTheater (std::string **arr, int numRows, int numSeats);

// Checks if the specified row and seat numbers are valid
bool isValidSeat(std::string **arr, int row, int seat);

// Updates the seating chart after each time
// the user purchases a ticket
void updateSeatingChart(std::string ** arr, int row, int seat);

// Reads the price for a set in each row from a file named
// rowPrices.txt and stores them in an array
float *setPriceArray(int numRows);

// Prompts the user to purchase a seat until
// they want to quit.
void theaterPrompt();

// Sets up the theater. All of the seats are available
std::string **theaterSetUp(int numRows, int numSeats);

// Calculates the number of seats sold
int calculateSeatsSold(std::string **arr, int numRows, int numSeats);

// Calculates the number of seats available in each row
int calculateAvailableRowSeats(std::string **arr, int row, int numRows, int numSeats);

// Calculates the number of seats available in the entire auditorium
int calculateTotalAvailableSeats(std::string **arr, int numRows, int numSeats);

// Writes the seating chart to a file named finalSeatingChart.txt.
// Writes the total ticket sales, seats sold, seats available in
// each row and seats available in the entire auditorium to a file
// named finalSales.txt
void printResults(std::string **arr, int numRows, int numSeats, float totalSales);


#endif /* THEATER_PROGRAM_HPP_ */
