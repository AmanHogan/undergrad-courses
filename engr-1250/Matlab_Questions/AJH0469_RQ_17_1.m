%{
Aman Hogan-Bailey ENGR 1250-002 10/12/2020

Matlab Assignment #2 Chapter 17 Problem number 1

Problem Statement: Solving for the length of a side of a cube [in] if the
user inputs mass [kg].

Variables: 
po = density of gold [kg/m^3]
pw = density of water [kg/m^3]
sg = specific gravity of gold [-]
m = mass [kg]
L = length of side [in]
V = volume of cube [m^3]
user_in = user input
%}

clear
clc

%defining variables and constants
sg = 19.3;
pw=1000;

%finding density of gold [kg/m^3]
po = sg*pw;

%asking user to input mass [kg]
m = input('Enter the mass of the cube [kilograms]: ');

%finding volume [m^3]
V=m/po;

%finding the length [m]
L = V^(1/3);

%converting [m] to [in]
L = L*(3.28*12);

%printing the answer with 2 floating point number
fprintf('The length of one side of the cube is %.2f inches.', L)