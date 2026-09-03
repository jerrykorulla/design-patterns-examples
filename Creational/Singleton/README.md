# Before Singleton: order-processing logger

This example models a small order-processing flow. `OrderService` and
`PaymentService` both need to record events in the same application log.

Without a singleton, each service creates its own `Logger` and repeats the
file-name configuration. Each logger also opens a separate handle to the same
file. As the application gains services, changing the log destination or
format means changing every service.

Compile and run from the `0-before` folder:

```powershell
g++ -std=c++17 main.cpp -o before-logger.exe
.\before-logger.exe
Get-Content application.log
```

The follow-up Singleton version can centralize logger creation and file
configuration so all services use the one shared object.

# After Singleton: shared logger

`Logger::instance()` returns a reference to the one `Logger` shared by the
whole application. The constructor is private and copying is disabled, so
`PaymentService` and `OrderService` can no longer create their own logger or
duplicate the file-name configuration — they just ask the singleton for the
shared instance. The log file is opened exactly once, on first use.

Compile and run from the `1-after` folder:

```powershell
g++ -std=c++17 main.cpp -o after-logger.exe
.\after-logger.exe
Get-Content application.log
```
