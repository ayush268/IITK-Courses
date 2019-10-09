import os
import numpy as np

# a = np.arange(15)
# print a

# a = a.reshape(5,3)
# print a

# print a.shape

# print a.ndim

# print a.dtype.name

# print a.itemsize

# print a.size

# print type(a)

# b = np.array([6, 7, 8])
# print b

# zero = np.zeros((4,5))
# print zero

# one = np.ones((2,3,4), dtype=np.int16)
# print one

# t = np.arange( 0, 100, 5 )
# print t

# x = [4,7,10]
# print x
# x_array = np.array(x)
# print x_array


# A = np.array( [[1,1], [0,1], [3,2]] )
# B = np.array( [[2,0,1], [3,4,2]] )

# print "A: shape", A.shape
# print "B: shape", B.shape
# print "\n"

# print "A:", A
# print "B:", B
# print "\n"

# C = B.transpose() 				 # OR C = np.transpose(B)
# print "C:", C
# print "\n"

# D = A*C                          # elementwise product
# print "D:", D
# print "\n"

# E = A.dot(B)                    # matrix product
# print "E:", E
# print "\n"

# F = np.dot(A, B)                # another matrix product
# print "F:", E
# print "\n"

# A = np.matrix(A)
# B = np.matrix(B)

# print "A: shape", A.shape
# print "B: shape", B.shape
# print "\n"

# print "A:", A
# print "B:", B
# print "\n"

# G = A*B
# print "G:", G
# print "\n"

# G_det = np.linalg.det(G)
# print "G_det:", G_det

# G[0,2] = 9
# print "G:", G
# print "\n"

# G_inv = np.linalg.inv(G)
# print "G_inv:", G_inv

# G_det = np.linalg.det(G)
# print "G_det:", G_det


# x = np.array([9,4,6,5])
# z = np.array([11,56,1,25])
# print 'x', x
# print 'z', z

# indx = np.argsort(x)
# x = np.sort(x)		# x = x[indx] will suffice
# z = z[indx]

# print 'x', x
# print 'z', z