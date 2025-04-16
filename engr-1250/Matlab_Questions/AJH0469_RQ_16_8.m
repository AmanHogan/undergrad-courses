%{
Aman Hogan-Bailey ENGR 1250-002 10/13/2020

Promblem Statement: Calculates how far the vehicle traveled in kilometers

Variables: 
f - fuel efficiency of car [mi/gal]
m - mass of fuel [g]
sg - specific gravity of fuel [-]
po - density of object [kg/L]
pw - density of water [kg/L]
d - distance traveled [km]
n - amount of fuel [L]

%}
clear
clc

%defining the variables and constants
m=100;
f=1075;
sg=.789;
pw=1;

%converting [g] to [kg]
m = m/1000;

%converting [mi/gal] to [km/L]
f = f*(.264/.621);

%calculating for the density of the object
po = pw*sg;

%calculating the amount of fuel
n = po/m;

%scalculating the distance travled
d = f*n




