#!/usr/bin/env Rscript

# Declaring Data
num_elements <- 50000

x <- rexp(num_elements, 0.2)
sorted_x <- sort(x)

# Declaring Generator
distFuncGenerator <- function(ydata, len, pdf, range)
{
  pdata <- rep(0, range);

  for(i in 1:len){
    val = round(ydata[i], 0);
    if(val <= range){
      pdata[val] <- pdata[val] + 1/len;
    }
  }

  if(pdf){
    return (pdata);
  }
  
  cdata <- rep(0, range);

  cdata[1] <- pdata[1]

  for(i in 2:range){
    cdata[i] <- cdata[i-1] + pdata[i];
  }

  return (cdata);
}

frequency <- function(ydata)
{
  tab <- table(round(ydata));
  return (tab);
}


# Step 1
scatter_plot <- data.frame(Index = seq(1, num_elements, 1), Value = sorted_x)
plot(scatter_plot)


# Step 2
y <- vector(mode="list", length=500);

a = 1
for (i in seq(1, num_elements, 100)){
  small_vector <- x[i:(i+99)];
  y[[a]] <- small_vector;
  a <- a + 1;
}


# Step 3
xcols <- c(0:99)
cd <- vector(mode="list", length=5);
pd <- vector(mode="list", length=5);
for (i in 1:5){
  cd[[i]] <- distFuncGenerator(y[[i]], 100, FALSE, 100);
  pd[[i]] <- distFuncGenerator(y[[i]], 100, TRUE, 100);
  plot(xcols, pd[[i]], "l", xlab="X", ylab="f(X)")
  plot(xcols, cd[[i]], "o", col="blue", xlab="X", ylab="F(X)");
}

mean <- rep(0, 500);
standard_deviation <- rep(0, 500);

a <- 1
for (i in 1:500) {
  mean[i] <- mean(y[[a]]);
  standard_deviation[i] <- sd(y[[a]])
  a <- a + 1;
}

for(i in 1:5) {
  str(mean[i]);
  str(standard_deviation[i]);
}


# Step 4
z <- mean;
xcols <- c(0:9)
plot(frequency(z), "h", xlab="Value", ylab="Frequency");
pfunc <- distFuncGenerator(z, 500, TRUE, 10);
cfunc <- distFuncGenerator(z, 500, FALSE, 10);
plot(xcols, pfunc, "l", xlab="X", ylab="f(X)");
plot(xcols, cfunc, "o", col="blue", xlab="X", ylab="F(X)");


# Step 5
Final_mean <- mean(z);
Final_standard_deviation <- sd(z);


# Step 6
percent_error_mean <- (abs(Final_mean - mean(x)) / mean(x)) * 100 
percent_error_from_original <- (abs(Final_standard_deviation - sd(x)/10) / sd(x)) * 100
print (Final_mean);
print (mean(x));
print (percent_error_mean);
print (Final_standard_deviation);
print (sd(x));
print (percent_error_from_original)
