[TOP]
components : Motion@Motion
in : Command
out : Done
out : J1_Position J2_Position
out : Efficiency
Link : Command Command@Motion
Link : Done@Motion Done
Link : J1_Position@Motion J1_Position
Link : J2_Position@Motion J2_Position
Link : Efficiency@Motion Efficiency

[Motion]
timeout : 00:00:00:400