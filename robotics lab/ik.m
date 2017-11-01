function [theta1, theta2, theta3 ] = ik( X, Y, Z )
   L1 = 0.103;
   L2 = 0.27;
   L3 = 0.02;
   L4 = 0.205;
   L = sqrt(L3^2 + L2^2);
   
%    L1 = 1;
%    L4 = 0.89;
%    L = 1.05;
   
   
   if (X < 0)
       theta1 = atan2d(Y, -X);
   else
       theta1 = atan2d(-Y, X);
   end
   
   
   b = ((X*cos(theta1) + Y*sin(theta1))^2 + (Z-L1)^2 - L^2 - L4^2)/(2*L*L4);
   
   theta3 = atan2d(-sqrt(1-b^2), b);
   if (theta3 > 90 || theta3 < -90)
       theta3 = atan2d(sqrt(1-b^2), b);
   end
   
   a = (X*cos(theta1)) + (Y*sin(theta1));
   c = (L4*cos(theta3)) + L;
   
   r = sqrt(a^2 + Z^2);
   theta2 = atan2d(c, -sqrt(r^2 - c^2)) - atan2d(a, Z);
   if (theta2 > 90 || theta2 < -90)
       theta2 = atan2d(c, sqrt(r^2 - c^2)) - atan2d(a, Z);
   end
end

