clear
clc
close all


R=[0.5 1 1.25 1.5 2];
V=[3 13 20 28 50];



figure('Color','w')
plot(R,V,'sb','MarkerFaceColor','b','MarkerSize',14);
xlabel('Radius (R) [cm]','FontSize',12);
ylabel('Volume (V) [cm^3]','FontSize',12);
axis([0 3 0 60]);

grid on

C = polyfit(log(R), log(V), 1);
m=C(1);
b = exp(C(2));

Rpf=[.5:.1:2];
Vpf=b*Rpf.^m;

hold on
plot(Rpf, Vpf, '--b', 'LineWidth', 3)

TE = sprintf('V=%.0fR^{%0.3f}', b,m);
text(1,5,TE,'BackgroundColor', 'w');