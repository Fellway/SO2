# Operating Systems - Project to pass the course

## Introduction

This project was created for the purpose of completing the course SO2 at the Lodz University of Technology.
It was written using C ++ and WinApi. I am not a C ++ specialist. 
The program may contain a lot of confusion and there were certainly many things that could be done easier.

## Description
The program uses two processes when it is launched. They are called "Writer" and "Monitor".
"Writer" draws random numbers and saves them to File.txt. "Monitor" reads the saved numbers and on the basis of them calculates the average and indicates the minimum and maximum number. The results are saved to the Monitor.txt file. There are two versions of this program. The first one uses only one thread. The second uses 3 threads, one for each operation (min, max, avg). The 3-thread version is merged into the master. The single-thread version is on the app-A branch.

## Application run
There will be 3 arguments required to start the application 
<br />
e.g 
```
10000 1 2
```
* 1000 - The first argument is how many numbers are to be drawn.
* 1 - The second argument is the time intervals at which the draws will be performed
* 2 - The third argument is how many times the draw is to be repeated.


## Results

The results are listed in a table in the Monitor.txt file and look like this:
```
Total numbers: 10 | Version: Single-threading 
Machine: 
	Number of processors: 4
	Page size: 4096
	Processor type: 586
	Minimum app address: 0x10000
	Maximum app address: 0x7ffeffff
Replies: 10 | Pause: 1
Nr.		Min		Max		Avg
0.		15		77		38.1
1.		4		74		41.2
2.		2		88		37.7
3.		5		81		30.9
4.		2		99		49.9
5.		3		72		32.4
6.		5		96		53.4
7.		10		85		49.1
8.		3		92		47.8
9.		11		84		43.1
```