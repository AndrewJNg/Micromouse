fclose all; close all; clear all; clc;


%%

a = 1000; %mm/s2
v_max = 800; %mm/s
freq = 200;
interval = 1/freq;


d_final = 2050; %200*1e-3; % m 

t_accel = v_max/a;
t_final = d_final/v_max - v_max/a + 2*t_accel;

t_accel_burst = sqrt(d_final / (a));
t_final_burst = t_accel_burst*2;


if((d_final/1000)>= (a/1000*v_max/1000))
    t = 0:interval:t_final;
else
    t = 0:interval:t_final_burst;
end

v = zeros(size(t));
d = zeros(size(t));

d(1) = 0;
% v0= 0;


for iter = 2:size(t,2)
    % for longer path reaching max velocity
    if(t_final > (2*t_accel))
            if(t(iter)<t_accel) % accel
                v(iter) = a*t(iter);
            elseif (t(iter)>=t_accel && t(iter)<=(t_final-t_accel)) %max_speed
                v(iter) = v_max;
            elseif(t(iter)>(t_final-t_accel)) %decel 
                v(iter) = v_max -a*(t(iter)-(t_final-t_accel));
            end


    % for shorter burst        
    else
        if(t(iter)< (t_accel_burst)) %accel
                v(iter) = a*t(iter);
                v_max = max(v(iter));
        elseif(t(iter)>=(t_accel_burst))  %decel
                v(iter) = v_max- a*( t(iter) -(t_accel_burst) ) ;
        end
    end

    % integration to get distance
    d(iter) = d(iter-1)+ v(iter)*interval;


    
        
end


figure(1)
subplot(2,1,1)
plot(t,v,t,d)
legend('velocity','displacement','Location','northwest')
xlabel('time')
ylabel('')

%%
km = 2100/6;%1000/1;
Tm = 1;

% vel = Vmax*(1-exp(-t/Tm));
Volt = v/km ./ (1-exp(-t/Tm));

subplot(2,1,2)
plot(t,Volt)

% figure(2)
% vel = km*(1-exp(-t/Tm));
% plot(t,vel)


%%
x = 1./km .* (1/2 + exp(-t./(2*Tm)/(4*Tm)  )  ) .* v


figure(3)
plot(t,x)



% Ks = 0.14;
% Kv = 0.00048;
% Ka = 0.00016;
% 
% d_d = v;
% d_dd = a;

% y = (1/2 *t - 1/(2^2) + 1/(2^2)*exp(-2*t)) *5

% volt = v ./ (1/2 .*t - 1/(2^2) + 1/(2^2).*exp(-2.*t));
% figure(3)
% plot(t,volt)


