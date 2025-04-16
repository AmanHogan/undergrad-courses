%{
Aman Hogan-Bailey ENGR 1250-002 10/13/2020

Problem Statement: Finding the mass of O2 in grams given its various
properties.

Variables:
mw = molecular weight [g/mol]
v = volume [gal]
t = temparature [degree celcius]
r = gas constant [(atm*L)/(mol*K)]
n = amount [mol]
m = mass [mol]
p = pressure [atm]

%}

clear
clc

%defining variables and constants
mw=32;
v=1.25;
t=125;
p=2.5;
r=.08206;

%converting [gal] to [L]
v = v/.264;

%converting [celcius] to [K]
t = t+273;

%caclutaing the amoount of O2 in moles
n = (p*v)/(r*t);

%calculating the mass
m = mw*n
