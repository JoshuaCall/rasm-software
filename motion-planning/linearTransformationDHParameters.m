% Linear transformation for the RASM
clear, clc, close all

syms th d al a
Ti = [ cos(th), -sin(th), 0, a;
      sin(th)*cos(al),cos(th)*cos(al), -sin(al), -sin(al)*d;
      sin(th)*sin(al), cos(th)*sin(al), cos(al), cos(al)*d;
      0, 0, 0, 1];
  
aiMinus1 = [0, 16, 19.75, 1.5, 1]; % units in inches
alphaiMinus1 = [0,0,0, -pi/2, -pi/2]; % units in radians
di = zeros(1,5);
% syms a0 a1 a2 a3 a4 alpha0 alpha1 alpha2 alpha3 alpha4
% aiMinus1 = [a0, a1, a2, a3, a4];
% alphaiMinus1 = [alpha0, alpha1, alpha2, alpha3, alpha4];
% di = sym('d%d', [1,5]);
thi = sym('th%d', [1,5]);
transformation = eye(4);

for i = 1:5
    T(:,:,i) = subs(Ti, {a,al,d,th}, {aiMinus1(i),alphaiMinus1(i),di(i),thi(i)});
    transformation = transformation * T(:,:,i);
end

% Now that we have the T1*T2*T3*T4*T5 transformation, multiply it by the
% (x,y,z,1) vector to find the location in space of the Tobii screen

% syms x y z
x = -6.5; y = 0.5; z = -4.5; % units in inches
position = transformation * [x;y;z;1];
simplify(position)
