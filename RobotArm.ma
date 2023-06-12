[TOP]
components : Homing MotionController
out : RobotJ1 RobotJ2 RobotEfficiency
in : User_Input
Link : User_Input Input_Command@MotionController
Link : OutJ1_Pos@MotionController RobotJ1
Link : OutJ2_Pos@MotionController RobotJ2
Link : OutEfficiency@MotionController RobotEfficiency
Link : M_Homing_Command@MotionController H_Homing_Command@Homing
Link : Homed@Homing Done@MotionController

[Homing]
components : Joint1@Joint1 Joint2@Joint2
out : Homed
in : H_Homing_Command
Link : H_Homing_Command Homing@Joint1
Link : Done@Joint1 Homing@Joint2
Link : Done@Joint2 Homed

[MotionController]
components : Decision@Decision Motion@Motion
in : Input_Command Done
out : M_Homing_Command OutJ1_Pos OutJ2_Pos OutEfficiency
Link : Input_Command UserCommand@Decision
Link : Done Done_Homing@Decision
Link : Home_Command@Decision M_Homing_Command
Link : J1_Position@Motion OutJ1_Pos
Link : J2_Position@Motion OutJ2_Pos
Link : Efficiency@Motion OutEfficiency
Link : Motion_Command@Decision Command@Motion
Link : Done@Motion Done_Motion@Decision


[Decision]


[Motion]
timeout : 00:00:00:400

[Joint1]
homingtime : 00:00:00:180

[Joint2]
homingtime : 00:00:00:180
