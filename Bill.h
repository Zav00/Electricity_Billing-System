#ifndef BILL_H
#define BILL_H
#include <iostream>
#include <string>
class Bill {
private:
    std::string customerName;
    std::string date;
    double electricityConsumption;
    double ratePerUnit;
public:
    Bill(const std::string &customerName, const std::string &date, double electricityConsumption, double ratePerUnit)
            : customerName(customerName), date(date), electricityConsumption(electricityConsumption),
              ratePerUnit(ratePerUnit) {}

    const std::string &getCustomerName() const {
        return customerName;
    }

    const std::string &getDate() const {
        return date;
    }

    double getElectricityConsumption() const {
        return electricityConsumption;
    }

    double getRatePerUnit() const {
        return ratePerUnit;
    }
    double calculateTotalAmountDue() const {
            return electricityConsumption * ratePerUnit;
        }
};
#endif