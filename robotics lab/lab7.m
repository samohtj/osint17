function [] = lab7()
    p1 = [0.40, 0.10, 0.15];
    p2 = [0.40, 0.10, 0.30];


    pause on
    open();
    [t1, t2, t3, t4] = ik(p1(1), p1(2), p1(3));
    setRobotPosition([t1, t2, t3, t4]);
%     pause(1);
    
    close();
%     pause(2);
    
%     [t1, t2, t3, t4] = ik(0.40, 0, 0.43);
%     setRobotPosition([t1, t2, t3, t4]);
    moveRobot(p1 ,p2);
%     pause(2);
    
%     [t1, t2, t3, t4] = ik(0.40, 0,0.18);
%     setRobotPosition([t1, t2, t3, t4]);
    moveRobot(p2, p1);
%     pause(2);
    
    open();
    



end