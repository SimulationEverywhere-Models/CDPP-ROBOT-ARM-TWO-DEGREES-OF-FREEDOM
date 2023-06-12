[TOP]
components : Decision@Decision
out : Motion_Command
out : Home_Command
in : UserCommand
in : Done_Motion
in : Done_Homing
Link : UserCommand UserCommand@Decision
Link : Done_Motion Done_Motion@Decision
Link : Done_Homing Done_Homing@Decision
Link : Motion_Command@Decision Motion_Command
Link : Home_Command@Decision Home_Command
