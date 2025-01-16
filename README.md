# Console-App-Ransac-III

The application is a CLI tool designed to process a CSV file containing 2D data and compute linear fits using least squares and the RANSAC algorithm.

## Description

The application takes a CSV file as input. The file should have exactly **two columns**:

- The **first column** represents the abscissa (x-values).
- The **second column** represents the ordinate (y-values).

The application performs the following tasks:

1. Computes the linear fit for the dataset using the least squares method.
2. Computes the linear fit for the dataset using the RANSAC algorithm.
3. Produces a new CSV file that includes:
   - The original abscissa values (column 1).
   - The original ordinate values (column 2).
   - The ordinate values of the least squares fit evaluated at the abscissa knots (column 3).
   - The ordinate values of the RANSAC fit evaluated at the abscissa knots (column 4).

The output CSV will have the following format:

| Abscissa (x) | Ordinate (y) | Least Squares Fit | RANSAC Fit |
|--------------|--------------|-------------------|------------|
| x1           | y1           | y1_fit_ls         | y1_fit_ransac |
| x2           | y2           | y2_fit_ls         | y2_fit_ransac |
| ...          | ...          | ...               | ...          |

This structure allows for easy comparison of the original data with the computed linear fits.

## Usage

1. Prepare a CSV file with two columns: `abscissa` and `ordinate`.
2. Run the application and provide the input file path.
3. The application will generate a new CSV file with the computed results.

## Example

### Input CSV:
```
Abscissa,Ordinate
1.0,2.1
2.0,4.2
3.0,6.1
4.0,8.3
```

### Output CSV:
```
Abscissa,Ordinate,Least Squares Fit,RANSAC Fit
1.0,2.1,2.0,2.05
2.0,4.2,4.0,4.10
3.0,6.1,6.0,6.05
4.0,8.3,8.0,8.10 