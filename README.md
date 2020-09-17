# gr-pthread
This general OOT block try to pass numbers 1,2,3,4,5 from one thread to the main thread using ZMQ sockets.

When I compile the block (cmake ../,make,sudo make install,sudo ldconfig), there isn't any problem. When I try to run the block in a flowgraph in GNU Radio companion, it appears the mistake: AttributeError: 'module' object has no attribute 'pthread'. 

I looked in the gr-zeromq block in the workarea-gnuradio and it seems that the problem is in one of the CMakeslist.txt. Probably because when generating the top_block.py the library:from gnuradio import zeromq is not included... I'm not sure if my suspect is correct and I don't know in which CMakelist.txt add it.

I really appreciate any help.

Thanks
