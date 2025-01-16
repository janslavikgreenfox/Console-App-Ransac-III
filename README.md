# Console-App-Ransac-III

The application is a CLI application that processes a CSV file to compute a linear fits for multiple 2D datasets using the RANSAC algorithm.

## Description

The application takes a CSV file as input. The file should have `n` columns where:

- The **first column** represents the abscissa (x-values).
- Columns **2 to n** represent the ordinates (y-values) for `n-1` sets of 2D data: `(column[1], column[i])` for `i = 2...n`.

The application performs the following tasks:

1. Computes the linear fit for each 2D dataset using the RANSAC algorithm.
2. Adds `n-1` additional columns to the CSV file. These new columns contain the ordinates of the linear fits for the corresponding datasets, computed at the abscissa values (column[1]).

I.e., `column[i+n]` will contain the ordinate values of the linear fit for `(column[1], column[i])` at the points defined in `column[1]` for `i = 2...n`.

The result is a new CSV file that will have the same number of rows as the input file, but `n` additional columns.