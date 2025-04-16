

%{
    Group Project:
        Chavarria, Joanna Yamille
        Hogan-Bailey, Aman June
        Mier, Matthew A
        
    2208-ENGR-1250-002 // 12_MON_5 // 11/3/2020
    
Problem Statement:

    Perform a breakeven analysis on the different materials 
    and construction methods,and determine the expected return on investment.

Assumptions: 

    N/A

Equations:

y = mx+ b
Breakevenp point = {Revenue = Cost}
Cost = FixedCost + VariableCost * ( x )
V = SA * Thickness = L * L * L
Revenue = Aggregate input * ( x )


Variables:
    
Info = needed 3x7 cell array
Choice = choice the user makes
SA = Surface Area [ft^2]
Thickness = Thickness of material [in] >> [ft]
Volume = Volume of material [ft^3]

Material_C = Total Material cost [$]
Misc_C = Total Miscellanious cost [$]
Labor_C_C = Total Construction Labor Cost [$]
Fixed_C = Fixed Cost [$]

Energy_C = Energy cost per week [$/week]
Labor_O_C = Operational Labor cost per week [$/week]
Maint_C  = Maintenece cost per week [$/week
Land_C  = Landfill cost per week [$/week]
Weeks = Number of weeks the zoo will operate
Years = Years of analysis [yr]

Admission_P = Price of admission per person [$/person]
People_N = Number of people per week [#]
Donate_P = Expected donations per week [$/week]
Revenue = Revenue [$]
Variable_C = Variable Cost [$]

Cost_Equa = Total Cost with respect to x [$]
Cost_Equa_Years = total cost to operate given years [$]
Revenue_Equa = Total Revenu with respect to x[$]
Revenue_Equa_Years

Profit = Revenue - cost [$]
Breakeven_P = Revenue = Cost [$]
Onetime_D = Onetime_D = (Fixed_C/28[7 months]) + Variable_C -(Admission_P *
People_N) [$]

Cost_Equa_2 = The cost for only one year [$]

LT = The legend consiting of cost and revenue [-]

figure(2) = graph of profit

figure(1) = grpah of revenue and cost

%}

clear
clc
close all

%Defining 3x7 cell array
Info = {'Concrete' 16 30 96000 900 5 5; 
        'Wood' 23 53 115000 800 12 11; 
        'Adobe' 18 42 68000 600 6 5};
    
%Allowing user to choose material // storing intput into Choice
Choice = menu('Choose one of the following materials: ', Info{:,1});

    %Initializing fixed surface area
    SA = 3000; %[ft^2]

    %Converting thickness in [in] to [ft]
    Thickness = Info{Choice,2}/12; %[in] to [ft]

    %Computing volume [ft^3]
    Volume = SA * Thickness; %[ft^3]

    %Computing the total / Materials Cost [($/ft^3)*(ft^3)] = [$] /
    Material_C = Volume * Info{Choice, 3}; %[$]

    %Computing the cost of / Miscellaneous Construction Materials [$] /
    Misc_C = Info{Choice, 4}; %[$]

    %Computing the total / Labor Construction Cost [$] /
    Labor_C_C = Info{Choice, 5}*Info{Choice, 6}*Info{Choice, 7};

    %Computing the / Fixed cost [$] / or / Cost of Construction /
    Fixed_C = Misc_C + Material_C + Labor_C_C; %[$]

%Allowing user to input their costs (Variable Cost) //
    Energy_C = input('\nEnergy cost per week [$/week]: ');
    Labor_O_C = input('\nLabor cost per week [$/week]: ');
    Maint_C = input('\nMaintenece cost per week [$/week]: ');
    Land_C = input('\nLandfill cost per week [$/week]: ');
    
%Allowing user to input their time frame [#] & [yr]
    Weeks = input('\nNumber of weeks the zoo will operate per year: [#/yr] ');
    Years = input('\nNumber of years for analysis [#]: ');

%Allowing user to input their revenue
    Admission_P = input('\nPrice of admission per person [$/person]: ');
    People_N = input('\nNumber of people per week [#]: ');
    Donate_P = input('\nExpected amount of donations per week [$/week]: ');

%Initializing scope of analysis
Y = Years;
Years = [0:Years];

%Computing Revenue and Cost
    %Computing revenue per week [$/week] / Revenue = m = slope /
    Revenue = (Admission_P * People_N) + Donate_P; %[$/week] 

    %Computing variable cost per week [$] / Variable_C = m = slope /
    Variable_C = Energy_C + Labor_O_C + Maint_C + Land_C; %[$/week]

    %Computing Cost / y=mx+b / Years = x
    Cost_Equa = Variable_C * Weeks * (Years) + Fixed_C; %[$]

    %Computing Cost for each year [Vector]
    Cost_Equa_Years = (Variable_C *Weeks.*Years) + Fixed_C;

    %Computing Revenue / y=mx+b / Years = x
    Revenue_Equa = Revenue * Weeks * (Years); %[$]

    %Computing Revenue for each year [Vector]
    Revenue_Equa_Years = Revenue * Weeks.*Years;

    %Computing Profit / Revenue - Cost / [Vector]
    Profit = (Revenue * Weeks.*Years) - ((Variable_C *Weeks.*Years) + Fixed_C);

%Computing The breakeven point and Onetime Donation
    %Converting [weeks] to [years]
    Breakeven_P = (Fixed_C/(Revenue-Variable_C))/4.00000;
    
    %Computing Onetime donation after 7 months / rearranged equation /
    Onetime_D = (Fixed_C/28.00000) + Variable_C -(Admission_P * People_N); %[$]

%Graphing both equations
    %Graphing Cost v Time & Revenue v Time
    figure(1);
    %Converting breakeven point from [months] to [years]
    %plotting Revenue & Cost
    plot(Years,Cost_Equa, '-r',Years, Revenue_Equa, '-b', Breakeven_P/12.00000,  Revenue * Weeks*(Breakeven_P/12.00000), 'ko','MarkerSize',12, 'MarkerfaceColor','k')
    grid on

    %Labeling the x-axis
    xlabel('Time (t) [yr]');
    ylabel('Amount of Money (A) [$]');

    %Creating legend and title
    LT = {'Cost' 'Revenue'};
    legend(LT,'Location','Best');
    title('Breakeven analysis of the Zoo');

%Graphing Profit v Time & Breakeven point
    figure(2);
    plot(Years,Profit,'-r',Breakeven_P/12.000000,(Revenue * Weeks*(Breakeven_P/12.000000) - ((Variable_C *Weeks*(Breakeven_P/12.000000)) + Fixed_C)),'ko','MarkerSize',12,'MarkerFaceColor','k');
    xlabel('Time (t) [yr]');
    ylabel('Total Profit (P) [$]');
    title('The Zoos Profit');

%Initializing new cost that is only for 1 year
Cost_Equa_2 = (Variable_C)*Weeks + Fixed_C;

%printing first part of summary
fprintf('Material: %s\n\tOperating %.0f weeks per year will generate per year:',Info{Choice,1},Weeks)
fprintf('\n\t\tRevenue:\t$%.0f\n\t\tCost:\t\t$%.0f',Revenue*Weeks,Cost_Equa_2)
fprintf('\n\tThe breakeven time is %2.2f months',Breakeven_P)
fprintf('\n\tThe total profit after %2.0f years is $%.3e', Y, Profit(Y+1))
fprintf('\n\nIt will take a one-time donation of $%5.2f to breakeven in seven months',Onetime_D);










