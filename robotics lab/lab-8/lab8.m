function [ ] = lab8(center, radius )
    
    
    height = 0.16;
    a = [center(1), center(2) - radius, height];
    b = [center(1) - (radius*sind(45)), center(2) - (radius*sind(45)), height];
    c = [center(1) - radius, center(2), height];
    d = [center(1) - (radius*sind(45)), center(2) + (radius*sind(45)), height];
    e = [center(1), center(2) + radius, height];
    f = [center(1) + (radius*sind(45)), center(2) + (radius*sind(45)), height];
    g = [center(1) + radius, center(2), height];
    h = [center(1) + (radius*sind(45)), center(2) - (radius*sind(45)), height];


    pause on
    %open();
    [t1, t2, t3, t4] = ik(a(1), a(2), a(3));
    setRobotPosition([t1, t2, t3, t4]);
    
    % Grab the marker
    %open();
    pause(3);
    close();
    
    moveRobot(a ,b);
    moveRobot(b ,c);
    moveRobot(c ,d);
    moveRobot(d ,e);
    moveRobot(e ,f);
    moveRobot(f ,g);
    moveRobot(g ,h);
    moveRobot(h ,a);
end

% Comput forward kinematics
function [X] = fk(motorAngles)
    L2 = 0.27;
    L3 = 0.038;

    theta1 = motorAngles(1);
    theta2 = motorAngles(2) - 90 + atan2d(L3,L2);
    theta3 = motorAngles(3) + 90 - atan2d(L3,L2);
    theta4 = motorAngles(4);
    thetas = [theta1, theta2, theta3, theta4];

    X = T4_0(thetas);
end

% Compute inverse kinematics, including gripper
function [theta1, theta2, theta3, theta4 ] = ik( Xg, Yg, Zg )

    L1 = 0.103;
    L2 = 0.27;
    L3 = 0.038;
    L4 = 0.205;
    L = sqrt(L3^2 + L2^2);
    L5 = 0.095;
    L6 = 0.012;

    theta1 = atan2d(Yg,Xg);
    dg = sqrt(Xg^2 + Yg^2);
    dw = dg - L6;

    X = dw*cosd(theta1);
    Y = dw*sind(theta1);
    Z = Zg + L5; % Gripper always down

    b = ((X*cosd(theta1) + Y*sind(theta1))^2 + (Z-L1)^2 - L4^2 - L^2)/(2.0*L*L4);
    if (b > 1)
        b = 1;
    elseif (b < -1)
        b = -1;
    end
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

    theta4 = -(theta2 + theta3) - 90;
end

% Generate a transformation matrix from the 4 cs to the 1 cs
function [X] = T4_0(thetas)
    L1 = 0.103;
    L2 = 0.27;
    L3 = 0.038;
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

% Generate a transformation matrix from an mdh table row
function [T] = tmatrix_from_mdh(a, alpha, d, theta)
    T = [cosd(theta), -sind(theta), 0, a;
        sind(theta)*cosd(alpha), cosd(theta)*cosd(alpha), -sind(alpha), -1*d*sind(alpha);
        sind(theta)*sind(alpha), cosd(theta)*sind(alpha), cosd(alpha), d*cosd(alpha);
        0, 0, 0, 1];
end

% Write a position to a motor, in degrees
function writePos(n,deg)
    DEFAULT_PORTNUM = 5;
    DEFAULT_BAUDNUM = 1;

    pause on

    if libisloaded('dynamixel') == false
        loadlibrary('dynamixel','dynamixel.h');
    end
    res = calllib('dynamixel','dxl_initialize',DEFAULT_PORTNUM,DEFAULT_BAUDNUM);
    if res == 1
        goalPos = 4096*deg/360;
        goalPos = mod(goalPos + 2048,4096);
        current_speed = calllib('dynamixel', 'dxl_read_word', n, 32);
        %     calllib('dynamixel', 'dxl_write_word', 2, 32, 1);
        moveMotor(n,goalPos);
    else
        disp('Failed to connect.')
    end
end

% Set the given kinematic angles to the robot's motors
function [] = setRobotPosition(motorAngles)
    L2 = 0.27;
    L3 = 0.038;

    theta1 = motorAngles(1);
    theta2 = motorAngles(2) - 90 + atan2d(L3,L2);
    theta3 = motorAngles(3) + 90 - atan2d(L3,L2);
    theta4 = motorAngles(4);
    writePos(4, theta4);
    writePos(1, theta1);
    writePos(2, theta2);
    writePos(3, theta3);
end

% Move the robot from one point in space to another
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

% Move the given motor to the desired angle. Will stop motors from making
% impossible moves.
function moveMotor(ID, GoalPos)
    orthogonalArm = 1350;
    flatArm = 3000;
    bentArm = 1500;

    speed = 100; % change speed from here

    Motor3Pos = calllib('dynamixel','dxl_read_word',3,36);
    Motor2Pos = calllib('dynamixel','dxl_read_word',2,36);

    calllib('dynamixel','dxl_write_word',ID,32,speed);

    if (ID==1)
        if(Motor2Pos < orthogonalArm && Motor3Pos<bentArm )
            disp('Cannnot turn motor 1 to this goal position because the arm is bent on the table');
        else
            calllib('dynamixel', 'dxl_write_word',ID,30,GoalPos);
        end

    elseif (ID==2)
        if (GoalPos<=orthogonalArm)
            if(Motor3Pos <= flatArm)
                disp('Cannot turn motor 2 to this goal position. Motor 3 needs to be turned first')
            else
                calllib('dynamixel', 'dxl_write_word',ID,30,GoalPos);
            end
        else
            calllib('dynamixel', 'dxl_write_word',ID,30,GoalPos);
        end

    elseif(ID==3)
        if(GoalPos <=flatArm)
            if(Motor2Pos <=orthogonalArm)
                disp('Cannot turn motor 3 to this goal position. Motor 2 needs to be turned first');
            else
                calllib('dynamixel', 'dxl_write_word',ID,30,GoalPos);
            end
        else
            calllib('dynamixel', 'dxl_write_word',ID,30,GoalPos);
        end

    elseif(ID==4 || ID == 5)
        calllib('dynamixel', 'dxl_write_word', ID, 30, GoalPos);
    end
end

function [ ] = open( )
    calllib('dynamixel', 'dxl_write_word', 5, 30, 512);
end

function [ ] = close( )
   calllib('dynamixel', 'dxl_write_word', 5, 30, 860);
end
