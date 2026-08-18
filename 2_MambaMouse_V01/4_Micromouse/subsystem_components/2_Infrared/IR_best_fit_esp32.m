%Written by: ???, ID: ???
%Created: ???
%Using linear regression
clear all; close all; clc;

%data
y = [
4025
3930
3120
2250
1712
1330
1020
833
700
587
508
450
415
350
310
287
272
260
250
240
];
x = (10:10:200)';

%% plotting
y = y;
y_1 = y;
x_1 = 1./x;
axis([0,200,0,4095])
plot(x,y,'ko')
xlabel('x')
ylabel('y')

%% calculating linear coefficients
[a0,a1,r2] = linreg_template(x_1,y_1);

b= a0
a= a1

%% plotting line of best fit

%y_2 = 500:3000;
%y_2 = 1000:4096;
%x_2 = a1./(y_2-a0);

%hold on
%axis([0,200,0,4095])
%plot (x_2,y_2,'r-');


