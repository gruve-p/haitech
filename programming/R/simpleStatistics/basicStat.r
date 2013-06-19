#!/usr/bin/Rscript

#load data
mock_class_data <- read.table("mock_class_data.csv",header=T,sep=",",quote="")
#change var type from double to factor
mock_class_data[,3]<-as.factor(mock_class_data[,3])
#sort
mock_class_data<- sort(mock_class_data, by=~ Varsity -WritingLove)
#filter
mock_class_data.sub<-subset(mock_class_data,Mathlove >= 70)
#check data
summary(mock_class_data)
#histogram for the variable ‘coffee’
library(ggplot2)
jpeg('coffee.jpeg')
ggplot() +
geom_histogram(aes(x = coffee),data=mock_class_data,colour = '#0000ff',fill = '#0000cc')
dev.off()
#catterplot of hours of exercise ('exercise') vs. hours of homework ('homework')
jpeg('exercise_hw.jpeg')
ggplot() +
geom_point(aes(x = exercise,y = homework),data=mock_class_data) +
geom_smooth(aes(x = exercise,y = homework),data=mock_class_data,method = 'loess')
dev.off()
#histogram for Milk
jpeg('milk.jpeg')
ggplot() +
geom_histogram(aes(x = Milk),data=mock_class_data,colour = '#0000ff',fill = '#0000cc')
dev.off()
#add new column MilkFixed, encode 50 to 5, plot MilkFixed histogram
mock_class_data[c("MilkFixed")] <- recode.variables(mock_class_data[c("Milk")] , "50 -> 5;")
#mean, standard deviation, and median number of hours of sleep
library(Deducer,DeducerExtras)
descriptive.table(vars = d(sleep),data= mock_class_data,
 func.names =c("Mean","St. Deviation","Valid N","Median"))
#Stratified analysis of mean outlook on life by alcohol consumption.
descriptive.table(vars = d(optimism) ,
  strata = d(alcohol),data= mock_class_data,
  func.names =c("Mean","St. Deviation","Median"))
#frequency of people who consider themselves street smart
frequencies(mock_class_data[c("IsBookSmart")] , r.digits = 1)
#box plot for fruitveg
jpeg('fruitveg.jpeg')
ggplot() +
  geom_boxplot(aes(y = fruitveg,x = 1),data=mock_class_data) +
  scale_x_continuous(name = ' ',breaks = c(1),labels = c(" "))
dev.off()
#the relationship of mean optimism by alcohol consumption using a group box plot.
jpeg('opti_by_alcohol.jpeg')
ggplot() +
  geom_boxplot(aes(y = optimism,x = as.factor(alcohol)),data=mock_class_data) +
  coord_flip()
dev.off()