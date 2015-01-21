{application, heis,
 [{description, "Elevator control application"},
  {vsn, "1.0.0"},
  {modules, [elev_io, elev_fsm, client, client_network, 
  	     server, server_network, init_network, files,
  	     orderlist, main_supervisor, order_handler, heis]},
  {registered, [door, elev_fsm, client, server, server_network,
  	        client_network]},
  {applications, [stdlib, kernel]},
  {mod, {heis,[]}}
 ]}.