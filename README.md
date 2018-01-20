# Computer_Graphics-Drawing_Torus

* Data Points for Torus

Generate torus by revolving a circle around the y-axis

-position p[36][18];

-18 curve points for the circle

-36 steps for sweeping around the y-axis

-Use GL_QUAD_STRIP



* Drawing Torus
 
 he program should be able to control the sweep angle using keyboard inputs.
 
-‘a’ key: increase the sweep angle by 10° around the y-axis

-‘s’ key: decrease the sweep angle by -10° around the y-axis

-‘j’ key: increase the sweep angle by 20° around the z-axis

-‘k’ key: increase the sweep angle by -20° around the z-axis

Two-sided constant shading

-Blue for outside

-Red for inside

How?

-n: normal vector at each polygon

-v: vector from the center of a polygon to COP
