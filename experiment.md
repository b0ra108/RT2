### experiment: test bounce lighting with direct light source

The two lighting approaches conflict.

Shirley's approach assumes no explicit light sources and relies on
light bouncing between surfaces. This renderer already uses a direct
light source, and combining both methods produced incorrect results.

Branch kept for reference.