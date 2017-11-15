function [ ] = moveRobot( from, to )
    pause on
    time = 1;
    steps = 10;
    diff = to - from;
    increment = diff / steps;
    
    for i=1:steps
        pos = from + (increment .* i);
        [x, y, z, a] = ik(pos(1), pos(2), pos(3));
        setRobotPosition([x, y, z, a]);
%         pause(time/steps);
    end
end

