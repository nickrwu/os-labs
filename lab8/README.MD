## Question 1: Revision and Improvement

I added functionality so that multiple consumers can access and consume from the buffer. To do this, I had to add a -1 flag for the amount of consumer threads the program is generating to signal when to stop. Then, I just create the number of consumer threads that the program requests.

## Question 2: Matrix Multiplication

Without concurrency, our run time exponentially grows as the size of our matrix grows larger. However, our run time significantly improves as n increases when we multiply the matrix using threads. I could only multiply matrices of around 800 x 800 without concurrency. However, I could multiply matrices of over size 15,000 x 15,000 using 4 threads.

***n x n* Matrix Multiplication (No Concurrency)**
|n            | Time (s)    |
| ----------- | ----------- |
| 1           | 0.000003    |
| 5           | 0.000003    |
| 10          | 0.000007    |
| 25          | 0.000046    |
| 50          | 0.000337    |
| 100         | 0.00292     |
| 200         | 0.022979    |
| 300         | 0.083545    |
| 400         | 0.191701    |
| 500         | 0.384814    |
| 600         | 0.705192    |
| 700         | 1.259125    |
| 800         | 1.67899     |

***n x n* Matrix Multiplication (4 Thread Concurrency)**
|n            | Time (s)    |
| ----------- | ----------- |
| 1           | 0.000248    |
| 5           | 0.000257    |
| 10          | 0.000191    |
| 25          | 0.00031     |
| 50          | 0.00028     |
| 100         | 0.000543    |
| 200         | 0.00058     |
| 300         | 0.00169     |
| 400         | 0.003008    |
| 500         | 0.003696    |
| 600         | 0.005209    |
| 700         | 0.007282    |
| 800         | 0.00761     |