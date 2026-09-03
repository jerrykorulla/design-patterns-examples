#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

// After Singleton: the whole application shares one Logger instance, so the
// log file is opened once and its configuration lives in a single place.
class Logger {
public:
    static Logger& instance() {
        // Meyers' Singleton: the local static is constructed on first use and
        // destructed at program exit. Construction is guaranteed thread-safe
        // by the C++11 standard, so no extra locking is needed here.
        static Logger instance{"application.log"};
        return instance;
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void info(const std::string& message) {
        output_ << "[INFO] " << message << '\n';
    }

private:
    explicit Logger(const std::string& fileName) : output_(fileName, std::ios::app) {
        if (!output_) {
            throw std::runtime_error("Unable to open log file: " + fileName);
        }
    }

    std::ofstream output_;
};

class PaymentService {
public:
    void charge(const std::string& orderId) {
        Logger& logger = Logger::instance();
        logger.info("Charging payment for order " + orderId);
        // ... call the payment provider ...
        logger.info("Payment accepted for order " + orderId);
    }
};

class OrderService {
public:
    void placeOrder(const std::string& orderId) {
        Logger& logger = Logger::instance();
        logger.info("Received order " + orderId);

        paymentService_.charge(orderId);

        logger.info("Order " + orderId + " completed");
    }

private:
    PaymentService paymentService_;
};

int main() {
    OrderService orderService;
    orderService.placeOrder("ORD-1042");

    std::cout << "Wrote order activity to application.log\n";
}
