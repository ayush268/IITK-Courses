#Prime number check

#function ret = isPrime(X)
#   num = ceil(sqrt(X));
#   for i = 2:num,
#      if (mod(X, i) == 0),
#            disp(sprintf("%i is divisible by %i", X, i));
#            ret=0;
#      end,     
#   end,
#   if ( i > num),
#      ret=1;
#   end,
#endfunction

#Return multiple
#function [tfunc, hmean] = HM(X)    #X is a vector
#   hsum=0;
#   for i=1 : length(X),
#       tfunc(i) = sin(pi/X(i));
#       hsum = hsum + 1/tfunc(i)
#   end,
#   hmean = length(X)/(hsum);
#endfunction

function retval = avg (v)
  retval = 0;
  if (isvector (v))
    retval = sum (v) / length (v);
  else
    error ("avg: expecting vector argument");
  endif
endfunction

#invoke the functions

retval = isPrime(25)

#
#if (isPrime(23)),
#   disp("23 is a prime number");
#end,

#X=[2:4];

#[x,y] = HM(X)
