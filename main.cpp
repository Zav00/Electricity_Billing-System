#include<iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Bill.h"
#include"Custumer.h"

void saveBillToFile(const Bill &bill) {
    std::string fileName = bill.getCustomerName() + "_" + bill.getDate() + ".txt";
    std::ofstream file(fileName);
    if (file.is_open()) {
        std::cout << "Unable saved in File" << std::endl;
        file << "Customer Name:" << bill.getCustomerName() << std::endl;
        file << "Date:" << bill.getDate() << std::endl;
        file << "Electricity Consumption" << bill.getElectricityConsumption() << std::endl;
        file << "Rate per Unit: $:" << bill.getRatePerUnit() << std::endl;
        file << "Total Amount Due: $" << bill.calculateTotalAmountDue() << std::endl;
        std::cout << "Bill saved to file" << fileName << std::endl;
    } else {
        std::cout << "Unable saved in file" << std::endl;
    }
}

void saveCustomerToFile(const Customer &customer) {
    std::string filename = customer.getName() + ".txt";
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Customer Name" << customer.getName() << std::endl;
        file << "Contact Info" << customer.getContactInfo() << std::endl;
        file << "Meter Number" << customer.getMeterNumber() << std::endl;
        std::cout << "Customer info saved in File" << std::endl;
    } else {
        std::cout << "ERROR:Unable saved info in File" << std::endl;
    }
}

int main() {
    std::vector<Customer> customers;
    std::vector<Bill> bills;
    double ratePerUnit;
    std::cout << "Enter rate per unit of electricity: $";
    std::cin >> ratePerUnit;
    std::cin.ignore();
    int choice = -1;
    while (choice != 0) {
        std::cout << "Electricity Billing System" << std::endl;
        std::cout << "1. Customer Registration" << std::endl;
        std::cout << "2. Enter Electricity Consumption" << std::endl;
        std::cout << "3. Generate Bill" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();
        if (choice == 1) {
            std::string name, contactInfo, meterNumber;
            std::cout << "Enter customer's name: ";
            getline(std::cin, name);
            std::cout << "Enter customer's contact information: ";
            getline(std::cin, contactInfo);
            std::cout << "Enter customer's meter number: ";
            getline(std::cin, meterNumber);
            customers.emplace_back(name, contactInfo, meterNumber);
            // Save customer details to file
            saveCustomerToFile(customers.back());
        } else if (choice == 2) {
            if (customers.empty()) {
                std::cout << "No customers registered." << std::endl;
            } else {
                std::string customerName;
                std::cout << "Enter customer's name: ";
                getline(std::cin, customerName);
                bool found = false;

                for (Bill &bill: bills) {
                    if (bill.getCustomerName() == customerName) {
                        double consumption;
                        std::cout << "Enter electricity consumption (in units): ";
                        std::cin >> consumption;
                        std::cin.ignore();  // Clear the newline character from the input stream
                        // Generate current date
                        time_t now = time(nullptr);
                        tm *localTime = localtime(&now);
                        char dateBuffer[50];
                        strftime(dateBuffer, sizeof(dateBuffer), "%d-%m-%Y", localTime);
                        std::string date = dateBuffer;
                        bill = Bill(customerName, date, consumption, ratePerUnit);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << "Customer not found." << std::endl;
                }
            }
        } else if (choice == 3) {
            if (bills.empty()) {
                std::cout << "No bills available." << std::endl;
            } else {
                std::string customerName;
                std::cout << "Enter customer's name: ";
                getline(std::cin, customerName);
                bool found = false;

                for (const Bill &bill: bills) {
                    if (bill.getCustomerName() == customerName) {
                        std::cout << "Customer Name: " << bill.getCustomerName() << std::endl;
                        std::cout << "Electricity Consumption: " << bill.getElectricityConsumption() << " units"
                                  << std::endl;
                        std::cout << "Rate per Unit: $" << bill.getRatePerUnit() << std::endl;
                        std::cout << "Total Amount Due: $" << bill.calculateTotalAmountDue() << std::endl;

                        // Save bill details to file
                        saveBillToFile(bill);

                        found = true;
                        break;
                    }
                }

                if (!found) {
                    std::cout << "Customer not found." << std::endl;
                }
            }
        }
    }

    std::cout << "Exiting the program." << std::endl;
    return 0;
}

