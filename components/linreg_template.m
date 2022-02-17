function [a0,a1,r2] = linreg_template(x,y)
% [a0,a1,r2] = linreg(x_linear, y_linear) 
% Written by: ???, ID: ???
% Last modified: ???
% Performs linear regression on the linear x and y data set 
%
% INPUTS:
%  - x: linear independent data set 
%  - y: linear dependent data set 
% OUTPUT:
%  - a0: constant in y=a1*x + a0 
%  - a1: gradient in y=a1*x + a0
%  - r2: coefficient of determination

% Getting best regression coefficients
n = length (x); 

sx = sum(x);
sy = sum(y);
sxy = sum(x.*y);
sx2 = sum(x.^2);


a1 =( n*sxy - sx*sy )  / (n*sx2 - sx^2);

a0 = mean(y) - a1*mean(x);

% Getting r2 value

sr = sum((y-a0-a1*x).^2);
st = sum((y-mean(y)).^2);

r2 = (st - sr )/st;












