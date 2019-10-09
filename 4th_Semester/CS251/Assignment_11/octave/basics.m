a = 5
b = 7.5

a*b
#intermediate output suppression
a = 9.3;
b = 2.3;
c = a / b
clc

#row vector

a = [1 2 3]
b = [4 5 6]

#Access elements
a(1)
b(2)

#Element by element operation
a .* b
#col vector
clc

a = [1; 2; 3;10]
b= [4; 5; 6; 7]

#Access elements
a(1)
b(2)


#Element by element operation
a .+ b

a + 5


#Matrix and their operations
clc

m1 = [1 2 3; 2 4 6; 7 8 9]
m2 = [1 2 3; 2 4 6; 7 8 9]


#matrix using sequences
m5 = [1:3; 9:-3:3; 4:2:8]

#matrix access
m5(1,2)
m5(2,1)
m5(2, [1,2])
m5(2, [1:2])
m5(3, :)
m5(3, :)'
(m5'(3, :))'

clc
#operations on matrix

m1 + 2
m2 - 1

m3 = m1 .+ m2
m3 .- m2


#special matrices
ones(3, 4)
zeros(4,5)
eye(3,3)
rand(1,3)
randn(3,3)

#Add rows and cols to a matrix

clc
a=[1:3; 4:2:8; 3:3:9]

i= ones(3,1)

b= [a, i]

i=ones(1,3)

c = [a; i]

