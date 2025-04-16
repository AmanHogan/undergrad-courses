%{
Aman Hogan-Bailey ENGR 1250-002 10/12/2020

Matlab Assignment #2 Chapter 17 Problem number 5

Problem Statement: Calculating the amount of heat needed to raise the
tempature of a substance by a specified number of degrees in [J]

Variables: 
ti = initial temparature [F]
tf = final temparature [F]
m = mass of substance [g]
c = specific heat of substance [J/(kg*K)]
user_name = user's name
Day_list = list of the days allowed
Day_week = list of the days from drop down menu
q = heat [J]


%}

clear
clc
%getting user's name
user_name = input('Enter yout name ', 's');
%assigning the days of the week to a cell array
Day_list = {'Monday', 'Wednesday', 'Friday'};
Day_Week= menu('What day is it', Day_list{1,:});

%gathering input variable
m = input('\nWhat is the mass of the substance in grams? ');
c = input('\nWhat is the specific heat of the substance in [J/(kg*K)]? ');
ti = input('\nWhat is the initial temparature in degrees Fahrenheit? ');
tf = input('\nWhat is the final temparature in degrees Fahrenheit? ');


%printing out the desired caption
fprintf('On %s, the user %s enterd a %2.2f gram mass with \na specific heat of %2.2f J/(kg K) that should be \nraised from %2.2f degrees Fahrenheit to %2.2f degrees \nFahrenheit. ', Day_list{1}, user_name, m, c, ti, tf);


%converting [g] to [kg]
m = m/1000;
%coverting [J/(kg*K)] to [J/(kg*F)]
c = c/1.8;
q=m*c*(tf-ti);

%calculating the amount of heat and printing the result
fprintf('This should require %2.1f J of heat to be added to the \nsubstance.',q);
