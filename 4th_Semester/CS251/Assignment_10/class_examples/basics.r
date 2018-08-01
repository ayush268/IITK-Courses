a <- 5
a
class(a)
str(a)
print(a)

#rm(a)
#print(a)

a <- (1:5)
class(a)
print(a)
#
a[6] = 98.3
class(a)
print(a)
#
a[7] = FALSE
#
class(a)
print(a)
#
a[8] = "cs251"
class(a)
print(a)

mat_a <- matrix(c(1:12), 3, 4)
mat_a

class(mat_a)
print(mat_a)



l <- list(1, 0.5, "help")
class(l)
str(l[1])
str(l[3])

courses <- c("cs251", "cs330", "cs315")
regs <- c(110, 90, 70)
drops <- c(5, 3, 1)

srecs <- data.frame(courses, regs, drops)

srecs
class(srecs)
str(srecs)
#
srecs1 <- data.frame(CourseNo = courses, Registrations = regs, Drops = drops)


srecs1
class(srecs1)
str(srecs1)
#
stars <- c(10, 10 ,2);
#
srecs2 <- cbind(srecs1, Stars = stars)
#
srecs2
#
srecs3 <- cbind(Seq = seq(1,3,1), srecs2)
#
srecs3
str(srecs3)
#
regs_e <- srecs3 $ "Registrations"
#
regs_e 
#
str(regs_e)
#
print(regs_e)
#
