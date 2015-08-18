// 
// Name: Emily Puth
// ID: 28239807
//

#include "theater-program.hpp"

void printTheater (std::string **arr, int numRows, int numSeats) {
	std::cout << "Available seats are marked with a '#'.\n\nSeats" << std::endl;
	std::cout << "       12345678901234567890234567890" << std::endl;
	for (int r=0; r<9; r++) {
		std::cout << "Row " << r+1 << "  ";
		for (int c=0; c<numSeats; c++)
			std::cout << arr[r][c];
		std::cout << "\n";
	}
	for (int r=9; r<numRows; r++) {
		std::cout << "Row " << r+1 << " ";
		for (int c=0; c<numSeats; c++)
			std::cout << arr[r][c];
		std::cout << "\n";
	}
}

bool isValidSeat(std::string **arr, int row, int seat) {
	if (row > 15) {
		std::cout << "ERROR: Please enter a valid row number." << std::endl;
		return false;
	}
	if (seat >30) {
		std::cout << "ERROR: Please enter a valid seat number." << std::endl;
		return false;
	}
	if (arr[row-1][seat-1] == ".") {
		std::cout << "That seat is not available." << std::endl;
		return false;
	}
	return true;
}

void updateSeatingChart(std::string **arr, int row, int seat) {
	arr[row-1][seat-1] = ".";
}

float *setPriceArray(int numRows) {
	std::ifstream priceFile("rowPrices.txt");
	float *priceArray = new float [numRows];
	if (priceFile.is_open()) {
		for (int r=0; r<numRows; r++)
			priceFile >> priceArray[r];
	}
	return priceArray;
}

std::string **theaterSetUp(int numRows, int numSeats) {
	std::string **seatingChart = new std::string *[numRows];
	for (int r=0; r<numRows; r++)
		seatingChart[r] = new std::string[numSeats];
	for (int r=0; r<numRows; r++)
		for (int c=0; c<numSeats; c++)
			seatingChart[r][c] = "#";
	return seatingChart;
}

int calculateSeatsSold(std::string **arr, int numRows, int numSeats) {
	int seatsSold = 0;
	for (int r=0; r<numRows; r++)
		for (int c=0; c<numSeats; c++)
			if (arr[r][c] == ".")
				seatsSold++;
	return seatsSold;
}

int calculateAvailableRowSeats(std::string **arr, int row, int numRows, int numSeats) {
	int rowSeats = 0;
	for (int r=0; r<numRows; r++)
		if(r==row)
			for (int c=0; c<numSeats; c++)
				if (arr[r][c] == "#")
					rowSeats++;
	return rowSeats;
}

int calculateTotalAvailableSeats(std::string **arr, int numRows, int numSeats) {
	int totalAvailableSeats = 0;
	for (int r=0; r<numRows; r++)
		for (int c=0; c<numSeats; c++)
			if(arr[r][c] == "#")
				totalAvailableSeats++;
	return totalAvailableSeats;
}
	
void theaterPrompt() {
	int numRows = 15; int numSeats = 30;
	float *prices = setPriceArray(numRows);
	std::string **seatingChart = theaterSetUp(numRows, numSeats);
	
	float totalTicketSales = 0;
	std::cout << "Welcome to the Theater!" << std::endl;
	printTheater(seatingChart, numRows, numSeats);
	std::string option = "y"; // if option == "q", program quits
	while (1) {
		int row, seat;
			std::cout << "\nWould you like to buy a seat (y/n)? "; std::cin >>  option;
		if (option == "n") {std::cout << "\nOk! Thank you for your purchase.\n"; break;}
		else if (option == "y") {
			std::cout << "What is the row and seat number you'd like to buy? " << std::endl; 
			std::cout << "  Row Number: "; std::cin >> row;
			std::cout << "  Seat Number: "; std::cin >> seat;
			if (!isValidSeat(seatingChart, row, seat)) continue; else {
			totalTicketSales += prices[row-1];
			updateSeatingChart(seatingChart, row, seat);
			std::cout << "\nOk! You have purchased seat " << seat << " in row " << row << " for $" << prices[row-1] << ".\n" << std::endl;
			printTheater(seatingChart, numRows, numSeats);
			}
		}
	printResults(seatingChart, numRows, numSeats, totalTicketSales);
	}
}

void printResults(std::string **arr, int numRows, int numSeats, float totalSales) {
	std::ofstream seatingChartFile("finalSeatingChart.txt");
	seatingChartFile << "       123456789012345678901234567890" << std::endl;
	for (int r=0; r<9; r++) {
		seatingChartFile << "Row " << r+1 << "  ";
		for (int c=0; c<numSeats; c++)
			seatingChartFile << arr[r][c];
		seatingChartFile << "\n";
	}
	for (int r=9; r<numRows; r++) {
		seatingChartFile << "Row " << r+1 << " ";
		for (int c=0; c<numSeats; c++)
			seatingChartFile << arr[r][c];
		seatingChartFile << "\n";
	}

	std::ofstream finalSalesFile("finalSales.txt");
	finalSalesFile << "Total Ticket Sales: $" << totalSales << std::endl;
	int seatsSold = calculateSeatsSold(arr, numRows, numSeats);
	finalSalesFile << "Number of Seats Sold: " << seatsSold << std::endl;
	finalSalesFile << "Seats Available By Row: " << std::endl;
	for (int r=0; r<numRows; r++) {
		int availableRowSeats = calculateAvailableRowSeats(arr, r, numRows, numSeats);
		finalSalesFile << "    Row " << r+1 << ": " << availableRowSeats << std::endl;
	}
	int totalAvailableSeats = calculateTotalAvailableSeats(arr, numRows, numSeats);
	finalSalesFile << "\nTotal Number of Seats Available: " << totalAvailableSeats << std::endl;	
}

int main() {
	theaterPrompt();
}
