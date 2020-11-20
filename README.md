# Utility to calculate amount of liquid/gas phase in the domain
The utility was tested on OpenFOAM v2006. It uses the option for multiregion solvers.

## Using getAlpha for non-multiregion

```
getAlpha myAlpha
```
where *myAlpha* is the name of your alpha.

## Using getAlpha for multiregion

```
getAlpha myAlpha -region myRegion
```

where *myAlpha* is the name of your alpha and *myRegion* is the name of your region

## Output
The utility print output to the terminal and also save it in *postProcessing* directory with the name myAlpha.dat (*myAlpha* is the name of alpha).

The output file includes header. So to plot it with gnuplot just use `set key autotitle columnhead`

Example of gnuplot file

```
set key autotitle columnhead
plot 'myAlpha.dat' with lines
pause -1
```

