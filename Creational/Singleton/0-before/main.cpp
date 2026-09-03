#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

// Before Singleton: every collaborating class creates and configures its own
// logger, even though the whole application should use one application log.
class Logger {
public:
    explicit Logger(const std::string& fileName) : output_(fileName, std::ios::app) {
        if (!output_) {
            throw std::runtime_error("Unable to open log file: " + fileName);
        }
    }

    void info(const std::string& message) {
        output_ << "[INFO] " << message << '\n';
    }

private:
    std::ofstream output_;
};

class PaymentService {
public:
    void charge(const std::string& orderId) {
        // Configuration is duplicated in every class that needs logging.
        Logger logger{"application.log"};
        logger.info("Charging payment for order " + orderId);
        // ... call the payment provider ...
        logger.info("Payment accepted for order " + orderId);
    }
};

class OrderService {
public:
    void placeOrder(const std::string& orderId) {
        // This is another Logger object, with its own open file handle.
        Logger logger{"application.log"};
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
