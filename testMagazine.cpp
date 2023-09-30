#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main() {
    // Open the CSV file
    std::ifstream file("Magazines.csv");

    // Check if the file is open
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return 1; // Return an error code
    }

    // Print the header for reference
    std::cout << "Publication, Rank" << std::endl;

    // Read and print the header line
    std::string header;
    if (std::getline(file, header)) {
        // Ignore double quotes in the header
        size_t pos = header.find('"');
        while (pos != std::string::npos) {
            header.erase(pos, 1); // Remove double quotes
            pos = header.find('"', pos); // Find the next double quote
        }
        std::cout << header << std::endl;
    }

    // Read the data line by line and print "publication" and "rank"
    std::string line;
    while (std::getline(file, line)) {
        // Ignore double quotes in the line
        size_t pos = line.find('"');
        while (pos != std::string::npos) {
            line.erase(pos, 1); // Remove double quotes
            pos = line.find('"', pos); // Find the next double quote
        }

        // Use stringstream to split the line into tokens
        std::istringstream iss(line);
        std::string publication, rank, token;

        // Read the first token (publication)
        if (std::getline(iss, publication, ',')) {
            // Read the second token (rank)
            if (std::getline(iss, rank, ',')) {
                std::cout << publication << ", " << rank << std::endl;
            }
        }
    }

    // Close the file
    file.close();

    return 0; // Return success
}
