# Data-Visualization-with-Linear-Combinations
Visualization of multi-dimensional data using a linear combination from an equation which separates data in multi-dimensional space.

Images included in this repository show how the lines behave using different coefficients. The saperation
of classes does not seem to be effected much by using random coefficients.

The images are labeled based on what coefficients were used:
coefficients_1 :  {0.3, 0.9, 0.6, 0.8, 0.8, 0.7, 0.6, 0.9, 0.8}
coefficients_2 :  {0.3, 0.5, 0.6, 0.8, 0.8, 0.7, 0.5, 0.9, 0.8}
coefficients_3 :  {0.3, 0.2, 0.6, 0.5, 0.3, 0.2, 0.6, 0.5, 0.3}
coefficients_4 :  {0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9}
coefficients_5 :  {0.9, 0.5, 0.8, 0.9, 0.7, 0.9, 0.3, 0.7, 0.6}

The dataset used can be found here:

http://archive.ics.uci.edu/ml/machine-learning-databases/breast-cancer-wisconsin/breast-cancer-wisconsin.data

With the first column removed(which is the ID), and null values were changed to 1.
The last column is the class label(2 or 4). The red lines and dots correspond to the 4's in the class label.

The code was written in 2012 Microsofts Visual Studio. 
It requires openGL.
