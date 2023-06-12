[TOP]
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

