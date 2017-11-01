function moveMotor(ID, GoalPos)


orthogonalArm = 1350; 
flatArm = 3000; 
bentArm = 1500; 

speed = 200; % change speed from here

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
end

        
end