num_samples <- 10000
data <- rexp(num_samples, 0.2)
x <- data.frame(X = seq(1, num_samples , 1), Y = sort(data))
plot(x)


tab <- table(round(data))

str(tab)
plot(tab, "h", xlab="Value", ylab="Frequency")

pdata <- rep(0, 100);

for(i in 1:num_samples){
    val=round(data[i], 0);
    if(val <= 100){
       pdata[val] = pdata[val] + 1/ num_samples; 
    }
}

xcols <- c(0:99)

str(pdata)
str(xcols)

plot(xcols, pdata, "l", xlab="X", ylab="f(X)")

cdata <- rep(0, 100)

cdata[1] <- pdata[1]

for(i in 2:100){
    cdata[i] = cdata[i-1] + pdata[i]
}

plot(xcols, cdata, "o", col="blue", xlab="X", ylab="F(X)");

print (mean(data))

