clear
clc
close all

t=[1 5 15 20 30];
V=[18.1 12.1 4.5 2.75 1];

figure('Color','w')
plot(t,V,'hg','MarkerFaceColor','g','MarkerSize',14)
xlabel('Time (t) [s]','FontSize',12)
ylabel('Voltage (V) [V]','FontSize',12)

axis([0 40 0 20])
grid on

C=polyfit(t, log(V), 1);

m=C(1);
b=exp(C(2));

tpf=[1:1:30];
Vpf=b*exp(m*tpf);

hold on

plot(tpf, Vpf,'-g', 'LineWidth', 3);
TE=sprintf('V=%0.2fe^{%0.2ft}', b,m);
text(20, 5, TE);

