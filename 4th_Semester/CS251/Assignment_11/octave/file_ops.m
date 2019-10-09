m = rand(10,3)
save input.mat

load("input.mat")
size(m)

a = rand(5,3)
size(a)

res = [m;a]

#Save the data back to a file

save ("output.mat", "res");

