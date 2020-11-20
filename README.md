# Utility to calculate amount of liquid/gas phase in the domain
The utility uses option for multiregion solvers.

## Using getAlpha for multiregion

```
getAlpha myAlpha -region myRegion
```

where *myAlpha* is the name of your alpha and *myRegion* is the name of your region

## Output
The utility print output to the terminal and also save it in *postProcessing* directory with the name myAlpha.dat

The output file includes header. So to plot it with gnuplot just use `set key autotitle columnhead`

Example of gnuplot file

```
set key autotitle columnhead
plot 'myAlpha.dat' with lines
pause -1
```

