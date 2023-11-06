## Lab Info
This lab seeks to simulate real-world concurrency by providing an application interface. The user can send messages which is handled by the producer and added to a shared message queue. Meanwhile, the consumer concurrently receives the message and removes it from the queue to display it on the application.

**This application was built using GTK+ 2.0**


To run this application, install GTK+ 2 and use `make messenger` to build the app. Then, use `make run` to run the application.