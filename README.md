# ADCmulti

Continuously reading ADC value from SEVERAL pins using Free-Running mode and interrupt.

Library switch between analog pins in free-running mode and returns average of last measurements.

Each cycle doing 1024 measurement for each pin/port - it takes ~100 ms per port.

Litle bit stupid and not effective style of programming but easy to use with some limitations. :-)

See also https://github.com/Tomat7/ADCmultiplexer - works by the same princinples but more effective. (I thinks so :-)
