# monte_carlo
## Comparision between serial and parallel monte carlo integration using openMP

To compile serial code use:
```
gcc monte_carlo_serial.c -lm -o serial
```
And run it with:
``` 
./serial [number_of_points] 
```
where number_of_points is the number of points used in integration of a function

To compile parallel code use:
``` 
gcc monte_carlo_parallel.c -lm -o -fopenmp parallel 
```
And run it with:
``` 
./parallel [number_of_points]
```




