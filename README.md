# ADCmulti

# readonly now use https://github.com/Tomat7/ADCmulti or https://github.com/Tomat7/ADCmultiplexer

Continuously reading ADC value from SEVERAL pins using **Free-Running mode** and interrupt. (ie working in background)  
The library switch between analog pins in free-running mode and returns **average** value of last measurement cycle.  
Each cycle doing 1024 measurement for each pin/port - it takes ~100 ms per port.  
So, it is necessary to use periodically `check()` method to update value and switching to next pin/port.  
See `/example` for details.

Little bit stupid and not effective style of programming but easy to use with some limitations. :-)  
See also https://github.com/Tomat7/ADCmultiplexer - works similar but returns [RMS](https://en.wikipedia.org/wiki/Root_mean_square "Google's RMS definition") and little bit effective. (I thinks so :-)
