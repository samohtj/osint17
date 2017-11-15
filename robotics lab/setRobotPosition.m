function [] = setRobotPosition(motorAngles)
    L2 = 0.27;
    L3 = 0.02;

    theta1 = motorAngles(1);
    theta2 = motorAngles(2) - 90 + atan2d(L3,L2);
    theta3 = motorAngles(3) + 90 - atan2d(L3,L2);
    theta4 = motorAngles(4);
    writePos(4, theta4);
    writePos(1, theta1);
    writePos(2, theta2);
    writePos(3, theta3);
    

end