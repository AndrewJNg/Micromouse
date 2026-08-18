
clear all; close all; clc;
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
y_1 = 100./log(y);
x_1 = x;
plot(x,y_1,'ko')
xlabel('distance (mm)')
ylabel('100/ln(ADC)')

%% lin reg
[a0,a1,r2] = linreg_template(x_1,y_1);
b= a0;
a= a1;

%%
ADC100 =  y(5);

A = 100*log(ADC100)./log(y);
B = [A , x]
figure(2)
plot(x,A)
grid minor 


