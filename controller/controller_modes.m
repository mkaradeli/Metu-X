classdef controller_modes < Simulink.IntEnumType
    enumeration
        DISABLE (0)
	    DUTY (1)
	    CURRENT (2)
	    SPEED (3)
	    POSITION (4)
	    PRESSURE (5)
	    FORCE (6)
    end
end
