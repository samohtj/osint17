function [X] = fk(motorAngles)

    L2 = 0.27;
    L3 = 0.02;

    theta1 = motorAngles(1);
    theta2 = 90 + motorAngles(2) - atan2d(L3,L2);
    theta3 = motorAngles(3) - 90 + atan2d(L3,L2);
    theta4 = 0 % it’s always zero since motor 4 is not connected to any link

    thetas = [theta1, theta2, theta3, theta4];

    X = T4_0(thetas);
	
end