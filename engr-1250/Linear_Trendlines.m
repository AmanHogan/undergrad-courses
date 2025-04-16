clear
clc
close all

T=[375 395 420 450 500];
P=[2.2 2.3 2.5 2.6 2.9];

figure('Color', 'w');
plot(T, P,'dr', 'MarkerFaceColor', 'r', 'MarkerSize', 14);
xlabel('Temperature (T) [K]', 'FontSize', 12);
ylabel('Pressure (P) [atm]', 'FontSize', 12);

axis([350 550 2 3]);
grid on;


C = polyfit(T, P, 1);
m=C(1);
b=C(2);

Tpf=[375:10:505];
Ppf=m*Tpf+b;

hold on

plot(Tpf, Ppf, 'r', 'LineWidth', 3);

TE=sprintf('P=%.3fT+%.3f', m, b);
text(460, 2.55, TE, 'BackgroundColor', 'w', 'EdgeColor', 'r');