function [theta1, theta2, theta3, theta4 ] = ik( Xg, Yg, Zg )

   L1 = 0.103;
   L2 = 0.27;
   L3 = 0.038;
   L4 = 0.205;
   L = sqrt(L3^2 + L2^2);
   L5 = 0.095;
   L6 = 0.012;
   
   dg = sqrt(Xg^2 + Yg^2);
   dw = dg - L5;
   theta1 = atan2d(Yg,Xg);
    X = dw*cosd(theta1);
    Y = dw*sind(theta1);
    Z = Zg - L6;

%    L1 = 1;
%    L4 = 0.89;
%    L = 1.05;
   
   

   
   
   b = ((X*cosd(theta1) + Y*sind(theta1))^2 + (Z-L1)^2 - L4^2 - L^2)/(2.0*L*L4);
   theta3 = atan2d(-sqrt(1-b^2), b);
   if (theta3 >= 90)
       theta3 = atan2d(sqrt(1-b^2), b);
   end
   
   a = Z - L1;
   b = -(X*cosd(theta1) + Y*sind(theta1));
   c = L4*sind(theta3);
   
   theta2a = atan2d(c, -sqrt(a^2 + b^2 - c^2)) - atan2d(a, b);
   theta2b = atan2d(c, sqrt(a^2 + b^2 - c^2)) - atan2d(a, b);
   
   fkresult1 = fk([theta1, theta2a, theta3, 0]);
   fkresult2 = fk([theta1, theta2b, theta3, 0]);
   
   in = [X;Y;Z;1];
   if (abs(fkresult1 - in) > abs(fkresult2 - in))
       theta2 = theta2b;
   else
       theta2 = theta2a;
   end
   
   theta4 = -(theta2 + theta3);
end


