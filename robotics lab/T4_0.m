function [X] = T4_0(thetas)
   L1 = 0.103;
   L2 = 0.27;
   L3 = 0.02;
   L4 = 0.205;
   
   t1_0 = tmatrix_from_mdh(0, 0, L1, thetas(1));
   t2_1 = tmatrix_from_mdh(0, 90, 0, thetas(2));
   t3_2 = tmatrix_from_mdh(sqrt((L2^2) + (L3^2)), 0, 0, thetas(3));
   T3_0 = t1_0*t2_1*t3_2;
   
   r4_0 = T3_0*[L4;0;0;1];
    
   x = r4_0(1);
   y = r4_0(2);
   z = r4_0(3);
   X=[x;y;z;1];
end