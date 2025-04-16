%{
Aman Hogan-Bailey ENGR 1250-002 10/13/2020

Problem Statement: Finding the =time it takes for a motor to raise a load
into the air in seconds.

Variables:

pin = power in [W]
pout = power out [W]
n = efficiency [-]
m = mass [kg]
h = height [m]
t = time [s]
g = graviry on Earth [9.81m/s^2]
%}
clear
clc

%Defining the variables and constants
pin=100;
m=100;
h=5;
n=60;
g=9.81;

%Converting whole number efficeincy to percentage
n=n/100;

%Calculating the power out [W]
pout=pin*n;

%solving for t [s]
t= (m*g*h)/pout
