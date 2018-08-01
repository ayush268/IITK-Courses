student.data <-
    data.frame( student = 1:25,
               age = round(rnorm(25, mean = 18, sd = 3)),
               course = sample(paste("CS",320:325, sep="-"), 25, replace = TRUE))

student.data

table(student.data $ "course")
table(student.data $ "age")
table(student.data $ "age" < 20)
