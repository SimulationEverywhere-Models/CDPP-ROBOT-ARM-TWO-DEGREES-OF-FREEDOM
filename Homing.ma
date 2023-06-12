[TOP]
components : Joint1@Joint1 Joint2@Joint2
out : Homed
in : H_Homing_Command
Link : H_Homing_Command Homing@Joint1
Link : Done@Joint1 Homing@Joint2
Link : Done@Joint2 Homed

[Joint1]
homingtime : 00:00:00:180

[Joint2]
homingtime : 00:00:00:180