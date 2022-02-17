%Written by: ???, ID: ???
%Created: ???
%Using linear regression
clear all; close all; clc;

%data
y = [
506
570
630
675
703
728
745
764
780
800
808
812
821
828
830
835
];
x = (60:10:210)';

%% plotting
y = 1023-y;
y_1 = y;
x_1 = 1./x;
plot(x,y,'ko')
xlabel('x')
ylabel('y')

%% calculating linear coefficients
[a0,a1,r2] = linreg_template(x_1,y_1);

b= a0;
a= a1;

%% plotting line of best fit

y_2 = 150:850;
%y_2 = 1000:4096;
x_2 = a1./(y_2-a0);

hold on
axis([0,200,0,1000])
plot (x_2,y_2,'r-');


