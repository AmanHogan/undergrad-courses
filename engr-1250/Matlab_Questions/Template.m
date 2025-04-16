%{
Aman Hogan-Bailey ENGR 1250-002 10/12/2020

Problem Statement: Calculates the volume and surface area of a cylnder

Variables: 
r - radius of cylinder [cm]
H - height of the cylinder [cm]
V - volume of the cylinder [cm^3]
SA - surface area of cylinder [cm^2]
%}

clear
clc

%set input variables listed above
r=3;
H=4;

%calculate the volume and surface area
V = pi*r^2*H
SA = 2*pi*r*H+2*(pi*r^2)


